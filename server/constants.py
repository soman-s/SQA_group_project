class Constants:
    # Transaction Codes
    LOGOUT_CODE= "00"
    SELL_GAME_CODE= "03"
    REFUND_CODE= "05"
    BUY_CODE = "04"
    CREATE_CODE = "01"
    DELETE_CODE = "02"
    ADD_CREDIT_CODE = "06"
    ALL_CODES=[LOGOUT_CODE,SELL_GAME_CODE,REFUND_CODE,BUY_CODE,CREATE_CODE,DELETE_CODE,ADD_CREDIT_CODE]

    # Account types:
    ADMIN_ACCOUNT="AA"
    SELL_ACCOUNT="SS"
    BUY_ACCOUNT="BS"
    FULL_ACCOUNT="FS"
    ACCOUNT_MANAGER="AM"

    ALL_ACCOUNTS=[ADMIN_ACCOUNT,SELL_ACCOUNT,BUY_ACCOUNT,FULL_ACCOUNT,ACCOUNT_MANAGER]


    #File Name
    MERGE_DAILY_TRANSACTION_FILENAME='merged_daily_transactions.etf'

    #input File PATHS
    LOG_FILES_PATH="ori_log_files/daily_transactions"



    # INPUT File Locations
    INPUT__MERGE_DAILY_TRANSACTION="ori_log_files/merged_daily_transactions.etf"
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
    MAX_GAME_PRICE_LENGTH=6
    MAX_CREDIT_LENGTH=9
    CHAR_BETWEEN_COMPONENTS=" "
    USER_CODE_START_INDEX = 19
    USER_CODE_END_INDEX = 21


    # FAIL
    FAIL_CODE="-1"
