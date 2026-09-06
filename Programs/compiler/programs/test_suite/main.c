/* ============================================================================
 * RISC-V ARCHITECTURAL VERIFICATION SUITE (RV32IM)
 * Based on the Official RISC-V Architecture Test Specifications
 * ============================================================================
 * Target: Custom Bare-Metal RV32IM Processor (Digilent Arty A7-100T)
 * Load Address: 0x00010000 | Stack Pointer: 0x0003FFF0
 *
 * Test Suite Breakdown:
 *  - [001..004] arch-test/I: x0 Hardwired Zero Immutability
 *  - [005..010] arch-test/I: LUI & AUIPC Upper Immediate Arithmetic
 *  - [011..024] arch-test/I: I-Type Arithmetic & Logical Boundaries
 *  - [025..036] arch-test/I: Shift Instructions & 5-bit Shamt Masking
 *  - [037..048] arch-test/I: R-Type Arithmetic & Logical Comparisons
 *  - [049..064] arch-test/I: Branch Condition Matrix (Taken / Not-Taken /
 * Signs)
 *  - [065..070] arch-test/I: JAL & JALR Link Register & Alignment
 *  - [071..086] arch-test/I: Memory Load/Store & Byte-Lane Isolation
 *  - [087..102] arch-test/M: Multiplier Suite (MUL, MULH, MULHU, MULHSU)
 *  - [103..120] arch-test/M: Divider & Modulo Suite (Milestone 202)
 * ============================================================================
 */

#include <stdint.h>

/* Set to 1 once Milestone 202 multi-cycle divider is implemented in RTL */
#define ENABLE_DIV_REM_TESTS 0

#if ENABLE_DIV_REM_TESTS
#define TOTAL_TEST_COUNT 120
#else
#define TOTAL_TEST_COUNT 102
#endif

/* MMIO Register Definitions */
#define UART_DATA ((volatile uint32_t *)0x20000000)
#define UART_STATUS ((volatile uint32_t *)0x20000004)
#define PAGE_REG ((volatile uint32_t *)0x20000008)
#define GRAPHIC_RAM ((volatile uint16_t *)0x10000000)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define PAGE_PIXELS (SCREEN_WIDTH * SCREEN_HEIGHT) // 64,000 pixels
#define PAGE_STRIDE 65536 // 128 KB page stride (32,768 words)

/* RGB565 Palette */
#define COLOR_BLACK ((uint16_t)0x0000)
#define COLOR_WHITE ((uint16_t)0xFFFF)
#define COLOR_RED ((uint16_t)0xF800)
#define COLOR_GREEN ((uint16_t)0x07E0)
#define COLOR_BLUE ((uint16_t)0x001F)
#define COLOR_NAVY ((uint16_t)0x000E)
#define COLOR_DARK_GRAY ((uint16_t)0x18C3)

static uint32_t g_pass_count = 0;
static uint32_t g_fail_count = 0;
static uint32_t g_test_index = 0;

static uint32_t mem_test_buffer[8] __attribute__((aligned(16)));

/* ============================================================================
 * TERMINAL & GRAPHICS DRIVERS
 * ============================================================================
 */

static void print_char(char c) {
  // Auto-inject carriage return before newline for terminal formatting
  if (c == '\n') {
    while (!(*UART_STATUS & 0x02))
      ;
    *UART_DATA = (uint32_t)'\r';
  }
  while (!(*UART_STATUS & 0x02))
    ; // Wait until TX ready (bit 1)
  *UART_DATA = (uint32_t)(uint8_t)c;
}

static void print_string(const char *str) {
  while (*str) {
    print_char(*str++);
  }
}

static void print_dec(uint32_t val) {
  char buf[12];
  int i = 0;
  if (val == 0) {
    print_char('0');
    return;
  }
  while (val > 0) {
    buf[i++] = (val % 10) + '0';
    val /= 10;
  }
  while (i > 0) {
    print_char(buf[--i]);
  }
}

static void print_hex32(uint32_t val) {
  const char hex_digits[] = "0123456789ABCDEF";
  print_string("0x");
  for (int i = 7; i >= 0; i--) {
    print_char(hex_digits[(val >> (i * 4)) & 0xF]);
  }
}

static inline void put_pixel(int page, int x, int y, uint16_t color) {
  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
    GRAPHIC_RAM[(page * PAGE_STRIDE) + (y * SCREEN_WIDTH) + x] = color;
  }
}

static void fill_rect(int page, int x, int y, int w, int h, uint16_t color) {
  for (int j = 0; j < h; j++) {
    for (int i = 0; i < w; i++) {
      put_pixel(page, x + i, y + j, color);
    }
  }
}

static void clear_page(int page, uint16_t color) {
  for (int i = 0; i < PAGE_PIXELS; i++) {
    GRAPHIC_RAM[(page * PAGE_STRIDE) + i] = color;
  }
}

static inline int is_key_available(void) {
  return (*UART_STATUS & 0x01); // Bit 0 is RX ready
}

static inline char read_key(void) {
  while (!is_key_available())
    ;
  return (char)(*UART_DATA & 0xFF);
}

