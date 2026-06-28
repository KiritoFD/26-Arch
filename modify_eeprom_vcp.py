"""
FT2232H EEPROM raw word/bit CLI 修改工具
用法：
  python modify_eeprom_vcp.py                       # 显示当前状态 + 候选 bit 分析
  python modify_eeprom_vcp.py --backup              # 仅备份当前 EEPROM
  python modify_eeprom_vcp.py --restore FILE        # 从备份文件恢复
  python modify_eeprom_vcp.py --set WORD_OFFSET VALUE  # 设置某个 word (hex)
  python modify_eeprom_vcp.py --flip WORD_OFFSET BIT   # 翻转某个 bit
  python modify_eeprom_vcp.py --try-a-vcp           # 试错: 改 word 4 bit 7 = 0 (假设 AIsVCP=1=D2XX, 0=VCP)
  python modify_eeprom_vcp.py --try-b-vcp           # 试错: 改 word 5 bit 3 = 0
  python modify_eeprom_vcp.py --try-both-vcp        # 试错: word 4 bit 7 = 0 + word 5 bit 2/3 = 0
  python modify_eeprom_vcp.py --restore-last        # 从最近一次备份恢复

每次修改自动：
  1. 备份当前 256 words 到 timestamped .bin 文件
  2. 修改目标 word（同时同步镜像 word 128..254）
  3. 重算 word 255 校验和 (XOR of word 0..254)
  4. 用 FT_WriteEE 写入
  5. dump 验证

注意：
  - word 0..126 的镜像在 word 128..254（dual image）
  - word 127 和 word 255 都是校验和
  - word 255 = word 0..254 XOR
"""
import sys
import os
import time
import argparse
import ftd2xx
from ftd2xx._ftd2xx import FT_ReadEE, FT_WriteEE, DWORD, WORD
import ctypes


BACKUP_DIR = 'eeprom_backup'


def open_dev():
    devices = ftd2xx.listDevices()
    print(f"[INFO] Found {len(devices) if devices else 0} FTDI device(s)")
    if not devices:
        return None
    for idx in range(len(devices)):
        try:
            d = ftd2xx.open(idx)
            print(f"[INFO] Opened channel index {idx}")
            return d
        except ftd2xx.DeviceError:
            continue
    return None


def dump_all(handle):
    words = []
    for i in range(256):
        val = WORD(0)
        st = FT_ReadEE(handle, DWORD(i), ctypes.byref(val))
        if st != 0:
            raise RuntimeError(f"FT_ReadEE({i})={st}")
        words.append(val.value)
    return words


def calc_checksum(words_0_254):
    c = 0
    for w in words_0_254:
        c ^= w
    return c & 0xFFFF


def backup_to_file(words, tag='backup'):
    os.makedirs(BACKUP_DIR, exist_ok=True)
    ts = time.strftime('%Y%m%d_%H%M%S')
    path = os.path.join(BACKUP_DIR, f'eeprom_{tag}_{ts}.bin')
    with open(path, 'wb') as f:
        for w in words:
            f.write(bytes([w & 0xFF, (w >> 8) & 0xFF]))
    print(f"[OK] Backup saved: {path}")
    return path


def write_full_image(handle, words):
    """写入全部 256 words"""
    for i, v in enumerate(words):
        st = FT_WriteEE(handle, DWORD(i), WORD(v))
        if st != 0:
            raise RuntimeError(f"FT_WriteEE({i})={st}")


def modify_word(words, idx, new_value):
    """修改 word idx，同步镜像 (128..254)，重算 word 255 校验和"""
    new_value &= 0xFFFF
    words[idx] = new_value
    # 同步镜像：word 0..126 的镜像在 word 128..254
    if idx < 128:
        mirror = idx + 128
        if mirror < 255:
            words[mirror] = new_value
    # 重算校验和
    cs = calc_checksum(words[:255])
    words[255] = cs
    return words


def flip_bit(words, idx, bit):
    cur = words[idx]
    new_val = cur ^ (1 << bit)
    return modify_word(words, idx, new_val), cur, new_val


