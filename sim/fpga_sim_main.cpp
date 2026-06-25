#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <verilated.h>
#include "VSimTopFPGA.h"

static VSimTopFPGA* top = nullptr;
static vluint64_t sim_time = 0;

static void tick() {
    top->clock = 0;
    top->eval();
    top->clock = 1;
    top->eval();
    sim_time++;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    top = new VSimTopFPGA;

    // Initialize inputs
    top->clock = 0;
    top->reset = 1;
    top->io_logCtrl_log_begin = 0;
    top->io_logCtrl_log_end = 0;
    top->io_logCtrl_log_level = 0;
    top->io_perfInfo_clean = 0;
    top->io_perfInfo_dump = 0;
    top->io_uart_in_ch = 0;

    // Reset for 100 cycles
    for (int i = 0; i < 100; i++) {
        tick();
    }
    top->reset = 0;

    printf("[FPGA_SIM] Reset done, running simulation...\n");

    // Debug: track device bus activity
    vluint64_t device_read_count = 0;
    vluint64_t device_write_count = 0;
    vluint64_t last_debug_cycle = 0;
    bool first_uart_read = true;
    bool first_uart_write = true;
    bool first_lsr_read = true;

    // Run for up to 50M cycles
    const vluint64_t max_cycles = 20000000;
    for (vluint64_t i = 0; i < max_cycles; i++) {
        tick();

        // Monitor device bus (cbus_crossbar outputs to device)
        // These are internal signals - access via hierarchy
        // device_valid, device_addr, device_wvalid, device_rdata, device_ready

        // Monitor the crossbar's RAM side for instruction fetches
        // We'll check the top-level oreq signals

        // Periodic debug output
        if (i % 5000000 == 0 && i > 0) {
            printf("[FPGA_SIM] Cycle %llu: device_reads=%llu device_writes=%llu\n",
                   (unsigned long long)i,
                   (unsigned long long)device_read_count,
                   (unsigned long long)device_write_count);
        }
    }

    printf("[FPGA_SIM] Simulation finished after %llu cycles\n", (unsigned long long)sim_time);
    printf("[FPGA_SIM] Total device reads: %llu, writes: %llu\n",
           (unsigned long long)device_read_count,
           (unsigned long long)device_write_count);

    top->final();
    delete top;
    return 0;
}
