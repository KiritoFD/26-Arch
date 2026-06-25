#!/bin/bash
# Build and run FPGA simulation using Verilator
# This script should be run from WSL or Linux

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="${PROJECT_DIR}/sim/build_fpga"

echo "=== FPGA Simulation Build Script ==="
echo "Project dir: ${PROJECT_DIR}"
echo "Build dir:   ${BUILD_DIR}"

# Check for Verilator
if ! command -v verilator &> /dev/null; then
    echo "ERROR: verilator not found. Install with: sudo apt install verilator"
    exit 1
fi

# Create build directory
mkdir -p "${BUILD_DIR}"

# Convert kernel.bin to hex for $readmemh
echo "Converting kernel.bin to hex..."
python3 "${SCRIPT_DIR}/bin2hex.py" "${PROJECT_DIR}/third_party/xv6-riscv/kernel/kernel.bin" "${BUILD_DIR}/kernel_hex.txt"

# Convert fs.img to disk hex for simulation disk
echo "Converting fs.img to disk hex..."
if [ -f "${PROJECT_DIR}/third_party/xv6-riscv/fs.img" ]; then
    python3 "${SCRIPT_DIR}/fs2hex.py" "${PROJECT_DIR}/third_party/xv6-riscv/fs.img" "${BUILD_DIR}/disk_hex.txt"
else
    echo "WARNING: fs.img not found, using empty disk"
    python3 -c "open('${BUILD_DIR}/disk_hex.txt','w').write('00000000\n'*256000)"
fi

# Source file list
VSRC_DIR="${PROJECT_DIR}/vsrc"
VIVADO_SRC="${PROJECT_DIR}/vivado/src"

# Collect all Verilog source files
VFILES=(
    "${VSRC_DIR}/SimTopFPGA.sv"
    "${VSRC_DIR}/VTop.sv"
    "${VSRC_DIR}/BehavioralBRAM.sv"
    "${VSRC_DIR}/src/core.sv"
    "${VSRC_DIR}/src/core/core_pkg.sv"
    "${VSRC_DIR}/src/core/core_decode.sv"
    "${VSRC_DIR}/src/core/core_execute.sv"
    "${VSRC_DIR}/src/core/core_mdu.sv"
    "${VSRC_DIR}/src/core/core_csr.sv"
    "${VSRC_DIR}/src/core/core_commit.sv"
    "${VSRC_DIR}/util/IBusToCBus.sv"
    "${VSRC_DIR}/util/DBusToCBus.sv"
    "${VSRC_DIR}/util/CBusArbiter.sv"
    "${VSRC_DIR}/util/mmu.sv"
    "${VIVADO_SRC}/device.sv"
    "${VIVADO_SRC}/spi_flash_disk.sv"
    "${VIVADO_SRC}/with_delay/cbus_crossbar.sv"
)

# Check all files exist
for f in "${VFILES[@]}"; do
    if [ ! -f "$f" ]; then
        echo "ERROR: Source file not found: $f"
        exit 1
    fi
done

# Verilator compilation
echo "Running Verilator..."
cd "${BUILD_DIR}"

verilator \
    --cc \
    --exe \
    --top-module SimTopFPGA \
    +define+VERILATOR=1 \
    +define+FPGA_SIM=1 \
    +define+PRINTF_COND=1 \
    -I"${VSRC_DIR}" \
    -I"${VSRC_DIR}/include" \
    -I"${VIVADO_SRC}" \
    -I"${PROJECT_DIR}/difftest/src/test/vsrc/common" \
    --x-assign unique \
    -O3 \
    -Wno-IMPLICIT \
    -Wno-WIDTH \
    -Wno-UNUSEDSIGNAL \
    -Wno-UNOPTFLAT \
    -Wno-CASEINCOMPLETE \
    -Wno-TIMESCALEMOD \
    -Wno-INITIALDLY \
    -CFLAGS "-g -std=c++17 -I${BUILD_DIR}" \
    -LDFLAGS "-lpthread" \
    -o fpga_sim \
    "${VFILES[@]}" \
    "${SCRIPT_DIR}/fpga_sim_main.cpp"

# Build the executable
echo "Building executable..."
make -C obj_dir -f VSimTopFPGA.mk -j$(nproc)

# Run the simulation
echo "Running simulation..."
cd "${BUILD_DIR}"
cp obj_dir/fpga_sim .
./fpga_sim 2>&1 | tee sim_output.log

echo "=== Simulation complete ==="
echo "Output saved to: ${BUILD_DIR}/sim_output.log"
