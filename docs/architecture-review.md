# RISC-V SoC Architecture Review & Risk Assessment

## 1. System Overview

### 1.1 Block Diagram

```
                    Basys3 (Artix-7 XC7A35T)
                    ┌──────────────────────────────────┐
                    │  clk_wiz_0 (MMCM)                 │
  100MHz ──►────────│  100MHz → 25MHz cpu_clk           │
  btnC ───►────────│  reset → sys_reset (| ~locked)   │
                    │                                    │
                    │  ┌──────────────────────┐        │
                    │  │ soc_top               │        │
                    │  │  ┌────────────┐       │        │
                    │  │  │ mycpu_top  │       │        │
                    │  │  │  ┌─────┐  │       │        │
                    │  │  │  │VTop │  │ cbus   │        │
                    │  │  │  │core │──│ req   │        │
                    │  │  │  │+mmu│  │       │        │
                    │  │  │  │+arb│◄─│ cbus   │        │
                    │  │  │  └─────┘  │ resp  │        │
                    │  │  └────────────┘       │        │
                    │  │          │              │        │
                    │  │  cbus_crossbar          │        │
                    │  │  addr[31]=1→RAM  0→DEV │        │
                    │  │          │       │      │        │
                    │  │  ┌───────▼──┐ ┌─▼────┐ │        │
                    │  │  │bram_wrap│ │device│ │        │
                    │  │  │(2MB)    │ │.sv   │ │        │
                    │  │  └─────────┘ │      │ │        │
                    │  │              │ UART ├─►RsTx    │
                    │  │              │ SPI  ├─►Flash  │
                    │  │              │ CLINT│ │        │
                    │  │              └──────┘ │        │
                    │  └──────────────────────┘        │
                    └──────────────────────────────────┘
```

### 1.2 Pipeline Architecture

5-stage in-order single-core pipeline: **IF → ID → EX → MEM → WB**

- **IF** (Fetch): Issues ibus_req, 1-entry fetch buffer, redirect on branch/trap
- **ID** (Decode): Full decode + forwarding from EX/MEM/WB
- **EX** (Execute): ALU, branch resolve, MDU (multi-cycle mul/div), AMO state machine
- **MEM** (Memory): Load/store via dbus, 1-cycle stall for BRAM latency
- **WB** (Writeback): GPR write, CSR write, trap handling

MMU (Sv39 page table walker) sits between core and bus converters:
```
core ↔ MMU ↔ IBusToCBus/DBusToCBus ↔ CBusArbiter → cbus_crossbar
```

### 1.3 Memory Map

| Region | Address Range | Device | Width |
|--------|--------------|--------|-------|
| UART | 0x10000000–0x10000005 | 16550-style registers | byte |
| DISK_CTRL | 0x10001000 | blockno register | 32-bit |
| DISK_STATUS | 0x10001008 | ready bit | 32-bit |
| DISK_DATA | 0x10001100–0x100014FF | 1KB data window | 32-bit |
| COUNTER_2 | 0x20003000 | mtime mirror | 64-bit |
| FINISH | 0x23333000 | simulation halt | 64-bit |
| SW | 0x23333008 | switch register | 64-bit |
| CLINT | 0x3800bff8 | mtime | 64-bit |
| RAM | 0x80000000–0x801FFFFF | BRAM (2MB sim / 164KB FPGA) | 64-bit |

### 1.4 Key Parameters

| Parameter | Simulation | FPGA (Basys3) |
|-----------|-----------|---------------|
| CPU clock | = input clock | 25MHz (MMCM from 100MHz) |
| BRAM size | 2MB (behavioral) | ~164KB (real Xilinx BRAM) |
| PHYSTOP | 1MB (FPGA_SIM=1) | 164KB |
| Disk | in-memory sim_disk_mem | SPI Flash N25Q032 @ offset 0x300000 |
| UART output | $write/%c | RsTx pin → FT232H Channel B |
| Disk ready | combinational (always 1) | 1-cycle BRAM read latency |

---

## 2. Detailed Module Review & Issues Found

### 2.1 CPU Core (vsrc/src/core.sv + submodules)

**Architecture**: 5-stage in-order, no branch prediction (static not-taken), no cache (direct CBus).

#### 2.1.1 Front-End (Fetch)

- Fetch buffer: 1-entry, allows 1 outstanding fetch. On redirect, 2-cycle bubble injected.
- `fetch_drop_resp_pending`: correctly drops stale bus responses after redirect.
- **Issue [P2] IBus addr_ok never checked**: `ireq.valid` is asserted without checking `iresp.addr_ok`. This is safe only because the downstream CBusArbiter and IBusToCBus guarantee eventual delivery, but violates the bus protocol spec. No functional impact currently.
- **Issue [P3] No branch prediction**: Every taken branch/jal/jalr costs 2 bubble cycles. For xv6 kernel boot with frequent function calls and conditionals, this is a significant performance penalty but functionally correct.