def show_state(words):
    print("\n" + "=" * 70)
    print("当前 EEPROM 关键状态")
    print("=" * 70)
    print(f"Word 0 (header)     : 0x{words[0]:04x}")
    print(f"Word 1 (VID)        : 0x{words[1]:04x}")
    print(f"Word 2 (PID)        : 0x{words[2]:04x}")
    print(f"Word 3 (BCD Device) : 0x{words[3]:04x}")
    print(f"Word 4 (USB Config) : 0x{words[4]:04x}")
    print(f"  bit 5 (RemoteWakeup)  = {(words[4] >> 5) & 1}")
    print(f"  bit 6 (SelfPowered)   = {(words[4] >> 6) & 1}")
    print(f"  bit 7 (?? 未知)       = {(words[4] >> 7) & 1}")
    print(f"  bits 8-15 (MaxPower)  = 0x{(words[4] >> 8) & 0xff:02x} = {(words[4] >> 8) & 0xff} -> {((words[4] >> 8) & 0xff) * 2}mA")
    print(f"Word 5              : 0x{words[5]:04x}")
    print(f"  bit 2 (?? 未知)       = {(words[5] >> 2) & 1}")
    print(f"  bit 3 (?? 未知)       = {(words[5] >> 3) & 1}")
    print(f"Word 6              : 0x{words[6]:04x}")
    print(f"Word 7              : 0x{words[7]:04x}")

    # 校验和
    cs_calc = calc_checksum(words[:255])
    print(f"\nChecksum: stored=0x{words[255]:04x} calc=0x{cs_calc:04x} {'OK' if cs_calc == words[255] else 'MISMATCH'}")

    # 候选 VCP bit 分析
    print("\n" + "-" * 70)
    print("VCP 控制 bit 候选分析（基于实验）")
    print("-" * 70)
    print("已知：eeProgram 对 AIsVCP/BIsVCP 字段无效，必须改 raw bit")
    print(f"当前 word 4 = 0x{words[4]:04x}: bit 7 = {(words[4] >> 7) & 1}  <- 候选 AIsVCP (1=D2XX, 0=VCP)")
    print(f"当前 word 5 = 0x{words[5]:04x}: bit 2 = {(words[5] >> 2) & 1}, bit 3 = {(words[5] >> 3) & 1}  <- 候选 BIsVCP")


def cmd_show(dev, args):
    words = dump_all(dev.handle)
    show_state(words)
    backup_to_file(words, tag='show')


def cmd_backup(dev, args):
    words = dump_all(dev.handle)
    show_state(words)
    backup_to_file(words, tag='manual')


def cmd_restore(dev, args):
    path = args.restore
    if not os.path.exists(path):
        print(f"[ERROR] File not found: {path}")
        return 1
    with open(path, 'rb') as f:
        data = f.read()
    if len(data) != 512:
        print(f"[ERROR] Expected 512 bytes, got {len(data)}")
        return 1
    words = []
    for i in range(0, 512, 2):
        words.append(data[i] | (data[i + 1] << 8))
    print(f"[INFO] Restoring from {path}")
    print(f"[INFO] word 4 = 0x{words[4]:04x}, checksum = 0x{words[255]:04x}")
    # 先备份当前
    cur = dump_all(dev.handle)
    backup_to_file(cur, tag='pre_restore')
    # 写入
    write_full_image(dev.handle, words)
    # 验证
    after = dump_all(dev.handle)
    if after == words:
        print(f"[OK] Restore successful")
    else:
        diff = sum(1 for a, b in zip(words, after) if a != b)
        print(f"[ERROR] Restore failed, {diff} words mismatch")


def cmd_set(dev, args):
    idx = int(args.set[0], 0)
    val = int(args.set[1], 0)  # 支持 0x.. 和十进制
    print(f"[INFO] Set word {idx} = 0x{val:04x}")
    cur = dump_all(dev.handle)
    backup_to_file(cur, tag='pre_set')
    modify_word(cur, idx, val)
    print(f"[INFO] After modify: word {idx} = 0x{cur[idx]:04x}, checksum = 0x{cur[255]:04x}")
    write_full_image(dev.handle, cur)
    after = dump_all(dev.handle)
    if after == cur:
        print(f"[OK] Set successful")
    else:
        print(f"[ERROR] Verify failed")


def cmd_flip(dev, args):
    idx = int(args.flip[0], 0)
    bit = int(args.flip[1], 0)
    print(f"[INFO] Flip word {idx} bit {bit}")
    cur = dump_all(dev.handle)
    backup_to_file(cur, tag='pre_flip')
    before_val = cur[idx]
    cur, old_val, new_val = flip_bit(cur, idx, bit)
    print(f"[INFO] word {idx}: 0x{before_val:04x} -> 0x{cur[idx]:04x}")
    print(f"[INFO] checksum: 0x{cur[255]:04x}")
    write_full_image(dev.handle, cur)
    after = dump_all(dev.handle)
    if after == cur:
        print(f"[OK] Flip successful. Now拔插 USB 验证设备管理器有无新 COM 口出现")
    else:
        print(f"[ERROR] Verify failed")


def cmd_try_a_vcp(dev, args):
    """试错: 改 word 4 bit 7 = 0 (假设 AIsVCP 反相: 1=D2XX, 0=VCP)"""
    print("[INFO] Try: A=VCP — flip word 4 bit 7 (0x80 -> 0x00)")
    cur = dump_all(dev.handle)
    backup_to_file(cur, tag='pre_try_a_vcp')
    if (cur[4] & 0x80) == 0:
        print(f"[WARN] word 4 bit 7 already 0, no flip needed")
        return
    print(f"[INFO] word 4: 0x{cur[4]:04x} -> 0x{cur[4] & ~0x80:04x}")
    modify_word(cur, 4, cur[4] & ~0x80)
    write_full_image(dev.handle, cur)
    after = dump_all(dev.handle)
    if after == cur:
        print(f"[OK] word 4 bit 7 flipped to 0")
        print(f"[INFO] 拔插 USB 后查看设备管理器 — 看 Port A 是否出现 COM 口")
        print(f"[INFO] 若 Port A 出现 COM: 说明 bit 7 = AIsVCP (反相), A=VCP 成功")
        print(f"[INFO] 若 Port B 出现 COM: 说明 bit 7 = BIsVCP (反相), 需改其他 bit")
        print(f"[INFO] 若无变化: 恢复 + 试 word 5 bit 2/3")
        print(f"[INFO] 恢复命令: python modify_eeprom_vcp.py --restore-last")


