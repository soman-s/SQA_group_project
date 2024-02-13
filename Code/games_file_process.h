#ifndef GAMES_FILE_PROCESS
#define GAMES_FILE_PROCESS

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief This class provides functionality for processing game files and related operations.
 */
class games_file_process {
public:
    /**
     * @brief Default constructor for the games_file_process class.
     */
    games_file_process();

    /**
     * @brief Retrieves all game information from the specified game file.
     *
     * @param game_file The file containing game information.
     * @return A vector containing all game information.
     */
    vector<string> get_all_game_info(string game_file);

    /**
     * @brief Checks if a game name is valid.
     *
     * @param game_name The name of the game to check.
     * @return True if the game name is valid, false otherwise.
     */
    bool check_valid_game_name(string& game_name);

    /**
     * @brief Checks if a game already exists in the provided game information.
     *
     * @param game_info Vector containing game information.
     * @param game_name The name of the game to check.
     * @return True if the game already exists, false otherwise.
     */
    bool check_game_already_exists(vector<string>& game_info, string& game_name);

    /**
     * @brief Checks if a user owns a particular game.
     *
     * @param games_collection Vector containing the user's game collection.
     * @param game_name The name of the game to check ownership for.
     * @param user_name The name of the user to check ownership against.
     * @return True if the user owns the game, false otherwise.
     */
    bool check_user_owns_game(vector<string>& games_collection, string& game_name, string& user_name);

    /**
     * @brief Checks if a user sells a particular game.
     *
     * @param all_games Vector containing all available games.
     * @param game_name The name of the game to check for sale.
     * @param seller_name The name of the user selling the game.
     * @return True if the user sells the game, false otherwise.
     */
    bool check_user_sells_game(vector<string>& all_games, string& game_name, string& seller_name);

    /**
     * @brief Checks if a game has a price associated with it.
     *
     * @param all_games Vector containing all available games.
     * @param game_name The name of the game to check.
     * @param game_price Reference to store the price of the game if found.
     * @return True if the game has a price, false otherwise.
     */
    bool is_game_price(vector<string>& all_games, string& game_name, float& game_price);

    /**
     * @brief Removes a game from a user's collection.
     *
     * @param games_collection Vector containing the user's game collection.
     * @param game_name The name of the game to remove.
     * @param user_name The name of the user from whose collection the game is removed.
     */
    void remove_game_from_user_collection(vector<string>& games_collection, string& game_name, string& user_name);
};

#endif