#### 2.1.2 Decode & Forwarding

- Full forwarding: EX→ID (ex_forwardable), MEM→ID, WB→ID.
- CSR read forwarding: handles writes in EX/MEM/WB stages.
- **Issue [P1] EX→ID forwarding for load-use hazard is UNSOUND**:
  `raw_hazard_ex` stalls when EX has a load whose data isn't ready yet (`!ex_result_ready`). However, `core_decode.sv:118` checks `ex_forwardable` which requires `ex_result_ready`. If EX has a non-load instruction (e.g., ADD) that writes to rd, and ID uses that register, the forwarding path works. But if EX has a LOAD, `ex_result_ready=0`, the pipeline stalls via `raw_hazard_ex`, so the ID never sees the forwarded value — it waits until MEM where `raw_hazard_mem` handles it. This is functionally correct but worth noting: the forwarding network has two layers (EX fast-path + MEM slow-path for loads).

- **Issue [P1] MEM→ID forwarding may forward stale data**:
  `core_decode.sv:119` forwards from `mem_r.result` when `mem_r.valid && mem_r.wen && mem_r.rd != 0`. For loads, `mem_r.result` is the load data. But `mem_r.result` is set from `ex_result` (for non-loads) or `ex_r.wb_pc4 ? pc+4 : ex_result` at the time MEM is entered (core.sv:753). For loads, `mem_r.result` is updated to `mem_load_data` only in `mem_stage_result` (core_execute.sv:147), which feeds `wb_r.result`, not `mem_r.result` directly. **Actually wait** — `mem_r.result` is set at the transition from EX→MEM (core.sv:753): `mem_r.result = ex_r.is_amo ? amo_result : (ex_r.wb_pc4 ? (ex_r.pc + 4) : ex_result)`. For loads, `ex_result` is the ALU output (address), not the loaded data. The loaded data only becomes available when `dresp.data_ok` arrives. At that point, `mem_stage_result` (core_execute.sv:147) selects `mem_load_data`. But `mem_stage_result` feeds `wb_r.result`, not `mem_r.result`. So `mem_r.result` for a load still holds the address, and `mem_stage_result` holds the actual data.
  
  **This means MEM→ID forwarding via `mem_r.result` for a load instruction forwards the ADDRESS, not the loaded data.** However, `raw_hazard_mem` requires `stall_if_mem`, which is true when `mem_r.valid && (mem_r.is_load || mem_r.is_store)` (core_execute.sv:52). This means when MEM has a load, `stall_if_mem=1`, which forces `stall_front=1`, preventing ID from consuming the forwarded value. The pipeline stalls until the load completes and moves to WB, at which point WB→ID forwarding via `wb_r.result` (= `mem_stage_result` = correct load data) works.
  
  **Conclusion**: Functionally correct, but the MEM→ID forwarding path is dead for loads (stall prevents consumption). Only WB→ID forwarding handles load-use. This is fine but wastes combination logic.

#### 2.1.3 Execute & MDU

- MDU: multi-cycle shift-add multiplier, restoring divider. Early-out for 0, 1, power-of-2 divisor.
- **Issue [P2] MDU `mdu_out_valid` cleared conditionally**: At core_mdu.sv:86, `mdu_out_valid` is cleared when `!halted && !trap_commit && !stall_pipe && ex_r.valid && ex_is_mdu && mdu_out_valid`. If the pipeline is stalled (e.g., by a concurrent load), the MDU result stays valid and held. This is correct.

- **Issue [P3] No divide-by-zero exception**: RISC-V spec says div by zero returns -1 (signed) or all-1s (unsigned) for quotient, dividend for remainder. The implementation handles this as a fast path (mdu_out_valid=1 immediately), which is correct per spec. No trap needed.

#### 2.1.4 AMO State Machine

- Located in core.sv (lines 196-268). 6 states: IDLE→LOAD→STORE_W→DONE.
- LR/SC reservation set: 2 entries, cleared on SC success.
- **Issue [P1] AMO_LD→AMO_ST_STORE_W race with dresp**: When `amo_state` transitions from AMO_ST_LOAD to AMO_ST_STORE_W (or AMO_ST_DONE for LR), it sets `amo_dreq_valid` and the new state simultaneously in the same `always_ff` block. The `dreq.valid` output depends on `amo_owns_dreq = ex_r.valid && ex_r.is_amo && (amo_state != AMO_ST_IDLE)`. On the cycle AMO_ST_LOAD sees `dresp.data_ok`, `amo_state` transitions to STORE_W, and `amo_dreq_valid` is set. But `amo_owns_dreq` depends on the **registered** `amo_state`, which hasn't updated yet (it updates on the next posedge). So on the current cycle, `amo_owns_dreq=1` (still in LOAD), `amo_dreq_valid=0` (still in LOAD's default). On the **next** cycle, `amo_state=STORE_W` and `amo_dreq_valid=1`, so the store request appears. This is correct — 1-cycle gap between load data arriving and store request going out. No bug.

