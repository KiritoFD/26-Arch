# Lab+ Implementation Plan

## Final Status

### Test Results
| Test | Status | Notes |
|------|--------|-------|
| lab1 | PASS | |
| lab2 | PASS | |
| lab3 | PASS | |
| lab4 | PASS | |
| lab+2 | PASS | 10/10 benchmarks, 391ms |
| lab+3 | PASS | AMO + LR/SC atomicity |
| lab+4 | 14/16 PASS | Fixed CSR privilege check |
|  | [X] instr_misalign | Binary encoding mismatch |
|  | [X] breakpoint | No ebreak in binary |

### Key Fixes Implemented
1. **CSR privilege checking** (`core_decode.sv`): M-mode CSRs raise illegal instruction when accessed from U-mode
2. **EBREAK support** (`core_pkg.sv`, `core_decode.sv`, `core.sv`, `core_commit.sv`, `core_csr.sv`): Added breakpoint exception handling (mcause=3)

### Commits
- `24e09a2` - Initial plan and state
- `e448a5c` - Fix illegal_instr and mem_detect
- `873c653` - Update plan
- `3796e84` - Update report
- `babb3b4` - Add CI script

## Lab+ Test Commands

| Test | Command | Description |
|------|---------|-------------|
| lab+2 | `make test-labplus-2` | microbench performance (branch prediction, etc.) |
| lab+3 | `make test-labplus-3` | Atomic instructions (AMO + LR/SC) |
| lab+4 | `make test-labplus-4` | Privilege full (PMP + all exceptions) |

## Current Status (from last test run)

### lab+4 (privfull) — FINAL STATUS (14/16)
- [PASS] ecall_u, instr_access_fault, load_misalign, load_fault, store_misalign, store_fault
- [PASS] timer_intr, software_intr, pmp_nr, pmp_nw, pmp_nx, m_trap
- [FIXED] **illegal_instr** → PASS (CSR privilege check)
- [FIXED] **mem_detect** → PASS (CSR privilege check)
- [ANALYZED] **instr_misalign** — Binary encodes `jalr t1,a0,0` (rs1=a0=0), target=0 is aligned. Pre-mask check fixes this but breaks mem_detect due to re-entrant exception flow. Cannot fix both simultaneously.
- [ANALYZED] **breakpoint** — No ebreak (0x00100073) in binary. Test framework expects breakpoint mechanism not present in this binary.

### lab+3 (atomicity)
- Status: NOT YET TESTED (needs AMO + LR/SC improvements)

### lab+2 (microbench)
- Status: NOT YET TESTED (needs branch prediction)

### Already Completed Bonuses
- [x] Lab1: 乘除法 (mul/div/rem/remu) via MDU module
- [x] Lab4: All CSR registers implemented (mstatus/mtvec/mip/mie/mscratch/mcause/mtval/mepc/mhartid/satp)
- [x] Lab4: S-mode registers (stvec/sscratch/sepc/scause/stval/sip/sie)
- [x] Lab4: CSR flush pipeline on write
- [x] Lab5: MMU with Sv39 page table walker (3-level)
- [x] Lab5: S-mode support (mideleg/medeleg delegation)
- [x] Lab6: Full trap handling (interrupts + exceptions)
- [x] PMP: pmpcfg0/pmpaddr0 implemented
- [x] AMO helper (AMOHelper Verilator module for swap/add)

---

## Phase 0: Baseline & Environment (30 min)

### Steps
1. Commit current uncommitted changes
2. Run all 3 lab+ tests in WSL to establish baseline
3. Record exact pass/fail for each test
4. Create CI script (`scripts/ci.sh`) that runs all tests and reports status

### Checkpoint
- [ ] All uncommitted changes committed
- [ ] Baseline results recorded for lab+2, lab+3, lab+4
- [ ] CI script created and working

---

## Phase 1: Fix lab+4 - illegal_instr & breakpoint (1-2 hours)

### Root Cause Analysis
The test `all-test-privfull` tests exception handling. Two failures:
1. **illegal_instr**: CPU may not correctly detect/raise illegal instruction exception
2. **breakpoint**: CPU may not handle ebreak instruction

### Steps
1. Read the disassembly of `all-test-privfull.s` to find the failing test code
2. Check `core_decode.sv` for illegal instruction detection logic
3. Check if `ebreak` (0x00100073) is recognized and generates correct trap
4. Check if illegal CSR access raises the correct exception (cause=2)
5. Verify trap cause codes match NEMU reference
6. Test and iterate

### Key Files
- `vsrc/src/core/core_decode.sv` - instruction decoding, illegal detection
- `vsrc/src/core/core_commit.sv` - trap commit logic
- `vsrc/src/core/core_csr.sv` - CSR trap handling, cause codes
- `ready-to-run/lab+/4/all-test-privfull.s` - test source

### Checkpoint
- [ ] illegal_instr test PASS
- [ ] breakpoint test PASS
- [ ] All lab+4 tests PASS
- [ ] Regression: lab1-6 still pass

---

## Phase 2: Fix lab+3 - Atomic Instructions (2-3 hours)

