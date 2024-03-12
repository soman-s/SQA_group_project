import string
import utils
import os
from constants import Constants


def read_file_contents(file_name: str) -> list[str]:
    """
    Read the contents of a file and return them as a list of strings.

    Parameters:
        file_name (str): The name of the file to read.

    Returns:
        list[str]: A list containing the contents of the file as strings.
    """
    try:
        with open(file_name, 'r') as file:
            lines = file.readlines()
            lines = [line.rstrip('\n') for line in lines]
            lines = [line.lstrip('\n') for line in lines]
            return lines
    except FileNotFoundError:
        print(f"Error: File '{file_name}' not found.")
        return []


def write_file_contents(output_file_name: str, contents: list[str]):
    """
    Write the contents to a file.

    Parameters:
        output_file_name (str): The name of the file to write to.
        contents (list[str]): The contents to write to the file.
    """
    try:
        with open(output_file_name, 'w') as file:
            for line in contents:
                file.write(line + '\n')
        print(f"Contents written to '{output_file_name}' successfully.")
    except Exception as e:
        print(f"Error writing to file '{output_file_name}': {e}")


def update_and_write_file(output_file: str, data: list[str], end_length: int):
    """
    Update file contents and write back to the file.

    Parameters:
        output_file (str): The name of the output file to write to.
        data (list[str]): The data to write to the file.
        end_length (int): The length of padding to add at the end of the file.
    """
    file_ending = utils.pad_end_file(end_length)
    data.append(file_ending)
    write_file_contents(output_file, data)


def merge_daily_transaction_files(input_folder, output_file):
    """
    Merge daily transaction files into a single file.

    Parameters:
        input_folder (str): The folder containing the daily transaction files.
        output_file (str): The name of the output file to write the merged transactions.
    """
    with open(output_file, 'w') as outfile:
        for filename in sorted(os.listdir(input_folder)):
            if 'daily_transaction' in filename and filename != Constants.MERGE_DAILY_TRANSACTION_FILENAME:
                with open(os.path.join(input_folder, filename), 'r') as infile:
                    for line in infile:
                        outfile.write(line)

        # Add a line with a 00 transaction code at the end
        outfile.write("00\n")
