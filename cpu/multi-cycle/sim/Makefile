TOP := arty_a7_top
MOD := V$(TOP)

CPU_CLK_FREQ ?= 25000000
UART_BAUD    ?= 115200

NPROC := $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	ARCH_OPT     := -mcpu=native
	LTO_FLAGS    := -flto=thin
	EXTRA_CXXOPT :=
else
	ARCH_OPT     := -march=native
	LTO_FLAGS    := -flto=auto
	EXTRA_CXXOPT := -fomit-frame-pointer -fno-stack-protector -fno-plt
endif

SDL_CFLAGS := $(shell sdl2-config --cflags 2>/dev/null || pkg-config --cflags sdl2)
SDL_LIBS   := $(shell sdl2-config --libs 2>/dev/null || pkg-config --libs sdl2)

# Auto-detect RISC-V bare-metal toolchain for building boot.mem
RISCV_PREFIX := $(shell \
	for p in riscv-none-elf- riscv64-unknown-elf- riscv64-elf- riscv32-unknown-elf- riscv64-linux-gnu-; do \
		if command -v $${p}gcc >/dev/null 2>&1; then echo $$p; break; fi; \
	done)
RISCV_GCC     := $(RISCV_PREFIX)gcc
RISCV_OBJCOPY := $(RISCV_PREFIX)objcopy
PYTHON        := $(shell if [ -x ../../../.venv/bin/python3 ]; then echo ../../../.venv/bin/python3; else echo python3; fi)

BOOT_ASM := ../../../Programs/bootloaders/multi_cycle/visual_wozmon320x200.s
CORE_DIR := ../core

SV_SRCS := \
	sim.vlt \
	clk_wiz_0.sv \
	$(CORE_DIR)/rv32_pkg.sv \
	$(CORE_DIR)/alu.sv \
	$(CORE_DIR)/bram_ram.sv \
	$(CORE_DIR)/control_fsm.sv \
	$(CORE_DIR)/datapath.sv \
	$(CORE_DIR)/div_unit.sv \
	$(CORE_DIR)/imm_gen.sv \
	$(CORE_DIR)/mul_unit.sv \
	$(CORE_DIR)/regfile.sv \
	$(CORE_DIR)/rv32_core.sv \
	$(CORE_DIR)/uart.sv \
	$(CORE_DIR)/vga_controller.sv \
	$(CORE_DIR)/vram.sv \
	$(CORE_DIR)/soc_top.sv \
	$(CORE_DIR)/arty_a7_top.sv

CORE_ONLY_SV := $(filter-out sim.vlt clk_wiz_0.sv $(CORE_DIR)/soc_top.sv $(CORE_DIR)/arty_a7_top.sv,$(SV_SRCS))
SOC_ONLY_SV  := $(CORE_ONLY_SV) $(CORE_DIR)/soc_top.sv

# Default to --x-assign fast / --x-initial fast for simulation throughput;
# use 'make strict' to rebuild with --x-assign unique / --x-initial unique.
X_MODE ?= fast
VFLAGS ?= -O3 --x-assign $(X_MODE) --x-initial $(X_MODE) --noassert \
          --threads 1 \
          --inline-mult 1000 \
          --output-split 20000 \
          --output-split-cfuncs 500 \
          -GCPU_CLK_FREQ=$(CPU_CLK_FREQ) \
          -GUART_BAUD=$(UART_BAUD)

PGO_FLAGS ?=

CXXOPT := -O3 $(ARCH_OPT) $(LTO_FLAGS) $(EXTRA_CXXOPT) -DNDEBUG -pipe \
          -Wall -Wextra \
          -DCPU_CLK_FREQ=$(CPU_CLK_FREQ)ULL \
          -DUART_BAUD=$(UART_BAUD)ULL \
          $(PGO_FLAGS)

ifeq ($(UNAME_S), Darwin)
	LDLIBS := $(SDL_LIBS) -lpthread
else
	LDLIBS := $(SDL_LIBS) -lutil -lpthread
endif

.PHONY: all strict run run-pin lint pgo-gen pgo-use clean pgo-clean

all: boot.mem obj_dir/$(MOD)

strict:
	rm -rf obj_dir
	$(MAKE) all X_MODE=unique

boot.mem: $(BOOT_ASM) gen_boot_mem.py
	@if [ -z "$(RISCV_PREFIX)" ]; then \
		echo "Error: No RISC-V GCC toolchain found in PATH to build boot.mem."; \
		exit 1; \
	fi
	$(RISCV_GCC) -march=rv32im -mabi=ilp32 -nostdlib -nostartfiles -Wl,-Ttext=0x0 -o boot.elf $<
	$(RISCV_OBJCOPY) -O binary boot.elf boot.bin
	$(PYTHON) gen_boot_mem.py boot.bin $@
	rm -f boot.elf boot.bin

obj_dir/$(MOD).mk: sim_main.cpp $(SV_SRCS)
	verilator $(VFLAGS) --cc --exe --top-module $(TOP) \
		$(SV_SRCS) sim_main.cpp \
		-CFLAGS "$(SDL_CFLAGS) $(CXXOPT)" \
		-LDFLAGS "$(LDLIBS) $(CXXOPT)"

obj_dir/$(MOD): obj_dir/$(MOD).mk sim_main.cpp $(SV_SRCS)
	$(MAKE) -C obj_dir -f $(MOD).mk \
		OPT_FAST="$(CXXOPT)" OPT_GLOBAL="$(CXXOPT)" LDFLAGS="$(CXXOPT) $(LDLIBS)" -j$(NPROC)

run: all
	./obj_dir/$(MOD)

run-pin: all
	./obj_dir/$(MOD) --vga-mode pin

lint:
	verilator --lint-only --top-module rv32_core $(CORE_ONLY_SV)
	verilator --lint-only --top-module soc_top $(SOC_ONLY_SV)
	verilator --lint-only --top-module $(TOP) $(SV_SRCS)

pgo-gen:
	@echo "[PGO] Step 1: Building with Profile Generation..."
	rm -rf obj_dir $(CURDIR)/pgo_data
	mkdir -p $(CURDIR)/pgo_data
ifeq ($(UNAME_S), Darwin)
	$(MAKE) all PGO_FLAGS="-fprofile-instr-generate=$(CURDIR)/pgo_data/default-%p.profraw"
else
	$(MAKE) all PGO_FLAGS="-fprofile-generate=$(CURDIR)/pgo_data"
endif
	@echo "[PGO] Step 1 Complete. Run 'make run', let it run 10-15s, and close the window."

pgo-use:
	@echo "[PGO] Step 2: Compiling final build with Profile Feedback..."
	rm -rf obj_dir
ifeq ($(UNAME_S), Darwin)
	xcrun llvm-profdata merge -output=$(CURDIR)/pgo_data/merged.profdata $(CURDIR)/pgo_data/*.profraw
	$(MAKE) all PGO_FLAGS="-fprofile-instr-use=$(CURDIR)/pgo_data/merged.profdata"
else
	$(MAKE) all PGO_FLAGS="-fprofile-use=$(CURDIR)/pgo_data -fprofile-correction -Wno-error=missing-profile"
endif
	@echo "[PGO] Step 2 Complete! Maximum performance binary generated."

clean:
	rm -rf obj_dir boot.elf boot.bin boot.mem

pgo-clean:
	rm -rf obj_dir pgo_data boot.elf boot.bin boot.mem
