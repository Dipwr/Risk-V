.section .text
.globl _start

_start:
	# Preserve Wozmon Return Address (0x00000000) in s2 (overwriting white color later when needed)
	# Or simply re-initialize ra at the end of the program.

	# Point s0 to Graphic RAM MMIO Base Address (0x00080000)
	lui	s0, 0x00080

	# Colors (RGB555 high-color format)
	lui	s1, 0x00008			# Black = 0x8000

	# --- RENDER LOOP INITIALIZATION ---
	addi	s3, zero, 0			# Y = 0 (Row counter)
	li	s10, 64				# Max iterations (Increased for fidelity)

row_loop:
	addi	s4, zero, 0			# X = 0 (Column counter)

col_loop:
	# -------------------------------------------------------------
	# 1. MAP SCREEN (X, Y) TO COMPLEX PLANE (Cr, Ci) in Q2.14 format
	# -------------------------------------------------------------
	# Cr = (X * 256) - 32768
	slli	s5, s4, 8			# s5 = X * 256
	li	t4, 32768
	sub	s5, s5, t4			# s5 (Cr) = (X * 256) - 32768

	# Ci = (Y * 393) - 19660
	slli	t1, s3, 8			# Y * 256
	slli	t2, s3, 7			# Y * 128
	add	t1, t1, t2			# Y * 384
	slli	t2, s3, 3			# Y * 8
	add	t1, t1, t2			# Y * 392
	add	t1, t1, s3			# + Y = Y * 393
	li	t4, 19660
	sub	s6, t1, t4			# s6 (Ci) = (Y * 393) - 19660

	# -------------------------------------------------------------
	# 2. MANDELBROT ITERATION: Zr = 0, Zi = 0
	# -------------------------------------------------------------
	addi	s7, zero, 0			# s7 (Zr) = 0
	addi	s8, zero, 0			# s8 (Zi) = 0
	addi	s9, zero, 0			# s9 (Iteration count) = 0

iter_loop:
	# Compute Zr * Zr
	addi	a0, s7, 0
	addi	a1, s7, 0
	jal	ra, multiply			# a2 = Zr * Zr
	srai	s11, a2, 14			# s11 = Zr^2 (Q2.14 format)

	# Compute Zi * Zi
	addi	a0, s8, 0
	addi	a1, s8, 0
	jal	ra, multiply			# a2 = Zi * Zi
	srai	t3, a2, 14			# t3 = Zi^2 (Q2.14 format)

	# Escape check: Zr^2 + Zi^2 > 65536 (4.0 in Q2.14)
	add	t0, s11, t3
	li	t1, 65536
	bgt	t0, t1, render_pixel		# Escaped!

	# Iteration limit check
	addi	s9, s9, 1
	bge	s9, s10, render_pixel		# Reached max iterations

	# Compute 2 * Zr * Zi
	addi	a0, s7, 0
	addi	a1, s8, 0
	jal	ra, multiply			# a2 = Zr * Zi
	srai	a2, a2, 14			# Return to Q2.14 (MUST be srai for signs)
	slli	a2, a2, 1			# a2 = 2 * Zr * Zi

	# Compute new Zr: Zr = Zr^2 - Zi^2 + Cr
	sub	t0, s11, t3			# Zr^2 - Zi^2
	add	s7, t0, s5			# new Zr = + Cr

	# Compute new Zi: Zi = 2 * Zr * Zi + Ci
	add	s8, a2, s6			# new Zi = + Ci

	j	iter_loop

render_pixel:
	# -------------------------------------------------------------
	# 3. CHOOSE COLOR BASED ON ESCAPE ITERATION (s9)
	# -------------------------------------------------------------
	beq	s9, s10, is_black		# Max iterations = Inside set = Black

	slli	a2, s9, 3			# Scale color index
	lui	a5, 0x00008			# Base high-color bit
	add	a2, a2, a5			# Colorful escape shade
	j	write_pixel

is_black:
	addi	a2, s1, 0			# Black color (0x8000)

write_pixel:
	# -------------------------------------------------------------
	# 4. WRITE PIXEL TO SCREEN BUFFER: Index = (Y * 160) + X
	# -------------------------------------------------------------
	slli	t4, s3, 7			# Y * 128
	slli	t5, s3, 5			# Y * 32 (Using t5 to not clobber limits)
	add	t4, t4, t5			# Y * 160
	add	t4, t4, s4			# + X
	slli	t4, t4, 2			# 32-bit word byte offset (* 4)
	add	t4, s0, t4			# Target memory address (0x00080000 + offset)

	sw	a2, 0(t4)			# Blast pixel to Graphic RAM!

	# -------------------------------------------------------------
	# 5. ADVANCE LOOP COUNTERS
	# -------------------------------------------------------------
	addi	s4, s4, 1			# X++
	li	t0, 160
	blt	s4, t0, col_loop

	addi	s3, s3, 1			# Y++
	li	t0, 100
	blt	s3, t0, row_loop

done:
	# -------------------------------------------------------------
	# EXIT BACK TO WOZMON
	# -------------------------------------------------------------
	li	ra, 0x00000000			# Restore Wozmon entry point address
	ret					# Jump back to Wozmon monitor prompt!

# =====================================================================
# SIGN-AWARE SOFTWARE MULTIPLY SUBROUTINE (Inputs: a0, a1 -> Output: a2)
# Handles negative numbers correctly for Q2.14 bounds.
# Uses t1, t2 as scratch.
# =====================================================================
multiply:
	addi	a2, zero, 0			# Product = 0
	addi	t1, zero, 0			# Sign tracker (0 = pos, 1 = neg)

	bge	a0, zero, mul_check_a1
	sub	a0, zero, a0			# a0 = Abs(a0)
	xori	t1, t1, 1			# Flip sign tracker

mul_check_a1:
	bge	a1, zero, mul_loop
	sub	a1, zero, a1			# a1 = Abs(a1)
	xori	t1, t1, 1			# Flip sign tracker

mul_loop:
	beq	a1, zero, mul_done		# While multiplier != 0
	andi	t2, a1, 1			# Check lowest bit
	beq	t2, zero, mul_skip
	add	a2, a2, a0			# Product += multiplicand
mul_skip:
	slli	a0, a0, 1			# Multiplicand <<= 1
	srli	a1, a1, 1			# Multiplier >>= 1
	j	mul_loop

mul_done:
	beq	t1, zero, mul_return		# If sign tracker is 0, we are done
	sub	a2, zero, a2			# Otherwise, negate the product

mul_return:
	jalr	zero, 0(ra)			# Return from subroutine