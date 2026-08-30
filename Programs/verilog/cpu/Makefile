TOP    := main_cpu
MOD    := V$(TOP)

# Cross-platform CPU core count detection (Linux 'nproc' vs macOS 'sysctl')
NPROC  := $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Detect OS to select correct host architecture tuning flag (-mcpu vs -march)
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	ARCH_OPT := -mcpu=native
else
	ARCH_OPT := -march=native
endif

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LIBS   := $(shell sdl2-config --libs)

# --- Verilator Optimizations & Warning Suppression ---
VFLAGS := -Wno-fatal -Wno-DECLFILENAME -Wno-PINMISSING -Wno-WIDTHTRUNC -Wno-UNOPTFLAT -O3 \
          --x-assign fast --x-initial fast --noassert \
          --inline-mult 1000 \
          --output-split 20000 \
          --output-split-cfuncs 500

# --- PGO Variable Injection ---
PGO_FLAGS ?=

# --- Host C++ Compiler & Linker Optimizations ---
CXXOPT := -O3 $(ARCH_OPT) -flto -fomit-frame-pointer -fno-stack-protector -DNDEBUG $(PGO_FLAGS)

.PHONY: all run lint verify clean pgo-gen pgo-use

all: obj_dir/$(MOD)

# Step 1: Generate C++ model + makefile
obj_dir/$(MOD).mk: sim_main.cpp $(TOP).v
	verilator $(VFLAGS) --cc --exe --top-module $(TOP) \
		sim_main.cpp $(TOP).v \
		-CFLAGS "$(SDL_CFLAGS) $(CXXOPT)" \
		-LDFLAGS "$(SDL_LIBS) $(CXXOPT)"

# Step 2: Compile native binary
obj_dir/$(MOD): obj_dir/$(MOD).mk
	$(MAKE) -C obj_dir -f $(MOD).mk \
		OPT_FAST="$(CXXOPT)" OPT_GLOBAL="$(CXXOPT)" LDFLAGS="$(CXXOPT) $(SDL_LIBS)" -j$(NPROC)

run: obj_dir/$(MOD)
	./obj_dir/$(MOD)

lint:
	verilator --lint-only -Wall --top-module $(TOP) $(TOP).v

verify: obj_dir/$(MOD).mk
	$(MAKE) -C obj_dir -f $(MOD).mk -Bn \
		OPT_FAST="$(CXXOPT)" OPT_GLOBAL="$(CXXOPT)" \
		| grep -m1 -- '-c ' || echo "(no compile line found -- try 'make clean' first)"

# --- PGO (Profile-Guided Optimization) Automation ---
pgo-gen:
	@echo "[PGO] Building with Profile Generation..."
	$(MAKE) clean
	mkdir -p $(CURDIR)/pgo_data
	$(MAKE) all PGO_FLAGS="-fprofile-generate=$(CURDIR)/pgo_data"
	@echo "[PGO] Step 1 Complete. Now run the emulator (make run) and exit to generate profile data."

pgo-use:
	@echo "[PGO] Building with Profile Data..."
	$(MAKE) clean
	$(MAKE) all PGO_FLAGS="-fprofile-use=$(CURDIR)/pgo_data -fprofile-correction -Wno-error=missing-profile"
	@echo "[PGO] Step 2 Complete. Emulator is now perfectly optimized for your workloads!"

clean:
	rm -rf obj_dir