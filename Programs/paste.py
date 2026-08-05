import sys
import time
from pynput import keyboard
from pynput.keyboard import Controller, Key
import pyperclip

keyboard_controller = Controller()

# Store last execution timestamp to prevent double-firing
last_trigger_time = 0.0
done = False


def type_clipboard():
	global last_trigger_time, done

	current_time = time.time()
	# Ignore any trigger that happens within 1.0 second of the last one
	if (current_time - last_trigger_time) < 1.0:
		return

	# Record execution time immediately
	last_trigger_time = current_time

	# 1. Fetch text from system clipboard
	text = pyperclip.paste()
	if not text:
		print("\n[!] Clipboard is empty!")
		done = True
		return

	print(f"\n[+] Typing clipboard contents ({len(text)} chars)...")

	# Small pause to ensure physical shortcut keys are fully released by OS
	time.sleep(0.3)

	# 2. Type character by character into the focused window
	for char in text:
		time.sleep(0.0005)
		if char == "\n":
			keyboard_controller.press(Key.enter)
			keyboard_controller.release(Key.enter)
		elif char == "\r":
			continue  # Skip carriage returns
		else:
			keyboard_controller.type(char)

	print("[+] Done! Exiting auto-typer.")

	# Signal main thread to exit
	done = True


def main():
	HOTKEY = "<ctrl>+<shift>+v"

	print("==================================================")
	print(" Digital Hardware Auto-Typer Running (One-Shot)")
	print(" 1. Click on the Keyboard component in Digital.")
	print(" 2. Press 'Ctrl+Shift+V' to auto-type.")
	print(" Program will auto-exit when pasting finishes.")
	print("==================================================")

	with keyboard.GlobalHotKeys({HOTKEY: type_clipboard}) as h:
		# Wait until typing finishes
		while not done:
			time.sleep(0.1)

	# Clean exit from main thread
	sys.exit(0)


if __name__ == "__main__":
	# If a file path was passed as an argument, copy its content to clipboard first
	if len(sys.argv) > 1:
		hex_file = sys.argv[1]
		try:
			with open(hex_file, "r") as f:
				content = f.read().strip()
				pyperclip.copy(content)
				print(
					f"[+] Copied '{hex_file}' ({len(content)} chars) to system clipboard!"
				)
		except Exception as e:
			print(f"[!] Could not read '{hex_file}': {e}")

	try:
		main()
	except KeyboardInterrupt:
		print("\nExiting Auto-Typer.")