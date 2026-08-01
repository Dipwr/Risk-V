
	# MMIO Page Register (GrRAM Page: 0x000A0000 - 0x000A0003)
	lui	s8, 0x000A0                  # MMIO Page Register Base (0x000A0000)

	# Colors
	lui	s1, 0x00008                  # Black (0x8000)
	lui	s2, 0x10000
	addi	s2, s2, -1                   # White (0xFFFF)

	# Physics State
	addi	s3, zero, 20                 # Current X
	addi	s4, zero, 20                 # Current Y
	addi	s5, zero, 1                  # dX = +1
	addi	s6, zero, 1                  # dY = +1
	addi	s7, zero, 0                  # Displayed Buffer (0 or 1)

	# Buffer 0 History
	addi	s9, zero, 20                 # Buffer 0 Old X
	addi	s10, zero, 20                # Buffer 0 Old Y

	# Buffer 1 History
	addi	a3, zero, 20                 # Buffer 1 Old X
	addi	a4, zero, 20                 # Buffer 1 Old Y

	# Initialize hardware Page register
	sw	zero, 0(s8)

frame_loop:
	# -------------------------------------------------------------
	# 1. IDENTIFY OFF-SCREEN BUFFER
	# -------------------------------------------------------------
	xori	t0, s7, 1                    # t0 is the buffer we DRAW TO
	bne	t0, zero, draw_buffer_1      # If t0 == 1, branch to Buffer 1

draw_buffer_0:
	lui	s0, 0x00080                  # s0 = Buffer 0 Base Address (0x00080000)

	# Erase old box in Buffer 0
	addi	a0, s9, 0
	addi	a1, s10, 0
	addi	a2, s2, 0                    # White
	jal	ra, fast_draw_4x4

	# Draw new box in Buffer 0
	addi	a0, s3, 0
	addi	a1, s4, 0
	addi	a2, s1, 0                    # Black
	jal	ra, fast_draw_4x4

	# Update Buffer 0 history to current position
	addi	s9, s3, 0
	addi	s10, s4, 0
	j	finish_draw

draw_buffer_1:
	lui	s0, 0x00090                  # Start with 0x00090000
	addi	s0, s0, -1536                # Subtract 1536 to hit 0x0008FA00!

	# Erase old box in Buffer 1
	addi	a0, a3, 0
	addi	a1, a4, 0
	addi	a2, s2, 0                    # White
	jal	ra, fast_draw_4x4

	# Draw new box in Buffer 1
	addi	a0, s3, 0
	addi	a1, s4, 0
	addi	a2, s1, 0                    # Black
	jal	ra, fast_draw_4x4

	# Update Buffer 1 history to current position
	addi	a3, s3, 0
	addi	a4, s4, 0

finish_draw:
	# -------------------------------------------------------------
	# 2. FLIP DISPLAY
	# -------------------------------------------------------------
	xori	s7, s7, 1                    # Toggle display state
	sw	s7, 0(s8)                    # Write to Page Register (0x000A0000)

	# -------------------------------------------------------------
	# 3. ADVANCE PHYSICS FOR NEXT FRAME
	# -------------------------------------------------------------
	add	s3, s3, s5                   # X = X + dX
	add	s4, s4, s6                   # Y = Y + dY

	# Bounce checks
	blez	s3, invert_x
	addi	t0, zero, 156
	bge	s3, t0, invert_x
	j	check_y

invert_x:
	sub	s5, zero, s5

check_y:
	blez	s4, invert_y
	addi	t0, zero, 96
	bge	s4, t0, invert_y
	j	frame_loop

invert_y:
	sub	s6, zero, s6
	j	frame_loop


# =====================================================================
# HYPER-FAST DRAW SUBROUTINE
# =====================================================================
fast_draw_4x4:
	# Shift-Add: (Y * 160) = (Y * 128) + (Y * 32)
	slli	t4, a1, 7
	slli	t5, a1, 5
	add	t4, t4, t5
	add	t4, t4, a0                   # Pixel Index = (Y * 160) + X
	slli	t4, t4, 2                    # Byte offset = Index * 4
	add	t4, s0, t4                   # Memory Target = Base + Offset

	addi	t1, zero, 640                # Row Stride (160 pixels * 4 bytes)

	# Row 0
	sw	a2, 0(t4)
	sw	a2, 4(t4)
	sw	a2, 8(t4)
	sw	a2, 12(t4)
	add	t4, t4, t1

	# Row 1
	sw	a2, 0(t4)
	sw	a2, 4(t4)
	sw	a2, 8(t4)
	sw	a2, 12(t4)
	add	t4, t4, t1

	# Row 2
	sw	a2, 0(t4)
	sw	a2, 4(t4)
	sw	a2, 8(t4)
	sw	a2, 12(t4)
	add	t4, t4, t1

	# Row 3
	sw	a2, 0(t4)
	sw	a2, 4(t4)
	sw	a2, 8(t4)
	sw	a2, 12(t4)

	jalr	zero, 0(ra)
