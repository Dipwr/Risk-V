#!/usr/bin/env python3
"""Convert a raw RISC-V binary into a 256 KB (65536-word) 32-bit hex file for $readmemh."""

import argparse
import struct
from pathlib import Path


TOTAL_WORDS = 65536


def main() -> None:
	parser = argparse.ArgumentParser(
		description="Convert raw .bin into 65536-word 32-bit little-endian .mem file."
	)
	parser.add_argument("input_bin", type=Path, help="Input flat binary path")
	parser.add_argument("output_mem", type=Path, help="Output .mem hex file path")
	parser.add_argument(
		"--words",
		type=int,
		default=TOTAL_WORDS,
		help=f"Total 32-bit words in output file (default: {TOTAL_WORDS})",
	)
	args = parser.parse_args()

	data = args.input_bin.read_bytes()
	max_bytes = args.words * 4
	if len(data) > max_bytes:
		raise SystemExit(
			f"Error: {args.input_bin} ({len(data)} bytes) exceeds {max_bytes} bytes"
		)

	padded = data + b"\x00" * (max_bytes - len(data))
	words = struct.unpack(f"<{args.words}I", padded)

	args.output_mem.parent.mkdir(parents=True, exist_ok=True)
	with args.output_mem.open("w", encoding="ascii") as f:
		for word in words:
			f.write(f"{word:08x}\n")


if __name__ == "__main__":
	main()