def cmd_try_b_vcp(dev, args):
    """试错: 改 word 5 bit 3 = 0 (假设 BIsVCP 反相)"""
    print("[INFO] Try: B=VCP — flip word 5 bit 3")
    cur = dump_all(dev.handle)
    backup_to_file(cur, tag='pre_try_b_vcp')
    if (cur[5] & 0x08) == 0:
        print(f"[WARN] word 5 bit 3 already 0")
        return
    print(f"[INFO] word 5: 0x{cur[5]:04x} -> 0x{cur[5] & ~0x08:04x}")
    modify_word(cur, 5, cur[5] & ~0x08)
    write_full_image(dev.handle, cur)
    after = dump_all(dev.handle)
    if after == cur:
        print(f"[OK] word 5 bit 3 flipped to 0")
        print(f"[INFO] 拔插 USB 查看 Port B 是否出现 COM 口")


def cmd_try_both_vcp(dev, args):
    """同时改 word 4 bit 7 + word 5 bit 2/3 为 0"""
    print("[INFO] Try: A+B both VCP — flip word 4 bit 7 + word 5 bit 2/3")
    cur = dump_all(dev.handle)
    backup_to_file(cur, tag='pre_try_both_vcp')
    new_w4 = cur[4] & ~0x80
    new_w5 = cur[5] & ~0x0c
    print(f"[INFO] word 4: 0x{cur[4]:04x} -> 0x{new_w4:04x}")
    print(f"[INFO] word 5: 0x{cur[5]:04x} -> 0x{new_w5:04x}")
    modify_word(cur, 4, new_w4)
    modify_word(cur, 5, new_w5)
    write_full_image(dev.handle, cur)
    after = dump_all(dev.handle)
    if after == cur:
        print(f"[OK] Flipped word 4 bit 7 + word 5 bit 2/3 to 0")
        print(f"[INFO] 拔插 USB 查看是否出现 2 个 COM 口")


def cmd_restore_last(dev, args):
    """从最近一次备份恢复"""
    backups = sorted([f for f in os.listdir(BACKUP_DIR) if f.endswith('.bin')])
    if not backups:
        print(f"[ERROR] No backup found in {BACKUP_DIR}/")
        return 1
    last = backups[-1]
    path = os.path.join(BACKUP_DIR, last)
    print(f"[INFO] Restoring from last backup: {path}")
    with open(path, 'rb') as f:
        data = f.read()
    words = []
    for i in range(0, len(data), 2):
        words.append(data[i] | (data[i + 1] << 8))
    write_full_image(dev.handle, words)
    after = dump_all(dev.handle)
    if after == words:
        print(f"[OK] Restore from {last} successful")
    else:
        diff = sum(1 for a, b in zip(words, after) if a != b)
        print(f"[ERROR] Restore mismatch, {diff} words differ")


def main():
    p = argparse.ArgumentParser(description='FT2232H EEPROM raw bit CLI')
    p.add_argument('--backup', action='store_true', help='仅备份当前 EEPROM')
    p.add_argument('--restore', metavar='FILE', help='从备份文件恢复')
    p.add_argument('--restore-last', action='store_true', help='从最近备份恢复')
    p.add_argument('--set', nargs=2, metavar=('WORD', 'VALUE'), help='设置 word (WORD,VALUE 都支持 0x..)')
    p.add_argument('--flip', nargs=2, metavar=('WORD', 'BIT'), type=int, help='翻转 word 的 bit')
    p.add_argument('--try-a-vcp', action='store_true', help='试错: 改 word 4 bit 7 = 0 (假设 AIsVCP)')
    p.add_argument('--try-b-vcp', action='store_true', help='试错: 改 word 5 bit 3 = 0 (假设 BIsVCP)')
    p.add_argument('--try-both-vcp', action='store_true', help='试错: 同时改 word 4 bit 7 + word 5 bit 2/3')
    args = p.parse_args()

    dev = open_dev()
    if dev is None:
        print("[ERROR] Cannot open any FTDI channel")
        return 1

    try:
        if args.backup:
            cmd_backup(dev, args)
        elif args.restore:
            return cmd_restore(dev, args)
        elif args.restore_last:
            return cmd_restore_last(dev, args)
        elif args.set:
            cmd_set(dev, args)
        elif args.flip:
            cmd_flip(dev, args)
        elif args.try_a_vcp:
            cmd_try_a_vcp(dev, args)
        elif args.try_b_vcp:
            cmd_try_b_vcp(dev, args)
        elif args.try_both_vcp:
            cmd_try_both_vcp(dev, args)
        else:
            cmd_show(dev, args)
    finally:
        dev.close()

    return 0


if __name__ == '__main__':
    sys.exit(main())
