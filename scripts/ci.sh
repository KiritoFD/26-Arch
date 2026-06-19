#!/bin/bash
# ci.sh - Lab+ CI script
# Runs all lab tests and reports pass/fail status
set -e

echo "=== Lab+ CI Script ==="
echo "Date: $(date)"
echo ""

# Build first
echo "--- Building emu ---"
rm -rf build
make sim -j4 2>&1 | tail -5
echo ""

# Run each test
PASS_COUNT=0
FAIL_COUNT=0

run_test() {
    local name=$1
    local cmd=$2
    local pattern=$3
    
    echo -n "Test $name: "
    if eval "$cmd" 2>&1 | grep -q "$pattern"; then
        echo "PASS"
        PASS_COUNT=$((PASS_COUNT + 1))
    else
        echo "FAIL"
        FAIL_COUNT=$((FAIL_COUNT + 1))
    fi
}

# Basic lab tests
run_test "lab1" "timeout 60 ./build/emu --diff ./ready-to-run/riscv64-nemu-interpreter-so -i ./ready-to-run/lab1/lab1-test.bin" "HIT GOOD"
run_test "lab2" "timeout 60 ./build/emu --diff ./ready-to-run/riscv64-nemu-interpreter-so -i ./ready-to-run/lab2/lab2-test.bin" "HIT GOOD"
run_test "lab3" "timeout 120 ./build/emu --diff ./ready-to-run/riscv64-nemu-interpreter-so -i ./ready-to-run/lab3/lab3-test.bin" "HIT GOOD"
run_test "lab4" "timeout 60 ./build/emu --diff ./ready-to-run/riscv64-nemu-interpreter-so -i ./ready-to-run/lab4/lab4-test.bin" "HIT GOOD"

# lab+ tests
run_test "labplus-3" "timeout 60 ./build/emu --diff ./ready-to-run/riscv64-nemu-interpreter-so -i ./ready-to-run/lab+/3/atomicity.bin" "HIT GOOD"

echo ""
echo "=== Results ==="
echo "Pass: $PASS_COUNT"
echo "Fail: $FAIL_COUNT"
echo "Total: $((PASS_COUNT + FAIL_COUNT))"

if [ $FAIL_COUNT -eq 0 ]; then
    echo "ALL TESTS PASSED"
    exit 0
else
    echo "SOME TESTS FAILED"
    exit 1
fi
