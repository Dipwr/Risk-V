#!/bin/bash
set -e

echo "=== Building C Program for RISC-V Core ==="

# Detect Python interpreter (prefer project venv if present, else system python)
if [ -f "../.venv/bin/python3" ]; then
	PYTHON_BIN="../.venv/bin/python3"
elif [ -f ".venv/bin/python3" ]; then
	PYTHON_BIN=".venv/bin/python3"
else
	PYTHON_BIN="python3"
fi

# Auto-detect RISC-V toolchain prefix across macOS and Fedora
if command -v riscv64-elf-gcc &> /dev/null; then
	PREFIX="riscv64-elf-"
elif command -v riscv64-unknown-elf-gcc &> /dev/null; then
	PREFIX="riscv64-unknown-elf-"
elif command -v riscv64-linux-gnu-gcc &> /dev/null; then
	PREFIX="riscv64-linux-gnu-"
else
	echo "Error: No supported RISC-V GCC toolchain found in PATH."
	exit 1
fi

echo "Using toolchain: ${PREFIX}gcc"
echo "Using python: ${PYTHON_BIN}"

# Create output directory if it doesn't exist
mkdir -p out

# 1. Compile C source to object file in out/
${PREFIX}gcc -c -march=rv32im -mabi=ilp32 -O2 -ffreestanding main.c -o out/main.o

# 2. Assemble boot wrapper into out/
${PREFIX}as -march=rv32im -mabi=ilp32 boot.s -o out/boot.o

# 3. Link objects using root linker.ld into out/program.elf
${PREFIX}gcc -march=rv32im -mabi=ilp32 -T ./linker.ld -nostdlib -Wl,-m,elf32lriscv out/boot.o out/main.o -o out/program.elf

# 4. Extract raw binary payload into out/
${PREFIX}objcopy -O binary out/program.elf out/program.bin

# 5. Convert binary to space-separated hex in out/
${PYTHON_BIN} bin2hex.py out/program.bin out/program.hex

# 6. Copy program hex to clipboard via paste.py
echo "=== Copying program hex to clipboard ==="
${PYTHON_BIN} ../paste.py out/program.hex

echo "=== Success! Build complete and hex payload ready in clipboard ==="