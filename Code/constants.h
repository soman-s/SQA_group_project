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
    static const std::string LOGOUT;

    // file stuff
    static const std::string ALL_USER_FILE;

    // Constraints
    static const int MAX_USER_LENGTH;
    static const std::string EXIT_OPTION;


};

#endif
