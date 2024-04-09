#ifndef TRANSACTIONS
#define TRANSACTIONS

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


#include "menus.h"
#include "user_file_process.h"
#include "games_file_process.h"
#include "constants.h"
#include "utils.h"

using namespace std;

/**
 * @brief This class provides functionality for processing transactions.
 */
class transactions {
public:
    /**
     * @brief Default constructor for the transactions class.
     */
    transactions();

    /**
     * @brief Process the selling of a game.
     *
     * @param all_games Vector containing all available games.
     * @param games_to_add Vector containing games to be added to the user's collection.
     * @param current_user_name The name of the current user.
     * @return A message indicating the result of the transaction.
     */
    string process_sell(vector<string>& all_games, vector<string>& games_to_add, string current_user_name,vector<string>& transaction_log);

    /**
     * @brief Process the creation of a new user.
     *
     * @param all_users Vector containing all user information.
     * @param transaction_log Vector containg all transaction logs
     * @return A message indicating the result of the transaction.
     */
    string process_create(vector<string>& all_users,vector<string>& transaction_log, string current_user_type);

    /**
     * @brief Process the deletion of a user.
     *
     * @param all_users Vector containing all user information.
     * @param current_user The name of the user to be deleted.
     * @param transaction_log Vector containg all transaction logs
     * @return A message indicating the result of the transaction.
     */
    string process_delete(vector<string>& all_users, string current_user,vector<string>& transaction_log, string user_to_remove_type);

    /**
     * @brief Show information about all users.
     *
     * @param all_users Vector containing all user information.
     */
    void show_all_users(vector<string>& all_users);

    /**
     * @brief Show information about all games.
     *
     * @param all_users Vector containing all user information (used to get game collections).
     */
    void show_all_game_info(vector<string>& all_users);

    /**
     * @brief Process a refund transaction.
     *
     * @param all_users Vector containing all user information.
     * @param all_games Vector containing all available games.
     * @param game_collec Vector containing game collections.
     * @return A message indicating the result of the refund transaction.
     */
    string refund(vector<string>& all_users, vector<string>& all_games, vector<string>& game_collec,vector<string>& transaction_log);

    /**
     * @brief Process a buy transaction.
     *
     * @param buyer_name Name of buyer
     * @param all_users Vector containing all user information.
     * @param all_games Vector containing all available games.
     * @param game_collec Vector containing game collections.
     * @return A message indicating the result of the buy transaction.
     */
    string process_buy(string buyer_name, vector<string>& all_users, vector<string>& all_games, vector<string>& game_collec, vector<string>& transaction_log);


    /**
     * @brief Process a add-credit transaction.
     *
     * @param menu_option menu option to determine if it's an admin or non-admin menu
     * @param all_users Vector containing all user information.
     * @param user user to add credit amount to.
     * @return A message indicating the result of the add credit transaction.
     */
    string process_credit(string menu_option, vector<string>& all_users, string user,vector<string>& transaction_log, unordered_map<string, float>& user_total_credits, unordered_map<string, float>& user_session_credits);


    void process_logout(vector<string>& transaction_log);


    /**
     * @brief search users and games.
     *
     * @param user_name user name of logged in account to determine account type.
     * @param all_users Vector containing all user information.
     * @param all_games Vector containing all available games.
     * @return Results of the search
     */
    string search(string user_name, vector<string>& all_users, vector<string>& all_games);
};

#endif
