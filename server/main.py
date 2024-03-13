from constants import Constants
import process_files
import transactions
import utils

"""
Organize and process transactions in the back end.

Reads input files, merges daily transaction files, processes transactions,
and updates back-end files accordingly.
"""
def main():

    print("Reading in Files...")
    # Reading contents of input files
    all_users = process_files.read_file_contents(Constants.INPUT_ALL_USER_FILE)
    available_games = process_files.read_file_contents(Constants.INPUT_AVAILABLE_GAMES)
    games_collection = process_files.read_file_contents(Constants.INPUT_GAMES_COLLECTION)

    # checking the validity of the input fuiles
    if(utils.check_valid_file(all_users,Constants.INPUT_ALL_USER_FILE)== False):
        return
    elif (utils.check_valid_file(games_collection,Constants.INPUT_GAMES_COLLECTION)== False):
        return
    elif(utils.check_valid_file(available_games,Constants.INPUT_AVAILABLE_GAMES)== False):
        return

    # Removing the last line of each file since it's an end line
    all_users = all_users[:-1]
    available_games = available_games[:-1]
    games_collection = games_collection[:-1]

    # Merging all the daily transaction files
    process_files.merge_daily_transaction_files(Constants.LOG_FILES_PATH, Constants.INPUT__MERGE_DAILY_TRANSACTION)
    daily_transactions = process_files.read_file_contents(Constants.INPUT__MERGE_DAILY_TRANSACTION)

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

    # Updating and writing back to the available_games file
    process_files.update_and_write_file(Constants.OUTPUT_AVAILABLE_GAMES,
                                        available_games,
                                        Constants.MAX_GAME_NAME_LENGTH + Constants.MAX_USER_NAME_LENGTH + Constants.MAX_GAME_PRICE_LENGTH + 2)

    # Updating and writing back to the games_collection file
    process_files.update_and_write_file(Constants.OUTPUT_GAMES_COLLECTION,
                                        games_collection,
                                        Constants.MAX_GAME_NAME_LENGTH + Constants.MAX_USER_NAME_LENGTH + 1)

    # Updating and writing back to the all_users file
    process_files.update_and_write_file(Constants.OUTPUT_ALL_USER_FILE,
                                        all_users,
                                        Constants.MAX_USER_NAME_LENGTH + 1 + Constants.MAX_ACCOUNT_TYPE_LENGTH + 1 + Constants.MAX_CREDIT_LENGTH)


if __name__ == "__main__":
    main()
