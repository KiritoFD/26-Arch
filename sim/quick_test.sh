#!/bin/bash
cd /mnt/g/GitHub/26-Arch
REF=./ready-to-run/riscv64-nemu-interpreter-so
NEMU=./ready-to-run/riscv64-nemu-interpreter-so
declare -A BINS=(
  [test-lab1-extra]=./ready-to-run/lab1/lab1-extra-test.bin
  [test-lab2]=./ready-to-run/lab2/lab2-test.bin
  [test-lab3]=./ready-to-run/lab3/lab3-test.bin
  [test-lab3-extra]=./ready-to-run/lab3/lab3-extra-test.bin
  [test-lab4]=./ready-to-run/lab4/lab4-test.bin
  [test-lab5]=./ready-to-run/lab5/kernel.bin
  [test-lab5-extra]=./ready-to-run/lab5_yzy/kernel_bonus.bin
  [test-labplus-2]=./ready-to-run/lab+/2/microbench-riscv64-nutshell.bin
  [test-labplus-3]=./ready-to-run/lab+/3/atomicity.bin
)
for t in test-lab1-extra test-lab2 test-lab3 test-lab3-extra test-lab4 test-lab5 test-lab5-extra test-labplus-2 test-labplus-3; do
  echo "=== $t ==="
  bin=${BINS[$t]}
  if [[ "$t" == "test-labplus-3" ]]; then
    timeout 90 ./build/emu --diff $NEMU -i "$bin" 2>&1 | grep -E "GOOD TRAP|BAD TRAP|CBus request|different|TIMEOUT|HIT" | head -5
  else
    timeout 90 ./build/emu --diff $REF -i "$bin" 2>&1 | grep -E "GOOD TRAP|BAD TRAP|CBus request|different|TIMEOUT|HIT" | head -5
  fi
  echo ""
done
