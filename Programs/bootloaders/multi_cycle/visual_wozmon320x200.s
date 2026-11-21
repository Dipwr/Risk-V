# =====================================================================
# RV32I Interactive Monitor & Program Loader (Wozmon-style)
# =====================================================================

.equ GRAPHIC_RAM,    0x10000000     # VRAM Page 0 base address (256 KB)
.equ UART_DATA_ADDR, 0x20000000     # UART Data Register
.equ UART_STAT_ADDR, 0x20000004     # UART Status: bit 0 = RX ready, bit 1 = TX ready
.equ PAGE_REG_ADDR,  0x20000008     # Display Page Flip Register
.equ RAM_BASE_ADDR,  0x00010000     # User Program Load Target (64 KB offset)

# RGB565 Color definitions
.equ COLOR_TEXT,     0x0000         # Black text (0x0000)
.equ COLOR_BG,       0xFFFF         # White background (0xFFFF)

.section .text
.globl _start

_start:
	# 1. Initialize Stack Pointer to 64 KB (giving the monitor its own stack)
	li   sp, 0x0000FFF0

	# 0. Force Hardware Display Presenter to Page 0 VRAM
	li   t0, PAGE_REG_ADDR
	sw   zero, 0(t0)

	# Initialize RAM Base Pointer
	li   s0, RAM_BASE_ADDR

	# Load persistent constants
	li   s5, GRAPHIC_RAM        # Graphic RAM base address
	li   s8, COLOR_BG           # Background color (16-bit)
	li   s9, COLOR_TEXT         # Text color (16-bit)

	# 1. Clear Graphic RAM Screen
	jal  t6, clear_screen_sub

	# 2. Reset Cursor Grid Position (Col 0, Row 0)
	li   s10, 0                 # Cursor X (0..63)
	li   s11, 0                 # Cursor Y (0..32)

print_prompt:
	# Output Newline sequence: '>', ' '
	li   a0, '>'
	jal  ra, out_char
	li   a0, ' '
	jal  ra, out_char

	# Reset Accumulator & Flags
	li   s1, 0                  # Parsed Hex Accumulator
	li   s2, 0                  # Digit Flag

read_char_loop:
	# Poll UART RX
	li   t1, UART_STAT_ADDR
poll_key:
	lw   t2, 0(t1)
	andi t2, t2, 0x1            # Bit 0 = RX ready
	beqz t2, poll_key

	# Read ASCII character from UART
	li   t1, UART_DATA_ADDR
	lbu  a0, 0(t1)

	# Convert Lowercase to Uppercase
	li   t0, 'a'
	blt  a0, t0, skip_upper
	li   t0, 'z'
	bgt  a0, t0, skip_upper
	addi a0, a0, -32            # Convert 'a'-'z' to 'A'-'Z'
skip_upper:

	# Echo character to both Graphic RAM and UART TX
	jal  ra, out_char

	# Check for Enter ('\r' / '\n')
	li   t0, 0x0D
	beq  a0, t0, handle_enter
	li   t0, 0x0A
	beq  a0, t0, handle_enter

	# Check for Colon (':')
	li   t0, ':'
	beq  a0, t0, handle_colon

	# Check for 'R' / 'r'
	li   t0, 'R'
	beq  a0, t0, handle_run

	# Hex Parsing ('0'-'9', 'A'-'F')
	li   t0, '0'
	blt  a0, t0, read_char_loop
	li   t0, '9'
	bgt  a0, t0, try_hex_alpha
	addi t0, a0, -'0'
	j    append_nibble

try_hex_alpha:
	li   t0, 'A'
	blt  a0, t0, read_char_loop
	li   t0, 'F'
	bgt  a0, t0, read_char_loop
	addi t0, a0, -55

append_nibble:
	andi t0, t0, 0xF
	slli s1, s1, 4
	or   s1, s1, t0
	li   s2, 1
	j    read_char_loop

# =====================================================================
# COMMAND HANDLERS
# =====================================================================

handle_enter:
	beqz s2, do_read_mem
	mv   s0, s1

do_read_mem:
	li   a0, ':'
	jal  ra, out_char
	li   a0, ' '
	jal  ra, out_char

	lw   s3, 0(s0)              # Read 32-bit word from RAM

	# Print 8 hex digits
	li   s4, 28
print_word_loop:
	srl  t0, s3, s4
	andi t0, t0, 0xF
	li   t1, 10
	blt  t0, t1, is_num
	addi t0, t0, 55
	j    out_nibble
is_num:
	addi t0, t0, '0'
