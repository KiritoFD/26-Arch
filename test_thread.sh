#!/bin/bash
cd /mnt/g/GitHub/26-Arch
export NOOP_HOME=/mnt/g/GitHub/26-Arch
export NEMU_HOME=/mnt/g/GitHub/26-Arch/ready-to-run

TMPDIR=$(mktemp -d)
PIPE=$TMPDIR/uart_pipe
mkfifo "$PIPE"

# Single background process: writes commands with delays, then keeps pipe open
(
  sleep 8
  printf 'echo thread_test\n'
  sleep 5
  printf 'ls\n'
  sleep 15
) > "$PIPE" &

SDCARD_IMAGE=third_party/xv6-riscv/fs.img TEST=sys timeout 35 ./build/emu --no-diff -i third_party/xv6-riscv/kernel/kernel.bin < "$PIPE" 2>&1 | tail -30

rm -rf "$TMPDIR"
