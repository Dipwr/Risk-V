#!/bin/bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROGRAMS_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
cd "$PROGRAMS_DIR"

CPU_FREQ=84000000
OPT_LEVEL="-O2"

while [[ $# -gt 0 ]]; do
	case "$1" in
		--freq) CPU_FREQ="$2"; shift 2 ;;
		--opt)  OPT_LEVEL="$2"; shift 2 ;;
		*) echo "Unknown option: $1"; exit 1 ;;
	esac
done

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

RT_DIR="$PROGRAMS_DIR/riscv-tests"
DHRY_DIR="$RT_DIR/benchmarks/dhrystone"
if [ ! -f "$DHRY_DIR/dhrystone_main.c" ]; then
	echo "Cloning riscv-tests into $RT_DIR ..."
	git clone --depth 1 https://github.com/riscv-software-src/riscv-tests.git "$RT_DIR"
fi

OUT_DIR="$PROGRAMS_DIR/out/multi_cycle/dhrystone"
rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"

BASE_CFLAGS=(
	-march="${TARGET_MARCH}"
	-mabi=ilp32
	"${OPT_LEVEL}"
	"-D${TARGET_MACRO}"
	"-DCPU_CLK_FREQ=${CPU_FREQ}ULL"
	"-I$SCRIPT_DIR"
	"-I$DHRY_DIR"
	"-I$BSP_DIR/../include"
)

echo "=================================================="
echo " Building Dhrystone 2.2"
echo " ISA:   ${TARGET_MARCH}"
echo " Opt:   ${OPT_LEVEL}"
echo " Clock: ${CPU_FREQ} Hz"
echo "=================================================="

echo "[CC] $DHRY_DIR/dhrystone_main.c"
"${PREFIX}gcc" -c "${BASE_CFLAGS[@]}" -std=gnu89 -Wno-implicit-int -Wno-implicit-function-declaration -Wno-return-type \
	"$DHRY_DIR/dhrystone_main.c" -o "$OUT_DIR/dhrystone_main.o"

echo "[CC] $DHRY_DIR/dhrystone.c"
"${PREFIX}gcc" -c "${BASE_CFLAGS[@]}" -std=gnu89 -Wno-implicit-int -Wno-implicit-function-declaration -Wno-return-type \
	"$DHRY_DIR/dhrystone.c" -o "$OUT_DIR/dhrystone.o"

echo "[CC] $SCRIPT_DIR/dhry_port.c"
"${PREFIX}gcc" -c "${BASE_CFLAGS[@]}" "$SCRIPT_DIR/dhry_port.c" -o "$OUT_DIR/dhry_port.o"

echo "[CC] $BSP_DIR/hal.c"
"${PREFIX}gcc" -c "${BASE_CFLAGS[@]}" "$BSP_DIR/hal.c" -o "$OUT_DIR/hal.o"

echo "[CC] $PROGRAMS_DIR/lib/syscalls.c"
"${PREFIX}gcc" -c "${BASE_CFLAGS[@]}" "$PROGRAMS_DIR/lib/syscalls.c" -o "$OUT_DIR/syscalls.o"

echo "[AS] $BSP_DIR/boot.s"
"${PREFIX}as" -march="${TARGET_MARCH}" -mabi=ilp32 "$BSP_DIR/boot.s" -o "$OUT_DIR/boot.o"

echo "[LD] $OUT_DIR/program.elf"
"${PREFIX}gcc" -march="${TARGET_MARCH}" -mabi=ilp32 -T "$BSP_DIR/linker.ld" \
	--specs=nano.specs -nostartfiles -Wl,-m,elf32lriscv -Wl,-u,_printf_float \
	"$OUT_DIR/boot.o" "$OUT_DIR/dhrystone_main.o" "$OUT_DIR/dhrystone.o" \
	"$OUT_DIR/dhry_port.o" "$OUT_DIR/hal.o" "$OUT_DIR/syscalls.o" \
	-lc -lm -lgcc -o "$OUT_DIR/program.elf"

"${PREFIX}objcopy" -O binary "$OUT_DIR/program.elf" "$OUT_DIR/program.bin"
python3 "$PROGRAMS_DIR/tools/bin2hex.py" --addr "$WOZMON_ADDR" "$OUT_DIR/program.bin" "$OUT_DIR/program.hex"
"${PREFIX}size" "$OUT_DIR/program.elf"
echo "Upload: python3 tools/upload.py out/multi_cycle/dhrystone/program.bin --port /dev/ttyUSB1 --monitor"
