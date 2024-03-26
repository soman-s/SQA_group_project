import pytest
import sys
sys.path.append('..')
import logging
from io import StringIO
import sys
import utils



from transactions import process_create
from transactions import process_delete
from transactions import process_credit
from transactions import process_sell


def test_create():
    current_users = []
    transaction_line = "01 admin4          AA 000500.00"
    process_create(transaction_line, current_users)
    assert current_users[0] == "admin4          AA 000500.00"

def test_delete():
    current_users = ["admin2          AA 000500.00"]
    available_games = ["PUBG                      admin2          030.00"]
    games_collection = ["PUBG                      admin2         "]
    transaction_line = "02 admin2          AA 000500.00"
    process_delete(transaction_line, current_users, available_games, games_collection)

    assert len(current_users) == 0
    assert len(available_games) == 0
    assert len(games_collection) == 0

def test_credit():
    current_users = ["admin2          AA 000500.00"]
    transaction_line = "06 admin2          AA 000100.00"
    process_credit(transaction_line, current_users)
    new_amount = current_users[0][19:]
    assert new_amount == "000600.00"

def test_process_sell():

    # Test that Error message is shown if game is already listed for sale
    available_games = ["admingame1                admin2          010.00"]
    games_collection = ["admingame1                admin2         "]
    transaction_line = "03 admingame1                admin1          045.00"

    process_sell(transaction_line, available_games, games_collection)

    # Redirect stdout to a StringIO object
    captured_output = StringIO()
    sys.stdout = captured_output


    process_sell(transaction_line, available_games, games_collection)

    # Get the captured output
    captured_output_value = captured_output.getvalue()
    sys.stdout = sys.__stdout__  # Restore stdout
