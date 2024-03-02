#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

/**
 * @brief This class contains constants used throughout the program.
 */
class constants {
public:
    /**
     * @brief Default constructor for the constants class.
     */
    constants();

    // user types
    static const std::string ADMIN; /**< Administrator user type. */
    static const std::string FULL_STANDARD; /**< Full standard user type. */
    static const std::string SELL_STANDARD; /**< Sell standard user type. */
    static const std::string BUY_STANDARD; /**< Buy standard user type. */
    static const std::string UNKNOWN; /**< Unknown user type. */

    // menu stuff
    static const std::string LOGIN; /**< Menu option: Login. */
    static const std::string EXIT; /**< Menu option: Exit. */
    static const std::string CREATE; /**< Menu option: Create. */
    static const std::string DELETE; /**< Menu option: Delete. */
    static const std::string SELL; /**< Menu option: Sell. */
    static const std::string BUY; /**< Menu option: Buy. */
    static const std::string REFUND; /**< Menu option: Refund. */
    static const std::string LIST_AVAILABLE_GAMES; /**< Menu option: List available games. */
    static const std::string LIST_ALL_USERS; /**< Menu option: List all users. */
    static const std::string ADD_CREDIT; /**< Menu option: Add credit. */
    static const std::string LOGOUT; /**< Menu option: Logout. */

    // file stuff
    static const std::string ALL_USER_FILE; /**< File name for storing all user data. */
    static const std::string AVAILABLE_GAMES; /**< File name for storing available games data. */
    static const std::string GAMES_COLLECTION; /**< File name for storing games collection data. */

    // Constraints
    static const int MAX_USER_NAME_LENGTH; /**< Maximum length of a user name. */
    static const int MAX_GAME_NAME_LENGTH; /**< Maximum length of a game name. */
    static const int MAX_ACCOUNT_TYPE_LENGTH; /**< Maximum length of an account type. */
    static const float MAX_GAME_PRICE; /**< Maximum price of a game. */
    static const std::string EXIT_MENU_OPTION; /**< Menu option: Exit. */
    static const double MAX_CREDIT_AMOUNT; /**< Maximum credit amount. */
    static const double MIN_CREDIT_AMOUNT; /**< Minimum credit amount. */
    static const float MIN_ADD_CREDITS; /**< Minimum credit amount to add */
    static const float MAX_ADD_CREDITS;/**< Maximum credit amount to add */
    static const std::string FAIL_OPTION; /**< Option indicating failure. */
    static const std::string SUCESS_OPTION; /**< Option indicating success. */
    static const std::string ERROR_CODE; /**< Option indicating success. */

    // log codes
    static const std::string LOGOUT_CODE;
    static const std::string SELL_GAME_CODE;
    static const std::string REFUND_CODE;
    static const std::string BUY_CODE;
    static const std::string CREATE_CODE;
    static const std::string DELETE_CODE;



};

#endif
