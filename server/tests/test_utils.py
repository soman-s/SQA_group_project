import pytest
import sys
sys.path.append('..')
import logging
from io import StringIO
import sys

from utils import pad_end_file
from utils import remove_item
from utils import update_balance
from utils import display_error_message
from utils import display_success_message
from utils import check_valid_file


INPUT_ALL_USER_FILE="ori_log_files/current_users.etf"

def read_file_contents(file_name: str) -> list[str]:
    """
    Read the contents of a file and return them as a list of strings.

    Parameters:
        file_name (str): The name of the file to read.

    Returns:
        list[str]: A list containing the contents of the file as strings.
    """

    with open(file_name, 'r') as file:
        lines = file.readlines()
        lines = [line.rstrip('\n') for line in lines]
        lines = [line.lstrip('\n') for line in lines]
        return lines
        
def test_pad_end_file():
    # Test case 1 where total_chars is greater than length of "END"
    result = pad_end_file(10)
    assert len(result) == 10
    assert result == "END       "

    # Test case 2 where total_chars is equal to length of "END"
    result = pad_end_file(3)
    assert len(result) == 3
    assert result == "END"
     # Test case where total_chars is less than length of "END"

    result = pad_end_file(2)
    assert len(result) == 3
    assert result == "END"


def test_remove_item():
    # Test removing a single item
    items = ['apple', 'banana', 'cherry']
    item_to_remove = 'banana'
    remove_item(items, item_to_remove)
    assert 'banana' not in items
    assert len(items) == 2

    # Test removing multiple occurrences of an item
    items = ['apple', 'banana', 'cherry', 'banana']
    item_to_remove = 'banana'
    remove_item(items, item_to_remove)
    assert 'banana' not in items
    assert len(items) == 2

    # Test removing an item not in the list
    items = ['apple', 'banana', 'cherry']
    item_to_remove = 'grape'
    remove_item(items, item_to_remove)
    assert 'grape' not in items
    assert len(items) == 3  # No change in the list

    # Test removing from an empty list
    items = []
    item_to_remove = 'apple'
    remove_item(items, item_to_remove)
    assert len(items) == 0  # List should remain empty


def test_update_balance():
    # Test positive balance change
    user = "admin1          AA 000500.00"
    balance_change = 100.50
    updated_user = update_balance(user, balance_change)
    assert updated_user.endswith("000600.50")

    # Test negative balance change
    user = "admin1          AA 000500.00"
    balance_change = -100.50
    updated_user = update_balance(user, balance_change)
    assert updated_user.endswith("000399.50")

    # Test zero balance change
    user = "admin1          AA 000500.00"
    balance_change = 0
    updated_user = update_balance(user, balance_change)
    assert updated_user.endswith("000500.00")

    # Test large balance change
    user = "admin1          AA 000500.00"
    balance_change = 400.24
    updated_user = update_balance(user, balance_change)
    assert updated_user.endswith("000900.24")

def test_display_error_message(capsys):
    # Call the function with a test error message
    error_message = "File not found"
    display_error_message(error_message)

    # Capture the printed output
    captured = capsys.readouterr()

    # Check if the printed message matches the expected error message
    assert captured.out.strip() == f"Error: {error_message}"

    # Call the function with a test error message
    error_message = ""
    display_error_message(error_message)

    # Capture the printed output
    captured = capsys.readouterr()

    # Check if the printed message matches the expected error message
    assert captured.out.strip() == f"Error:{error_message}"


def test_display_success_message(capsys):
    # Call the function with a test transaction
    transaction = "Payment of $100"
    display_success_message(transaction)

    # Capture the printed output
    captured = capsys.readouterr()

    # Check if the printed message matches the expected success message
    assert captured.out.strip() == f"Transaction processed: {transaction}"

    # Call the function with a test transaction
    transaction = ""
    display_success_message(transaction)

    # Capture the printed output
    captured = capsys.readouterr()

    # Check if the printed message matches the expected success message
    assert captured.out.strip() == f"Transaction processed:{transaction}"

def test_check_valid_file():

    # Test for valid file
    test_file="test_files/test_user_1.etf"
    test_data=read_file_contents(test_file)
    test_data=test_data[:-1]
    result=check_valid_file(test_data,INPUT_ALL_USER_FILE)
    assert result==True
