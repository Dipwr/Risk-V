import os
import subprocess
import sys


def calculate_checksum(data_bytes):
	"""Calculates the 2's complement Intel HEX checksum."""
	total = sum(data_bytes) & 0xFF
	return (~total + 1) & 0xFF


def assemble_to_binary(asm_file, bin_file):
	"""Compiles RISC-V assembly into raw machine code binary using GCC toolchain."""
	obj_file = "temp_build.o"

	# 1. Assemble .s file to .o object file (forcing RV32I architecture)
	as_cmd = [
		"riscv64-linux-gnu-as",
		"-march=rv32i",
		"-mabi=ilp32",
		asm_file,
		"-o",
		obj_file,
	]

	# 2. Extract raw binary payload from object file
	objcopy_cmd = [
		"riscv64-linux-gnu-objcopy",
		"-O",
		"binary",
		obj_file,
		bin_file,
	]

	try:
		subprocess.run(as_cmd, check=True)
		subprocess.run(objcopy_cmd, check=True)
	except FileNotFoundError:
		print(
			"Error: RISC-V toolchain not found! Make sure 'binutils-riscv64-linux-gnu' is installed."
		)
		sys.exit(1)
	except subprocess.CalledProcessError as e:
		print(f"Error during assembly: {e}")
		sys.exit(1)
	finally:
		if os.path.exists(obj_file):
			os.remove(obj_file)


def binary_to_hex_formats(bin_file, ihex_file, raw_hex_file):
	"""Converts raw binary machine code into both Intel HEX and space-separated 32-bit HEX formats."""
	with open(bin_file, "rb") as f_in:
		raw_bytes = f_in.read()

	# Pad binary length to a multiple of 4 bytes (32-bit instruction alignment)
	remainder = len(raw_bytes) % 4
	if remainder != 0:
		raw_bytes += b"\x00" * (4 - remainder)

	raw_words = []

	with open(ihex_file, "w") as f_ihex:
		# Process 4 bytes (one 32-bit word) at a time
		for i in range(0, len(raw_bytes), 4):
			chunk = raw_bytes[i : i + 4]
			b0, b1, b2, b3 = chunk[0], chunk[1], chunk[2], chunk[3]

			# --- 1. INTEL HEX FORMAT ---
			byte_addr = i
			byte_count = 0x04
			addr_hi = (byte_addr >> 8) & 0xFF
			addr_lo = byte_addr & 0xFF
			record_type = 0x00

			data = [byte_count, addr_hi, addr_lo, record_type, b0, b1, b2, b3]
			chk = calculate_checksum(data)

			f_ihex.write(
				f":{byte_count:02X}{addr_hi:02X}{addr_lo:02X}{record_type:02X}"
				f"{b0:02X}{b1:02X}{b2:02X}{b3:02X}{chk:02X}\n"
			)

			# --- 2. RAW / SPACE-SEPARATED HEX FORMAT ---
			# Combine 4 bytes into a single 32-bit word (Little-Endian)
			word32 = (b3 << 24) | (b2 << 16) | (b1 << 8) | b0
			raw_words.append(f"{word32:08X}")

		# Write End-Of-File (EOF) record for Intel HEX
		f_ihex.write(":00000001FF\n")

	# Write space-separated raw hex words to the raw hex file
	with open(raw_hex_file, "w") as f_raw:
		f_raw.write(" ".join(raw_words))


def main():
	asm_file = sys.argv[1] if len(sys.argv) > 1 else "program.s"
	base_name = os.path.splitext(asm_file)[0]

	ihex_file = sys.argv[2] if len(sys.argv) > 2 else f"{base_name}.intel.hex"
	raw_hex_file = sys.argv[3] if len(sys.argv) > 3 else f"{base_name}.hex"
	bin_file = "temp_build.bin"

	if not os.path.exists(asm_file):
		print(f"Error: Source assembly file '{asm_file}' not found.")
		sys.exit(1)

	print(f"Assembling '{asm_file}'...")
	assemble_to_binary(asm_file, bin_file)

	print(f"Generating Intel HEX  -> '{ihex_file}'...")
	print(f"Generating Normal HEX -> '{raw_hex_file}'...")
	binary_to_hex_formats(bin_file, ihex_file, raw_hex_file)

	if os.path.exists(bin_file):
		os.remove(bin_file)

	print("Done! Files ready for Digital and Wozmon.")


if __name__ == "__main__":
	main()