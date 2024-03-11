class Constants:
    # Transaction Codes
    LOGOUT_CODE= "00"
    SELL_GAME_CODE= "03"
    REFUND_CODE= "05"
    BUY_CODE = "04"
    CREATE_CODE = "01"
    DELETE_CODE = "02"
    ADD_CREDIT_CODE = "06"



    # INPUT File Locations
    INPUT_DAILY_TRANSACTION="ori_log_files/daily_transactions.etf"
    INPUT_ALL_USER_FILE="ori_log_files/current_users.etf"
    INPUT_AVAILABLE_GAMES="ori_log_files/available_games.etf"
    INPUT_GAMES_COLLECTION="ori_log_files/game_collection.etf"

    #output file locations
    OUTPUT_DAILY_TRANSACTION="mod_log_files/daily_transaction.etf"
    OUTPUT_ALL_USER_FILE="mod_log_files/current_users.etf"
    OUTPUT_AVAILABLE_GAMES="mod_log_files/available_games.etf"
    OUTPUT_GAMES_COLLECTION="mod_log_files/game_collection.etf"



    #Constraints
    MAX_USER_NAME_LENGTH=15
    MAX_GAME_NAME_LENGTH=25
    MAX_ACCOUNT_TYPE_LENGTH=2
    MAX_GAME_PRICE=99999.99
    MAX_CREDIT_AMOUNT=999999.00
    MIN_CREDIT_AMOUNT=0
    MIN_ADD_CREDITS=0
    MAX_ADD_CREDITS=1000.00
    MAX_GAME_PRICE_LENGTH=6
