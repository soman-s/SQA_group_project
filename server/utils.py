from typing import Union
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

def display__sucess_message(transaction: str):
    """
    Display a sucess message

    Args:
        Transaction (str): The tranaction that was sucessful processed.
    """
    print(f"Transaction processed: {transaction}")
