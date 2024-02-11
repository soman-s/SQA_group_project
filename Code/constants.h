#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

class constants {
public:
    constants();

    // user types
    static const std::string ADMIN;
    static const std::string FULL_STANDARD;
    static const std::string SELL_STANDARD;
    static const std::string BUY_STANDARD;
    static const std::string UNKNOWN;


    // menu stuff
    static const std::string LOGIN;
    static const std::string EXIT;
    static const std::string CREATE;
    static const std::string DELETE;
    static const std::string SELL;
    static const std::string BUY;
    static const std::string REFUND;
    static const std::string LIST_AVAILABLE_GAMES;
    static const std::string LIST_ALL_USERS;
    static const std::string ADD_CREDIT;
    static const std::string LOGOUT;

    // file stuff
    static const std::string ALL_USER_FILE;
    static const std::string AVAILABLE_GAMES;
    static const std::string GAMES_COLLECTION;


    // Constraints
    static const int MAX_USER_NAME_LENGTH;
    static const int MAX_GAME_NAME_LENGTH;
    static const int MAX_ACCOUNT_TYPE_LENGTH;
    static const float MAX_GAME_PRICE;
    static const std::string EXIT_MENU_OPTION;
    static const float MAX_CREDIT_AMOUNT;
    static const float MIN_CREDIT_AMOUNT;
    static const std::string FAIL_OPTION;
    static const std::string SUCESS_OPTION;



};

#endif
