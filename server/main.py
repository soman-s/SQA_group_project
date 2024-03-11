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
            print("UPDATE REFUND STUFF")

    print("Writing back into the transaction files")

    # updating and writing back to the available_games file
    end_avaiable_games=Constants.MAX_GAME_NAME_LENGTH+Constants.MAX_USER_NAME_LENGTH+Constants.MAX_GAME_PRICE_LENGTH+2
    file_ending=utils.pad_end_file(end_avaiable_games)
    available_games.append(file_ending)
    process_files.write_file_contents(Constants.OUTPUT_AVAILABLE_GAMES,available_games)

    end_games_collection=Constants.MAX_GAME_NAME_LENGTH+Constants.MAX_USER_NAME_LENGTH+1
    file_ending=utils.pad_end_file(end_games_collection)
    games_collection.append(file_ending)
    process_files.write_file_contents(Constants.OUTPUT_GAMES_COLLECTION,games_collection)





if __name__ == '__main__':
    # Call the main function
    main()