out_nibble:
	mv   a0, t0
	jal  ra, out_char
	addi s4, s4, -4
	bge  s4, zero, print_word_loop

	addi s0, s0, 4
	j    char_newline_then_prompt

handle_colon:
	beqz s2, write_mode_loop
	mv   s0, s1

write_mode_loop:
	li   s1, 0

parse_val_loop:
	li   t1, UART_STAT_ADDR
poll_val_key:
	lw   t2, 0(t1)
	andi t2, t2, 0x1
	beqz t2, poll_val_key

	li   t1, UART_DATA_ADDR
	lbu  a0, 0(t1)

	# Convert Lowercase to Uppercase
	li   t0, 'a'
	blt  a0, t0, skip_upper_val
	li   t0, 'z'
	bgt  a0, t0, skip_upper_val
	addi a0, a0, -32
skip_upper_val:

	jal  ra, out_char

	li   t0, ' '
	beq  a0, t0, commit_write
	li   t0, 0x0D
	beq  a0, t0, commit_write_end
	li   t0, 0x0A
	beq  a0, t0, commit_write_end

	li   t0, '0'
	blt  a0, t0, parse_val_loop
	li   t0, '9'
	bgt  a0, t0, try_val_alpha
	addi t0, a0, -'0'
	j    shift_val_nibble

try_val_alpha:
	li   t0, 'A'
	blt  a0, t0, parse_val_loop
	li   t0, 'F'
	bgt  a0, t0, parse_val_loop
	addi t0, a0, -55

shift_val_nibble:
	andi t0, t0, 0xF
	slli s1, s1, 4
	or   s1, s1, t0
	j    parse_val_loop

commit_write:
	sw   s1, 0(s0)
	addi s0, s0, 4
	j    write_mode_loop

commit_write_end:
	sw   s1, 0(s0)
	addi s0, s0, 4
	j    char_newline_then_prompt

handle_run:
	beqz s2, execute_jump
	mv   s0, s1

execute_jump:
	li   s10, 0
	li   s11, 0
	jal  t6, clear_screen_sub

	li   ra, 0x00000000         # Soft-boot back vector
	jr   s0                     # Jump and run user program!

char_newline_then_prompt:
	jal  ra, char_newline
	j    print_prompt

# Output character to BOTH Screen and UART
out_char:
	addi sp, sp, -8
	sw   ra, 0(sp)
	sw   a0, 4(sp)

	# 1. Send to UART TX
	li   t1, UART_STAT_ADDR
uart_tx_wait:
	lw   t2, 0(t1)
	andi t2, t2, 0x2            # Bit 1 = TX ready
	beqz t2, uart_tx_wait
	li   t1, UART_DATA_ADDR
	sb   a0, 0(t1)

	# 2. Draw on Screen
	jal  ra, draw_char

	lw   a0, 4(sp)
	lw   ra, 0(sp)
	addi sp, sp, 8
	jr   ra

# =====================================================================
# GRAPHIC FONT ENGINE (320x200 16-bit RGB565)
# =====================================================================

# Clears Graphic RAM (320x200 = 64,000 pixels = 32,000 words = 128 KB)
clear_screen_sub:
	mv   t0, s5                 # t0 = GRAPHIC_RAM
	li   t1, 4000               # 32,000 words / 8 per iteration
	# Pack two 16-bit background pixels into one 32-bit word:
	slli t3, s8, 16
	or   t3, t3, s8
clear_loop:
	sw   t3, 0(t0)
	sw   t3, 4(t0)
	sw   t3, 8(t0)
	sw   t3, 12(t0)
	sw   t3, 16(t0)
	sw   t3, 20(t0)
	sw   t3, 24(t0)
	sw   t3, 28(t0)
	addi t0, t0, 32
	addi t1, t1, -1
	bnez t1, clear_loop
	jr   t6

# Renders ASCII character in a0 to Graphic RAM
draw_char:
	li   t0, 0x0A
	beq  a0, t0, char_newline
	li   t0, 0x0D
	beq  a0, t0, char_newline

	li   t0, ' '
	beq  a0, t0, draw_char_advance

	jal  t6, get_glyph

	# Pixel Base X = s10 * 5, Base Y = s11 * 6
	slli t0, s10, 2             # X * 4
	add  t0, t0, s10            # X * 5 (BaseX)
	slli t1, s11, 2             # Y * 4
	slli t2, s11, 1             # Y * 2
	add  t1, t1, t2             # Y * 6 (BaseY)

	# BaseY * 320 = (BaseY * 256) + (BaseY * 64)
	slli t4, t1, 8              # BaseY * 256
	slli t5, t1, 6              # BaseY * 64
	add  t4, t4, t5             # BaseY * 320
	add  t4, t4, t0             # + BaseX
	slli t4, t4, 1              # -> byte offset (* 2 for 16-bit pixels)
	add  t4, t4, s5             # + GRAPHIC_RAM

	li   a7, 19
	li   t2, 0                  # Row counter (0..4)

