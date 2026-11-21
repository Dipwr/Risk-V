import argparse
import time
import serial


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
	args = parser.parse_args()

	with serial.Serial(args.port, args.baud) as ser:
		with open(args.hex_file, "r") as f:
			for char in f.read():
				ser.write(char.encode())
				if args.delay > 0:
					time.sleep(args.delay)


if __name__ == "__main__":
	main()
