#!/bin/bash
# Run all lab tests and report pass/fail
cd /mnt/g/GitHub/26-Arch

TESTS="test-lab1 test-lab1-extra test-lab2 test-lab3 test-lab3-extra test-lab4 test-lab5 test-lab5-extra test-labplus-2 test-labplus-3 test-labplus-4"

for t in $TESTS; do
    echo "=========================================="
    echo "=== Running: $t ==="
    echo "=========================================="
    OUTPUT=$(timeout 120 make $t 2>&1)
    echo "$OUTPUT" | tail -15
    echo ""
done
