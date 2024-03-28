from typing import Union
import re

from constants import Constants

def pad_end_file(total_chars: int) -> str:
    """
    Pad the end of a file with spaces to reach a total number of characters.

    Args:
        total_chars (int): The total number of characters desired.

    Returns:
        str: A string containing 'END' followed by spaces to reach the desired total number of characters.
    """
    ending = "END" + " " * (total_chars - len("END"))
    return ending

def remove_item(items, item_to_remove):
    """
    Remove an item from a list.

    Args:
        items: The list from which to remove the item.
        item_to_remove: The item to remove from the list.
    """
    for item in items:
        if item_to_remove in item:
            items.remove(item)

def update_balance(user: str, balance_change: Union[int, float]) -> str:
    """
    Update the balance of a user.

    Args:
        user (str): The user string.
        balance_change (Union[int, float]): The change in balance.

    Returns:
        str: The updated user string with the modified balance.
    """
    balance_index: int = Constants.MAX_USER_NAME_LENGTH + 1 + Constants.MAX_ACCOUNT_TYPE_LENGTH + 1
    balance: float = float(user[balance_index:])
    balance += balance_change
    formatted_balance: str = "{:09.2f}".format(balance)
    return user[:balance_index] + formatted_balance


def display_error_message(message: str):
    """
    Display an error message.

    Args:
        message (str): The error message to display.
    """
    print(f"Error: {message}")

def display_success_message(transaction: str):
    """
    Display a sucess message

    Args:
        Transaction (str): The tranaction that was sucessful processed.
    """
    print(f"Transaction processed: {transaction}")


def check_valid_file(data: list[str], file_name: str) -> bool:
    """
    Validate if file has not been corrupted

    Args:
        data (list[str]): The data from the input files.
        file_name (str): File name of the file being checked

    Returns:
        bool: True if file is valid, False otherwise.
    """
    # if file_name==INPUT_ALL_USER_FILE.:
    if "current_users.etf"in file_name:
        print("Checking Validity of Current Users File")

        for line_num,line in enumerate(data[:],start=0):
            # check to see that after user name there is a space
            check_format=line[Constants.MAX_USER_NAME_LENGTH:Constants.MAX_USER_NAME_LENGTH+1]
            if check_format!=Constants.CHAR_BETWEEN_COMPONENTS:
                display_error_message(f"INVALID CURRENT USERS FILE, username not formatted properly on line: {line_num+1}")
                return False

            # checjing for account type
            check_format=line[Constants.MAX_USER_NAME_LENGTH+1:Constants.MAX_USER_NAME_LENGTH+1+Constants.MAX_ACCOUNT_TYPE_LENGTH]
            if check_format.lower() not in [account.lower() for account in Constants.ALL_ACCOUNTS]:
                display_error_message(f"INVALID CURRENT USERS FILE, invalid account type on line:  {line_num+1}")
                return False

            # checking for credit
            pattern = r'^[\d.]{%d}$' % Constants.MAX_CREDIT_LENGTH
            check_format=line[Constants.MAX_USER_NAME_LENGTH+1+Constants.MAX_ACCOUNT_TYPE_LENGTH+1:]


            if not re.match(pattern, check_format):
                display_error_message(f"INVALID CURRENT USERS FILE, invalid balance on line:  {line_num+1}")
                return False
        print("CURRENT USER FILE is Valid")
        return True

    #elif file_name==Constants.INPUT_GAMES_COLLECTION:
    elif "game_collection.etf"in file_name:
        print("Checking Validity of GAMES COLLECTIONS FILE")
        for line_num,line in enumerate(data[:],start=0):

            # check to see that after game name there is a space
            check_format=line[Constants.MAX_GAME_NAME_LENGTH:Constants.MAX_GAME_NAME_LENGTH+1]

            if check_format!=Constants.CHAR_BETWEEN_COMPONENTS:
                display_error_message(f"INVALID GAMES COLLECTIONS FILE, game name not formatted properly on line: {line_num+1}")
                return False

            #  chceck that the usernames are valid foramtting
            check_format=line[Constants.MAX_GAME_NAME_LENGTH+1:]
            if len(check_format)!=Constants.MAX_USER_NAME_LENGTH:
                display_error_message(f"INVALID GAMES COLLECTIONS FILE, user name  not formatted properly on line: {line_num+1}")
                return False

        print("GAMES COLLECTION FILE is VALID")
        return True

    #elif file_name==Constants.INPUT_AVAILABLE_GAMES:
    elif "available_games.etf" in file_name:
        print("Checking Validity of AVAILABLE GAMES FILE")
        for line_num,line in enumerate(data[:],start=0):


            # check to see that after game name there is a space
            check_format=line[Constants.MAX_GAME_NAME_LENGTH:Constants.MAX_GAME_NAME_LENGTH+1]


            if check_format!=Constants.CHAR_BETWEEN_COMPONENTS:
                display_error_message(f"INVALID AVAILABLE GAMES FILE, game name not formatted properly on line: {line_num+1}")
                return False

            # check to see that after username  there is a space
            check_format=line[Constants.MAX_GAME_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH:Constants.MAX_GAME_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1]
            if check_format!=Constants.CHAR_BETWEEN_COMPONENTS:
                display_error_message(f"INVALID AVAILABLE GAMES FILE, user name not formatted properly on line: {line_num+1}")
                return False

            #checking for credit
            check_format=line[Constants.MAX_GAME_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1:]
            pattern = r'^[\d.]{%d}$' % Constants.MAX_GAME_PRICE_LENGTH

            if not re.match(pattern, check_format):
                display_error_message(f"INVALID AVAILABLE GAMES FILE, invalid game price on line:  {line_num+1}")
                return False

        print("AVAILABLE GAMES FILE is VALID")
        return True



