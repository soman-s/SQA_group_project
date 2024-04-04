from constants import Constants
import string
import utils


def process_create(transaction_line: string, current_users: list[str]):
    """
    Process a 'create' transaction.

    Parameters:
        transaction_line (string): The transaction line to process.
        current_users (list[str]): The list of current users.

    """
    start_index = Constants.MAX_ACCOUNT_TYPE_LENGTH + 1
    new_user = transaction_line[start_index:Constants.MAX_USER_NAME_LENGTH + start_index]
    new_user_code = transaction_line[19:21]
    new_user_amount = transaction_line[len(transaction_line) - Constants.MAX_USER_NAME_LENGTH + start_index + 3:len(transaction_line)]

    for user in current_users:
        if new_user in user:
            return
    current_users.append(new_user + " " + new_user_code + " " + new_user_amount)


def process_delete(transaction_line: string, current_users: list[str], available_games: list[str], games_collection: list[str]):
    """
    Process a 'delete' transaction.

    Parameters:
        transaction_line (string): The transaction line to process.
        current_users (list[str]): The list of current users.
        available_games (list[str]): The list of available games.
        games_collection (list[str]): The list of games in the collection.
    """
    start_index = Constants.MAX_ACCOUNT_TYPE_LENGTH + 1
    removed_user = transaction_line[start_index:Constants.MAX_USER_NAME_LENGTH + start_index]

    for user in current_users:
        if removed_user in user:
            utils.remove_item(current_users, removed_user)
            utils.remove_item(available_games, removed_user)
            utils.remove_item(games_collection, removed_user)
            return
    return "User not found"


def process_credit(transaction_line: string, current_users: list[str]):
    """
    Process a 'credit' transaction.

    Parameters:
        transaction_line (string): The transaction line to process.
        current_users (list[str]): The list of current users.
    """
    start_index = Constants.MAX_ACCOUNT_TYPE_LENGTH + 1
    new_user_amount = float(transaction_line[len(transaction_line) - Constants.MAX_USER_NAME_LENGTH + start_index + 3:].lstrip('0'))
    curr_user = transaction_line[start_index:Constants.MAX_USER_NAME_LENGTH + start_index]
    for i, user in enumerate(current_users):
        if curr_user in user:
            current_users[i] = utils.update_balance(user, new_user_amount)
            return
    return "User not found"


def process_buy(transaction_line: string, current_users: list[str], games_collection: list[str]):
    """
    Process a 'buy' transaction.

    Parameters:
        transaction_line (string): The transaction line to process.
        current_users (list[str]): The list of current users.
        games_collection (list[str]): The list of games in the collection.
    """
    start_index = Constants.MAX_ACCOUNT_TYPE_LENGTH + 1

    game_name = transaction_line[start_index:start_index + Constants.MAX_GAME_NAME_LENGTH]

    seller_name = transaction_line[start_index + Constants.MAX_GAME_NAME_LENGTH + 1:start_index + Constants.MAX_GAME_NAME_LENGTH + 1 + Constants.MAX_USER_NAME_LENGTH]

    buyer_name = transaction_line[start_index + Constants.MAX_GAME_NAME_LENGTH + Constants.MAX_USER_NAME_LENGTH + 2:
                                  start_index + Constants.MAX_GAME_NAME_LENGTH + Constants.MAX_USER_NAME_LENGTH + 2 + Constants.MAX_USER_NAME_LENGTH]

    game_price_current_users = transaction_line[start_index + Constants.MAX_GAME_NAME_LENGTH + 1 + Constants.MAX_USER_NAME_LENGTH + 1 + Constants.MAX_USER_NAME_LENGTH + 1:]

    game_price_available_games = game_price_current_users[3:]
    game_price_available_games = float(game_price_available_games)


    # prevents a deleted buyer from buying a game
    user_exist = False
    for i, user in enumerate(current_users):
        current_user_name = user[:Constants.MAX_USER_NAME_LENGTH]
        if  current_user_name == buyer_name:
            user_exist=True
            break

    if user_exist:
        # prevents buy from occuring if it results in a negative balance for the buyer
        for i, user in enumerate(current_users):
            current_user_name = user[:Constants.MAX_USER_NAME_LENGTH]
            if  current_user_name == buyer_name:
                balance_index: int = Constants.MAX_USER_NAME_LENGTH + 1 + Constants.MAX_ACCOUNT_TYPE_LENGTH + 1

                balance: float = float(user[balance_index:])
                balance = balance - game_price_available_games

                if balance < 0:
                    utils.display_error_message("Cannot process Buy, Buyer will have negative balance")
                    return


        game_to_add = game_name + " " + buyer_name

        game_added = False
        for collection_entry in games_collection:
            if game_to_add.lower() == collection_entry.lower():
                game_added = True

        if game_added == False:
            for i, user in enumerate(current_users):
                # balance_index: int = Constants.MAX_USER_NAME_LENGTH + 1 + Constants.MAX_ACCOUNT_TYPE_LENGTH + 1
                # user_balance: float = float(user[balance_index:])
                current_user_name = user[:Constants.MAX_USER_NAME_LENGTH]
                if current_user_name == seller_name:
                    current_users[i] = utils.update_balance(user, game_price_available_games)

                elif current_user_name == buyer_name:
                    current_users[i] = utils.update_balance(user, -game_price_available_games)

            games_collection.append(game_name + " " + buyer_name)
            utils.display_success_message("Buy")
            return
        else:
            utils.display_error_message("Buy cannot be processed, buy already processed")
            return

    print("Cannot process buy transaction, buyer not in the system")




