TOP    := main_cpu
MOD    := V$(TOP)

NPROC  := $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	ARCH_OPT := -mcpu=native
else
	ARCH_OPT := -march=native
endif

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LIBS   := $(shell sdl2-config --libs)

# --- Verilator Optimizations ---
VFLAGS := -Wno-fatal -Wno-DECLFILENAME -Wno-PINMISSING -Wno-WIDTHTRUNC -Wno-UNOPTFLAT -O3 \
          --x-assign fast --x-initial fast --noassert \
          --threads 1 \
          --inline-mult 1000 \
          --output-split 20000 \
          --output-split-cfuncs 500

PGO_FLAGS ?=

# --- Host C++ Compiler & Linker Flags ---
CXXOPT := -O3 $(ARCH_OPT) -flto=auto -fomit-frame-pointer -fno-stack-protector \
          -fno-plt -DNDEBUG -pipe $(PGO_FLAGS)

.PHONY: all run lint clean pgo-clean pgo-gen pgo-use

# Standard daily build (fast compile, fully optimized without profiling requirement)
all: obj_dir/$(MOD)

obj_dir/$(MOD).mk: sim_main.cpp $(TOP).v
	verilator $(VFLAGS) --cc --exe --top-module $(TOP) \
		sim_main.cpp $(TOP).v \
		-CFLAGS "$(SDL_CFLAGS) $(CXXOPT)" \
		-LDFLAGS "$(SDL_LIBS) $(CXXOPT)"

obj_dir/$(MOD): obj_dir/$(MOD).mk
	$(MAKE) -C obj_dir -f $(MOD).mk \
		OPT_FAST="$(CXXOPT)" OPT_GLOBAL="$(CXXOPT)" LDFLAGS="$(CXXOPT) $(SDL_LIBS)" -j$(NPROC)

run: obj_dir/$(MOD)
	./obj_dir/$(MOD)

lint:
	verilator --lint-only -Wall --top-module $(TOP) $(TOP).v

# --- Profile-Guided Optimization (PGO) ---
pgo-gen:
	@echo "[PGO] Step 1: Building with Profile Generation..."
	rm -rf obj_dir $(CURDIR)/pgo_data
	mkdir -p $(CURDIR)/pgo_data
	$(MAKE) all PGO_FLAGS="-fprofile-generate=$(CURDIR)/pgo_data"
	@echo "[PGO] Step 1 Complete. Run 'make run', let it run 10-15s, and close the window."

pgo-use:
	@echo "[PGO] Step 2: Compiling final build with Profile Feedback..."
	rm -rf obj_dir
	$(MAKE) all PGO_FLAGS="-fprofile-use=$(CURDIR)/pgo_data -fprofile-correction -Wno-error=missing-profile"
	@echo "[PGO] Step 2 Complete! Maximum performance binary generated."

clean:
	rm -rf obj_dir

pgo-clean:
	rm -rf obj_dir pgo_data