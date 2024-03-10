#include "constants.h"

// Account Types
const std::string constants::ADMIN = "AA";
const std::string constants::FULL_STANDARD = "FS";
const std::string constants::SELL_STANDARD = "SS";
const std::string constants::BUY_STANDARD = "BS";
const std::string constants::UNKNOWN = "-1";

// Menu Options
const std::string constants::LOGIN = "Login";
const std::string constants::EXIT = "Exit";
const std::string constants::CREATE = "Create";
const std::string constants::DELETE = "Delete";
const std::string constants::SELL = "Sell";
const std::string constants::BUY = "Buy";
const std::string constants::REFUND = "Refund";
const std::string constants::SEARCH = "Search";
const std::string constants::LIST_AVAILABLE_GAMES = "View Available Games";
const std::string constants::LIST_ALL_USERS = "View All Users";
const std::string constants::ADD_CREDIT = "Add Credit";
const std::string constants::LOGOUT = "Logout";


// file stuff
const std::string constants::ALL_USER_FILE="log_files/current_users.etf";
const std::string constants::AVAILABLE_GAMES="log_files/available_games.etf";
const std::string constants::GAMES_COLLECTION="log_files/game_collection.etf";

// Constraints
const int constants::MAX_USER_NAME_LENGTH=15;
const int constants::MAX_GAME_NAME_LENGTH=25;
const int constants::MAX_ACCOUNT_TYPE_LENGTH=2;
const float constants::MAX_GAME_PRICE=99999.99;
const double constants::MAX_CREDIT_AMOUNT=999999.00;
const double constants::MIN_CREDIT_AMOUNT=0;
const float constants::MIN_ADD_CREDITS=0;
const float constants::MAX_ADD_CREDITS=1000.00;
const std::string constants::EXIT_MENU_OPTION="-1";
const std::string constants:: FAIL_OPTION="-1";
const std::string constants:: SUCESS_OPTION="1";
const std::string constants:: ERROR_CODE="-10";


// transaction log codes

const std::string constants::LOGOUT_CODE= "00";
const std::string constants::SELL_GAME_CODE= "03";
const std::string constants::REFUND_CODE= "05";
const std::string constants::BUY_CODE = "04";
const std::string constants::CREATE_CODE = "01";
const std::string constants::DELETE_CODE = "02";
const std::string constants::ADD_CREDIT_CODE = "06";