draw_row:
	srl  t5, a1, a7
	andi t5, t5, 1
	beqz t5, dc_bg0
	sh   s9, 0(t4)
	j    dc_next0
dc_bg0:
	sh   s8, 0(t4)
dc_next0:
	addi a7, a7, -1

	srl  t5, a1, a7
	andi t5, t5, 1
	beqz t5, dc_bg1
	sh   s9, 2(t4)
	j    dc_next1
dc_bg1:
	sh   s8, 2(t4)
dc_next1:
	addi a7, a7, -1

	srl  t5, a1, a7
	andi t5, t5, 1
	beqz t5, dc_bg2
	sh   s9, 4(t4)
	j    dc_next2
dc_bg2:
	sh   s8, 4(t4)
dc_next2:
	addi a7, a7, -1

	srl  t5, a1, a7
	andi t5, t5, 1
	beqz t5, dc_bg3
	sh   s9, 6(t4)
	j    dc_next3
dc_bg3:
	sh   s8, 6(t4)
dc_next3:
	addi a7, a7, -1

	addi t4, t4, 640            # Next row down (320 pixels * 2 bytes)
	addi t2, t2, 1
	li   t5, 5                  # 5 rows
	blt  t2, t5, draw_row

draw_char_advance:
	addi s10, s10, 1
	li   t0, 64                 # 64 Columns max (320 / 5)
	blt  s10, t0, draw_char_done

char_newline:
	li   s10, 0                 # Reset X
	addi s11, s11, 1            # Y++
	li   t0, 33                 # 33 Rows max (200 / 6)
	blt  s11, t0, draw_char_done

	# Cursor wrapped past bottom row -> Reset and clear
	li   s11, 0
	jal  t6, clear_screen_sub

draw_char_done:
	jr   ra

get_glyph:
	li   t0, '0'
	beq  a0, t0, g_0
	li   t0, '1'
	beq  a0, t0, g_1
	li   t0, '2'
	beq  a0, t0, g_2
	li   t0, '3'
	beq  a0, t0, g_3
	li   t0, '4'
	beq  a0, t0, g_4
	li   t0, '5'
	beq  a0, t0, g_5
	li   t0, '6'
	beq  a0, t0, g_6
	li   t0, '7'
	beq  a0, t0, g_7
	li   t0, '8'
	beq  a0, t0, g_8
	li   t0, '9'
	beq  a0, t0, g_9
	li   t0, 'A'
	beq  a0, t0, g_A
	li   t0, 'B'
	beq  a0, t0, g_B
	li   t0, 'C'
	beq  a0, t0, g_C
	li   t0, 'D'
	beq  a0, t0, g_D
	li   t0, 'E'
	beq  a0, t0, g_E
	li   t0, 'F'
	beq  a0, t0, g_F
	li   t0, 'R'
	beq  a0, t0, g_R
	li   t0, ':'
	beq  a0, t0, g_colon
	li   t0, '>'
	beq  a0, t0, g_gt
g_space:
	li   a1, 0x00000; jr t6
g_0:	li   a1, 0x69996; jr t6
g_1:	li   a1, 0x4C44E; jr t6
g_2:	li   a1, 0x6924F; jr t6
g_3:	li   a1, 0xF161F; jr t6
g_4:	li   a1, 0x99F11; jr t6
g_5:	li   a1, 0xF8E1E; jr t6
g_6:	li   a1, 0x78E96; jr t6
g_7:	li   a1, 0xF1244; jr t6
g_8:	li   a1, 0x69696; jr t6
g_9:	li   a1, 0x69716; jr t6
g_A:	li   a1, 0x69F99; jr t6
g_B:	li   a1, 0xE9E9E; jr t6
g_C:	li   a1, 0x69896; jr t6
g_D:	li   a1, 0xE999E; jr t6
g_E:	li   a1, 0xF8E8F; jr t6
g_F:	li   a1, 0xF8E88; jr t6
g_R:	li   a1, 0xE9EA9; jr t6
g_colon:li   a1, 0x02020; jr t6
g_gt:	li   a1, 0x84248; jr t6