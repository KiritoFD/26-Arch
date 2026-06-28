"""
对比当前 EEPROM 和最早的全量备份 eeprom_full.bin，找出差异。
"""
import sys
import ftd2xx
from ftd2xx._ftd2xx import FT_ReadEE, DWORD, WORD
import ctypes


def open_dev():
    devices = ftd2xx.listDevices()
    if not devices:
        return None
    for idx in range(len(devices)):
        try:
            return ftd2xx.open(idx)
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


def read_bin_file(path):
    with open(path, 'rb') as f:
        data = f.read()
    words = []
    for i in range(0, len(data), 2):
        words.append(data[i] | (data[i + 1] << 8))
    return words


def main():
    # 读取多个备份对比
    backup_files = [
        'eeprom_full.bin',
        'eeprom_dump_current.bin',
        'eeprom_backup_before_restore.bin',
        'eeprom_backup_before_a_b_swap.bin',
        'eeprom_backup/eeprom_pre_try_a_vcp_20260628_083455.bin',
        'eeprom_backup/eeprom_show_20260628_082844.bin',
        'eeprom_backup/eeprom_show_20260628_084814.bin',
    ]

    print("=" * 80)
    print("对比所有备份文件")
    print("=" * 80)

    backups = {}
    for path in backup_files:
        try:
            words = read_bin_file(path)
            if len(words) == 256:
                backups[path] = words
                print(f"[OK] {path}: 256 words, word 4 = 0x{words[4]:04x}, checksum = 0x{words[255]:04x}")
            else:
                print(f"[WARN] {path}: {len(words)} words (expected 256)")
        except FileNotFoundError:
            print(f"[MISS] {path}: not found")
        except Exception as e:
            print(f"[ERR] {path}: {e}")

    # 读当前 EEPROM
    print("\n[INFO] Reading current EEPROM...")
    dev = open_dev()
    if dev is None:
        print("[ERROR] Cannot open device")
        return 1

    cur = dump_all(dev.handle)
    print(f"[INFO] Current: word 4 = 0x{cur[4]:04x}, checksum = 0x{cur[255]:04x}")
    dev.close()

    # 对比当前和每个备份
    print("\n" + "=" * 80)
    print("当前 EEPROM vs 备份 差异")
    print("=" * 80)
    for path, words in backups.items():
        diff_count = sum(1 for a, b in zip(cur, words) if a != b)
        if diff_count == 0:
            print(f"[MATCH] {path}: 完全一致")
        else:
            print(f"[DIFF]  {path}: {diff_count} words differ")
            for i, (a, b) in enumerate(zip(cur, words)):
                if a != b:
                    print(f"  word {i:3d}: current=0x{a:04x}  backup=0x{b:04x}  diff=0x{a ^ b:04x}")

    return 0


if __name__ == '__main__':
    sys.exit(main())
