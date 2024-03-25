import pytest
import sys
sys.path.append('..')
import logging
from io import StringIO
import sys
import utils

from process_files import read_file_contents
from process_files import update_and_write_file
from process_files import merge_daily_transaction_files
from process_files import write_file_contents


def test_read_file_contents():

    #test can read file contents
    file_content = "Line 1\nLine 2\nLine 3\n"
    file_path =  "test_files/test_file.txt"
    with open(file_path, 'w') as file:
        file.write(file_content)

    lines = read_file_contents(file_path)
    assert lines == ["Line 1", "Line 2", "Line 3"]

    # test it doesn't write to a nonexistent file
    # Call the function with a non-existent file
    lines = read_file_contents("nonexistent_file.txt")
    # Check if the function returns an empty list for non-existent file
    assert lines == []

def test_update_and_write_file():

    # Define test data without adding padding
    data = ["line 1", "line 2"]
    end_length = 0
    update_and_write_file("test_files/update_and_write_file_1.etf", data, end_length)
    # Read the file and check its contents
    with open("test_files/update_and_write_file_1.etf", "r") as file:
        file_contents = file.readlines()

    assert file_contents == ["line 1\n", "line 2\n","END\n"]

    # Define test data with non-zero  padding
    data = ["line 1", "line 2"]
    end_length = 5
    update_and_write_file("test_files/update_and_write_file_2.etf", data, end_length)
    # Read the file and check its contents
    with open("test_files/update_and_write_file_2.etf", "r") as file:
        file_contents = file.readlines()

    assert file_contents == ["line 1\n", "line 2\n","END  \n"]


def test_merge_daily_transaction_files():

    merge_daily_transaction_files("test_files/test_transaction_files","test_files/test_merged_file.etf")

    with open("test_files/test_merged_file.etf", "r") as file:
        test_file_contents = file.readlines()

    with open("test_files/expected_merged_file.etf", "r") as file:
        expected_file_contents = file.readlines()

    assert test_file_contents==expected_file_contents
