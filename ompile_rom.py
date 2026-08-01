# compile_rom.py (Little-Endian Intel HEX Output)

def calculate_checksum(data_bytes):
	# 2's complement of the sum of all record bytes
	total = sum(data_bytes) & 0xFF
	return ((~total + 1) & 0xFF)

def compile_rom():
	rom_data = [0] * 32

	with open("control_rom.txt", "r") as f:
		for line_num, line in enumerate(f, 1):
			line = line.strip()
			if not line or line.startswith("#"):
				continue

			try:
				code_part = line.split('#')[0].strip()
				opcode_str, signals_str = code_part.split(';')

				opcode_clean = opcode_str.strip()
				rom_idx = int(opcode_clean[:5], 2)

				signals_clean = signals_str.replace(" ", "").strip()
				signal_val = int(signals_clean, 2)

				rom_data[rom_idx] = signal_val

			except Exception as e:
				print(f"Error on line {line_num}: {line}\n -> {e}")

	# Output to Little-Endian Intel HEX format
	with open("control_rom.hex", "w") as f_out:
		for i, val in enumerate(rom_data):
			byte_count = 0x02
			addr_hi = (i * 2) >> 8
			addr_lo = (i * 2) & 0xFF
			record_type = 0x00

			# Split into Little-Endian byte order (LSB first, MSB second)
			val_lsb = val & 0xFF
			val_msb = (val >> 8) & 0xFF

			data = [byte_count, addr_hi, addr_lo, record_type, val_lsb, val_msb]
			chk = calculate_checksum(data)

			f_out.write(f":{byte_count:02X}{addr_hi:02X}{addr_lo:02X}{record_type:02X}{val_lsb:02X}{val_msb:02X}{chk:02X}\n")

		# End of File Record
		f_out.write(":00000001FF\n")

	print("Successfully compiled 'control_rom.txt'")

if __name__ == "__main__":
	compile_rom()