/* Draws a 12-column test status matrix */
static void record_test_visual(int test_id, int passed) {
  int col = test_id % 12;
  int row = test_id / 12;
  int x = 16 + col * 24;
  int y = 35 + row * 12;
  uint16_t color = passed ? COLOR_GREEN : COLOR_RED;

  fill_rect(0, x, y, 22, 10, color);
}

/* Master Assertion */
static void assert_test(const char *name, uint32_t actual, uint32_t expected) {
  int passed = (actual == expected);

  print_string("  [");
  if (g_test_index + 1 < 10)
    print_char('0');
  if (g_test_index + 1 < 100)
    print_char('0');
  print_dec(g_test_index + 1);
  print_string("] ");
  print_string(name);
  print_string(" ... ");

  if (passed) {
    print_string("PASS\n");
    g_pass_count++;
  } else {
    print_string("FAIL! Expected: ");
    print_hex32(expected);
    print_string(" Got: ");
    print_hex32(actual);
    print_string("\n");
    g_fail_count++;
  }

  record_test_visual(g_test_index, passed);
  g_test_index++;
}

/* ============================================================================
 * 1. ZERO REGISTER (x0) IMMUTABILITY SUITE
 * ============================================================================
 */
void test_suite_x0_immutability(void) {
  print_string("\n--- [arch-test/I: Register x0 Immutability] ---\n");
  uint32_t res;

  // ADDI to x0
  __asm__ volatile("addi x0, x0, 100\n\t addi %0, x0, 0" : "=r"(res));
  assert_test("I-x0-ADDI-01", res, 0);

  // ADD to x0
  __asm__ volatile("li t0, 55\n\t add x0, t0, t0\n\t addi %0, x0, 0"
                   : "=r"(res)
                   :
                   : "t0");
  assert_test("I-x0-ADD-01", res, 0);

  // Load to x0
  mem_test_buffer[0] = 0xDEADBEEF;
  __asm__ volatile("lw x0, 0(%1)\n\t addi %0, x0, 0"
                   : "=r"(res)
                   : "r"(mem_test_buffer));
  assert_test("I-x0-LW-01", res, 0);

  // MUL to x0
  __asm__ volatile("li t0, 12\n\t mul x0, t0, t0\n\t addi %0, x0, 0"
                   : "=r"(res)
                   :
                   : "t0");
  assert_test("I-x0-MUL-01", res, 0);
}

/* ============================================================================
 * 2. LUI & AUIPC UPPER IMMEDIATES SUITE
 * ============================================================================
 */
void test_suite_upper_immediates(void) {
  print_string("\n--- [arch-test/I: LUI & AUIPC Specifications] ---\n");
  uint32_t res, pc_ref;

  __asm__ volatile("lui %0, 0x00000" : "=r"(res));
  assert_test("I-LUI-01 (Zero)", res, 0x00000000);

  __asm__ volatile("lui %0, 0x12345" : "=r"(res));
  assert_test("I-LUI-02 (Standard Pattern)", res, 0x12345000);

  __asm__ volatile("lui %0, 0xFFFFF" : "=r"(res));
  assert_test("I-LUI-03 (All Ones)", res, 0xFFFFF000);

  __asm__ volatile("lui %0, 0x80000" : "=r"(res));
  assert_test("I-LUI-04 (Sign Bit Pattern)", res, 0x80000000);

  // AUIPC Base: auipc at label 1 (pc_ref - 8)
  __asm__ volatile("1: auipc %0, 0\n\t"
                   "   jal %1, 2f\n\t"
                   "2: nop"
                   : "=r"(res), "=r"(pc_ref));
  assert_test("I-AUIPC-01 (Current PC)", res, pc_ref - 8);

  // AUIPC Offset: auipc + 0x2000
  __asm__ volatile("1: auipc %0, 2\n\t"
                   "   jal %1, 2f\n\t"
                   "2: nop"
                   : "=r"(res), "=r"(pc_ref));
  assert_test("I-AUIPC-02 (PC + 0x2000)", res, (pc_ref - 8) + 0x2000);
}

/* ============================================================================
 * 3. I-TYPE ARITHMETIC & LOGICAL BOUNDARIES SUITE
 * ============================================================================
 */
