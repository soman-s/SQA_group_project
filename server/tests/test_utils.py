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
from utils import check_valid_username_formatting
from utils import check_valid_account_type_formatting
from utils import check_valid_credit_amount_formatting
from utils import check_valid_account_type
from utils import check_valid_transaction_file


INPUT_ALL_USER_FILE="ori_log_files/current_users.etf"
INPUT_GAMES_COLLECTION="ori_log_files/game_collection.etf"
INPUT_AVAILABLE_GAMES="ori_log_files/available_games.etf"

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

    # Test for valid file in currernt users file
    test_file="test_files/test_check_valid_files/test_user_1.etf"
    test_data=read_file_contents(test_file)
    test_data=test_data[:-1]
    result=check_valid_file(test_data,INPUT_ALL_USER_FILE)
    assert result==True


    # Test for invalid username in currernt users file
    test_file="test_files/test_check_valid_files/test_user_2.etf"
    test_data=read_file_contents(test_file)
    test_data=test_data[:-1]
    result=check_valid_file(test_data,INPUT_ALL_USER_FILE)
    assert result==False


    # Test for invalid accunt type in currernt users file
    test_file="test_files/test_check_valid_files/test_user_3.etf"
    test_data=read_file_contents(test_file)
    test_data=test_data[:-1]
    result=check_valid_file(test_data,INPUT_ALL_USER_FILE)
    assert result==False

    # Test for invalid accunt type in currernt users file
    test_file="test_files/test_check_valid_files/test_user_4.etf"
    test_data=read_file_contents(test_file)
    test_data=test_data[:-1]
    result=check_valid_file(test_data,INPUT_ALL_USER_FILE)
    assert result==False

    # Test for valid games collection file
    test_file="test_files/test_check_valid_files/test_game_collection_1.etf"
    test_data=read_file_contents(test_file)
    test_data=test_data[:-1]
    result=check_valid_file(test_data,INPUT_GAMES_COLLECTION)
    assert result==True

    # Test for invalid game name in games collection file
    test_file="test_files/test_check_valid_files/test_game_collection_2.etf"
    test_data=read_file_contents(test_file)
    test_data=test_data[:-1]
    result=check_valid_file(test_data,INPUT_GAMES_COLLECTION)
    assert result==False

    # Test for invalid username in games collection file
    test_file="test_files/test_check_valid_files/test_game_collection_3.etf"
    test_data=read_file_contents(test_file)
    test_data=test_data[:-1]
    result=check_valid_file(test_data,INPUT_GAMES_COLLECTION)
    assert result==False

    # Test for valid games collection file
    test_file="test_files/test_check_valid_files/test_game_collection_1.etf"
    test_data=read_file_contents(test_file)
    test_data=test_data[:-1]
    result=check_valid_file(test_data,INPUT_GAMES_COLLECTION)
    assert result==True


    # Test for valid available games file
    test_file="test_files/test_check_valid_files/test_available_games_1.etf"
    test_data=read_file_contents(test_file)
    test_data=test_data[:-1]
    result=check_valid_file(test_data,INPUT_AVAILABLE_GAMES)
    assert result==True

    # Test for invalid game name in available games file
    test_file="test_files/test_check_valid_files/test_available_games_2.etf"
    test_data=read_file_contents(test_file)
    test_data=test_data[:-1]
    result=check_valid_file(test_data,INPUT_AVAILABLE_GAMES)
    assert result==False

    # Test for invalid username in available games file
    test_file="test_files/test_check_valid_files/test_available_games_3.etf"
    test_data=read_file_contents(test_file)
    test_data=test_data[:-1]
    result=check_valid_file(test_data,INPUT_AVAILABLE_GAMES)
    assert result==False

    # Test for invalid balance in available games file
    test_file="test_files/test_check_valid_files/test_available_games_4.etf"
    test_data=read_file_contents(test_file)
    test_data=test_data[:-1]
    result=check_valid_file(test_data,INPUT_AVAILABLE_GAMES)
    assert result==False







    # Test for valid file in games collection file

