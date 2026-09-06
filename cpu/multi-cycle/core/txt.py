import shutil
from pathlib import Path

# Automatically get the folder where this Python file is located
CURRENT_DIR = Path(__file__).resolve().parent
OUTPUT_DIR = CURRENT_DIR / "txt_copies"

# Create the output folder if it doesn't exist
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

THIS_SCRIPT = Path(__file__).resolve()

for file_path in CURRENT_DIR.iterdir():
    # Only copy files, ignore folders and don't copy the script itself
    if file_path.is_file() and file_path.resolve() != THIS_SCRIPT:
        dest_file = OUTPUT_DIR / f"{file_path.stem}.txt"

        shutil.copy2(file_path, dest_file)
        print(f"Copied: {file_path.name} -> {dest_file.name}")

print("\nDone! All text copies saved to 'txt_copies'.")