- **Issue [P2] LR/SC reservation set is only 2 entries**: RISC-V spec allows any size reservation set. With 2 entries, if software does 3 LR.W before any SC.W, the first reservation is lost. For xv6 single-core (spinlock), this is sufficient since only one LR/SC sequence runs at a time.

#### 2.1.5 Pipeline Hazard Control

- `stall_pipe`: OR of stall_ex_busy, stall_mem_busy, raw_hazard_ex, raw_hazard_mem
- `stall_front`: OR of stall_ex_busy, raw hazards, fetch_redirect_pending, stall_if_mem, front_trap_pending, ex_to_mem_blocks_front, mret_sret_in_pipe
- **Issue [P2] `mret_sret_in_pipe` stalls fetch but not ID→EX advancement**: When MRET/SRET is in EX/MEM/WB, `stall_front=1` prevents fetch. But the condition doesn't set `stall_pipe`. Looking at the pipeline advancement logic (core.sv:738), when `stall_front=1` and we're in the `else` branch (no trap/mmu/stall_mem), we have `ex_to_mem_blocks_front` and `raw_hazard_ex/mem` checks. If none of those fire, the pipeline keeps advancing even though MRET is in flight. But if MRET is in EX, `ex_r.valid=1` and pipeline advancement continues normally since `stall_pipe=0` (MRET doesn't set is_load/is_store/is_mdu). The concern is about speculative fetches under the OLD page table being incorrectly processed. But since `stall_front=1`, no new fetch fires. The MRET moves through MEM→WB and when it commits, `mret_redirect` fires and `flush_mmu_o` flushes the MMU. This appears correct.

#### 2.1.6 MMU (vsrc/util/mmu.sv)

- Sv39 3-level page table walker, supports 4KB/2MB/1GB pages.
- Crossbar interaction: PTE reads go through CBusArbiter (shared with instruction/data).
- **Issue [P1] MMU walk can be VERY slow**: Each PTE read goes through CBusArbiter → cbus_crossbar → bram_wrapper (2-cycle latency). A full 3-level walk takes at least 9 cycles (3 levels × 3 cycles each). With arbiter contention (IBus vs DBus vs PTE read), it could be much longer. For xv6 with many page table updates during fork/exec, this is a major performance bottleneck but functionally correct.

- **Issue [P1] satp_changed detection during walk**: If satp changes mid-walk, the FSM resets to WALK_IDLE (mmu.sv:453,469,487). `flush_mmu` also returns the FSM to IDLE. The CBusArbiter has drain_pending logic to avoid stale responses being mis-consumed. This was previously a source of bugs (trampoline 0x20009001 vs 0x20008801) and the current logic appears correct.

- **Issue [P2] PMP check only supports 1 entry**: Only pmpcfg0/pmpaddr0 are implemented. For xv6 this is sufficient (no PMP usage expected).

### 2.2 Bus Layer

#### 2.2.1 CBusArbiter (vsrc/util/CBusArbiter.sv)

- Priority: IBus(0) > DBus(1). Lock once accepted, release on ready+last.
- `drain_pending` state handles MMU flush during in-flight transaction.
- **Issue [P1] IBus starvation**: IBus has higher priority than DBus. If the CPU is fetching continuously (no stall), DBus transactions (data loads/stores) can be starved. In practice, the pipeline stalls when DBus needs access (`stall_if_mem`), so this doesn't happen in normal operation.

#### 2.2.2 IBusToCBus / DBusToCBus

- **Critical [P1] DBusToCBus `dcreq.valid` gating** (DBusToCBus.sv:50): `dcreq.valid = dreq.valid && (issue_now || req_inflight)`. This prevents stale valid from being sent to the bus after a transaction completes. Without this gate, BRAM/device may latch a duplicate request. This was previously the root cause of double UART writes.

- **Issue [P2] DBusToCBus `resp_seen` logic**: `resp_seen` is cleared when `!okay || !dreq.valid`. This means if CPU drops `dreq.valid` after issuing a request (e.g., due to a pipeline flush), the `req_inflight` flag will also be cleared on the next cycle (line 73: `else if (!dreq.valid) req_inflight <= 0`). But the bus may still return a response for the previously-latched request. This is handled by the CBusArbiter's lock mechanism (the locked request stays stable until ready+last). Potential risk: if CPU drops valid mid-transaction and the CBusArbiter has locked the request, the response goes to `iresps[lock_select]` but the DBusToCBus has `req_inflight=0` so `resp_fire=0` — the response is consumed by the arbiter but not forwarded to the core. This matches the drain_pending behavior for MMU flushes. Functionally correct but subtle.

#### 2.2.3 cbus_crossbar (vivado/src/with_delay/cbus_crossbar.sv)

- Ultra-simple: `addr[31]=1` → RAM, `addr[31]=0` → Device.
- `rdata`, `ready`, `last` are muxed by `addr[31]`.
- **Issue [P1] No default for rdata/ready/last on unused path**: When `addr[31]=1` (RAM access), the device path is not selected, but `device_valid=~addr[31] && valid = 0`. The device sees no valid request but its `rdata`/`ready`/`last` outputs are still muxed into the crossbar outputs. This is fine because the mux selects `ram_rdata`/`ram_ready`/`ram_last` when `addr[31]=1`.

- **Issue [P2] Address race on consecutive different-region accesses**: If the CPU issues a RAM access followed immediately by a Device access, the `addr` signal changes combinationally. Since the crossbar has no registered state, the `device_valid` and `ram_valid` signals track `addr[31]` directly. This is correct for a single-cycle crossbar.

### 2.3 BRAM Subsystem

#### 2.3.1 bram_wrapper (vivado/src/with_delay/bram_wrapper.sv)

- Transaction-based: latches request, counts BRAM_DELAY=2 cycles, asserts `real_valid` for 1 cycle.
- Read-Modify-Write (RMW): partial writes (wstrobe != 0xFF) take 2 phases (read old → merge → write back).
- BRAM IP: `latched_addr[20:3]` = 18-bit word address → 2^18 × 64-bit = 2MB.
- **Issue [P0] CRITICAL: BRAM capacity vs PHYSTOP mismatch for FPGA**:
  - bram_wrapper uses `latched_addr[20:3]` → 18-bit address → 2MB addressable.
  - But the actual Basys3 XC7A35T has only ~1.8Mbit (225KB) of Block RAM.
  - xv6 with `FPGA_SIM=undefined` sets PHYSTOP = KERNBASE + 164KB = 0x80029000.
  - The **real** FPGA BRAM can only hold ~225KB. With kernel binary ~49KB, usable memory = ~176KB. PHYSTOP=164KB is within this.
  - However, the bram_wrapper's `bram_0` IP instantiation must be configured to the correct size. If the Vivado BRAM IP is configured for the full 2MB but the FPGA doesn't have enough BRAM, Vivado will fail implementation.
  - **The bram_0 IP configuration must match the actual FPGA BRAM size.** If it's configured for 2MB (which works in simulation), implementation may fail or only partially initialize.

- **Issue [P1] RMW logic for non-INCR partial writes**: The `needs_rmw` flag is only set for partial writes with non-INCR burst. For INCR burst partial writes, the code goes through the normal write path (`bram_wea_wire = 1`). This means INCR burst partial writes will corrupt adjacent bytes. However, INCR burst is not used in this design (DBusToCBus always sets `len=MLEN1`, `burst=AXI_BURST_INCR` but `len=MLEN1=0` means single beat), so this is a theoretical issue.

- **Issue [P2] BRAM Delay counter edge case**: When `counter == BRAM_DELAY` and `last` arrives simultaneously, the `else if (last)` branch fires and clears the transaction. This is correct — the BRAM response has been consumed.

#### 2.3.2 BehavioralBRAM (vsrc/BehavioralBRAM.sv)

- Simulation equivalent of bram_wrapper. Read latency = 2 cycles, matches BRAM_DELAY.
- `real_valid` is a single-cycle pulse (same as bram_wrapper).
- **Verified**: Transaction protocol matches bram_wrapper exactly. Ready/last signals are consistent.

### 2.4 Device Layer (vivado/src/device.sv)

#### 2.4.1 UART TX

- FIFO-based: 64-entry TX FIFO, state machine sends start + 8 data + stop bits.
- `BIT_TMR_MAX = 216` → 25MHz/217 ≈ 115207 baud (spec: 115200, error: 0.006%, well within 2% tolerance).
- **Issue [P2] TX FIFO overflow not handled**: If CPU writes to THR while TX FIFO is full (count=64), the write is silently dropped (`fifo_write_en = cpu_tx_write && ~fifo_full`). The ready signal properly blocks via `uart_thr_write_req ? (~fifo_full & ~txn_done_pulse)`, so CPU should stall. But in simulation where `disk_rdata_valid=1` immediately, the CPU may issue back-to-back writes faster than the UART can drain. For xv6's console output, the FIFO depth of 64 is sufficient.

#### 2.4.2 UART RX

- Sampling-based: detects start bit, samples at mid-bit.
- `rxByteReady` pulse → 16-entry RX FIFO.
- **Issue [P3] RX not tested on FPGA**: jtag_uart is disabled, `jtag_cpu_rx = 1'b1`. Physical UART RX (`RsRx`) is not connected to the device. CPU cannot receive keyboard input. This means `sh` cannot receive typed commands. However, for boot verification, this is acceptable.

#### 2.4.3 CLINT mtime

- 25MHz/25 = 1MHz tick rate (mtime_div counts to 24, then increments mtime).
- **Issue [P2] Timer interrupt not connected**: `trint`, `swint`, `exint` are all tied to 0 in both `mycpu_top.sv` and `SimTopFPGA.sv`. xv6's timer interrupt handler will never fire. xv6's `usertrap()` checks `which_dev == 2` (timer) to yield via `yield()`. Without timer interrupts, processes never yield voluntarily — only `sleep()`/`exit()`/`wait()` cause context switches. For single-core xv6 with init→sh, this is acceptable because the shell never calls `sleep()` for normal operation. But if the shell spawns a long-running foreground process, it will never be preempted.

#### 2.4.4 Disk (SPI Flash)

**Simulation path** (`gen_sim_disk`):
- `disk_rdy = 1` always (write to DISK_BLOCKNO is instant).
- `disk_rdata_valid = 1'b1` (combinational).
- Data from `sim_disk_mem` (loaded from `disk_hex.txt`).
- **Issue [P2] sim_disk_mem address calculation overflow**: `disk_blockno * 256 + addr[9:2] - 64`. If `disk_blockno` is large, the index can exceed 256000 (the array size). For xv6 with FSSIZE=1000 blocks, max index = 999*256+255 = 255999, which matches the array size [0:255999]. Correct.

**FPGA path** (`gen_real_disk`):
- SPI Flash read at offset 0x300000 (past ~3MB FPGA bitstream area).
- `spi_flash_disk.sv`: standard SPI Read (0x03) command, 12.5MHz SPI clock.
- Block RAM buffer: 256×32-bit = 1KB data window.
- Read-modify-write for byte-strobed CPU writes (2-cycle latency).
- **Issue [P0] CRITICAL: SPI Flash offset 0x300000 may overlap bitstream**:
  - Basys3 bitstream for XC7A35T is typically ~2MB.
  - The full_flash.mcs layout documented: bitstream @ 0x000000 + fs.img @ 0x300000.
  - If bitstream grows beyond 3MB, it will overwrite fs.img. Current bitstream should be well under 3MB.
  - The SPI flash is N25Q032 = 32Mbit = 4MB, so 0x300000 + 1MB(fs.img) = 4MB → exactly at the limit. If fs.img exceeds 1MB, it overflows the flash.
  - xv6's FSSIZE=1000 → fs.img = 1000×1024 + metadata ≈ 1MB. Borderline.

- **Issue [P0] CRITICAL: Disk data byte-lane alignment**:
  In `device.sv:723`: `disk_rdata_shifted = {32'd0, disk_rdata_reg} << (disk_raddr_offset * 8)`.
  - `disk_raddr_offset = addr[2:0]` — this is the byte offset within the 64-bit word.
  - x18v6's `virtio_disk_rw` reads data as `uint32` from `DISK_DATA_REG` (= `0x10001100`).
  - For a word-aligned read: `addr[2:0] = 0`, so shift = 0. `rdata = {32'd0, disk_rdata_reg}`.
  - But the crossbar sends 64-bit data. The CPU issues a 32-bit load (MSIZE4), so the lower 32 bits are used.
  - **Wait — xv6's `disk_data = DISK_DATA_REG` is `(volatile uint32 *)(DISK_MMIO_BASE + 0x100)`. This generates a word-aligned 32-bit load. The CPU decodes this as MSIZE4, addr=0x10001100+i*4. In the crossbar, `addr[31]=0` → device path. In device.sv, `rdata` is computed and then the CPU's load path in core_execute.sv:141 returns `{32'd0, mem_aligned_data[31:0]}` for MSIZE4 unsigned. So `rdata[31:0]` from the device becomes the loaded value.**
  - `disk_rdata_reg` is the 32-bit BRAM word. For `addr = 0x10001100`, `addr[9:2] = 0x40 = 64`. `disk_cpu_raddr = 64 - 64 = 0`. `disk_rdata_reg = disk_buf[0] = first word`. `disk_rdata_shifted = {32'd0, disk_buf[0]} << 0`. This goes into `rdata[31:0]`, which the CPU reads. **Correct.**
  - For `addr = 0x10001104` (second word): `addr[9:2] = 0x41 = 65`. `disk_cpu_raddr = 1`. `disk_rdata_reg = disk_buf[1]`. **Correct.**
  - For misaligned byte access (not generated by xv6 driver): `addr[2:0] != 0`, `disk_rdata_shifted` shifts by `addr[2:0]*8` bits. The CPU's `mem_aligned_data = dresp.data >> (mem_byte_shift * 8)` in core_execute.sv:121, where `mem_byte_shift = addr[2:0]`. This double-shift may produce incorrect results for misaligned accesses. But since xv6 driver always does aligned word accesses, this is a theoretical concern.

- **Issue [P1] SPI Flash disk write does not persist**: The `spi_flash_disk.sv` module only supports read (SPI Read 0x03 command). CPU writes go to the Block RAM buffer (`disk_buf`) but are never written back to SPI Flash. This means disk writes (xv6 log layer) are lost on power cycle. For xv6 boot verification (read-only filesystem access during init), this is fine. For a persistent filesystem, a SPI Flash write command would be needed.

#### 2.4.5 Device Ready Timing

- `txn_done_pulse`: 1-cycle pulse after `txn_fire`, used to de-assert `ready` for 1 cycle to prevent double-firing.
- **Issue [P1] `is_disk_data_read` is combinational from `valid` and `addr`**: This means on FPGA, `ready` changes combinationally with `valid` and `addr`. If `valid` is high and `addr` changes from RAM to DISK_DATA, `ready` drops immediately (before BRAM data arrives). This is correct behavior but relies on the CPU not changing addr while valid is high (which it shouldn't, since CBusArbiter locks the address).

### 2.5 SoC Top & Board Level

#### 2.5.1 soc_top (vivado/src/with_delay/soc_top.sv)

- Connects CPU, crossbar, BRAM, and device.
- **Issue [P2] `device.size` is passed as `size` from CPU but not used in device for alignment**: The `size` signal goes to device but is only used as `size[1:0]` in debug mux (LED channel A). The device doesn't use `size` for anything functional. This is fine because byte alignment is handled by `wstrobe` for writes and `addr[2:0]` for reads.

#### 2.5.2 basys3_top (vivado/src/with_delay/basys3_top.sv)

- SPI clock via STARTUPE2 primitive (USRCCLKO → CCLK pin).
- SPI pin mapping: QspiDB[0]=MOSI, QspiDB[1]=MISO, QspiDB[2]=WP(high), QspiDB[3]=HOLD(high).
- **Issue [P0] CRITICAL: STARTUPE2 CCLK timing**:
  The STARTUPE2 primitive routes `spi_sck_int` (from spi_flash_disk) to the CCLK pin. This is the SPI clock for reads from flash. After FPGA configuration completes, the STARTUPE2 takes control of CCLK from the configuration logic. However, **the CCLK output enable timing during the transition from configuration to user mode is not guaranteed** — there may be a gap or glitch. The `EOS` (End Of Startup) signal should be checked before enabling SPI accesses.
  
  Currently `EOS` is not used. The CPU may attempt SPI reads before the STARTUPE2 has fully transitioned. This could cause the first disk reads to fail. With xv6's `fsinit()` being one of the first operations after `kvminit()`, this is a real risk.

- **Issue [P1] No pull-up on QspiDB pins**: The SPI flash data pins (QspiDB[1] = MISO) need a pull-up to avoid floating when SPI is idle. Basys3 schematic may have external pull-ups, but if not, the MISO line could float and cause garbage SPI reads.

#### 2.5.3 Clock & Reset

- MMCM: 100MHz input → 25MHz cpu_clk. `clk_locked` indicates PLL is stable.
- `sys_reset = reset | ~clk_locked` — held high until PLL locks.
- **Issue [P3] No glitch-free reset**: `btnC` (reset) is a mechanical switch with bounce. Each press/release can generate multiple reset pulses. This is usually harmless but could cause unexpected behavior during debugging.

### 2.6 xv6 Adaptation

#### 2.6.1 Memory Layout

- `FPGA_SIM=1` (simulation): PHYSTOP = 0x80100000 (1MB), NPROC=3, NBUF=4, USERSTACK=1
- FPGA (no FPGA_SIM): PHYSTOP = 0x80029000 (164KB), same reduced params
- **Issue [P0] CRITICAL: FPGA PHYSTOP must match real BRAM size**:
  - XC7A35T has 50 Block RAMs × 36Kb = 1,800Kb = 225KB.
  - Kernel binary ends at ~0x8000D1D8 (≈53KB). Free memory starts at ~0x8000E000.
  - Available BRAM = 225KB - 53KB = 172KB. PHYSTOP=164KB = 0x29000 offset → end at 0x80029000.
  - Pages available = (0x29000 - 0xE000) / 0x1000 = (164KB - 56KB) / 4KB = 27 pages.
  - For xv6: init+fork+exec+sh needs ~30+ pages. **27 pages may be insufficient** — this was the original `kalloc: freelist empty!` bug found earlier.
  - **The FPGA build cannot use 1MB PHYSTOP** because the real BRAM is only 225KB. If PHYSTOP exceeds actual BRAM, writes to addresses beyond BRAM will be lost and reads will return 0 (or whatever the BRAM IP returns for out-of-range addresses).

#### 2.6.2 Disk Driver

- Simple synchronous MMIO: write blockno, poll status, read/write data window.
- **Issue [P2] Debug printf's still in `virtio_disk_rw()`**: `printf("[DISK] %s block=%d\n", ...)` and `printf("[FS] ...")` calls. These slow down disk I/O significantly on FPGA (each printf → multiple UART TX bytes at 115200 baud = ~87μs per byte). For 256 words per block read, the overhead is minimal compared to the blocking poll. But the printf overhead for each `bread` call adds latency.

#### 2.6.3 Kernel Debug Prints

- Multiple `printf("[DBG]...")`, `printf("[DISK]...")`, `printf("[FS]...")` statements remain in the kernel.
- **Issue [P2] Verbose debug output slows boot significantly on FPGA**: Each `printf` call blocks the CPU for ~0.5-1ms (multiple characters at 115200 baud). With dozens of debug prints during boot, total overhead could be 50-100ms. Not a functional bug but makes boot slow.

---

## 3. Risk Summary & Priority

| # | Severity | Component | Issue | Impact | Mitigation |
|---|----------|-----------|-------|--------|-----------|
| 1 | **P0** | BRAM/FPGA | PHYSTOP(164KB) → only 27 free pages; may be insufficient for fork+exec | Kernel panic: `kalloc: freelist empty!` | Reduce kernel size or increase BRAM utilization |
| 2 | **P0** | BRAM/FPGA | bram_0 IP configured for 2MB but FPGA has only 225KB | Implementation may fail or address wrapping | Configure bram_0 IP to correct size for FPGA |
| 3 | **P0** | SPI/Board | STARTUPE2 CCLK timing: no EOS check before SPI reads | First disk reads may return garbage → `panic: invalid file system` | Wait for EOS before enabling CPU, or add retry logic |
| 4 | **P0** | SPI/Board | Flash offset 0x300000: bitstream may grow to overlap fs.img | Filesystem corruption | Verify bitstream size < 3MB; use larger offset |
| 5 | **P1** | CPU | MEM→ID forwarding for loads is dead (stall prevents use) | No functional impact, wasted logic | Accept for now |
| 6 | **P1** | Device | Timer interrupt not connected (trint=0) | No preemption; long processes hang | Connect trint from CLINT mtime comparison |
| 7 | **P1** | Device | Disk writes don't persist to SPI Flash | Filesystem changes lost on power cycle | Accept for read-only boot verification |
| 8 | **P1** | SPI | No SPI Flash write commands (read-only disk) | Same as #7 | Add SPI Write/Program/Erase commands |
| 9 | **P1** | Device | `is_disk_data_read` is combinational → ready depends on addr | Potential timing risk if addr changes while valid | Ensure CPU holds addr stable during valid |
| 10 | **P1** | Board | No pull-up on QspiDB[1] (MISO) | Floating MISO may cause garbage reads | Verify Basys3 has external pull-ups |
| 11 | **P2** | CPU | No branch prediction → 2-cycle penalty per taken branch | Performance only | Accept for minimal FPGA implementation |
| 12 | **P2** | CPU | LR/SC reservation set only 2 entries | Insufficient for concurrent LR sequences | Accept for single-core xv6 |
| 13 | **P2** | Device | TX FIFO overflow silently drops | Potential data loss under heavy write | Ready signal blocks CPU writes |
| 14 | **P2** | Kernel | Debug printf's slow FPGA boot | 50-100ms extra boot time | Remove debug prints for production |
| 15 | **P2** | BRAM | RMW for INCR burst partial writes would corrupt | Theoretical (INCR not used) | низкий риск |
| 16 | **P2** | Board | Mechanical debounce on btnC | Multiple reset pulses | Not functional impact |
| 17 | **P3** | CPU | IBus addr_ok never checked | Protocol violation, no functional impact | Accept |
| 18 | **P3** | Board | CPU UART RX not connected (jtag_uart disabled) | No keyboard input for sh | Accept for boot verification |

---

## 4. Simulation vs FPGA Divergence Points

| Aspect | Simulation (Verilator) | FPGA (Basys3) | Risk |
|--------|----------------------|---------------|------|
| BRAM | 2MB behavioral, unlimited | 225KB real BRAM | **HIGH** — PHYSTOP mismatch |
| Disk | In-memory, instant ready | SPI Flash, multi-ms read | **HIGH** — timing, offset |
| Clock | = input clock | 25MHz from MMCM | Low — functional parity |
| UART TX | $write/%c → stdout | RsTx → FT232H | Low — verified working |
| UART RX | Not simulated | Not connected | Low — not needed for boot |
| Timer | trint=0 (no interrupt) | trint=0 (no interrupt) | **MEDIUM** — no preemption |
| Reset | Clean synchronous | btnC + ~clk_locked | Low |
| BRAM latency | 2 cycles (matches) | 2 cycles (BRAM_DELAY=2) | None — matched |
| SPI clock | N/A (simulation disk) | 12.5MHz via STARTUPE2 | **MEDIUM** — CCLK startup |

---

## 5. Recommended Fix Order (for FPGA bring-up)

### Phase 1: Ensure simulation baseline is solid

1. **Verify xv6 boots to shell with `FPGA_SIM=1`** — rebuild kernel, run `./build/emu --no-diff`, confirm `$` prompt
2. **Remove verbose debug prints** from kernel (fs.c, virtio_disk.c, kalloc.c, proc.c) — they hide real issues and slow simulation
3. **Verify disk reads return correct data** in simulation — add assertion that superblock magic = 0x10203040

### Phase 2: Fix FPGA BRAM size

4. **Configure bram_0 IP for actual FPGA BRAM size** — either 164KB (matching PHYSTOP) or calculate exact BRAM capacity from XC7A35T resources
5. **If BRAM < 1MB, PHYSTOP must be reduced** — but with only 27 free pages, xv6 may not boot. Consider:
   - Reducing kernel size (strip unused functions)
   - Using CACHED BRAM (L2 cache) to extend effective address space
   - Reducing NPROC to 2, NBUF to 2

### Phase 3: Fix SPI Flash disk

6. **Add EOS check in basys3_top** — hold CPU reset until `EOS=1` from STARTUPE2
7. **Verify SPI Flash offset** — confirm bitstream ends before 0x300000
8. **Add SPI read timeout/retry** — if first read returns 0, retry once
9. **Verify SPI clock timing** — STARTUPE2 CCLK must run at ≤12.5MHz for N25Q032

### Phase 4: Connect timer interrupt

10. **Wire trint from CLINT mtime comparison** — xv6 expects timer interrupts for scheduling
11. **Add mtimecmp register to CLINT** — for timer interrupt acknowledgment

### Phase 5: Integration test

12. **Build bitstream with correct BRAM size, flash kernel+fs.img to SPI**
13. **Program FPGA, capture UART output via FT232H**
14. **Verify: `xv6 kernel is booting` → no panic → `$` prompt**

---

## 6. File Manifest

| File | Lines | Role | Modified for xv6 |
|------|-------|------|-------------------|
| vsrc/src/core.sv | 1031 | Pipeline controller + AMO state machine | Yes (AMO, debug prints) |
| vsrc/src/core/core_decode.sv | 438 | Instruction decode + forwarding | Yes (AMO decode, SFENCE) |
| vsrc/src/core/core_execute.sv | 154 | ALU, branch, load/store data | Yes (misalign, difftest_skip) |
| vsrc/src/core/core_commit.sv | 245 | WB, GPR write, trap handling | Yes (memdetect hack) |
| vsrc/src/core/core_csr.sv | 571 | CSR read/write, interrupt/trap logic | Yes (full S-mode CSRs) |
| vsrc/src/core/core_mdu.sv | 273 | Multi-cycle mul/div | Yes (fast paths) |
| vsrc/src/core/core_pkg.sv | 180 | Types, constants, AMO commands | Yes (AMO types added) |
| vsrc/util/mmu.sv | 521 | Sv39 page table walker | Yes (satp_changed, flush, PMP, U-bit) |
| vsrc/util/CBusArbiter.sv | 176 | IBus/DBus → shared CBus | Yes (drain_pending, flush) |
| vsrc/util/DBusToCBus.sv | 83 | DBus → CBus converter | Yes (valid gating, resp_seen) |
| vsrc/util/IBusToCBus.sv | 62 | IBus → CBus converter | Minimal |
| vsrc/VTop.sv | 124 | Core + MMU + bus converters | Yes (MMU integration) |
| vsrc/mycpu_top.sv | 55 | CBus → flat signal adapter | Minimal |
| vsrc/SimTopFPGA.sv | 250 | Verilator simulation top | Yes (FPGA_SIM debug) |
| vsrc/BehavioralBRAM.sv | 169 | Simulation BRAM | Yes (read/write monitors) |
| vsrc/include/common.sv | 249 | Types, bus definitions | No (original) |
| vsrc/include/config.sv | 9 | AXI_BURST_NUM | No |
| vivado/src/device.sv | 930 | UART + Disk + CLINT + debug | Yes (full rewrite for xv6) |
| vivado/src/spi_flash_disk.sv | 322 | SPI Flash disk controller | Yes (new module) |
| vivado/src/device.svh | 24 | Address constants | Yes (new file) |
| vivado/src/with_delay/soc_top.sv | 173 | SoC top (CPU+xbar+BRAM+device) | Yes (SPI, debug signals) |
| vivado/src/with_delay/bram_wrapper.sv | 168 | BRAM IP wrapper | Yes (RMW, burst support) |
| vivado/src/with_delay/cbus_crossbar.sv | 53 | Address router | Yes (new file) |
| vivado/src/with_delay/basys3_top.sv | 166 | Board top (SPI, LED debug mux) | Yes (STARTUPE2, SPI pins) |
| vivado/src/jtag_uart.sv | 352 | JTAG UART bridge (DISABLED) | Yes (now disabled) |
| third_party/xv6-riscv/kernel/memlayout.h | 67 | PHYSTOP, UART, DISK addresses | Yes (FPGA_SIM conditional) |
| third_party/xv6-riscv/kernel/virtio_disk.c | 82 | MMIO disk driver | Yes (full rewrite) |
| third_party/xv6-riscv/kernel/param.h | 14 | NPROC, NBUF, etc. | Yes (reduced for BRAM) |
