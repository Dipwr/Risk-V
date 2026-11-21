import argparse
import sys


def convert_bin_to_hex(input_path, output_path, addr="10000"):
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

	# Wrap with Wozmon load address, words, newline, and run command
	payload = f"{addr}:{' '.join(words)}\n{addr}r\n"

	with open(output_path, "w") as f:
		f.write(payload)


def main():
	parser = argparse.ArgumentParser(
		description="Convert raw binary to Wozmon hex paste payload."
	)
	parser.add_argument("input_file", nargs="?", default="out/program.bin")
	parser.add_argument("output_file", nargs="?", default="out/program.hex")
	parser.add_argument(
		"--addr",
		default="10000",
		help="Wozmon hex load/run address (default: 10000)",
	)
	args = parser.parse_args()
	convert_bin_to_hex(args.input_file, args.output_file, addr=args.addr)


if __name__ == "__main__":
	main()
