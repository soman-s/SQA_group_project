import string
import utils
from constants import Constants

def get_daily_transactions():
    pass

def update_files():
    pass

def read_file_contents(file_name: str) -> list[str]:
    try:
        with open(file_name, 'r') as file:
            # Read all lines from the file and store them in a list
            lines = file.readlines()
            # Remove newline characters from each line
            lines = [line.strip() for line in lines]
            return lines
    except FileNotFoundError:
        print(f"Error: File '{file_name}' not found.")
        return []

def write_file_contents(output_file_name: str, contents:list[str]):
    print("CONTENTS TO WRITE")
    for line in contents:
        print(line)

    try:
        with open(output_file_name, 'w') as file:
            for line in contents:
                file.write(line + '\n')  # Write each line to the file, adding a newline character
        print(f"Contents written to '{output_file_name}' successfully.")
    except Exception as e:
        print(f"Error writing to file '{output_file_name}': {e}")

    pass
