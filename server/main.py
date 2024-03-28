from constants import Constants
import process_files
import transactions
import utils

"""
Organize and process transactions in the back end.

Reads input files, merges daily transaction files, processes transactions,
and updates back-end files accordingly.
"""
def main(input_all_users,input_available_games,input_games_collection,
        log_file_path,merge_transaction_file,output_all_users,output_available_games,output_games_collection):

    print("Reading in Files...")
    # Reading contents of input files
    all_users = process_files.read_file_contents(input_all_users)
    available_games = process_files.read_file_contents(input_available_games)
    games_collection = process_files.read_file_contents(input_games_collection)



    # Removing the last line of each file since it's an end line
    all_users = all_users[:-1]
    available_games = available_games[:-1]
    games_collection = games_collection[:-1]

    # checking the validity of the input fuiles
    if(utils.check_valid_file(all_users,input_all_users)== False):
        return
    elif (utils.check_valid_file(games_collection,input_games_collection)== False):
        return
    elif(utils.check_valid_file(available_games,input_available_games)== False):
        return

    # Merging all the daily transaction files
    process_files.merge_daily_transaction_files(log_file_path, merge_transaction_file)
    daily_transactions = process_files.read_file_contents(merge_transaction_file)



    if(utils.check_valid_transaction_file(daily_transactions)==False):
        return

    print("Processing Daily Transaction Files..")
    # Loop through the daily transaction list to view transactions
    # and determine which files need to be updated in the back end
    for transaction in daily_transactions:
        current_code = transaction[0:2]

        # Process each transaction based on its code
        if current_code == Constants.SELL_GAME_CODE:
            transactions.process_sell(transaction, available_games, games_collection)
        elif current_code == Constants.REFUND_CODE:
            transactions.process_refund(transaction, games_collection, all_users)
        elif current_code == Constants.CREATE_CODE:
            transactions.process_create(transaction, all_users)
        elif current_code == Constants.DELETE_CODE:
            transactions.process_delete(transaction, all_users, available_games, games_collection)
        elif current_code == Constants.ADD_CREDIT_CODE:
            transactions.process_credit(transaction, all_users)
        elif current_code == Constants.BUY_CODE:
            transactions.process_buy(transaction, all_users, games_collection)

    print("Writing back into the transaction files")

    # Updating and writing back to the all_users file
    process_files.update_and_write_file(output_all_users,
                                        all_users,
                                        Constants.MAX_USER_NAME_LENGTH + 1 + Constants.MAX_ACCOUNT_TYPE_LENGTH + 1 + Constants.MAX_CREDIT_LENGTH)
    # Updating and writing back to the available_games file
    process_files.update_and_write_file(output_available_games,
                                        available_games,
                                        Constants.MAX_GAME_NAME_LENGTH + Constants.MAX_USER_NAME_LENGTH + Constants.MAX_GAME_PRICE_LENGTH + 2)

    # Updating and writing back to the games_collection file
    process_files.update_and_write_file(output_games_collection,
                                        games_collection,
                                        Constants.MAX_GAME_NAME_LENGTH + Constants.MAX_USER_NAME_LENGTH + 1)




if __name__ == "__main__":
    main(Constants.INPUT_ALL_USER_FILE,Constants.INPUT_AVAILABLE_GAMES,Constants.INPUT_GAMES_COLLECTION,Constants.LOG_FILES_PATH,
    Constants.INPUT__MERGE_DAILY_TRANSACTION,Constants.OUTPUT_ALL_USER_FILE,Constants.OUTPUT_AVAILABLE_GAMES,Constants.OUTPUT_GAMES_COLLECTION)
