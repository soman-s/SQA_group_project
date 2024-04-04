import pytest
import sys
sys.path.append('..')
import logging
from io import StringIO
import sys

from main import main

def check_string_in_file(file_path, target_string):
    with open(file_path, 'r') as file:
        for line in file:
            if target_string in line:
                return True
    return False

def test_main():
    # Test Path 1 all files are valid with Refund transactions
    input_all_users="test_files/test_main_files/test_1/current_users.etf"
    input_available_games= "test_files/test_main_files/test_1/available_games.etf"
    input_games_collection="test_files/test_main_files/test_1/game_collection.etf"
    log_file_path="test_files/test_main_files/test_1/daily_transactions"
    merge_transaction_file="test_files/test_main_files/test_1/merged_daily_transactions.etf"
    output_all_users="test_files/test_main_files/test_1/current_users.etf"
    output_available_games="test_files/test_main_files/test_1/available_games.etf"
    output_games_collection="test_files/test_main_files/test_1/game_collection.etf"

    main(input_all_users,input_available_games,input_games_collection,
        log_file_path,merge_transaction_file,output_all_users,output_available_games,output_games_collection)
    assert check_string_in_file(output_all_users,"admin1          AA 000490.00")
    assert check_string_in_file(output_all_users,"admin2          AA 000510.00")
    assert check_string_in_file(output_games_collection,"admingame1                admin1          ")==False


    # Test Path 2 all files are valid with Sell transactions
    input_all_users="test_files/test_main_files/test_2/current_users.etf"
    input_available_games= "test_files/test_main_files/test_2/available_games.etf"
    input_games_collection="test_files/test_main_files/test_2/game_collection.etf"
    log_file_path="test_files/test_main_files/test_2/daily_transactions"
    merge_transaction_file="test_files/test_main_files/test_2/merged_daily_transactions.etf"
    output_all_users="test_files/test_main_files/test_2/current_users.etf"
    output_available_games="test_files/test_main_files/test_2/available_games.etf"
    output_games_collection="test_files/test_main_files/test_2/game_collection.etf"



    main(input_all_users,input_available_games,input_games_collection,
        log_file_path,merge_transaction_file,output_all_users,output_available_games,output_games_collection)

    assert check_string_in_file(output_available_games,"admin game8               admin1          100.00")
    assert check_string_in_file(output_available_games,"admin game8               admin1         ")



    # Test Path 3 all files are valid with Buy transactions
    input_all_users="test_files/test_main_files/test_3/current_users.etf"
    input_available_games= "test_files/test_main_files/test_3/available_games.etf"
    input_games_collection="test_files/test_main_files/test_3/game_collection.etf"
    log_file_path="test_files/test_main_files/test_3/daily_transactions"
    merge_transaction_file="test_files/test_main_files/test_3/merged_daily_transactions.etf"
    output_all_users="test_files/test_main_files/test_3/current_users.etf"
    output_available_games="test_files/test_main_files/test_3/available_games.etf"
    output_games_collection="test_files/test_main_files/test_3/game_collection.etf"



    main(input_all_users,input_available_games,input_games_collection,
        log_file_path,merge_transaction_file,output_all_users,output_available_games,output_games_collection)

    assert check_string_in_file(output_games_collection,"PUBG                      admin1         ")


    # Test Path 4 all files are valid with add_credit transactions
    input_all_users="test_files/test_main_files/test_4/current_users.etf"
    input_available_games= "test_files/test_main_files/test_4/available_games.etf"
    input_games_collection="test_files/test_main_files/test_4/game_collection.etf"
    log_file_path="test_files/test_main_files/test_4/daily_transactions"
    merge_transaction_file="test_files/test_main_files/test_4/merged_daily_transactions.etf"
    output_all_users="test_files/test_main_files/test_4/current_users.etf"
    output_available_games="test_files/test_main_files/test_4/available_games.etf"
    output_games_collection="test_files/test_main_files/test_4/game_collection.etf"



    main(input_all_users,input_available_games,input_games_collection,
        log_file_path,merge_transaction_file,output_all_users,output_available_games,output_games_collection)
    assert check_string_in_file(output_all_users,"admin1          AA 000500.00")==False



    # Test Path 5 all files are valid with create transactions
    input_all_users="test_files/test_main_files/test_5/current_users.etf"
    input_available_games= "test_files/test_main_files/test_5/available_games.etf"
    input_games_collection="test_files/test_main_files/test_5/game_collection.etf"
    log_file_path="test_files/test_main_files/test_5/daily_transactions"
    merge_transaction_file="test_files/test_main_files/test_5/merged_daily_transactions.etf"
    output_all_users="test_files/test_main_files/test_5/current_users.etf"
    output_available_games="test_files/test_main_files/test_5/available_games.etf"
    output_games_collection="test_files/test_main_files/test_5/game_collection.etf"




    main(input_all_users,input_available_games,input_games_collection,
        log_file_path,merge_transaction_file,output_all_users,output_available_games,output_games_collection)

    assert check_string_in_file(output_all_users,"admin4          AA 000500.00")




    # Test Path 6 all files are valid with delete transactions
    input_all_users="test_files/test_main_files/test_6/current_users.etf"
    input_available_games= "test_files/test_main_files/test_6/available_games.etf"
    input_games_collection="test_files/test_main_files/test_6/game_collection.etf"
    log_file_path="test_files/test_main_files/test_6/daily_transactions"
    merge_transaction_file="test_files/test_main_files/test_6/merged_daily_transactions.etf"
    output_all_users="test_files/test_main_files/test_6/current_users.etf"
    output_available_games="test_files/test_main_files/test_6/available_games.etf"
    output_games_collection="test_files/test_main_files/test_6/game_collection.etf"


    main(input_all_users,input_available_games,input_games_collection,
        log_file_path,merge_transaction_file,output_all_users,output_available_games,output_games_collection)
    assert check_string_in_file(output_all_users,"admin2          AA 0005000.00")==False
    assert check_string_in_file(output_games_collection,"Minecraft                 admin2         ")==False
    assert check_string_in_file(output_available_games,"Dota                      admin2          999.00")==False



    # Test Path 7 invalid current  users file
    input_all_users="test_files/test_main_files/test_7/current_users.etf"
    input_available_games= "test_files/test_main_files/test_7/available_games.etf"
    input_games_collection="test_files/test_main_files/test_7/game_collection.etf"
    log_file_path="test_files/test_main_files/test_7/daily_transactions"
    merge_transaction_file="test_files/test_main_files/test_7/merged_daily_transactions.etf"
    output_all_users="test_files/test_main_files/test_7/current_users.etf"
    output_available_games="test_files/test_main_files/test_7/available_games.etf"
    output_games_collection="test_files/test_main_files/test_7/game_collection.etf"

    captured_output = StringIO()
    sys.stdout = captured_output
    main(input_all_users,input_available_games,input_games_collection,
        log_file_path,merge_transaction_file,output_all_users,output_available_games,output_games_collection)
    captured_output_value = captured_output.getvalue()
    sys.stdout = sys.__stdout__




    # Test Path 8 invalid available games file
    input_all_users="test_files/test_main_files/test_8/current_users.etf"
    input_available_games= "test_files/test_main_files/test_8/available_games.etf"
    input_games_collection="test_files/test_main_files/test_8/game_collection.etf"
    log_file_path="test_files/test_main_files/test_8/daily_transactions"
    merge_transaction_file="test_files/test_main_files/test_8/merged_daily_transactions.etf"
    output_all_users="test_files/test_main_files/test_8/current_users.etf"
    output_available_games="test_files/test_main_files/test_8/available_games.etf"
    output_games_collection="test_files/test_main_files/test_8/game_collection.etf"

    captured_output = StringIO()
    sys.stdout = captured_output
    main(input_all_users,input_available_games,input_games_collection,
        log_file_path,merge_transaction_file,output_all_users,output_available_games,output_games_collection)
    captured_output_value = captured_output.getvalue()
    sys.stdout = sys.__stdout__


    # Test Path 9 invalid games collection file
    input_all_users="test_files/test_main_files/test_9/current_users.etf"
    input_available_games= "test_files/test_main_files/test_9/available_games.etf"
    input_games_collection="test_files/test_main_files/test_9/game_collection.etf"
    log_file_path="test_files/test_main_files/test_9/daily_transactions"
    merge_transaction_file="test_files/test_main_files/test_9/merged_daily_transactions.etf"
    output_all_users="test_files/test_main_files/test_9/current_users.etf"
    output_available_games="test_files/test_main_files/test_9/available_games.etf"
    output_games_collection="test_files/test_main_files/test_9/game_collection.etf"

    captured_output = StringIO()
    sys.stdout = captured_output
    main(input_all_users,input_available_games,input_games_collection,
        log_file_path,merge_transaction_file,output_all_users,output_available_games,output_games_collection)
    captured_output_value = captured_output.getvalue()
    sys.stdout = sys.__stdout__


    # Test Path 10 invalid merged transaction file
    input_all_users="test_files/test_main_files/test_10/current_users.etf"
    input_available_games= "test_files/test_main_files/test_10/available_games.etf"
    input_games_collection="test_files/test_main_files/test_10/game_collection.etf"
    log_file_path="test_files/test_main_files/test_10/daily_transactions"
    merge_transaction_file="test_files/test_main_files/test_10/merged_daily_transactions.etf"
    output_all_users="test_files/test_main_files/test_10/current_users.etf"
    output_available_games="test_files/test_main_files/test_10/available_games.etf"
    output_games_collection="test_files/test_main_files/test_10/game_collection.etf"

    captured_output = StringIO()
    sys.stdout = captured_output
    main(input_all_users,input_available_games,input_games_collection,
        log_file_path,merge_transaction_file,output_all_users,output_available_games,output_games_collection)
    captured_output_value = captured_output.getvalue()
    sys.stdout = sys.__stdout__


    # Test Path 11 invalid transaction code in merged transaction file
    input_all_users="test_files/test_main_files/test_11/current_users.etf"
    input_available_games= "test_files/test_main_files/test_11/available_games.etf"
    input_games_collection="test_files/test_main_files/test_11/game_collection.etf"
    log_file_path="test_files/test_main_files/test_11/daily_transactions"
    merge_transaction_file="test_files/test_main_files/test_11/merged_daily_transactions.etf"
    output_all_users="test_files/test_main_files/test_11/current_users.etf"
    output_available_games="test_files/test_main_files/test_11/available_games.etf"
    output_games_collection="test_files/test_main_files/test_11/game_collection.etf"

    captured_output = StringIO()
    sys.stdout = captured_output
    main(input_all_users,input_available_games,input_games_collection,
        log_file_path,merge_transaction_file,output_all_users,output_available_games,output_games_collection)
    captured_output_value = captured_output.getvalue()
    sys.stdout = sys.__stdout__


    # Test Path 12 Process transaction file with all the different transaction codes
    input_all_users="test_files/test_main_files/test_12/current_users.etf"
    input_available_games= "test_files/test_main_files/test_12/available_games.etf"
    input_games_collection="test_files/test_main_files/test_12/game_collection.etf"
    log_file_path="test_files/test_main_files/test_12/daily_transactions"
    merge_transaction_file="test_files/test_main_files/test_12/merged_daily_transactions.etf"
    output_all_users="test_files/test_main_files/test_12/current_users.etf"
    output_available_games="test_files/test_main_files/test_12/available_games.etf"
    output_games_collection="test_files/test_main_files/test_12/game_collection.etf"


    main(input_all_users,input_available_games,input_games_collection,
        log_file_path,merge_transaction_file,output_all_users,output_available_games,output_games_collection)

    assert check_string_in_file(output_all_users,"admin2          AA 0005000.00")==False
    assert check_string_in_file(output_games_collection,"Minecraft                 admin2         ")==False
    assert check_string_in_file(output_available_games,"Dota                      admin2          999.00")==False
    assert check_string_in_file(output_games_collection,"PUBG                      admin1         ")
    assert check_string_in_file(output_all_users,"admin4          AA 000500.00")
    assert check_string_in_file(output_all_users,"admin1          AA 000500.00")==False
    assert check_string_in_file(output_available_games,"admin game8               admin1          100.00")
    assert check_string_in_file(output_available_games,"admin game8               admin1         ")