void test_suite_imm_arithmetic(void) {
  print_string("\n--- [arch-test/I: Immediate Arithmetic & Logic] ---\n");
  uint32_t res;

  // ADDI Max Positive (+2047) & Min Negative (-2048)
  __asm__ volatile("addi %0, x0, 2047" : "=r"(res));
  assert_test("I-ADDI-01 (Max Positive 0x7FF)", res, 2047);

  __asm__ volatile("addi %0, x0, -2048" : "=r"(res));
  assert_test("I-ADDI-02 (Min Negative -2048)", res, 0xFFFFF800);

  __asm__ volatile("addi %0, x0, -1" : "=r"(res));
  assert_test("I-ADDI-03 (All Ones Sign-Ext)", res, 0xFFFFFFFF);

  // ADDI Overflow wrapping
  __asm__ volatile("li t0, 0x7FFFFFFF\n\t addi %0, t0, 1" : "=r"(res) : : "t0");
  assert_test("I-ADDI-04 (INT_MAX + 1 Wrap)", res, 0x80000000);

  __asm__ volatile("li t0, 0x80000000\n\t addi %0, t0, -1"
                   : "=r"(res)
                   :
                   : "t0");
  assert_test("I-ADDI-05 (INT_MIN - 1 Wrap)", res, 0x7FFFFFFF);

  // SLTI Signed Comparisons
  __asm__ volatile("li t0, 0x80000000\n\t slti %0, t0, 0" : "=r"(res) : : "t0");
  assert_test("I-SLTI-01 (INT_MIN < 0)", res, 1);

  __asm__ volatile("li t0, 0x7FFFFFFF\n\t slti %0, t0, 0" : "=r"(res) : : "t0");
  assert_test("I-SLTI-02 (INT_MAX < 0)", res, 0);

  __asm__ volatile("li t0, -10\n\t slti %0, t0, -5" : "=r"(res) : : "t0");
  assert_test("I-SLTI-03 (-10 < -5)", res, 1);

  // SLTIU Unsigned Comparisons
  __asm__ volatile("li t0, 0xFFFFFFFF\n\t sltiu %0, t0, 1"
                   : "=r"(res)
                   :
                   : "t0");
  assert_test("I-SLTIU-01 (0xFFFFFFFF < 1)", res, 0);

  __asm__ volatile("li t0, 0\n\t sltiu %0, t0, 1" : "=r"(res) : : "t0");
  assert_test("I-SLTIU-02 (0 < 1)", res, 1);

  // ANDI / ORI / XORI
  __asm__ volatile("li t0, 0x12345678\n\t andi %0, t0, 0x0F0"
                   : "=r"(res)
                   :
                   : "t0");
  assert_test("I-ANDI-01 (Masking)", res, 0x00000070);

  __asm__ volatile("li t0, 0x12345600\n\t ori %0, t0, 0x07F"
                   : "=r"(res)
                   :
                   : "t0");
  assert_test("I-ORI-01 (Bit Insertion)", res, 0x1234567F);

  __asm__ volatile("li t0, 0xAAAAAAAA\n\t xori %0, t0, -1"
                   : "=r"(res)
                   :
                   : "t0");
  assert_test("I-XORI-01 (Bit Invert with -1)", res, 0x55555555);

  __asm__ volatile("li t0, 0x55555555\n\t xori %0, t0, 0x7FF"
                   : "=r"(res)
                   :
                   : "t0");
  assert_test("I-XORI-02 (Positive Imm 0x7FF)", res, 0x555552AA);
}

/* ============================================================================
 * 4. SHIFT INSTRUCTIONS & 5-BIT SHAMT MASKING SUITE
 * ============================================================================
 */
void test_suite_shifts(void) {
  print_string("\n--- [arch-test/I: Shift Instructions] ---\n");
  uint32_t res;

  __asm__ volatile("li t0, 1\n\t slli %0, t0, 0" : "=r"(res) : : "t0");
  assert_test("I-SLLI-01 (Shift 0)", res, 1);

  __asm__ volatile("li t0, 1\n\t slli %0, t0, 31" : "=r"(res) : : "t0");
  assert_test("I-SLLI-02 (Shift 31 to MSB)", res, 0x80000000);

  __asm__ volatile("li t0, 0xFFFFFFFF\n\t slli %0, t0, 4" : "=r"(res) : : "t0");
  assert_test("I-SLLI-03 (Walking 1s)", res, 0xFFFFFFF0);

  __asm__ volatile("li t0, 0x80000000\n\t srli %0, t0, 1" : "=r"(res) : : "t0");
  assert_test("I-SRLI-01 (MSB Shift 1)", res, 0x40000000);

  __asm__ volatile("li t0, 0x80000000\n\t srli %0, t0, 31"
                   : "=r"(res)
                   :
                   : "t0");
  assert_test("I-SRLI-02 (MSB Shift 31)", res, 0x00000001);

  __asm__ volatile("li t0, 0xFFFFFFFF\n\t srli %0, t0, 16"
                   : "=r"(res)
                   :
                   : "t0");
  assert_test("I-SRLI-03 (Halfword Shift)", res, 0x0000FFFF);

  __asm__ volatile("li t0, 0x80000000\n\t srai %0, t0, 1" : "=r"(res) : : "t0");
  assert_test("I-SRAI-01 (Sign Extension 1)", res, 0xC0000000);

  __asm__ volatile("li t0, 0x80000000\n\t srai %0, t0, 31"
                   : "=r"(res)
                   :
                   : "t0");
  assert_test("I-SRAI-02 (Sign Fill 31)", res, 0xFFFFFFFF);

  __asm__ volatile("li t0, 0x7FFFFFFF\n\t srai %0, t0, 31"
                   : "=r"(res)
                   :
                   : "t0");
  assert_test("I-SRAI-03 (Zero Fill 31)", res, 0x00000000);

  // Register shifts: RS2 must be truncated to lower 5 bits only
  __asm__ volatile("li t0, 1\n\t li t1, 37\n\t sll %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-SLL-01 (RS2 Masked 37 % 32 = 5)", res, 32);

  __asm__ volatile("li t0, 0x80000000\n\t li t1, 0xFFFFFFE4\n\t srl %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-SRL-01 (RS2 Masked 0xE4 % 32 = 4)", res, 0x08000000);

  __asm__ volatile("li t0, 0x80000000\n\t li t1, 0x104\n\t sra %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-SRA-01 (RS2 Masked 0x104 % 32 = 4)", res, 0xF8000000);
}