def process_sell(transaction_line: string, available_games: list[str], games_collection: list[str],current_users: list[str]):
    """
    Process a 'sell' transaction.

    Parameters:
        transaction_line (string): The transaction line to process.
        available_games (list[str]): The list of available games.
        games_collection (list[str]): The list of games in the collection.
    """
    start_index = Constants.MAX_ACCOUNT_TYPE_LENGTH + 1
    new_game_name = transaction_line[start_index:start_index + Constants.MAX_GAME_NAME_LENGTH]
    seller_name = transaction_line[start_index + Constants.MAX_GAME_NAME_LENGTH + 1:start_index + Constants.MAX_GAME_NAME_LENGTH + 1 + Constants.MAX_USER_NAME_LENGTH]
    game_price = transaction_line[start_index + Constants.MAX_GAME_NAME_LENGTH + 1 + Constants.MAX_USER_NAME_LENGTH + 1:]

    # prevents deleted users from selling games
    user_exist=False
    for i, user in enumerate(current_users):
        current_user_name = user[:Constants.MAX_USER_NAME_LENGTH]
        if  current_user_name == seller_name:
            user_exist=True
            break

    if user_exist:
        for games in available_games:
            current_game_name = games[:Constants.MAX_GAME_NAME_LENGTH]
            if current_game_name.lower() == new_game_name.lower():
                utils.display_error_message("Game is already listed for sale")
                return

        available_games.append(new_game_name + " " + seller_name + " " + game_price)
        games_collection.append(new_game_name + " " + seller_name)
        utils.display_success_message("Game listed for sale")
        return
    utils.display_error_message("Cannot list game for sale, Seller not in the system")


def process_refund(transaction_line: string, games_collection: list[str], current_users: list[str]):
    """
    Process a 'refund' transaction.

    Parameters:
        transaction_line (string): The transaction line to process.
        games_collection (list[str]): The list of games in the collection.
        current_users (list[str]): The list of current users.
    """
    start_index = Constants.MAX_ACCOUNT_TYPE_LENGTH + 1
    game_name_length = Constants.MAX_GAME_NAME_LENGTH
    user_name_length = Constants.MAX_USER_NAME_LENGTH

    refund_game_name = transaction_line[start_index:start_index + game_name_length]
    buyer_name = transaction_line[start_index + game_name_length + 1:start_index + game_name_length + 1 + user_name_length]
    seller_name = transaction_line[start_index + game_name_length + 1 + user_name_length + 1:start_index + game_name_length + 1 + user_name_length + 1 + user_name_length]
    refund_price = transaction_line[start_index + game_name_length + 1 + user_name_length + 1 + user_name_length + 1:]

    # prevents refund from occuring if it results in a negtuive balance for the user
    for i, user in enumerate(current_users):
        current_user_name = user[:Constants.MAX_USER_NAME_LENGTH]
        if  current_user_name.lower() == seller_name.lower():
            balance_index: int = Constants.MAX_USER_NAME_LENGTH + 1 + Constants.MAX_ACCOUNT_TYPE_LENGTH + 1
            balance: float = float(user[balance_index:])
            balance =balance- float(refund_price)
            if balance<0:
                utils.display_error_message("Cannot process Refund, Seller will have negative balance")
                return


    game_to_remove = refund_game_name + " " + buyer_name
    game_removed = False
    for collection_entry in games_collection:
        if game_to_remove.lower() == collection_entry.lower():
            games_collection.remove(collection_entry)
            #print(collection_entry)
            game_removed = True

    if game_removed:
        refund_price = float(refund_price)

        for i, user in enumerate(current_users):
            current_user_name = user[:Constants.MAX_USER_NAME_LENGTH]
            if current_user_name.lower() == buyer_name.lower():
                current_users[i] = utils.update_balance(user, refund_price)

            elif current_user_name.lower() == seller_name.lower():
                current_users[i] = utils.update_balance(user, -refund_price)
        utils.display_success_message("Refund")
    else:
        utils.display_error_message("Refund cannot be processed, refund already processed or game does not exist")
