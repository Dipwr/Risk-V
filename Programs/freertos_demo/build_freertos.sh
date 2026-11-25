#!/bin/bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROGRAMS_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$PROGRAMS_DIR"

if command -v riscv-none-elf-gcc &> /dev/null; then
	PREFIX="riscv-none-elf-"
elif command -v riscv64-unknown-elf-gcc &> /dev/null; then
	PREFIX="riscv64-unknown-elf-"
elif command -v riscv32-unknown-elf-gcc &> /dev/null; then
	PREFIX="riscv32-unknown-elf-"
else
	echo "Error: No supported RISC-V GCC toolchain found in PATH."
	exit 1
fi

BSP_DIR="$PROGRAMS_DIR/bsp/multi_cycle"
# shellcheck source=/dev/null
source "$BSP_DIR/target.env"
TARGET_MARCH="${TARGET_MARCH:-rv32im_zicsr_zicntr}"

KERNEL_DIR="$PROGRAMS_DIR/third_party/FreeRTOS-Kernel"
if [ ! -d "$KERNEL_DIR/include" ]; then
	echo "Cloning FreeRTOS-Kernel V11.1.0 into $KERNEL_DIR ..."
	mkdir -p "$PROGRAMS_DIR/third_party"
	git clone --depth 1 --branch V11.1.0 https://github.com/FreeRTOS/FreeRTOS-Kernel.git "$KERNEL_DIR"
fi

OUT_DIR="$PROGRAMS_DIR/out/multi_cycle/freertos_demo"
rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"

PORT_DIR="$KERNEL_DIR/portable/GCC/RISC-V"
CHIP_EXT_DIR="$PORT_DIR/chip_specific_extensions/RV32I_CLINT_no_extensions"

INCLUDES=(
	"-I$SCRIPT_DIR"
	"-I$BSP_DIR/../include"
	"-I$KERNEL_DIR/include"
	"-I$PORT_DIR"
	"-I$CHIP_EXT_DIR"
)

CFLAGS=(
	-march="${TARGET_MARCH}"
	-mabi=ilp32
	-O2
	"-D${TARGET_MACRO}"
	-DportasmHANDLE_INTERRUPT=freertos_unhandled_irq
	"${INCLUDES[@]}"
)

ASFLAGS=(
	-march="${TARGET_MARCH}"
	-mabi=ilp32
	-DportasmHANDLE_INTERRUPT=freertos_unhandled_irq
	"${INCLUDES[@]}"
)

SRCS_C=(
	"$SCRIPT_DIR/main.c"
	"$KERNEL_DIR/tasks.c"
	"$KERNEL_DIR/queue.c"
	"$KERNEL_DIR/list.c"
	"$KERNEL_DIR/portable/MemMang/heap_4.c"
	"$PORT_DIR/port.c"
	"$BSP_DIR/hal.c"
	"$PROGRAMS_DIR/lib/syscalls.c"
)

OBJS=()
echo "=================================================="
echo " Building FreeRTOS V11.1.0 Cooperative Demo"
echo " ISA:    ${TARGET_MARCH}"
echo " Output: ${OUT_DIR}"
echo "=================================================="

for src in "${SRCS_C[@]}"; do
	obj="$OUT_DIR/$(basename "${src%.c}").o"
	echo "[CC] $src"
	"${PREFIX}gcc" -c "${CFLAGS[@]}" "$src" -o "$obj"
	OBJS+=("$obj")
done

echo "[AS] $PORT_DIR/portASM.S"
"${PREFIX}gcc" -c "${ASFLAGS[@]}" "$PORT_DIR/portASM.S" -o "$OUT_DIR/portASM.o"
OBJS+=("$OUT_DIR/portASM.o")

echo "[AS] $BSP_DIR/boot.s"
"${PREFIX}as" -march="${TARGET_MARCH}" -mabi=ilp32 "$BSP_DIR/boot.s" -o "$OUT_DIR/boot.o"
OBJS+=("$OUT_DIR/boot.o")

echo "[LD] $OUT_DIR/program.elf"
"${PREFIX}gcc" -march="${TARGET_MARCH}" -mabi=ilp32 -T "$BSP_DIR/linker.ld" \
	--specs=nano.specs -nostartfiles -Wl,-m,elf32lriscv \
	"${OBJS[@]}" -lc -lm -lgcc -o "$OUT_DIR/program.elf"

"${PREFIX}objcopy" -O binary "$OUT_DIR/program.elf" "$OUT_DIR/program.bin"
python3 "$PROGRAMS_DIR/tools/bin2hex.py" --addr "$WOZMON_ADDR" "$OUT_DIR/program.bin" "$OUT_DIR/program.hex"
"${PREFIX}size" "$OUT_DIR/program.elf"
echo "Upload: python3 tools/upload.py out/multi_cycle/freertos_demo/program.bin --port /dev/ttyUSB1"
