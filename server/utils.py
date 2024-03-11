from typing import Union
from constants import Constants

def pad_end_file(total_chars:int)->str:
    ending=word = "END" + " " * (total_chars - len("END"))
    return ending




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
