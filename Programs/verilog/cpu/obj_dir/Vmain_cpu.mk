# Verilated -*- Makefile -*-
# DESCRIPTION: Verilator output: Makefile for building Verilated archive or executable
#
# Execute this makefile from the object directory:
#    make -f Vmain_cpu.mk

default: Vmain_cpu

### Constants...
# Perl executable (from $PERL, defaults to 'perl' if not set)
PERL = perl
# Python3 executable (from $PYTHON3, defaults to 'python3' if not set)
PYTHON3 = python3
# Path to Verilator kit (from $VERILATOR_ROOT)
VERILATOR_ROOT = /usr/share/verilator
# SystemC include directory with systemc.h (from $SYSTEMC_INCLUDE)
SYSTEMC_INCLUDE ?=
# SystemC library directory with libsystemc.a (from $SYSTEMC_LIBDIR)
SYSTEMC_LIBDIR ?=

### Switches...
# C++ code coverage  0/1 (from --prof-c)
VM_PROFC = 0
# SystemC output mode?  0/1 (from --sc)
VM_SC = 0
# Legacy or SystemC output mode?  0/1 (from --sc)
VM_SP_OR_SC = $(VM_SC)
# Deprecated
VM_PCLI = 1
# Deprecated: SystemC architecture to find link library path (from $SYSTEMC_ARCH)
VM_SC_TARGET_ARCH = linux

### Vars...
# Design prefix (from --prefix)
VM_PREFIX = Vmain_cpu
# Module prefix (from --prefix)
VM_MODPREFIX = Vmain_cpu
# User CFLAGS (from -CFLAGS on Verilator command line)
VM_USER_CFLAGS = \
  -I/usr/include/SDL2 -D_GNU_SOURCE=1 -D_REENTRANT -O3 -march=native -flto=auto -fomit-frame-pointer -fno-stack-protector -fno-plt -DNDEBUG -pipe -fprofile-use=/home/dpa/Documents/code/Digital_Logic/Digital/Risk-V/Programs/verilog/cpu/pgo_data -fprofile-correction -Wno-error=missing-profile \

# User LDLIBS (from -LDFLAGS on Verilator command line)
VM_USER_LDLIBS = \
  -lSDL2 -O3 -march=native -flto=auto -fomit-frame-pointer -fno-stack-protector -fno-plt -DNDEBUG -pipe -fprofile-use=/home/dpa/Documents/code/Digital_Logic/Digital/Risk-V/Programs/verilog/cpu/pgo_data -fprofile-correction -Wno-error=missing-profile \

# User .cpp files (from .cpp's on Verilator command line)
VM_USER_CLASSES = \
  sim_main \

# User .cpp directories (from .cpp's on Verilator command line)
VM_USER_DIR = \
  .. \

### Default rules...
# Include list of all generated classes
include Vmain_cpu_classes.mk
# Include global rules
include $(VERILATOR_ROOT)/include/verilated.mk

### Executable rules... (from --exe)
VPATH += $(VM_USER_DIR)

sim_main.o: sim_main.cpp 
	$(OBJCACHE) $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST)  -c -o $@ $<

### Link rules... (from --exe)
Vmain_cpu: $(VK_USER_OBJS) $(VK_GLOBAL_OBJS) $(VM_PREFIX)__ALL.a
	$(LINK) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) $(LIBS) $(SC_LIBS) -o $@

# Verilated -*- Makefile -*-
