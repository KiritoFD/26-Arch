# xv6 Main Track Progress

## Goal

Run xv6 on the current CPU in the difftest-based simulation environment, without diff checking, until the kernel can enter user space and reach the shell.

## Current Baseline

The following pieces are now in place:

- A local xv6 source tree exists at `third_party/xv6-riscv`.
- The WSL toolchain `gcc-riscv64-unknown-elf` and `binutils-riscv64-unknown-elf` are installed and can build xv6.
- The top-level `Makefile` now provides:
  - `build-xv6`
  - `test-xv6`
- `difftest` now accepts the disk image path at runtime through the `SDCARD_IMAGE` environment variable.
- The simulation-side UART compatibility path for xv6's `UART0=0x10000000` has been added.

Current observable result:

```text
xv6 kernel is booting
init: starting sh
$$
```

This confirms:

- the xv6 kernel image is loaded correctly at `0x80000000`
- the CPU can execute the early machine-mode and supervisor-mode boot path
- the ISA mismatch caused by xv6's default `rv64gc` target has been removed
- the UART compatibility layer is working well enough for kernel boot prints
- the first user process (`/init`) starts and runs its console setup path
- the shell process is launched and reaches the prompt
- the UART/MMIO write path is clean enough that the visible shell output is no longer duplicated

With the current bring-up branch, the boot path has progressed further:

- kernel init now advances through `kinit`, `kvminit`, `procinit`, `trapinit`, `binit`, `iinit`, `fileinit`, and `userinit`
- the first scheduled process reaches `forkret`
- `fsinit(ROOTDEV)` reads the xv6 superblock successfully through the MMIO disk path
- `prepare_return -> sret -> usertrap` is active and stable enough for `/init` and `sh`

## Source Changes Already Made

### Build / integration

- Added `build-xv6` and `test-xv6` targets to the repo `Makefile`
- Cloned upstream xv6 into `third_party/xv6-riscv`

### Toolchain / ISA compatibility

- Changed xv6 build flags from `rv64gc` to `rv64im_zicsr_zifencei`
- Added `-mabi=lp64`

### Single-core lock workaround

- Replaced xv6's `__atomic_exchange_n` / `__atomic_store_n` based spinlock implementation with a single-core version that relies on `push_off/pop_off` and plain load/store

### Simulation-side UART compatibility

- Added a minimal 16550-style UART compatibility model in `difftest/src/test/vsrc/common/ram.sv`
- Fixed byte-lane placement for byte MMIO reads so xv6's `lbu` from `UART0+5` sees `LSR_TX_IDLE`
- Avoided treating baud-rate setup writes as character output by honoring the DLAB bit

### MMIO disk path

- Added a simple disk block register at `VIRTIO0 + 0x000`
- Added a ready/status register at `VIRTIO0 + 0x008`
- Added a 1KB data window starting at `VIRTIO0 + 0x100`
- Backed the disk image with a host-side in-memory buffer loaded from `SDCARD_IMAGE`
- Added synchronous block reads and writes for xv6's `bread` / log traffic

### Supervisor-mode bring-up

- Added initial `sret` decode plumbing
- Added partial Supervisor CSR storage and delegation handling in the CPU
- Verified that `prepare_return()` writes `stvec` and `sepc`, and that `sret` executes
- Verified that user-mode `ecall` already traps back into the kernel (`scause = 8`)

## Current Status

The main xv6 shell bring-up path is working.

Open work remains outside the narrow main-track milestone:

1. clean up temporary bring-up shortcuts and logging where still present
2. harden Supervisor CSR and MMU behavior if stricter architectural correctness is required
3. continue with the later `labplus` items: branch prediction / performance, atomics, and PMP

## Next Step

Use this xv6 path as the stable baseline for any later work that depends on Supervisor mode, filesystem access, or user-space execution.
