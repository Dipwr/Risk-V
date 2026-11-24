#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# --- 1. Parse Flags & Arguments ---
NO_CLIP=0
POS_ARGS=()
for arg in "$@"; do
	if [ "$arg" = "--no-clip" ]; then
		NO_CLIP=1
	else
		POS_ARGS+=("$arg")
	fi
done

# --- 2. Python Detection ---
if [ -f "../.venv/bin/python3" ]; then
	PYTHON_BIN="../.venv/bin/python3"
elif [ -f ".venv/bin/python3" ]; then
	PYTHON_BIN=".venv/bin/python3"
else
	PYTHON_BIN="python3"
fi

# --- 3. Bare-Metal Toolchain Selection ---
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

# --- 4. Target & App Selection ---
TARGET=""
APP_ARG=""

if [ ${#POS_ARGS[@]} -eq 0 ]; then
	TARGETS=($(find bsp -mindepth 1 -maxdepth 1 -type d ! -name include -exec basename {} \; | sort))
	if [ ${#TARGETS[@]} -eq 0 ]; then
		echo "Error: No target BSPs found under bsp/"
		exit 1
	fi
	echo "=== Select Target CPU ==="
	PS3="Choose target number: "
	select t_choice in "${TARGETS[@]}"; do
		if [ -n "$t_choice" ]; then
			TARGET="$t_choice"
			break
		fi
	done

	DIRS=($(find apps -mindepth 1 -maxdepth 1 -type d -exec basename {} \; | sort))
	if [ ${#DIRS[@]} -eq 0 ]; then
		echo "Error: No apps found under apps/"
		exit 1
	fi
	echo "=== Select a Program to Build ==="
	PS3="Choose program number: "
	select a_choice in "${DIRS[@]}"; do
		if [ -n "$a_choice" ]; then
			APP_ARG="$a_choice"
			break
		fi
	done
elif [ ${#POS_ARGS[@]} -eq 1 ]; then
	TARGET="multi_cycle"
	APP_ARG="${POS_ARGS[0]}"
else
	TARGET="${POS_ARGS[0]}"
	APP_ARG="${POS_ARGS[1]}"
fi

BSP_DIR="bsp/$TARGET"
if [ ! -f "$BSP_DIR/target.env" ]; then
	echo "Error: Target BSP '$TARGET' not found (missing $BSP_DIR/target.env)."
	exit 1
fi
# shellcheck source=/dev/null
source "$BSP_DIR/target.env"
TARGET_MARCH="${TARGET_MARCH:-rv32im}"

if [ -d "apps/$APP_ARG" ]; then
	APP_DIR="apps/$APP_ARG"
elif [ -d "$APP_ARG" ]; then
	APP_DIR="$APP_ARG"
else
	echo "Error: App folder '$APP_ARG' not found."
	exit 1
fi

APP_NAME="$(basename "$APP_DIR")"
OUT_DIR="out/$TARGET/$APP_NAME"

echo "=================================================="
echo " Target CPU:       $TARGET ($TARGET_MACRO)"
echo " Target ISA:       $TARGET_MARCH"
echo " Building Project: $APP_DIR"
echo " Output Dir:       $OUT_DIR"
echo " Toolchain:        ${PREFIX}gcc (Newlib-nano Bare-Metal)"
echo "=================================================="

rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"

OBJS=()
CFLAGS=(-march=${TARGET_MARCH} -mabi=ilp32 -O2 "-D${TARGET_MACRO}" -Ibsp/include)

# 1. Collect all app subdirectories as include paths (-I)
INCLUDES=("-I$APP_DIR")
while IFS= read -r dir; do
	INCLUDES+=("-I$dir")
done < <(find "$APP_DIR" -type d)

# 2. Compile all app C files
while IFS= read -r src; do
	rel_path="${src#$APP_DIR/}"
	obj_dir="$OUT_DIR/$(dirname "$rel_path")"
	mkdir -p "$obj_dir"
	obj_name="$OUT_DIR/${rel_path%.c}.o"

	echo "[CC] $src"
	${PREFIX}gcc -c "${CFLAGS[@]}" "${INCLUDES[@]}" "$src" -o "$obj_name"
	OBJS+=("$obj_name")
done < <(find "$APP_DIR" -type f -name "*.c" | sort)

# 3. Assemble all app Assembly files (.S)
while IFS= read -r src; do
	rel_path="${src#$APP_DIR/}"
	obj_dir="$OUT_DIR/$(dirname "$rel_path")"
	mkdir -p "$obj_dir"
	obj_name="$OUT_DIR/${rel_path%.S}.o"

	echo "[AS] $src"
	${PREFIX}as -march=${TARGET_MARCH} -mabi=ilp32 "$src" -o "$obj_name"
	OBJS+=("$obj_name")
done < <(find "$APP_DIR" -type f -name "*.S" | sort)

# 4. Compile BSP HAL & Shared Syscalls
echo "[CC] $BSP_DIR/hal.c"
${PREFIX}gcc -c "${CFLAGS[@]}" "$BSP_DIR/hal.c" -o "$OUT_DIR/hal.o"
OBJS+=("$OUT_DIR/hal.o")

echo "[CC] lib/syscalls.c"
${PREFIX}gcc -c "${CFLAGS[@]}" lib/syscalls.c -o "$OUT_DIR/syscalls.o"
OBJS+=("$OUT_DIR/syscalls.o")

# 5. Assemble Target Boot Wrapper
echo "[AS] $BSP_DIR/boot.s"
${PREFIX}as -march=${TARGET_MARCH} -mabi=ilp32 "$BSP_DIR/boot.s" -o "$OUT_DIR/boot.o"
OBJS+=("$OUT_DIR/boot.o")

# 6. Link Everything (-nostartfiles skips crt0.o and uses target boot.s)
echo "[LD] Linking -> $OUT_DIR/program.elf"
${PREFIX}gcc -march=${TARGET_MARCH} -mabi=ilp32 -T "$BSP_DIR/linker.ld" --specs=nano.specs -nostartfiles -Wl,-m,elf32lriscv \
	"${OBJS[@]}" -lc -lm -lgcc -o "$OUT_DIR/program.elf"

# 7. Generate Binary & Wozmon Hex Payload
${PREFIX}objcopy -O binary "$OUT_DIR/program.elf" "$OUT_DIR/program.bin"
${PYTHON_BIN} tools/bin2hex.py --addr "$WOZMON_ADDR" "$OUT_DIR/program.bin" "$OUT_DIR/program.hex"

if [ "$NO_CLIP" -eq 0 ] && [ -f "tools/paste.py" ]; then
	if ${PYTHON_BIN} tools/paste.py "$OUT_DIR/program.hex"; then
		echo "[CLIPBOARD] Payload ready to paste into Wozmon!"
	else
		echo "[CLIPBOARD] Warning: clipboard copy skipped (no display or pyperclip unavailable)."
	fi
fi

echo "=================================================="
echo " Build Success: $TARGET / $APP_NAME"
echo "=================================================="
