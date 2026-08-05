import sys


def convert_bin_to_hex(input_path, output_path):
	with open(input_path, "rb") as f:
		raw = f.read()

	# Pad to 4-byte boundary
	remainder = len(raw) % 4
	if remainder != 0:
		raw += b"\x00" * (4 - remainder)

	# Convert little-endian bytes to 32-bit hex words
	words = []
	for i in range(0, len(raw), 4):
		word32 = (
			(raw[i + 3] << 24)
			| (raw[i + 2] << 16)
			| (raw[i + 1] << 8)
			| raw[i]
		)
		words.append(f"{word32:08X}")

	with open(output_path, "w") as f:
		f.write(" ".join(words))


if __name__ == "__main__":
	in_file = sys.argv[1] if len(sys.argv) > 1 else "out/program.bin"
	out_file = sys.argv[2] if len(sys.argv) > 2 else "out/program.hex"
	convert_bin_to_hex(in_file, out_file)