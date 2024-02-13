#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief This class provides functionality for displaying menus.
 */
class menus {
private:
    

    // Menu options
    vector<string> home_options = {"Login", "Exit"}; /**< Options for the home menu. */
    vector<string> admin_options = {"Create", "Delete", "Sell", "Buy", "Refund", "Add Credit", "View All Users", "View Available Games", "Logout"}; /**< Options for the admin menu. */
    vector<string> full_options = {"Sell", "Buy", "Add Credit", "View Available Games", "Logout"}; /**< Options for the full-standard user menu. */
    vector<string> buy_options = {"Buy", "Add Credit", "View Available Games", "Logout"}; /**< Options for the buy-standard user menu. */
    vector<string> sell_options = {"Sell", "Add Credit", "View Available Games", "Logout"}; /**< Options for the sell-standard user menu. */
    vector<string> create_options = {"Admin", "Full-Standard", "Buy-Standard", "Sell-Standard"}; /**< Options for the create menu. */

public:
    /**
     * @brief Default constructor for the menus class.
     */
    menus();

    /**
     * @brief Display the home menu options.
     */
    void display_home_menu();

    /**
     * @brief Display the menu options based on the user type.
     *
     * @param user_type The type of user.
     */
    void display_user_menus(string user_type);

    /**
     * @brief Get the number of options in the home menu.
     *
     * @return The number of home menu options.
     */
    int get_num_home_options();

    /**
     * @brief Get the home menu option at the specified index.
     *
     * @param index The index of the home menu option.
     * @return The home menu option at the specified index.
     */
    string get_home_option(int index);

    /**
     * @brief Get the number of options in the menu based on the user type.
     *
     * @param user_type The type of user.
     * @return The number of menu options for the specified user type.
     */
    int get_num_menu_options(string user_type);

    /**
     * @brief Get the menu option at the specified index based on the user type.
     *
     * @param user_type The type of user.
     * @param index The index of the menu option.
     * @return The menu option at the specified index for the specified user type.
     */
    string get_user_menu_option(string user_type, int index);

    /**
     * @brief Display all available user types for creation.
     */
    void display_all_user_types();
};

#endif
