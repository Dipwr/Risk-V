#!/bin/bash
set -e

echo "=== Building C Program for RISC-V Core ==="

# Create output directory if it doesn't exist
mkdir -p out

# 1. Compile C source to object file in out/
riscv64-elf-gcc -c -march=rv32i -mabi=ilp32 -O2 -ffreestanding main.c -o out/main.o

# 2. Assemble boot wrapper into out/
riscv64-elf-as -march=rv32i -mabi=ilp32 boot.s -o out/boot.o

# 3. Link objects using root linker.ld into out/program.elf
riscv64-elf-gcc -T ./linker.ld -nostdlib -Wl,-m,elf32lriscv out/boot.o out/main.o -o out/program.elf

# 4. Extract raw binary payload into out/
riscv64-elf-objcopy -O binary out/program.elf out/program.bin

# 5. Convert binary to space-separated hex in out/
python3 bin2hex.py out/program.bin out/program.hex

# 6. Run paste.py located one directory up
echo "=== Copying to clipboard via paste.py ==="
python3 ../paste.py out/program.hex

echo "=== Success! Output generated and processed ==="