/* ============================================================================
 * 5. R-TYPE ARITHMETIC & LOGICAL SUITE
 * ============================================================================
 */
void test_suite_reg_arithmetic(void) {
  print_string("\n--- [arch-test/I: Register-Register Operations] ---\n");
  uint32_t res;

  __asm__ volatile("li t0, 0xFFFFFFFF\n\t li t1, 1\n\t add %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-ADD-01 (Overflow 0xFFFFFFFF + 1)", res, 0);

  __asm__ volatile("li t0, 0x7FFFFFFF\n\t li t1, 1\n\t add %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-ADD-02 (INT_MAX + 1)", res, 0x80000000);

  __asm__ volatile("li t0, 0\n\t li t1, 1\n\t sub %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-SUB-01 (0 - 1)", res, 0xFFFFFFFF);

  __asm__ volatile("li t0, 0x12345678\n\t sub %0, t0, t0" : "=r"(res) : : "t0");
  assert_test("I-SUB-02 (Identity x - x)", res, 0);

  __asm__ volatile("li t0, 0x80000000\n\t li t1, 1\n\t sub %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-SUB-03 (INT_MIN - 1)", res, 0x7FFFFFFF);

  // SLT Signed
  __asm__ volatile("li t0, 0x80000000\n\t li t1, 0x7FFFFFFF\n\t slt %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-SLT-01 (INT_MIN < INT_MAX)", res, 1);

  __asm__ volatile("li t0, 0x7FFFFFFF\n\t li t1, 0x80000000\n\t slt %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-SLT-02 (INT_MAX < INT_MIN)", res, 0);

  __asm__ volatile("li t0, -50\n\t li t1, -10\n\t slt %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-SLT-03 (-50 < -10)", res, 1);

  // SLTU Unsigned
  __asm__ volatile("li t0, 0\n\t li t1, 0xFFFFFFFF\n\t sltu %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-SLTU-01 (0 < 0xFFFFFFFF)", res, 1);

  __asm__ volatile("li t0, 0x80000000\n\t li t1, 0x7FFFFFFF\n\t sltu %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-SLTU-02 (0x80000000 < 0x7FFFFFFF)", res, 0);

  // XOR / AND
  __asm__ volatile("li t0, 0xF0F0F0F0\n\t li t1, 0x0F0F0F0F\n\t xor %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-XOR-01 (Complement)", res, 0xFFFFFFFF);

  __asm__ volatile("li t0, 0x12345678\n\t li t1, 0x00FF00FF\n\t and %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-AND-01 (Masking)", res, 0x00340078);
}

/* ============================================================================
 * 6. BRANCH CONDITION MATRIX SUITE
 * ============================================================================
 */