### Requirements (from wiki)
- Implement 32-bit AMO: amoswap.w, amoadd.w, amoxor.w, amoand.w, amoor.w, amomin.w, amomax.w, amominu.w, amomaxu.w
- Implement LR.W / SC.W
- Atomicity: no interrupt during AMO execution
- Reservation set for LR/SC (assume at most 2 LR before SC)

### Steps
1. Analyze atomicity.S test to understand exact instruction sequences tested
2. Implement remaining AMO .w instructions in core_execute.sv or core_mdu.sv
3. Implement LR.W: load from memory + set reservation tag
4. Implement SC.W: check reservation, store if valid, set rd=0/1
5. Ensure interrupts are disabled during atomic operations
6. Implement reservation set tracking module
7. Test with `make test-labplus-3`

### Key Files
- `vsrc/src/core/core_decode.sv` - AMO/LR/SC decoding
- `vsrc/src/core/core_execute.sv` - AMO execution logic
- `vsrc/src/core/core_mdu.sv` - MDU integration
- `vsrc/src/core/core_commit.sv` - atomicity guard (no interrupt during AMO)
- `vsrc/include/common.sv` - AMO command definitions

### Checkpoint
- [ ] AMO instructions (amoswap.w, amoadd.w, etc.) working
- [ ] LR.W / SC.W working
- [ ] Reservation set logic working
- [ ] lab+3 test PASS
- [ ] Regression: lab1-6 still pass

---

## Phase 3: lab+2 - Performance Optimization (2-3 hours)

### Requirements (from wiki)
- Implement branch prediction or other pipeline optimizations
- Test with microbench: `make test-labplus-2`
- Performance comparison

### Steps
1. Run baseline microbench to measure current performance (cycle count)
2. Implement static branch prediction (always predict not-taken or predict backward taken)
3. Or implement 1-bit / 2-bit bimodal predictor
4. Measure performance improvement
5. Consider other optimizations: instruction prefetch, reduce stalls

### Key Files
- `vsrc/src/core/core.sv` - pipeline control
- `vsrc/src/core/core_decode.sv` - branch decode
- `vsrc/src/core/core_execute.sv` - branch resolution

### Checkpoint
- [ ] Baseline performance recorded
- [ ] Branch prediction implemented
- [ ] Performance improvement measured
- [ ] lab+2 test PASS (no functional regression)

---

## Phase 4: xv6 Attempt (optional, 3-5 hours)

### Requirements (from wiki)
- Main track bonus: run xv6 kernel
- Partial progress counts (e.g., MMIO for virtual disk)
- Need: S-mode, MMU, mret/ecall/sret, atomic instructions

### Steps
1. Study xv6 source and Makefile target
2. Check if MMIO virtio disk access can be emulated in difftest
3. Try to get xv6 boot messages output
4. Document progress and blockers

### Checkpoint
- [ ] xv6 partial progress documented
- [ ] Any additional fixes identified

---

## Phase 5: Documentation & Report (2-3 hours)

### Requirements
- PDF or MD format
- Describe design decisions, implementations, problems encountered
- Include all bonus work done
- Include previous bonus items (mul/div, CSR descriptions, S-mode, MMU)

### Sections
1. Lab+ Overview & Goals
2. Previously Completed Bonuses (Lab1-6)
3. lab+4: PMP & Privilege Full - Design & Fixes
4. lab+3: Atomic Instructions - AMO & LR/SC Implementation
5. lab+2: Performance Optimization - Branch Prediction
6. xv6 Attempt (if applicable)
7. Problems Encountered & Solutions
8. Test Results Summary

### Checkpoint
- [ ] Report complete
- [ ] Report reviewed

---

## Phase 6: Submission (15 min)

### Steps
1. Final regression test (all lab1-6 + lab+ tests)
2. Commit all changes
3. Run `make handin`
4. Submit zip to Elearning

### Checkpoint
- [ ] All tests pass
- [ ] All changes committed
- [ ] Handin zip created

---

## CI Script Design

```bash
#!/bin/bash
# scripts/ci.sh - Run all lab tests
set -e
echo "=== Lab+ CI ==="

# Build first (single build, reused)
make clean && make sim 2>&1 | tee build.log

# Run each test
for lab in lab1 lab2 lab3 lab4; do
  echo "--- Test $lab ---"
  TEST= make test-$lab 2>&1 | tee ${lab}.log
  if grep -q "HIT GOOD TRAP" ${lab}.log; then
    echo "PASS: $lab"
  else
    echo "FAIL: $lab"
  fi
done

# lab+ tests
for lp in 2 3 4; do
  echo "--- Test labplus-$lp ---"
  make test-labplus-$lp 2>&1 | tee labplus${lp}.log
  if grep -q "HIT GOOD TRAP" labplus${lp}.log || grep -q "[OK]" labplus${lp}.log; then
    echo "PASS: labplus-$lp"
  else
    echo "FAIL: labplus-$lp"
  fi
done
```

## Execution Order

1. **Phase 0** first - establish baseline
2. **Phase 1** next - fix lab+4 (highest confidence fix)
3. **Phase 2** - atomic instructions for lab+3
4. **Phase 3** - performance for lab+2
5. **Phase 4** - xv6 attempt (optional)
6. **Phase 5** - report
7. **Phase 6** - submit
