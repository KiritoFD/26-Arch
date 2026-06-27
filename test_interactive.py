import subprocess
import os
import re
import time

env = os.environ.copy()
env['NOOP_HOME'] = '/mnt/g/GitHub/26-Arch'
env['NEMU_HOME'] = '/mnt/g/GitHub/26-Arch/ready-to-run'
env['SDCARD_IMAGE'] = 'third_party/xv6-riscv/fs.img'
env['TEST'] = 'sys'

cmd = ['./build/emu', '--no-diff', '-i', 'third_party/xv6-riscv/kernel/kernel.bin']

proc = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=False, env=env)
# wait for shell prompt
print('waiting for shell prompt...')
time.sleep(4)
proc.stdin.write(b'ls\n')
proc.stdin.flush()
print('sent ls')
time.sleep(3)
proc.stdin.write(b'echo hello\n')
proc.stdin.flush()
print('sent echo hello')
time.sleep(3)
proc.kill()
out, _ = proc.communicate()

text = out.decode('utf-8', errors='replace')
chars = re.findall(r"UART_TX: 0x[0-9a-f]+ '(.)'", text)
result = ''.join(chars)
print('=== UART output ===')
print(result)
print('---TOTAL:', len(result))
