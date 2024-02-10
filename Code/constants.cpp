#include "constants.h"

const std::string constants::ADMIN = "AA";
const std::string constants::FULL_STANDARD = "FS";
const std::string constants::SELL_STANDARD = "SS";
const std::string constants::BUY_STANDARD = "BS";
const std::string constants::UNKNOWN = "-1";

const std::string constants::LOGIN = "Login";
const std::string constants::EXIT = "Exit";
const std::string constants::CREATE = "Create";
const std::string constants::DELETE = "Delete";
const std::string constants::SELL = "Sell";
const std::string constants::BUY = "Buy";
const std::string constants::REFUND = "Refund";
const std::string constants::LIST_AVAILABLE_GAMES = "View Available Games";
const std::string constants::LIST_ALL_USERS = "View All Users";
const std::string constants::ADD_CREDIT = "Add Credit";
const std::string constants::LOGOUT = "Logout";


// file stuff
const std::string constants::ALL_USER_FILE="files/current_users.etf";
const std::string constants::AVAILABLE_GAMES="files/available_games.etf";

// Constraints
const int constants::MAX_USER_NAME_LENGTH=15;
const int constants::MAX_GAME_NAME_LENGTH=25;
const int constants::MAX_ACCOUNT_TYPE_LENGTH=2;
const float constants::MAX_GAME_PRICE=999.99;
const float constants::MAX_CREDIT_AMOUNT=999.99;
const float constants::MIN_CREDIT_AMOUNT=0;
const std::string constants::EXIT_MENU_OPTION="-1";
