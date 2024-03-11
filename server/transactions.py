from constants import Constants
import string

def create_user():
    pass
def remove_user():
    pass
def add_credit():
    pass
def buy_game():
    pass

def process_sell(transaction_line: string, available_games:list[str], games_collection:list[str]):

    start_index = Constants.MAX_ACCOUNT_TYPE_LENGTH + 1
    new_game_name = transaction_line[start_index:start_index + Constants.MAX_GAME_NAME_LENGTH]
    seller_name= transaction_line[start_index + Constants.MAX_GAME_NAME_LENGTH+1:start_index + Constants.MAX_GAME_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH]
    game_price= transaction_line[start_index + Constants.MAX_GAME_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1:]


    # if game is already listed for sale, don't add
    for games in available_games:

        current_game_name=games[:Constants.MAX_GAME_NAME_LENGTH]
        if (current_game_name==new_game_name):
            #print("GAME ALREADY EXISTS")
            return

    # if game doesn't already exist, add to games_collection list and available_games list
    available_games.append(new_game_name+" "+seller_name+" "+game_price)
    games_collection.append(new_game_name+" "+seller_name)


def process_refund(transaction_line: string, games_collection:list[str],current_users:list[str]):

    start_index = Constants.MAX_ACCOUNT_TYPE_LENGTH + 1
    refund_game_name = transaction_line[start_index:start_index + Constants.MAX_GAME_NAME_LENGTH]
    print(refund_game_name)
