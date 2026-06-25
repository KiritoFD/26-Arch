#!/usr/bin/env python3

import time
from pyftdi.spi import SpiController

SPI_FLASH_SIZE = 32 * 1024 * 1024
SECTOR_SIZE = 4096

def main():
    print("Connecting to FTDI device...")
    
    spi = SpiController()
    spi.configure('ftdi://ftdi:2232/1')
    
    slave = spi.get_port(cs=0, freq=1000000)
    
    print("Connected!")
    
    def read_status():
        return slave.exchange([0x05], 1)[0]
    
    def wait_ready():
        while (read_status() & 0x01) != 0:
            time.sleep(0.001)
    
    def read_id():
        data = slave.exchange([0x9F], 3)
        print(f"Flash ID: Manufacturer=0x{data[0]:02X}, Memory=0x{data[1]:02X}, Capacity=0x{data[2]:02X}")
        return data
    
    def write_enable():
        slave.write([0x06])
    
    def erase_sector(addr):
        write_enable()
        slave.write([0x20, (addr >> 16) & 0xFF, (addr >> 8) & 0xFF, addr & 0xFF])
        wait_ready()
    
    def program_page(addr, data):
        write_enable()
        cmd = [0x02, (addr >> 16) & 0xFF, (addr >> 8) & 0xFF, addr & 0xFF]
        cmd.extend(data)
        slave.write(cmd)
        wait_ready()
    
    def read_data(addr, length):
        cmd = [0x03, (addr >> 16) & 0xFF, (addr >> 8) & 0xFF, addr & 0xFF]
        return slave.exchange(cmd, length)
    
    print("Reading flash ID...")
    read_id()
    
    flash_bin_path = r'G:\GitHub\26-Arch\vivado\test-cpu\project\project_3\full_flash.bin'
    print(f"Loading {flash_bin_path}...")
    
    with open(flash_bin_path, 'rb') as f:
        flash_data = f.read()
    
    print(f"Data size: {len(flash_data)} bytes")
    
    print("\nErasing SPI Flash...")
    num_sectors = (len(flash_data) + SECTOR_SIZE - 1) // SECTOR_SIZE
    for i in range(num_sectors):
        addr = i * SECTOR_SIZE
        print(f"  Erasing sector {i}/{num_sectors} (0x{addr:08X})...", end='\r')
        erase_sector(addr)
    print()
    
    print("\nProgramming SPI Flash...")
    addr = 0
    page_size = 256
    while addr < len(flash_data):
        chunk = flash_data[addr:addr + page_size]
        if len(chunk) < page_size:
            chunk = chunk + b'\xFF' * (page_size - len(chunk))
        
        print(f"  Programming address 0x{addr:08X}...", end='\r')
        program_page(addr, chunk)
        addr += page_size
    print()
    
    print("\nVerifying...")
    addr = 0
    errors = 0
    while addr < len(flash_data):
        read_data_chunk = read_data(addr, min(page_size, len(flash_data) - addr))
        expected_chunk = flash_data[addr:addr + len(read_data_chunk)]
        
        if read_data_chunk != expected_chunk:
            errors += 1
            if errors <= 5:
                print(f"  Error at 0x{addr:08X}")
        
        addr += page_size
        print(f"  Verified 0x{addr:08X}...", end='\r')
    print()
    
    if errors == 0:
        print("SUCCESS: SPI Flash programming verified!")
    else:
        print(f"FAILED: {errors} errors found")
    
    spi.terminate()

if __name__ == '__main__':
    main()