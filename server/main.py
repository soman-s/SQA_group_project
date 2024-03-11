
from constants import Constants
import process_files
import transactions
import utils


# This is the main program,
# This program will organize and process the transactions in the back end.
def main():
    all_users = process_files.read_file_contents(Constants.INPUT_ALL_USER_FILE)
    available_games=process_files.read_file_contents(Constants.INPUT_AVAILABLE_GAMES)
    games_collection=process_files.read_file_contents(Constants.INPUT_GAMES_COLLECTION)
    daily_transactions=process_files.read_file_contents(Constants.INPUT_DAILY_TRANSACTION)

    # reading only contents of the files, ignoring the last line since its the end line
    all_users=all_users[:-1]
    available_games=available_games[:-1]
    games_collection=games_collection[:-1]


    # loog through the daiily transaction list to view list of transactions
    # and to see which files need to be updated in the back end
    for transaction in daily_transactions:
        current_code=transaction[0:2]

        if (current_code==Constants.SELL_GAME_CODE):

            transactions.process_sell(transaction,available_games,games_collection)

        elif(current_code==Constants.REFUND_CODE):
            transactions.process_refund(transaction,games_collection,all_users)

        elif (current_code==Constants.CREATE_CODE):
            transactions.process_create(transaction,all_users)


    print("Writing back into the transaction files")


    # Updating and writing back to the available_games file
    process_files.update_and_write_file(Constants.OUTPUT_AVAILABLE_GAMES, available_games, Constants.MAX_GAME_NAME_LENGTH + Constants.MAX_USER_NAME_LENGTH + Constants.MAX_GAME_PRICE_LENGTH + 2)

    # Updating and writing back to the games_collection file
    process_files.update_and_write_file(Constants.OUTPUT_GAMES_COLLECTION, games_collection, Constants.MAX_GAME_NAME_LENGTH + Constants.MAX_USER_NAME_LENGTH + 1)

    # Updating and writing back to the all_users file
    process_files.update_and_write_file(Constants.OUTPUT_ALL_USER_FILE, all_users, Constants.MAX_USER_NAME_LENGTH + 1 + Constants.MAX_ACCOUNT_TYPE_LENGTH + 1 + Constants.MAX_CREDIT_LENGTH)




if __name__ == "__main__":
    main()
