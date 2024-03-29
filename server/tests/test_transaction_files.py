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
from transactions import process_refund
from transactions import process_buy


def test_create():
    # initilize the current users and the transactions to be processed
    current_users = []
    transaction_line = "01 admin4          AA 000500.00"

    # process transaction
    process_create(transaction_line, current_users)

    # Check if new user was sucessfully created
    assert current_users[0] == "admin4          AA 000500.00"

    transaction_line = "01 admin4          AA 000300.00"
    process_create(transaction_line, current_users)
    # check that duplicate users was not created 
    assert len(current_users) == 1

def test_delete():
    # initilize user and associated games to be removed
    current_users = ["admin2          AA 000500.00"]
    available_games = ["PUBG                      admin2          030.00"]
    games_collection = ["PUBG                      admin2         "]
    transaction_line = "02 admin2          AA 000500.00"

    # process transaction
    process_delete(transaction_line, current_users, available_games, games_collection)

    # check user and all associated games have been removed
    assert len(current_users) == 0
    assert len(available_games) == 0
    assert len(games_collection) == 0

    # initlizing a user to remove that doesn't exist
    current_users = ["admin5          AA 000500.00"]
    available_games = ["PUBG                      admin5          030.00"]
    games_collection = ["PUBG                      admin5         "]
    transaction_line = "02 admin9          AA 000500.00"

    # process transaction
    response = process_delete(transaction_line, current_users, available_games, games_collection)

    # validate user does not exist
    assert response == "User not found"


def test_credit():
    # initilize the current users and the transactions to be processed
    current_users = ["admin2          AA 000500.00"]
    transaction_line = "06 admin2          AA 000100.00"

    # process transaction
    process_credit(transaction_line, current_users)

    # validate that credit amount has been updated
    new_amount = current_users[0][19:]
    assert new_amount == "000600.00"

    # initilize the current users and the transactions to be processed
    current_users = ["admin2          AA 000500.00"]
    transaction_line = "06 admin4          AA 000100.00"

    # process transaction
    response = process_credit(transaction_line, current_users)

    # validate user does not exist
    assert response == "User not found"

def test_process_sell():

    # Test that Error message is shown if game is already listed for sale
    available_games = ["admingame1                admin2          010.00"]
    games_collection = ["admingame1                admin2         "]
    transaction_line = "03 admingame1                admin1          045.00"
    current_users=["admin1          AA 000500.00","admin2          AA 000500.00"]



    # Redirect stdout to a StringIO object
    captured_output = StringIO()
    sys.stdout = captured_output



    process_sell(transaction_line, available_games, games_collection,current_users)

    # Get the captured output
    captured_output_value = captured_output.getvalue()
    sys.stdout = sys.__stdout__  # Restore stdout


    # Test Sell transaction properly processes when new game is listed

    available_games = ["admingame1                admin2          010.00\n"]
    games_collection = ["admingame1                admin2         "]
    current_users=["admin1          AA 000500.00","admin2          AA 000500.00"]
    transaction_line = "03 admingame18               admin1          045.00"

    process_sell(transaction_line, available_games, games_collection,current_users)

    # Check if the new game is added to available_games and games_collection
    assert "admingame18               admin1          045.00" in available_games
    assert "admingame18               admin1         " in games_collection



    # Test that Error message is shown if deleted user tries to sell a game
    available_games = ["admingame1                admin2          010.00"]
    games_collection = ["admingame1                admin2         "]
    transaction_line = "03 admingame1                admin9          045.00"
    current_users=["admin1          AA 000500.00"]



    # Redirect stdout to a StringIO object
    captured_output = StringIO()
    sys.stdout = captured_output



    process_sell(transaction_line, available_games, games_collection,current_users)

    # Get the captured output
    captured_output_value = captured_output.getvalue()
    sys.stdout = sys.__stdout__  # Restore stdout

def test_process_refund():

    # Test prevents refund from occuring if it results in a negtuive balance for the user
    current_users=["admin1          AA 000500.00","admin2          AA 000500.00"]
    games_collection=["admingame1                admin2         ","admingame1                full1"]
    transaction_line="05 admingame1                admin2          admin1          111110.00"


    # Redirect stdout to a StringIO object
    captured_output = StringIO()
    sys.stdout = captured_output
    process_refund(transaction_line,games_collection,current_users)

    # Get the captured output
    captured_output_value = captured_output.getvalue()
    sys.stdout = sys.__stdout__

    # Test process refund properly  processes the refund trensaction

    # Test prevents refund from occuring if it results in a negtuive balance for the user
    current_users=["admin1          AA 000500.00","admin2          AA 000500.00"]
    games_collection=["admingame1                admin2         ","admingame1                full1"]
    transaction_line="05 admingame1                admin2          admin1          000010.00"
    process_refund(transaction_line,games_collection,current_users)

    assert "admingame1                admin2" not in games_collection
    assert "admin1          AA 000490.00" in current_users
    assert "admin2          AA 000510.00" in current_users


    # test that a refund won't happen twice

    current_users=["admin1          AA 000500.00","admin2          AA 000500.00"]
    games_collection=["admingame1                admin2         ","admingame1                full1"]
    transaction_line="05 admingame1                admin2          admin1          000010.00"
    process_refund(transaction_line,games_collection,current_users)


    transaction_line="05 admingame1                admin2          admin1          000010.00"
    # Redirect stdout to a StringIO object
    captured_output = StringIO()
    sys.stdout = captured_output
    process_refund(transaction_line,games_collection,current_users)

    captured_output_value = captured_output.getvalue()
    sys.stdout = sys.__stdout__  # Restore stdout

def test_process_buy():
    # # test prevents buy from occuring if it results in a negative balance for the buyer
    # transaction_line = "04 PUBG                      admin2          admin1          000030.00"
    # current_users = ["admin1          AA 000020.00", "admin2          AA 000500.00"]
    # games_collection = ["PUBG                      admin2         "]
    #
    # # Redirect stdout to a StringIO object
    # captured_output = StringIO()
    # sys.stdout = captured_output
    #
    # process_buy(transaction_line, current_users, games_collection)
    #
    # # Get the captured output
    # captured_output_value = captured_output.getvalue()
    # sys.stdout = sys.__stdout__
    #
    #
    #
    # # Test process_buy correctly processes the buy transaction
    # transaction_line = "04 PUBG                      admin2          admin1          000030.00"
    # current_users = ["admin1          AA 000500.00", "admin2          AA 000500.00"]
    # games_collection = ["PUBG                      admin2         "]
    #
    # process_buy(transaction_line, current_users, games_collection)
    #
    # # check if admin1 balance is decreased by game amount, admin2 balance is increased by game amount, and admin1 owns PUBG in games collection
    # assert "PUBG                      admin1" in games_collection
    # assert "admin1          AA 000470.00" in current_users
    # assert "admin2          AA 000530.00" in current_users



    # test that a buy transaction doesn't happen twice
    transaction_line = "04 PUBG                      admin2          admin1          000030.00"
    current_users = ["admin1          AA 000500.00", "admin2          AA 000500.00"]
    games_collection = ["PUBG                      admin2         "]

    process_buy(transaction_line, current_users, games_collection)

    # Redirect stdout to a StringIO object
    captured_output = StringIO()
    sys.stdout = captured_output

    process_buy(transaction_line, current_users, games_collection)

    captured_output_value = captured_output.getvalue()
    sys.stdout = sys.__stdout__  # Restore stdout