void test_suite_branches(void) {
  print_string("\n--- [arch-test/I: Branch Condition Matrix] ---\n");
  uint32_t res;

  // BEQ
  __asm__ volatile("li %0, 0\n\t li t0, 7\n\t li t1, 7\n\t beq t0, t1, 1f\n\t "
                   "li %0, 1\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BEQ-01 (Equal: Taken)", res, 0);

  __asm__ volatile("li %0, 1\n\t li t0, 7\n\t li t1, 8\n\t beq t0, t1, 1f\n\t "
                   "li %0, 0\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BEQ-02 (Not Equal: Not Taken)", res, 0);

  // BNE
  __asm__ volatile("li %0, 0\n\t li t0, 7\n\t li t1, 8\n\t bne t0, t1, 1f\n\t "
                   "li %0, 1\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BNE-01 (Not Equal: Taken)", res, 0);

  __asm__ volatile("li %0, 1\n\t li t0, 7\n\t li t1, 7\n\t bne t0, t1, 1f\n\t "
                   "li %0, 0\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BNE-02 (Equal: Not Taken)", res, 0);

  // BLT Signed
  __asm__ volatile("li %0, 0\n\t li t0, -10\n\t li t1, 10\n\t blt t0, t1, "
                   "1f\n\t li %0, 1\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BLT-01 (-10 < 10: Taken)", res, 0);

  __asm__ volatile("li %0, 1\n\t li t0, 10\n\t li t1, -10\n\t blt t0, t1, "
                   "1f\n\t li %0, 0\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BLT-02 (10 < -10: Not Taken)", res, 0);

  __asm__ volatile("li %0, 0\n\t li t0, 0x80000000\n\t li t1, 0x7FFFFFFF\n\t "
                   "blt t0, t1, 1f\n\t li %0, 1\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BLT-03 (INT_MIN < INT_MAX: Taken)", res, 0);

  __asm__ volatile("li %0, 1\n\t li t0, 0x7FFFFFFF\n\t li t1, 0x80000000\n\t "
                   "blt t0, t1, 1f\n\t li %0, 0\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BLT-04 (INT_MAX < INT_MIN: Not Taken)", res, 0);

  // BGE Signed
  __asm__ volatile("li %0, 0\n\t li t0, 10\n\t li t1, -10\n\t bge t0, t1, "
                   "1f\n\t li %0, 1\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BGE-01 (10 >= -10: Taken)", res, 0);

  __asm__ volatile("li %0, 1\n\t li t0, -10\n\t li t1, 10\n\t bge t0, t1, "
                   "1f\n\t li %0, 0\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BGE-02 (-10 >= 10: Not Taken)", res, 0);

  __asm__ volatile("li %0, 0\n\t li t0, 0x7FFFFFFF\n\t li t1, 0x80000000\n\t "
                   "bge t0, t1, 1f\n\t li %0, 1\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BGE-03 (INT_MAX >= INT_MIN: Taken)", res, 0);

  __asm__ volatile("li %0, 1\n\t li t0, 0x80000000\n\t li t1, 0x7FFFFFFF\n\t "
                   "bge t0, t1, 1f\n\t li %0, 0\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BGE-04 (INT_MIN >= INT_MAX: Not Taken)", res, 0);

  // BLTU / BGEU Unsigned
  __asm__ volatile("li %0, 0\n\t li t0, 10\n\t li t1, -10\n\t bltu t0, t1, "
                   "1f\n\t li %0, 1\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BLTU-01 (10 < 0xFFFFFFF6: Taken)", res, 0);

  __asm__ volatile("li %0, 1\n\t li t0, -10\n\t li t1, 10\n\t bltu t0, t1, "
                   "1f\n\t li %0, 0\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BLTU-02 (0xFFFFFFF6 < 10: Not Taken)", res, 0);

  __asm__ volatile("li %0, 0\n\t li t0, -10\n\t li t1, 10\n\t bgeu t0, t1, "
                   "1f\n\t li %0, 1\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BGEU-01 (0xFFFFFFF6 >= 10: Taken)", res, 0);

  __asm__ volatile("li %0, 1\n\t li t0, 10\n\t li t1, -10\n\t bgeu t0, t1, "
                   "1f\n\t li %0, 0\n\t 1: nop"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("I-BGEU-02 (10 >= 0xFFFFFFF6: Not Taken)", res, 0);
}

/* ============================================================================
 * 7. JUMP AND LINK (JAL & JALR) SUITE
 * ============================================================================
 */
void test_suite_jumps(void) {
  print_string("\n--- [arch-test/I: Jump & Link Flow] ---\n");
  uint32_t res = 0, link_reg = 0, pc_ref = 0;

  // Forward JAL Link Register = PC + 4
  __asm__ volatile("   jal %1, 1f\n\t"
                   "   li %0, 99\n\t"
                   "1: auipc %2, 0"
                   : "+r"(res), "=r"(link_reg), "=r"(pc_ref));
  assert_test("I-JAL-01 (Link Register PC+4)", link_reg, pc_ref - 4);

  // Backward JAL Jump
  res = 0;
  __asm__ volatile("   jal x0, 2f\n\t"
                   "1: li %0, 42\n\t"
                   "   jal x0, 3f\n\t"
                   "2: jal x0, 1b\n\t"
                   "3: nop"
                   : "=r"(res));
  assert_test("I-JAL-02 (Backward Jump)", res, 42);

  // JALR Target Jump
  res = 0;
  __asm__ volatile("la t0, 1f\n\t"
                   "jalr %1, t0, 0\n\t"
                   "li %0, 99\n\t"
                   "1: addi %0, %0, 15"
                   : "+r"(res), "=r"(link_reg)
                   :
                   : "t0");
  assert_test("I-JALR-01 (Target Jump)", res, 15);

  // JALR Bit 0 Clearing (target | 1 must clear LSB)
  res = 0;
  __asm__ volatile("la t0, 1f\n\t"
                   "ori t0, t0, 1\n\t"
                   "jalr x0, t0, 0\n\t"
                   "li %0, 99\n\t"
                   "1: addi %0, %0, 7"
                   : "+r"(res)
                   :
                   : "t0");
  assert_test("I-JALR-02 (LSB Zeroing)", res, 7);

  // JALR Link Register
  res = 0;
  __asm__ volatile("la t0, 1f\n\t"
                   "jalr %1, t0, 0\n\t"
                   "li %0, 99\n\t"
                   "1: auipc %2, 0"
                   : "+r"(res), "=r"(link_reg), "=r"(pc_ref)
                   :
                   : "t0");
  assert_test("I-JALR-03 (Link Register PC+4)", link_reg, pc_ref - 4);

  // JALR Non-Zero Immediate Offset
  res = 0;
  __asm__ volatile("la t0, 1f\n\t"
                   "addi t0, t0, -4\n\t"
                   "jalr x0, t0, 4\n\t"
                   "li %0, 99\n\t"
                   "1: addi %0, %0, 21"
                   : "+r"(res)
                   :
                   : "t0");
  assert_test("I-JALR-04 (Imm Offset Arithmetic)", res, 21);
}

/* ============================================================================
 * 8. MEMORY LOAD/STORE & HARDWARE BYTE-LANE ISOLATION SUITE
 * ============================================================================
 */
void test_suite_memory(void) {
  print_string("\n--- [arch-test/I: Memory Load/Store & Byte Isolation] ---\n");
  uint32_t res;
  volatile uint32_t *w = (volatile uint32_t *)mem_test_buffer;

  // SW & LW
  *w = 0x11223344;
  __asm__ volatile("lw %0, 0(%1)" : "=r"(res) : "r"(w) : "memory");
  assert_test("I-LW-01 (Full Word)", res, 0x11223344);

  // Byte lane stores (Checking byte isolation)
  *w = 0x11223344;
  __asm__ volatile("li t0, 0xAA\n\t sb t0, 0(%1)\n\t lw %0, 0(%1)"
                   : "=r"(res)
                   : "r"(w)
                   : "t0", "memory");
  assert_test("I-SB-01 (Byte Lane 0)", res, 0x112233AA);

  *w = 0x11223344;
  __asm__ volatile("li t0, 0xAA\n\t sb t0, 1(%1)\n\t lw %0, 0(%1)"
                   : "=r"(res)
                   : "r"(w)
                   : "t0", "memory");
  assert_test("I-SB-02 (Byte Lane 1)", res, 0x1122AA44);

  *w = 0x11223344;
  __asm__ volatile("li t0, 0xAA\n\t sb t0, 2(%1)\n\t lw %0, 0(%1)"
                   : "=r"(res)
                   : "r"(w)
                   : "t0", "memory");
  assert_test("I-SB-03 (Byte Lane 2)", res, 0x11AA3344);

  *w = 0x11223344;
  __asm__ volatile("li t0, 0xAA\n\t sb t0, 3(%1)\n\t lw %0, 0(%1)"
                   : "=r"(res)
                   : "r"(w)
                   : "t0", "memory");
  assert_test("I-SB-04 (Byte Lane 3)", res, 0xAA223344);

  // Halfword stores
  *w = 0x11223344;
  __asm__ volatile("li t0, 0xBBAA\n\t sh t0, 0(%1)\n\t lw %0, 0(%1)"
                   : "=r"(res)
                   : "r"(w)
                   : "t0", "memory");
  assert_test("I-SH-01 (Halfword 0)", res, 0x1122BBAA);

  *w = 0x11223344;
  __asm__ volatile("li t0, 0xBBAA\n\t sh t0, 2(%1)\n\t lw %0, 0(%1)"
                   : "=r"(res)
                   : "r"(w)
                   : "t0", "memory");
  assert_test("I-SH-02 (Halfword 1)", res, 0xBBAA3344);

  // LB / LBU Extensions
  *w = 0x000000FE;
  __asm__ volatile("lb %0, 0(%1)" : "=r"(res) : "r"(w) : "memory");
  assert_test("I-LB-01 (Sign Extension 0xFE)", res, 0xFFFFFFFE);

  *w = 0x0000007E;
  __asm__ volatile("lb %0, 0(%1)" : "=r"(res) : "r"(w) : "memory");
  assert_test("I-LB-02 (Positive Sign 0x7E)", res, 0x0000007E);

  *w = 0x000000FE;
  __asm__ volatile("lbu %0, 0(%1)" : "=r"(res) : "r"(w) : "memory");
  assert_test("I-LBU-01 (Zero Extension 0xFE)", res, 0x000000FE);

  // LH / LHU Extensions
  *w = 0x00008001;
  __asm__ volatile("lh %0, 0(%1)" : "=r"(res) : "r"(w) : "memory");
  assert_test("I-LH-01 (Sign Extension 0x8001)", res, 0xFFFF8001);

  *w = 0x00007FFF;
  __asm__ volatile("lh %0, 0(%1)" : "=r"(res) : "r"(w) : "memory");
  assert_test("I-LH-02 (Positive Sign 0x7FFF)", res, 0x00007FFF);

  *w = 0x00008001;
  __asm__ volatile("lhu %0, 0(%1)" : "=r"(res) : "r"(w) : "memory");
  assert_test("I-LHU-01 (Zero Extension 0x8001)", res, 0x00008001);

  // Negative Offsets
  mem_test_buffer[1] = 0x55AA55AA;
  volatile uint32_t *p = &mem_test_buffer[2];
  __asm__ volatile("lw %0, -4(%1)" : "=r"(res) : "r"(p) : "memory");
  assert_test("I-LW-02 (Negative Imm Offset)", res, 0x55AA55AA);

  __asm__ volatile("li t0, 0x12344321\n\t sw t0, -4(%1)\n\t lw %0, -4(%1)"
                   : "=r"(res)
                   : "r"(p)
                   : "t0", "memory");
  assert_test("I-SW-01 (Negative Imm Offset)", res, 0x12344321);

  // Back-to-back Load-Use Data Hazard
  mem_test_buffer[0] = 77;
  __asm__ volatile("lw t0, 0(%1)\n\t"
                   "addi %0, t0, 23"
                   : "=r"(res)
                   : "r"(mem_test_buffer)
                   : "t0", "memory");
  assert_test("I-RAW-01 (Load-Use RAW Hazard)", res, 100);
}

/* ============================================================================
 * 9. RV32M MULTIPLIER EXTENSION SUITE
 * ============================================================================
 */
void test_suite_mul(void) {
  print_string("\n--- [arch-test/M: Multiplier Verification] ---\n");
  uint32_t res;

  // MUL Low 32-bit
  __asm__ volatile("li t0, 0\n\t li t1, 12345\n\t mul %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-MUL-01 (Zero Factor)", res, 0);

  __asm__ volatile("li t0, 1\n\t li t1, 1\n\t mul %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-MUL-02 (Identity 1 * 1)", res, 1);

  __asm__ volatile("li t0, -1\n\t li t1, -1\n\t mul %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-MUL-03 (-1 * -1)", res, 1);

  __asm__ volatile("li t0, -1\n\t li t1, 1\n\t mul %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-MUL-04 (-1 * 1)", res, 0xFFFFFFFF);

  __asm__ volatile("li t0, -100\n\t li t1, 25\n\t mul %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-MUL-05 (-100 * 25)", res, (uint32_t)-2500);

  __asm__ volatile("li t0, 0x12345678\n\t li t1, 2\n\t mul %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-MUL-06 (Large Product Low)", res, 0x2468ACF0);

  __asm__ volatile("li t0, 0x80000000\n\t li t1, -1\n\t mul %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-MUL-07 (INT_MIN * -1 Low)", res, 0x80000000);

  // MULH (Signed x Signed -> High 32)
  __asm__ volatile("li t0, 0x7FFFFFFF\n\t li t1, 0x7FFFFFFF\n\t mulh %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-MULH-01 (INT_MAX^2)", res, 0x3FFFFFFF);

  __asm__ volatile("li t0, -2000000\n\t li t1, -3000000\n\t mulh %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-MULH-02 (Negatives: -2M * -3M)", res, 1396);

  __asm__ volatile("li t0, 0x7FFFFFFF\n\t li t1, -1\n\t mulh %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-MULH-03 (INT_MAX * -1)", res, 0xFFFFFFFF);

  __asm__ volatile("li t0, 0x80000000\n\t li t1, 0x80000000\n\t mulh %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-MULH-04 (INT_MIN * INT_MIN)", res, 0x40000000);

  __asm__ volatile("li t0, 0x80000000\n\t li t1, -1\n\t mulh %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-MULH-05 (INT_MIN * -1 High)", res, 0);

  // MULHU (Unsigned x Unsigned -> High 32)
  __asm__ volatile(
      "li t0, 0xFFFFFFFF\n\t li t1, 0xFFFFFFFF\n\t mulhu %0, t0, t1"
      : "=r"(res)
      :
      : "t0", "t1");
  assert_test("M-MULHU-01 (UINT_MAX^2)", res, 0xFFFFFFFE);

  __asm__ volatile(
      "li t0, 0x80000000\n\t li t1, 0x80000000\n\t mulhu %0, t0, t1"
      : "=r"(res)
      :
      : "t0", "t1");
  assert_test("M-MULHU-02 (0x80000000^2)", res, 0x40000000);

  __asm__ volatile("li t0, 0xFFFFFFFF\n\t li t1, 2\n\t mulhu %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-MULHU-03 (UINT_MAX * 2)", res, 1);

  // MULHSU (Signed x Unsigned -> High 32)
  __asm__ volatile(
      "li t0, 0x80000000\n\t li t1, 0xFFFFFFFF\n\t mulhsu %0, t0, t1"
      : "=r"(res)
      :
      : "t0", "t1");
  assert_test("M-MULHSU-01 (INT_MIN * UINT_MAX)", res, 0x80000000);
}

/* ============================================================================
 * 10. RV32M DIVIDER & MODULO EXTENSION SUITE (Milestone 202)
 * ============================================================================
 */
#if ENABLE_DIV_REM_TESTS
void test_suite_div_rem(void) {
  print_string("\n--- [arch-test/M: Divider & Modulo Verification] ---\n");
  uint32_t res;

  // Signed Division Signs
  __asm__ volatile("li t0, 100\n\t li t1, 7\n\t div %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-DIV-01 (+ / +)", res, 14);

  __asm__ volatile("li t0, -100\n\t li t1, 7\n\t div %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-DIV-02 (- / +)", res, (uint32_t)-14);

  __asm__ volatile("li t0, 100\n\t li t1, -7\n\t div %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-DIV-03 (+ / -)", res, (uint32_t)-14);

  __asm__ volatile("li t0, -100\n\t li t1, -7\n\t div %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-DIV-04 (- / -)", res, 14);

  __asm__ volatile("li t0, 0x80000000\n\t li t1, 1\n\t div %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-DIV-05 (INT_MIN / 1)", res, 0x80000000);

  // Signed Remainder Signs
  __asm__ volatile("li t0, 100\n\t li t1, 7\n\t rem %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-REM-01 (+ % +)", res, 2);

  __asm__ volatile("li t0, -100\n\t li t1, 7\n\t rem %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-REM-02 (- % +)", res, (uint32_t)-2);

  __asm__ volatile("li t0, 100\n\t li t1, -7\n\t rem %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-REM-03 (+ % -)", res, 2);

  __asm__ volatile("li t0, -100\n\t li t1, -7\n\t rem %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-REM-04 (- % -)", res, (uint32_t)-2);

  // Unsigned Division & Modulo
  __asm__ volatile("li t0, 1000\n\t li t1, 3\n\t divu %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-DIVU-01 (1000 / 3)", res, 333);

  __asm__ volatile("li t0, 1000\n\t li t1, 3\n\t remu %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-REMU-01 (1000 % 3)", res, 1);

  __asm__ volatile("li t0, 0xFFFFFFFF\n\t li t1, 2\n\t divu %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-DIVU-02 (UINT_MAX / 2)", res, 0x7FFFFFFF);

  __asm__ volatile("li t0, 0xFFFFFFFF\n\t li t1, 2\n\t remu %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-REMU-02 (UINT_MAX % 2)", res, 1);

  // Corner cases
  __asm__ volatile("li t0, 50\n\t li t1, 0\n\t div %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-DIV-ZERO-01 (50 / 0 = -1)", res, 0xFFFFFFFF);

  __asm__ volatile("li t0, 50\n\t li t1, 0\n\t divu %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-DIVU-ZERO-01 (50 / 0 = UINT_MAX)", res, 0xFFFFFFFF);

  __asm__ volatile("li t0, 50\n\t li t1, 0\n\t rem %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-REM-ZERO-01 (50 % 0 = 50)", res, 50);

  __asm__ volatile("li t0, 50\n\t li t1, 0\n\t remu %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-REMU-ZERO-01 (50 % 0 = 50)", res, 50);

  __asm__ volatile("li t0, 0x80000000\n\t li t1, -1\n\t div %0, t0, t1"
                   : "=r"(res)
                   :
                   : "t0", "t1");
  assert_test("M-DIV-OVERFLOW-01 (INT_MIN / -1 = INT_MIN)", res, 0x80000000);
}
#endif

/* ============================================================================
 * RETURN TO WOZMON BOOTLOADER
 * ============================================================================
 */
void return_to_wozmon(void) {
  print_string("\nTest suite execution finished.\nPress any key to jump to "
               "Wozmon ROM (0x00000000)...");
  (void)read_key();

  *PAGE_REG = 0;
  void (*wozmon_entry)(void) = (void (*)(void))0x00000000;
  wozmon_entry();
}

/* ============================================================================
 * MAIN ENTRY POINT
 * ============================================================================
 */
int main(void) {
  // 1. Clear Framebuffer and Display Page 0
  clear_page(0, COLOR_BLACK);
  clear_page(1, COLOR_BLACK);
  *PAGE_REG = 0;

  // Draw Dashboard Frame
  fill_rect(0, 0, 0, 320, 24, COLOR_BLUE);
  fill_rect(0, 12, 30, 296, 126, COLOR_DARK_GRAY);

  print_string("====================================================\n");
  print_string("   RISC-V ARCHITECTURAL VERIFICATION SUITE \n");
  print_string("====================================================\n");

  // 2. Run Architectural Verification Suites
  test_suite_x0_immutability();  // 4 Tests
  test_suite_upper_immediates(); // 6 Tests
  test_suite_imm_arithmetic();   // 14 Tests
  test_suite_shifts();           // 12 Tests
  test_suite_reg_arithmetic();   // 12 Tests
  test_suite_branches();         // 16 Tests
  test_suite_jumps();            // 6 Tests
  test_suite_memory();           // 16 Tests
  test_suite_mul();              // 16 Tests
#if ENABLE_DIV_REM_TESTS
  test_suite_div_rem(); // 18 Tests
#endif

  // 3. Print & Render Final Summary
  print_string("\n====================================================\n");
  print_string("ARCHITECTURAL TEST SUMMARY:\n");
  print_string("  TOTAL RUN:  ");
  print_dec(g_test_index);
  print_string(" / ");
  print_dec(TOTAL_TEST_COUNT);
  print_string("\n");
  print_string("  PASSED:     ");
  print_dec(g_pass_count);
  print_string("\n");
  print_string("  FAILED:     ");
  print_dec(g_fail_count);
  print_string("\n");

  if (g_fail_count == 0 && g_test_index == TOTAL_TEST_COUNT) {
    print_string(">>> 100% ARCHITECTURAL COMPLIANCE VERIFIED! <<<\n");
    fill_rect(0, 12, 162, 296, 32, COLOR_GREEN);
  } else {
    print_string(">>> COMPLIANCE FAILURES DETECTED! CHECK LOG ABOVE. <<<\n");
    fill_rect(0, 12, 162, 296, 32, COLOR_RED);
  }
  print_string("====================================================\n");

  return_to_wozmon();
  return 0;
}