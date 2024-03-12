from constants import Constants
import string
import utils

def process_create(transaction_line: string, current_users:list[str]):
    start_index = Constants.MAX_ACCOUNT_TYPE_LENGTH + 1
    new_user = transaction_line[start_index:Constants.MAX_USER_NAME_LENGTH+start_index]
    new_user_code = transaction_line[19:21]
    new_user_amount = transaction_line[len(transaction_line)-Constants.MAX_USER_NAME_LENGTH+start_index+3:len(transaction_line)]
    current_users.append(new_user+" "+new_user_code+" "+new_user_amount)
def process_delete(transaction_line: string, current_users:list[str],available_games:list[str], games_collection:list[str]):
    start_index = Constants.MAX_ACCOUNT_TYPE_LENGTH + 1
    removed_user = transaction_line[start_index:Constants.MAX_USER_NAME_LENGTH+start_index]
    utils.remove_item(current_users,removed_user)
    utils.remove_item(available_games,removed_user)
    utils.remove_item(games_collection,removed_user)
   
def process_credit(transaction_line: string, current_users:list[str]):
    start_index = Constants.MAX_ACCOUNT_TYPE_LENGTH + 1
    new_user_amount = float(transaction_line[len(transaction_line)-Constants.MAX_USER_NAME_LENGTH+start_index+3:].lstrip('0'))
    curr_user = transaction_line[start_index:Constants.MAX_USER_NAME_LENGTH+start_index]
    for i, user in enumerate(current_users):
        if curr_user in user:
            current_users[i] = utils.update_balance(user, new_user_amount)
            return
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
        if current_game_name.lower() == new_game_name.lower():
            #print("GAME ALREADY EXISTS")
            return

    # if game doesn't already exist, add to games_collection list and available_games list
    available_games.append(new_game_name+" "+seller_name+" "+game_price)
    games_collection.append(new_game_name+" "+seller_name)


def process_refund(transaction_line: string, games_collection:list[str],current_users:list[str]):

    start_index = Constants.MAX_ACCOUNT_TYPE_LENGTH + 1
    game_name_length = Constants.MAX_GAME_NAME_LENGTH
    user_name_length = Constants.MAX_USER_NAME_LENGTH

    refund_game_name = transaction_line[start_index:start_index + game_name_length]
    buyer_name = transaction_line[start_index + game_name_length + 1:start_index + game_name_length + 1 + user_name_length]
    seller_name = transaction_line[start_index + game_name_length + 1 + user_name_length + 1:start_index + game_name_length + 1 + user_name_length + 1 + user_name_length]
    refund_price=transaction_line[start_index + game_name_length + 1 + user_name_length + 1 + user_name_length+1:]


    game_to_remove=refund_game_name+" "+buyer_name
    game_removed=False
    for collection_entry in games_collection:

        # remove game from games collection , and issue refund from seller to buyer
        if game_to_remove.lower() == collection_entry.lower():
            games_collection.remove(collection_entry)
            game_removed=True


    # if game was removed from games_collection, the refund was not preoviosuly issued
    if game_removed:
        refund_price = float(refund_price)
        for i, user in enumerate(current_users):
            current_user_name = user[:Constants.MAX_USER_NAME_LENGTH]

            if current_user_name == buyer_name:
                current_users[i] = utils.update_balance(user, refund_price)
            elif current_user_name == seller_name:
                current_users[i] = utils.update_balance(user, -refund_price)


    return