def check_valid_username_formatting(line,line_num):
    check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_USER_NAME_LENGTH:Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1]
    if check_format!=Constants.CHAR_BETWEEN_COMPONENTS:
        display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid username formating on line:  {line_num+1}")
        return False
    return True
def check_valid_account_type_formatting(line,line_num):
    check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1+Constants.MAX_ACCOUNT_TYPE_LENGTH:
                     Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1+Constants.MAX_ACCOUNT_TYPE_LENGTH+1]
    if check_format!=Constants.CHAR_BETWEEN_COMPONENTS:
        display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid ACCOUNT TYPE formating on line:  {line_num+1}")
        return False
    return True

def check_valid_credit_amount_formatting(line,line_num):
    pattern = r'^[\d.]{%d}$' % Constants.MAX_CREDIT_LENGTH
    check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1+Constants.MAX_ACCOUNT_TYPE_LENGTH+1:]
    if not re.match(pattern, check_format):
        display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid balance on line:  {line_num+1}")
        return False
    return True

def check_valid_account_type(line,line_num):
    valid_accounts = set({"AA","FS","BS","SS"})
    account_type=line[Constants.USER_CODE_START_INDEX:Constants.USER_CODE_END_INDEX]
    if account_type not in valid_accounts:
        display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid ACCOUNT TYPE:  {line_num+1}")
        return False
    return True

def validation_checks(line,line_num):
    all_checks = [
        check_valid_username_formatting,
        check_valid_account_type_formatting,
        check_valid_credit_amount_formatting,
        check_valid_account_type
    ]
    for check in all_checks:
        if not check(line, line_num):
            return False
    return True


