#!/usr/bin/env python3
import argparse
import os
import struct
import sys
import time
import zlib

import serial

PROTO_ACK = 0x06
PROTO_NAK = 0x15


def parse_addr(val: str) -> int:
	return int(val, 0)


def read_ack_or_fail(ser: serial.Serial, stage: str) -> None:
	resp = ser.read(1)
	if len(resp) != 1:
		raise RuntimeError(f"{stage}: timed out waiting for bootloader ACK/NAK")
	code = resp[0]
	if code == PROTO_ACK:
		return
	if code == PROTO_NAK:
		err = ser.read(1)
		err_ch = chr(err[0]) if len(err) == 1 else "?"
		reasons = {
			"B": "bad header / address out of range",
			"U": "UART RX overrun or framing error",
			"C": "CRC32 mismatch",
			"T": "UART RX timeout waiting for data",
		}
		raise RuntimeError(
			f"{stage}: bootloader returned NAK ('{err_ch}': {reasons.get(err_ch, 'unknown error')})"
		)
	raise RuntimeError(f"{stage}: unexpected response byte 0x{code:02X}")


def main() -> int:
	parser = argparse.ArgumentParser(
		description="Upload a bare-metal binary to the Risk-V Phase 2 UART bootloader."
	)
	parser.add_argument(
		"bin_file",
		nargs="?",
		help="Path to program.bin (not required with --go-only)",
	)
	parser.add_argument(
		"--port",
		default="/dev/ttyUSB1",
		help="Serial port device (default: /dev/ttyUSB1)",
	)
	parser.add_argument(
		"--baud",
		type=int,
		default=115200,
		help="Baud rate (default: 115200)",
	)
	parser.add_argument(
		"--addr",
		type=parse_addr,
		default=0x00002000,
		help="Target load/entry address (default: 0x00002000)",
	)
	parser.add_argument(
		"--timeout",
		type=float,
		default=5.0,
		help="Serial read timeout in seconds (default: 5.0)",
	)
	parser.add_argument(
		"--go-only",
		action="store_true",
		help="Send RVGO <addr> to jump directly to a preloaded image in RAM",
	)
	parser.add_argument(
		"--monitor",
		action="store_true",
		help="Stream incoming UART output to stdout after boot until Ctrl+C",
	)
	args = parser.parse_args()

	if not args.go_only and not args.bin_file:
		parser.error("bin_file is required unless --go-only is set")

	with serial.Serial(args.port, args.baud, timeout=args.timeout) as ser:
		ser.reset_input_buffer()

		if args.go_only:
			pkt = b"RVGO" + struct.pack("<I", args.addr)
			ser.write(pkt)
			ser.flush()
			read_ack_or_fail(ser, "RVGO")
			print(f"[UPLOAD] Jumped to 0x{args.addr:08X} via RVGO")
		else:
			with open(args.bin_file, "rb") as f:
				data = f.read()
			if not data:
				raise RuntimeError("Input binary is empty")

			crc = zlib.crc32(data) & 0xFFFFFFFF
			header = b"RVBL" + struct.pack("<III", args.addr, len(data), crc)
			ser.write(header)
			ser.flush()
			read_ack_or_fail(ser, "Header")

			total = len(data)
			sent = 0
			chunk_size = 256
			t0 = time.monotonic()
			while sent < total:
				chunk = data[sent : sent + chunk_size]
				ser.write(chunk)
				sent += len(chunk)
				pct = (sent * 100) // total
				sys.stdout.write(f"\r[UPLOAD] {sent}/{total} bytes ({pct}%)")
				sys.stdout.flush()
			ser.flush()
			dt = max(time.monotonic() - t0, 1e-6)
			sys.stdout.write(
				f"\r[UPLOAD] {total}/{total} bytes (100%) in {dt:.2f}s "
				f"({total / dt / 1024:.1f} KB/s), CRC32=0x{crc:08X}\n"
			)
			sys.stdout.flush()

			read_ack_or_fail(ser, "CRC32")
			print(f"[UPLOAD] Verified & booting at 0x{args.addr:08X}")

		if args.monitor:
			print("[MONITOR] Streaming UART output (Ctrl+C to stop)...")
			try:
				while True:
					chunk = ser.read(ser.in_waiting or 1)
					if chunk:
						sys.stdout.write(chunk.decode("utf-8", errors="replace"))
						sys.stdout.flush()
			except KeyboardInterrupt:
				print("\n[MONITOR] Stopped.")

	return 0


if __name__ == "__main__":
	sys.exit(main())
