#!/bin/bash
set -e

# --- 1. Python Detection ---
if [ -f "../.venv/bin/python3" ]; then
	PYTHON_BIN="../.venv/bin/python3"
elif [ -f ".venv/bin/python3" ]; then
	PYTHON_BIN=".venv/bin/python3"
else
	PYTHON_BIN="python3"
fi

# --- 2. Bare-Metal Toolchain Selection ---
if command -v riscv-none-elf-gcc &> /dev/null; then
	PREFIX="riscv-none-elf-"
elif command -v riscv64-unknown-elf-gcc &> /dev/null; then
	PREFIX="riscv64-unknown-elf-"
elif command -v riscv64-elf-gcc &> /dev/null; then
	PREFIX="riscv64-elf-"
elif command -v riscv32-unknown-elf-gcc &> /dev/null; then
	PREFIX="riscv32-unknown-elf-"
elif command -v riscv64-linux-gnu-gcc &> /dev/null; then
	PREFIX="riscv64-linux-gnu-"
else
	echo "Error: No supported RISC-V GCC toolchain found in PATH."
	exit 1
fi

TARGET="$1"

if [ -z "$TARGET" ]; then
	if [ -d "programs" ]; then
		DIRS=($(find programs -mindepth 1 -maxdepth 1 -type d))
		if [ ${#DIRS[@]} -eq 0 ]; then
			echo "Error: No subfolders found in programs/"
			exit 1
		elif [ ${#DIRS[@]} -eq 1 ]; then
			TARGET="${DIRS[0]}"
		else
			echo "=== Select a Program to Build ==="
			PS3="Choose program number: "
			select choice in "${DIRS[@]#programs/}"; do
				TARGET="programs/$choice"
				break
			done
		fi
	fi
fi

if [ -d "programs/$TARGET" ]; then
	APP_DIR="programs/$TARGET"
elif [ -d "$TARGET" ]; then
	APP_DIR="$TARGET"
else
	echo "Error: App folder '$TARGET' not found."
	exit 1
fi

echo "=================================================="
echo " Building Project: $APP_DIR"
echo " Toolchain:        ${PREFIX}gcc (Newlib-nano Bare-Metal)"
echo "=================================================="

rm -rf out
mkdir -p out

OBJS=()

# 1. Automatically collect all subdirectories as include paths (-I)
INCLUDES=("-I$APP_DIR")
while IFS= read -r dir; do
	INCLUDES+=("-I$dir")
done < <(find "$APP_DIR" -type d)

# 2. Recursively find and compile all C files
while IFS= read -r src; do
	# Mirror directory structure in out/
	rel_path="${src#$APP_DIR/}"
	obj_dir="out/$(dirname "$rel_path")"
	mkdir -p "$obj_dir"
	obj_name="out/${rel_path%.c}.o"

	echo "[CC] $src"
	${PREFIX}gcc -c -march=rv32im -mabi=ilp32 -O2 "${INCLUDES[@]}" "$src" -o "$obj_name"
	OBJS+=("$obj_name")
done < <(find "$APP_DIR" -type f -name "*.c")

# 3. Recursively find and assemble all Assembly files (.S)
while IFS= read -r src; do
	rel_path="${src#$APP_DIR/}"
	obj_dir="out/$(dirname "$rel_path")"
	mkdir -p "$obj_dir"
	obj_name="out/${rel_path%.S}.o"

	echo "[AS] $src"
	${PREFIX}as -march=rv32im -mabi=ilp32 "$src" -o "$obj_name"
	OBJS+=("$obj_name")
done < <(find "$APP_DIR" -type f -name "*.S")

# Compile Shared Syscalls Bridge
if [ -f "syscalls.c" ]; then
	echo "[CC] syscalls.c"
	${PREFIX}gcc -c -march=rv32im -mabi=ilp32 -O2 syscalls.c -o out/syscalls.o
	OBJS+=("out/syscalls.o")
fi

# Assemble Boot Wrapper
if [ -f "boot.s" ]; then
	echo "[AS] boot.s"
	${PREFIX}as -march=rv32im -mabi=ilp32 boot.s -o out/boot.o
	OBJS+=("out/boot.o")
fi

# Link Everything (-nostartfiles skips crt0.o and uses our custom boot.s)
echo "[LD] Linking -> out/program.elf"
${PREFIX}gcc -march=rv32im -mabi=ilp32 -T ./linker.ld --specs=nano.specs -nostartfiles -Wl,-m,elf32lriscv \
	"${OBJS[@]}" -lc -lm -lgcc -o out/program.elf

# Generate Payload
${PREFIX}objcopy -O binary out/program.elf out/program.bin
${PYTHON_BIN} bin2hex.py out/program.bin out/program.hex

if [ -f "../paste.py" ]; then
	${PYTHON_BIN} ../paste.py out/program.hex
	echo "[CLIPBOARD] Payload ready to paste into Wozmon!"
elif [ -f "paste.py" ]; then
	${PYTHON_BIN} paste.py out/program.hex
	echo "[CLIPBOARD] Payload ready to paste into Wozmon!"
fi

echo "=================================================="
echo " Build Success: $(basename "$APP_DIR")"
echo "=================================================="