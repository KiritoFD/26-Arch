#!/usr/bin/env python3
"""Generate Intel MCS file for Basys3 SPI Flash.
Contains bitstream at offset 0 and fs.img at offset 0x400000.
Uses standard Intel MCS format with extended linear address records.
"""

import sys

def write_mcs_record(f, addr_lo, data, rec_type=0x00):
    """Write a single MCS record."""
    length = len(data)
    checksum = length + (addr_lo >> 8) + (addr_lo & 0xFF) + rec_type
    hex_data = ""
    for b in data:
        checksum += b
        hex_data += f"{b:02X}"
    checksum = (~checksum + 1) & 0xFF
    f.write(f":{length:02X}{addr_lo:04X}{rec_type:02X}{hex_data}{checksum:02X}\n")

def write_extended_addr(f, addr_hi):
    """Write extended linear address record (Type 04)."""
    checksum = 0x02 + 0x00 + 0x00 + 0x04 + (addr_hi >> 8) + (addr_hi & 0xFF)
    checksum = (~checksum + 1) & 0xFF
    f.write(f":02000004{addr_hi:04X}{checksum:02X}\n")

def main():
    bitstream_path = r'G:\GitHub\26-Arch\vivado\test-cpu\project\project_3\project_3.runs\impl_1\basys3_top.bit'
    fs_img_path = r'G:\GitHub\26-Arch\third_party\xv6-riscv\fs.img'
    mcs_file_path = r'G:\GitHub\26-Arch\vivado\test-cpu\project\project_3\full_flash.mcs'

    print(f"Loading bitstream: {bitstream_path}")
    with open(bitstream_path, 'rb') as f:
        bitstream_data = f.read()

    print(f"Loading fs.img: {fs_img_path}")
    with open(fs_img_path, 'rb') as f:
        fs_data = f.read()

    print(f"Bitstream size: {len(bitstream_data)} bytes ({len(bitstream_data)/1024:.1f} KB)")
    print(f"fs.img size: {len(fs_data)} bytes ({len(fs_data)/1024:.1f} KB)")

    fs_offset = 0x00400000  # 4MB offset

    # Build list of (offset, data) segments
    segments = [
        (0, bitstream_data),
        (fs_offset, fs_data),
    ]

    print(f"Creating MCS file: {mcs_file_path}")
    record_count = 0

    with open(mcs_file_path, 'w') as f:
        f.write("// MCS file for Basys3 SPI Flash (N25Q032, 32MB)\n")
        f.write("// Contains: bitstream at 0x0, fs.img at 0x400000\n\n")

        current_ext_addr = -1  # force first extended address record

        for seg_offset, seg_data in segments:
            pos = 0
            while pos < len(seg_data):
                abs_addr = seg_offset + pos
                ext_addr = (abs_addr >> 16) & 0xFFFF
                addr_lo = abs_addr & 0xFFFF

                # Write extended linear address record if needed
                if ext_addr != current_ext_addr:
                    write_extended_addr(f, ext_addr)
                    current_ext_addr = ext_addr
                    record_count += 1

                # Calculate how many bytes fit in this record
                bytes_left_in_seg = len(seg_data) - pos
                bytes_to_eob = 0x10000 - addr_lo  # end of 64KB block
                chunk_len = min(16, bytes_left_in_seg, bytes_to_eob)

                chunk = seg_data[pos:pos + chunk_len]
                write_mcs_record(f, addr_lo, chunk)
                record_count += 1

                pos += chunk_len

        # End-of-file record
        f.write(":00000001FF\n")
        record_count += 1

    mcs_size = len(open(mcs_file_path, 'rb').read())
    print(f"MCS file created: {mcs_size} bytes ({mcs_size/1024/1024:.1f} MB)")
    print(f"Total records: {record_count}")

if __name__ == '__main__':
    main()
