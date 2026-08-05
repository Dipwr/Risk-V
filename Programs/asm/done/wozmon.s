.equ TERMINAL_ADDR, 0x000A0004
.equ KEY_DATA_ADDR, 0x000A0020
.equ KEY_STAT_ADDR, 0x000A0024
.equ RAM_BASE_ADDR, 0x00040000

.section .text
.globl _start

_start:
	# Default memory pointer initialized to RAM Base (0x00040000)
	li	s0, RAM_BASE_ADDR

print_prompt:
	# 1. Output Newline sequence: '\r', '\n', '\', ' '
	li	t1, TERMINAL_ADDR
	li	t0, 0x0D
	sb	t0, 0(t1)
	li	t0, 0x0A
	sb	t0, 0(t1)
	li	t0, 0x5C		# Backslash '\'
	sb	t0, 0(t1)
	li	t0, 0x20		# Space ' '
	sb	t0, 0(t1)

	# 2. Reset Accumulator & Flags
	li	s1, 0			# s1 = Parsed Hex Accumulator
	li	s2, 0			# s2 = Digit Flag (0 = no digits typed, 1 = digits typed)

read_char_loop:
	# -----------------------------------------------------------------
	# Keyboard Polling
	# -----------------------------------------------------------------
	li	t1, KEY_STAT_ADDR
poll_key:
	lw	t2, 0(t1)
	andi	t2, t2, 0x1
	beqz	t2, poll_key

	# Read byte from keyboard (triggers Keyboard.en with MemRead = 1)
	li	t1, KEY_DATA_ADDR
	lbu	a0, 0(t1)

	# Echo character back to terminal
	li	t1, TERMINAL_ADDR
	sb	a0, 0(t1)

	# -----------------------------------------------------------------
	# Command Delimiter / Special Character Detection
	# -----------------------------------------------------------------
	# Check for Enter ('\r' = 0x0D or '\n' = 0x0A) -> READ / EXECUTE MEMORY
	li	t0, 0x0D
	beq	a0, t0, handle_enter
	li	t0, 0x0A
	beq	a0, t0, handle_enter

	# Check for Colon (':') -> WRITE MEMORY MODE
	li	t0, ':'
	beq	a0, t0, handle_colon

	# Check for 'R' or 'r' -> RUN / JUMP TO PROGRAM
	li	t0, 'R'
	beq	a0, t0, handle_run
	li	t0, 'r'
	beq	a0, t0, handle_run

	# -----------------------------------------------------------------
	# Hex ASCII Parsing ('0'-'9', 'A'-'F', 'a'-'f')
	# -----------------------------------------------------------------
	li	t0, '0'
	blt	a0, t0, read_char_loop	# Ignore invalid characters < '0'
	li	t0, '9'
	bgt	a0, t0, try_hex_alpha
	addi	t0, a0, -'0'		# Convert '0'..'9' to 0..9
	j	append_nibble

try_hex_alpha:
	andi	a0, a0, 0xDF		# Convert lowercase 'a'..'f' to uppercase 'A'..'F'
	li	t0, 'A'
	blt	a0, t0, read_char_loop	# Ignore invalid characters < 'A'
	li	t0, 'F'
	bgt	a0, t0, read_char_loop	# Ignore invalid characters > 'F'
	addi	t0, a0, -55		# Map 'A'..'F' to 10..15 (65 - 55 = 10)

append_nibble:
	andi	t0, t0, 0xF		# Mask: Ensure t0 is strictly 4 bits
	slli	s1, s1, 4		# Shift accumulator left by 4 bits
	or	s1, s1, t0		# Merge new nibble into accumulator
	li	s2, 1			# Set digit flag = 1
	j	read_char_loop		# Continue reading on the SAME line!


# =====================================================================
# COMMAND HANDLERS
# =====================================================================

handle_enter:
	# If the user typed an address, update current memory pointer s0
	beqz	s2, do_read_mem
	mv	s0, s1

do_read_mem:
	# Print ": "
	li	t1, TERMINAL_ADDR
	li	t0, ':'
	sb	t0, 0(t1)
	li	t0, ' '
	sb	t0, 0(t1)

	# Fetch 32-bit word from memory at address s0
	lw	t4, 0(s0)

	# Format and print 32-bit word in hex (8 hex digits)
	li	t5, 28
print_word_loop:
	srl	t0, t4, t5
	andi	t0, t0, 0xF
	li	t1, 10
	blt	t0, t1, is_num
	addi	t0, t0, 55		# Map 10..15 -> 'A'..'F' (10 + 55 = 65 -> 'A')
	j	out_nibble
is_num:
	addi	t0, t0, '0'		# Map 0..9 -> '0'..'9' (0 + 48 = 48 -> '0')
out_nibble:
	li	t1, TERMINAL_ADDR
	sb	t0, 0(t1)
	addi	t5, t5, -4
	bge	t5, zero, print_word_loop

	# Advance address pointer by 4 bytes (1 word)
	addi	s0, s0, 4

	# Return to prompt
	j	print_prompt


handle_colon:
	# If address was typed prior to ':', update s0
	beqz	s2, write_mode_loop
	mv	s0, s1

write_mode_loop:
	# Reset accumulator for parsing data word
	li	s1, 0

parse_val_loop:
	# Poll keyboard
	li	t1, KEY_STAT_ADDR
poll_val_key:
	lw	t2, 0(t1)
	andi	t2, t2, 0x1
	beqz	t2, poll_val_key

	li	t1, KEY_DATA_ADDR
	lbu	a0, 0(t1)

	# Echo character
	li	t1, TERMINAL_ADDR
	sb	a0, 0(t1)

	# Space (' ') -> Store word and continue write mode
	li	t0, ' '
	beq	a0, t0, commit_write

	# Enter ('\r' / '\n') -> Store word and exit write mode
	li	t0, 0x0D
	beq	a0, t0, commit_write_end
	li	t0, 0x0A
	beq	a0, t0, commit_write_end

	# Parse hex digit
	li	t0, '0'
	blt	a0, t0, parse_val_loop
	li	t0, '9'
	bgt	a0, t0, try_val_alpha
	addi	t0, a0, -'0'
	j	shift_val_nibble

try_val_alpha:
	andi	a0, a0, 0xDF
	li	t0, 'A'
	blt	a0, t0, parse_val_loop
	li	t0, 'F'
	bgt	a0, t0, parse_val_loop
	addi	t0, a0, -55

shift_val_nibble:
	andi	t0, t0, 0xF
	slli	s1, s1, 4
	or	s1, s1, t0
	j	parse_val_loop

commit_write:
	sw	s1, 0(s0)		# Store word to RAM[s0]
	addi	s0, s0, 4		# Advance RAM pointer by 4 bytes
	j	write_mode_loop

commit_write_end:
	sw	s1, 0(s0)		# Store final word to RAM[s0]
	addi	s0, s0, 4
	j	print_prompt


handle_run:
	# If target address was typed before 'R', update s0
	beqz	s2, execute_jump
	mv	s0, s1

execute_jump:
	# Print newline ('\r', '\n') before handing execution to the RAM program
	li	t1, TERMINAL_ADDR
	li	t0, 0x0D
	sb	t0, 0(t1)
	li	t0, 0x0A
	sb	t0, 0(t1)

	# Set Return Address (ra) to ROM entry point (0x00000000)
	# So executing 'ret' in the RAM program soft-boots back into Wozmon
	li	ra, 0x00000000
	jr	s0			# Jump to target RAM address