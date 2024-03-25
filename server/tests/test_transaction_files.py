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