def test_check_valid_transaction_file():

    # Test for valid merged daily transaction file
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_1.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==True

    # Test for invalid transaction code  merged daily transaction file
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_2.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid transaction code formatting merged daily transaction file
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_3.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid username formatting merged daily transaction file(LOGOUT CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_4.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid balance formatting merged daily transaction file(LOGOUT CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_5.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid Account type formatting merged daily transaction file(LOGOUT CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_6.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid game name formatting merged daily transaction file(SELL CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_7.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid user name formatting merged daily transaction file(SELL CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_8.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid game price merged daily transaction file(SELL CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_9.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid user name(buyer) formatting merged daily transaction file(Refund CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_10.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid user name(seller) formatting merged daily transaction file(Refund CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_11.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid game name formatting merged daily transaction file(Refund CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_12.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid game price formatting merged daily transaction file(Refund CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_13.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid username formatting merged daily transaction file(Create CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_14.etf"
    test_data=read_file_contents(test_file)
    print("test_data", test_data)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid balance formatting merged daily transaction file(Create CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_15.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid Account type formatting merged daily transaction file(Create CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_16.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid Account type name merged daily transaction file(Create CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_17.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

     # Test for invalid username formatting merged daily transaction file(Delete CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_18.etf"
    test_data=read_file_contents(test_file)
    print("test_data", test_data)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid balance formatting merged daily transaction file(Delete CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_19.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid Account type formatting merged daily transaction file(Delete CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_20.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid Account type name merged daily transaction file(Delete CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_21.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

     # Test for invalid username formatting merged daily transaction file(Add Credit CODE)
    # test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_22.etf"
    # test_data=read_file_contents(test_file)
    # print("test_data", test_data)
    # result=check_valid_transaction_file(test_data)
    # assert result==False

    # Test for invalid balance formatting merged daily transaction file(Add Credit CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_23.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid Account type formatting merged daily transaction file(Add Credit CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_24.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for invalid Account type name merged daily transaction file(Add Credit CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_25.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # Test for duplicate create transactions in merged daily transaction file(Create CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_26.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    #  Test for duplicate delete transactions in merged daily transaction file(Delete CODE)
    test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_27.etf"
    test_data=read_file_contents(test_file)
    result=check_valid_transaction_file(test_data)
    assert result==False

    # # Test for invalid user name (buyer) formatting merged daily transaction file (buy CODE)
    # test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_28.etf"
    # test_data=read_file_contents(test_file)
    # result=check_valid_transaction_file(test_data)
    # assert result==False

    # # Test for invalid user name (seller) formatting merged daily transaction file (buy CODE)
    # test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_29.etf"
    # test_data=read_file_contents(test_file)
    # result=check_valid_transaction_file(test_data)
    # assert result==False
    #
    # # Test for invalid game name formatting merged daily transaction file (buy CODE)
    # test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_30.etf"
    # test_data=read_file_contents(test_file)
    # result=check_valid_transaction_file(test_data)
    # assert result==False
    #
    # # Test for invalid game price formatting merged daily transaction file (buy CODE)
    # test_file="test_files/test_merged_transaction_files/test_merged_daily_transactions_31.etf"
    # test_data=read_file_contents(test_file)
    # result=check_valid_transaction_file(test_data)
    # assert result==False


def test_valid_username_formatting_success():

    test_line = "01 admin4          AA 000500.00"
    line_number  = 2
    result = check_valid_username_formatting(test_line, line_number)
    assert result==True

def test_valid_username_formatting_failure():
    test_line = "01 admin4    AA 000500.00"
    line_number  = 2
    result = check_valid_username_formatting(test_line, line_number)
    assert result==False

def test_valid_username_formatting_success():

    test_line = "01 admin4          AA 000500.00"
    line_number  = 2
    result = check_valid_username_formatting(test_line, line_number)
    assert result==True

def test_valid_account_type_formatting_success():
    test_line = "01 admin4          AA 000500.00"
    line_number  = 2
    result = check_valid_account_type_formatting(test_line, line_number)
    assert result==True

def test_valid_account_type_formatting_failure():
    test_line = "01 admin4     AA 000500.00"
    line_number  = 2
    result = check_valid_account_type_formatting(test_line, line_number)
    assert result==False

def test_valid_credit_amount_formatting_success():
    test_line = "01 admin4          AA 000500.00"
    line_number  = 2
    result = check_valid_credit_amount_formatting(test_line, line_number)
    assert result==True

def test_valid_credit_amount_formatting_failure():
    test_line = "01 admin4          AA 050.00"
    line_number  = 2
    result = check_valid_credit_amount_formatting(test_line, line_number)
    assert result==False

def test_valid_account_type_success():
    test_line = "01 admin4          AA 000500.00"
    line_number  = 2
    result = check_valid_account_type(test_line, line_number)
    assert result==True

def test_valid_account_type_failure():
    test_line = "01 admin4          SA 000500.00"
    line_number  = 2
    result = check_valid_account_type(test_line, line_number)
    assert result==False