def check_valid_transaction_file(data: list[str])-> bool:
    print("Checking Validity of Merged Transaction File")
    all_transactions = set()
    for line_num,line in enumerate(data[:-1],start=0):
        check_format=line[:Constants.MAX_ACCOUNT_TYPE_LENGTH]
        if check_format not in Constants.ALL_CODES:
            display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid code on line:  {line_num+1}")
            return False
        else:
            check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH:Constants.MAX_ACCOUNT_TYPE_LENGTH+1]
            if check_format!=Constants.CHAR_BETWEEN_COMPONENTS:
                display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid code formating on line:  {line_num+1}")
                return False

            current_code=line[:Constants.MAX_ACCOUNT_TYPE_LENGTH]

            # checking the transaction format based on code given
            if current_code==Constants.LOGOUT_CODE:

                check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_USER_NAME_LENGTH:Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1]
                if check_format!=Constants.CHAR_BETWEEN_COMPONENTS:
                    display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid username formating on line:  {line_num+1}")
                    return False


                check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1+Constants.MAX_ACCOUNT_TYPE_LENGTH:
                                Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1+Constants.MAX_ACCOUNT_TYPE_LENGTH+1]
                if check_format!=Constants.CHAR_BETWEEN_COMPONENTS:
                    display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid ACCOUNT TYPE formating on line:  {line_num+1}")
                    return False

                # checking avaiable credit component
                pattern = r'^[\d.]{%d}$' % Constants.MAX_CREDIT_LENGTH
                check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1+Constants.MAX_ACCOUNT_TYPE_LENGTH+1:]

                if not re.match(pattern, check_format):
                    display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid balance on line:  {line_num+1}")
                    return False

            elif current_code==Constants.SELL_GAME_CODE:

                check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_GAME_NAME_LENGTH:
                                Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_GAME_NAME_LENGTH+1]


                if check_format!=Constants.CHAR_BETWEEN_COMPONENTS:
                    display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid game name formating on line:  {line_num+1}")
                    return False


                check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_GAME_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH:
                                Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_GAME_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1:]

                if check_format!=Constants.CHAR_BETWEEN_COMPONENTS:
                    display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid username formating on line:  {line_num+1}")
                    return False

                check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_GAME_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1:]
                pattern = r'^[\d.]{%d}$' % Constants.MAX_GAME_PRICE_LENGTH

                if not re.match(pattern, check_format):
                    display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE invalid game price on line:  {line_num+1}")
                    return False
            elif current_code==Constants.REFUND_CODE:

                check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_GAME_NAME_LENGTH:
                                Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_GAME_NAME_LENGTH+1]

                check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_GAME_NAME_LENGTH:
                                Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_GAME_NAME_LENGTH+1]


                if check_format!=Constants.CHAR_BETWEEN_COMPONENTS:
                    display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid game name formating on line:  {line_num+1}")
                    return False


                check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_GAME_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH:
                                Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_GAME_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1:]

                if check_format!=Constants.CHAR_BETWEEN_COMPONENTS:
                    display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid username formating on line:  {line_num+1}")
                    return False

                check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_GAME_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH:
                                    Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_GAME_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1:]
                if check_format!=Constants.CHAR_BETWEEN_COMPONENTS:
                    display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid username formating on line:  {line_num+1}")
                    return False


                check_format=line[Constants.MAX_ACCOUNT_TYPE_LENGTH+1+Constants.MAX_GAME_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1+Constants.MAX_USER_NAME_LENGTH+1:]
                pattern = r'^[\d.]{%d}$' % Constants.MAX_CREDIT_LENGTH
                if not re.match(pattern, check_format):
                    display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, invalid refund amount format on line:  {line_num+1}")
                    return False



            #ADD CHECKS HERE
            elif current_code==Constants.BUY_CODE:
               return
            elif current_code==Constants.CREATE_CODE:
                if line in all_transactions:
                    display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, duplicate transaction:  {line_num+1}")
                    return False
                if not validation_checks(line,line_num):
                    return False
                else:
                    all_transactions.add(line)
            elif current_code==Constants.DELETE_CODE:
                if line in all_transactions:
                    display_error_message(f"INVALID MERGED DAILY TRANSACTION FILE, duplicate transaction:  {line_num+1}")
                    return False
                if not validation_checks(line,line_num):
                    return False
                else:
                    all_transactions.add(line)
            elif current_code==Constants.ADD_CREDIT_CODE:
                if not validation_checks(line,line_num):
                    return False

    print("MERGED DAILY TRANSACTION FILE is VALID")
    return True
