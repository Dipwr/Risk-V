import time
from pynput import keyboard
from pynput.keyboard import Controller, Key
import pyperclip

keyboard_controller = Controller()

# Store last execution timestamp to prevent double-firing
last_trigger_time = 0.0


def type_clipboard():
	global last_trigger_time

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
		return

	print(f"\n[+] Typing clipboard contents ({len(text)} chars)...")

	# Small pause to ensure physical shortcut keys are fully released by OS
	time.sleep(0.3)

	# 2. Type character by character into the focused window
	for char in text:
		if char == "\n":
			keyboard_controller.press(Key.enter)
			keyboard_controller.release(Key.enter)
		elif char == "\r":
			continue  # Skip carriage returns
		else:
			keyboard_controller.type(char)

		# 1ms delay so Digital's FIFO queue keeps up
		time.sleep(0.001)

	print("[+] Done!")


def main():
	HOTKEY = "<ctrl>+<shift>+v"

	print("==================================================")
	print(" Digital Hardware Auto-Typer Running (Debounced)")
	print(" 1. Copy your hex/text normally (Ctrl+C).")
	print(" 2. Click on the Keyboard component in Digital.")
	print(" 3. Press 'Ctrl+Shift+V' to auto-type.")
	print(" Press Ctrl+C in this terminal to exit.")
	print("==================================================")

	with keyboard.GlobalHotKeys({HOTKEY: type_clipboard}) as h:
		h.join()


if __name__ == "__main__":
	try:
		main()
	except KeyboardInterrupt:
		print("\nExiting Auto-Typer.")