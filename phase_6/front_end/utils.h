#ifndef UTILS
#define UTILS

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

/**
 * @brief A utility class providing various string manipulation functions.
 */
class utils {
public:
    /**
     * @brief Default constructor for the utils class.
     */
    utils();

    /**
     * @brief Converts a string to lowercase.
     *
     * @param str The input string to be converted.
     * @return The converted lowercase string.
     */
    string convert_to_lower(const string& str);

    /**
     * @brief Pads the given string with spaces to match the maximum username length(15 chars).
     *
     * @param input The input string to be padded.
     * @return The padded string.
     */
    string pad_username(const string& input);

    /**
     * @brief Checks if the given string contains only alphanumeric characters and spaces.
     *
     * @param input The input string to be checked.
     * @return True if the string contains only alphanumeric characters and spaces, false otherwise.
     */
    bool check_alpha_numeric_space(const string& input);

    /**
     * @brief Pads the given string with spaces to match the maximum game name length(25 chars).
     *
     * @param input The input string to be padded.
     * @return The padded string.
     */
    string pad_game_name(const string& input);

    /**
     * @brief Pads the given price with leading zeros and ensures it has two decimal places(max 6 characters).
     *
     * @param input The input price to be padded.
     * @return The padded price as a string.
     */
    string pad_game_price(const float& input);

    /**
     * @brief Pads the given credit amount with leading zeros and ensures it has two decimal places(max 9 characters).
     *
     * @param input The input credit amount to be padded.
     * @return The padded credit amount as a string.
     */
    string pad_credit_amount(const float& input);

    /**
 * @brief Updates the games to add vector with a new game to sell.
 *
 * @param games_to_add_vec The vector containing games to be added for sale.
 * @param new_game_to_sell The name of the new game to be added for sale.
 */
void update_games_to_add_vector(vector<string>& games_to_add_vec, string& new_game_to_sell);

/**
 * @brief Updates the current games list with new games.
 *
 * @param current_games The vector containing the current list of games.
 * @param new_games The vector containing new games to be added to the list.
 */
void update_games_list(vector<string>& current_games, vector<string>& new_games);

/**
 * @brief Updates the games collection with a new game and its owner.
 *
 * @param games_collect The vector containing the games collection.
 * @param game_name The name of the new game to be added.
 * @param owner The owner of the new game.
 */
void update_games_collection(vector<string>& games_collect, string& game_name, string& owner);

/**
 * @brief Removes a user from the list of all users.
 *
 * @param user The name of the user to be removed.
 * @param all_users The vector containing information about all users.
 */
void remove_user(string user, vector<string>& all_users);

void remove_games(string user, vector<string>& current_games);

void update_transction_log(string entry,vector<string>& transaction_log);

};

#endif
