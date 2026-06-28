#!/bin/bash
cd /mnt/g/GitHub/26-Arch
for t in lab1 lab2 lab3 lab4 lab6; do
  echo "=== $t ==="
  timeout 60 make test-$t 2>&1 | grep -E "instrCnt|Pass|OK|panic|Terminated|error" | head -3
done
echo "=== lab5 ==="
timeout 60 make test-lab5 2>&1 | grep -E "instrCnt|Pass|OK|panic|Terminated|error|invalid" | head -5
