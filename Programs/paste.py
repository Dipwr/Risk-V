import sys
import pyperclip


def main():
	if len(sys.argv) < 2:
		print("[!] Usage: python paste.py <path_to_hex_file>")
		sys.exit(1)

	hex_file = sys.argv[1]
	try:
		with open(hex_file, "r") as f:
			content = f.read().strip()
			pyperclip.copy(content)
			print(
				f"[+] Successfully copied '{hex_file}' ({len(content)} chars) to clipboard!"
			)
	except Exception as e:
		print(f"[!] Could not read '{hex_file}': {e}")
		sys.exit(1)


if __name__ == "__main__":
	main()