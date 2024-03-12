import string
import utils
import os
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
            lines = [line.rstrip('\n') for line in lines]  # Strip newline characters from the end of each line
            lines = [line.lstrip('\n') for line in lines]  # Strip newline characters from the beginning of each line
            return lines
    except FileNotFoundError:
        print(f"Error: File '{file_name}' not found.")
        return []

def write_file_contents(output_file_name: str, contents:list[str]):
    # print("CONTENTS TO WRITE")
    # for line in contents:
    #     print(line)

    try:
        with open(output_file_name, 'w') as file:
            for line in contents:
                file.write(line + '\n')  # Write each line to the file, adding a newline character
        print(f"Contents written to '{output_file_name}' successfully.")
    except Exception as e:
        print(f"Error writing to file '{output_file_name}': {e}")

    pass

def update_and_write_file(output_file: str, data: list[str], end_length: int):
    file_ending = utils.pad_end_file(end_length)
    data.append(file_ending)
    write_file_contents(output_file, data)



# Function to merge daily transaction files
def merge_daily_transaction_files(input_folder, output_file):
    with open(output_file, 'w') as outfile:
        for filename in sorted(os.listdir(input_folder)):
            if 'daily_transaction' in filename and filename !=Constants.MERGE_DAILY_TRANSACTION_FILENAME:
                with open(os.path.join(input_folder, filename), 'r') as infile:
                    for line in infile:
                        outfile.write(line)

        # Add a line with a 00 transaction code at the end
        outfile.write("00\n")
