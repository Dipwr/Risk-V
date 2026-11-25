#!/bin/bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROGRAMS_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
cd "$PROGRAMS_DIR"

ITERATIONS=50
CPU_FREQ=84000000
OPT_LEVEL="-O2"

while [[ $# -gt 0 ]]; do
	case "$1" in
		--iterations) ITERATIONS="$2"; shift 2 ;;
		--freq)       CPU_FREQ="$2"; shift 2 ;;
		--opt)        OPT_LEVEL="$2"; shift 2 ;;
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

CM_DIR="$PROGRAMS_DIR/third_party/coremark"
if [ ! -f "$CM_DIR/core_main.c" ]; then
	echo "Cloning eembc/coremark into $CM_DIR ..."
	mkdir -p "$PROGRAMS_DIR/third_party"
	git clone --depth 1 https://github.com/eembc/coremark.git "$CM_DIR"
fi

OUT_DIR="$PROGRAMS_DIR/out/multi_cycle/coremark"
rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"

FLAGS_STR="-march=${TARGET_MARCH} -mabi=ilp32 ${OPT_LEVEL}"
CFLAGS=(
	-march="${TARGET_MARCH}"
	-mabi=ilp32
	"${OPT_LEVEL}"
	"-D${TARGET_MACRO}"
	"-DITERATIONS=${ITERATIONS}"
	"-DCPU_CLK_FREQ=${CPU_FREQ}ULL"
	"-DFLAGS_STR=\"${FLAGS_STR}\""
	"-I$SCRIPT_DIR"
	"-I$CM_DIR"
	"-I$BSP_DIR/../include"
)

SRCS=(
	"$CM_DIR/core_list_join.c"
	"$CM_DIR/core_main.c"
	"$CM_DIR/core_matrix.c"
	"$CM_DIR/core_state.c"
	"$CM_DIR/core_util.c"
	"$SCRIPT_DIR/core_portme.c"
	"$BSP_DIR/hal.c"
	"$PROGRAMS_DIR/lib/syscalls.c"
)

OBJS=()
echo "=================================================="
echo " Building EEMBC CoreMark"
echo " ISA:        ${TARGET_MARCH}"
echo " Opt:        ${OPT_LEVEL}"
echo " Iterations: ${ITERATIONS}"
echo " Clock:      ${CPU_FREQ} Hz"
echo "=================================================="

for src in "${SRCS[@]}"; do
	obj="$OUT_DIR/$(basename "${src%.c}").o"
	echo "[CC] $src"
	"${PREFIX}gcc" -c "${CFLAGS[@]}" "$src" -o "$obj"
	OBJS+=("$obj")
done

echo "[AS] $BSP_DIR/boot.s"
"${PREFIX}as" -march="${TARGET_MARCH}" -mabi=ilp32 "$BSP_DIR/boot.s" -o "$OUT_DIR/boot.o"
OBJS+=("$OUT_DIR/boot.o")

echo "[LD] $OUT_DIR/program.elf"
"${PREFIX}gcc" -march="${TARGET_MARCH}" -mabi=ilp32 -T "$BSP_DIR/linker.ld" \
	--specs=nano.specs -nostartfiles -Wl,-m,elf32lriscv -Wl,-u,_printf_float \
	"${OBJS[@]}" -lc -lm -lgcc -o "$OUT_DIR/program.elf"

"${PREFIX}objcopy" -O binary "$OUT_DIR/program.elf" "$OUT_DIR/program.bin"
python3 "$PROGRAMS_DIR/tools/bin2hex.py" --addr "$WOZMON_ADDR" "$OUT_DIR/program.bin" "$OUT_DIR/program.hex"
"${PREFIX}size" "$OUT_DIR/program.elf"
echo "Upload: python3 tools/upload.py out/multi_cycle/coremark/program.bin --port /dev/ttyUSB1 --monitor"
