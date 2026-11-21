import argparse
import sys


def convert_bin_to_hex(input_path, output_path, addr="10000", auto_run=True):
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

	# Wrap with Wozmon load address, words, newline, and optional run command.
	# Omit trailing newline after '<addr>r' since Wozmon jumps immediately on 'r'
	# and a stray '\n' in the UART RX FIFO would trigger key-exit checks.
	if auto_run:
		payload = f"{addr}:{' '.join(words)}\n{addr}r"
	else:
		payload = f"{addr}:{' '.join(words)}\n"

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
	parser.add_argument(
		"--no-run",
		action="store_true",
		help="Load words into RAM without appending the '<addr>r' run command",
	)
	args = parser.parse_args()
	convert_bin_to_hex(
		args.input_file, args.output_file, addr=args.addr, auto_run=not args.no_run
	)


if __name__ == "__main__":
	main()
