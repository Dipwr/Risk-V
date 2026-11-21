import argparse
import re
import time
import serial


RUN_CMD_RE = re.compile(r"^[0-9A-Fa-f]+[rR]$")


def prepare_payload(raw_text, no_run=False):
	lines = raw_text.splitlines()
	while lines and not lines[-1].strip():
		lines.pop()
	if not lines:
		return raw_text

	has_trailing_run = bool(RUN_CMD_RE.match(lines[-1].strip()))
	if no_run:
		if has_trailing_run:
			lines.pop()
		return "\n".join(lines) + "\n" if lines else ""

	if has_trailing_run:
		# Strip any trailing newline after '<addr>r' so it isn't left in UART RX
		return "\n".join(lines)
	return raw_text


def main():
	parser = argparse.ArgumentParser(
		description="Upload Wozmon hex payload over UART serial."
	)
	parser.add_argument(
		"hex_file",
		nargs="?",
		default="out/multi_cycle/dvd_bounce/program.hex",
		help="Path to Wozmon .hex file",
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
		"--delay",
		type=float,
		default=0.01,
		help="Per-character delay in seconds (default: 0.01)",
	)
	parser.add_argument(
		"--no-run",
		action="store_true",
		help="Upload words to RAM and return to Wozmon prompt without running",
	)
	args = parser.parse_args()

	with open(args.hex_file, "r") as f:
		payload = prepare_payload(f.read(), no_run=args.no_run)

	with serial.Serial(args.port, args.baud) as ser:
		for char in payload:
			ser.write(char.encode())
			if args.delay > 0:
				time.sleep(args.delay)


if __name__ == "__main__":
	main()
