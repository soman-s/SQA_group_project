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

    void update_games_to_add_vector(vector<string>& games_to_add_vec,string& new_game_to_sell);
    void update_games_list(vector<string>& current_games,vector<string>& new_games);
    void update_games_collection(vector<string>& games_collect, string& game_name,string& owner);
    void remove_user(string user, vector<string>& all_users);
};

#endif
