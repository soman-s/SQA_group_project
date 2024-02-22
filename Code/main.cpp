#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <typeinfo>

// custom classes
#include "menus.h"
#include "user_file_process.h"
#include "games_file_process.h"
#include "constants.h"
#include "utils.h"
#include "transactions.h"

using namespace std;

int main()
{
    // Initialization of data structures
    vector <string> transaction_log;
    vector<string> all_users; /**< Vector containing information about all users. */
    vector<string> all_games; /**< Vector containing information about all available games. */
    vector<string> all_games_collection; /**< Vector containing information about games owned by users. */
    vector<string> games_to_add; /**< Vector containing games to be added for sale. */
    string current_user_type; /**< Type of the currently logged-in user. */
    string menu_option = ""; /**< Option selected from the menu. */

    // Load user and game information from files
    all_users = user_file_process().get_all_users_info(constants::ALL_USER_FILE);
    all_games = games_file_process().get_all_game_info(constants::AVAILABLE_GAMES);
    all_games_collection = games_file_process().get_all_game_info(constants::GAMES_COLLECTION);

    // Main loop for user interaction
    while (menu_option != constants::EXIT)
    {
        string user_input;
        int num_entry;

        // Display home menu
        menus().display_home_menu();
        cout << "Enter an option: ";
        cin >> user_input;

        try {
            num_entry = stoi(user_input);
            if (num_entry > 0 && num_entry <= menus().get_num_home_options())
             {
                // Process valid entry
                menu_option = menus().get_home_option(num_entry - 1);
            }
            else
            {
                cout << "Invalid entry" << endl;
                menu_option = "";
            }
        }
        catch (const std::invalid_argument&)
        {
            cerr << "Invalid argument. Please enter a valid integer." << endl;
            menu_option = "";
        }
        catch (const std::out_of_range&)
        {
            cerr << "Out of range. Please enter a smaller integer." << endl;
            menu_option = "";
        }

        // Process selected option
        if (menu_option == constants::LOGIN)
        {
            // User login process
            string current_user_name;
            cout << "Login" << endl;
            cout << "Enter Username: ";
            cin >> current_user_name;
            current_user_name = utils().pad_username(current_user_name);

            // Validate user login
            while (!user_file_process().check_user_names(all_users, current_user_name) && current_user_name != constants::EXIT_MENU_OPTION)
             {
                cout << "Invalid Login" << endl;
                cout << "Enter valid username or -1 to exit:";
                cin >> current_user_name;
                if (current_user_name != constants::EXIT_MENU_OPTION) {
                    current_user_name = utils().pad_username(current_user_name);
                } else {
                    cout << "EXIT" << endl;
                }
            }

            if (user_file_process().check_user_names(all_users, current_user_name)) {
                // Successful login, display user menu
                string user_menu_option = "";
                cout << "Logged IN" << endl;
                while (user_menu_option != constants::LOGOUT)
                {
                    // Display user-specific menu
                    current_user_type = user_file_process().get_user_type(all_users, current_user_name);
                    menus().display_user_menus(current_user_type);
                    cout << "Enter an option: ";
                    cin >> user_input;

                    try {
                        num_entry = stoi(user_input);
                        if (num_entry > 0 && num_entry <= menus().get_num_menu_options(current_user_type))
                         {
                            user_menu_option = menus().get_user_menu_option(current_user_type, num_entry - 1);
                            // Process selected user menu option
                            if (user_menu_option == constants::SELL)
                            {
                                string new_game_to_sell;
                                new_game_to_sell = transactions().process_sell(all_games, games_to_add, current_user_name);
                                if (new_game_to_sell !=constants::FAIL_OPTION)
                                 {
                                    string game_name = new_game_to_sell.substr(0, constants::MAX_GAME_NAME_LENGTH);

                                    // Don't update the vectors, only take in accounts read from file

                                    //utils().update_games_to_add_vector(games_to_add, new_game_to_sell);
                                    //utils().update_games_collection(all_games_collection, game_name, current_user_name);
                                }
                            }
                            else if (user_menu_option == constants::CREATE)
                             {
                                string new_user;
                                new_user = transactions().process_create(all_users);
                                if (new_user != constants::EXIT_MENU_OPTION) {
                                    all_users.push_back(new_user);
                                }
                            }
                            else if (user_menu_option == constants::DELETE)
                             {
                                string user_to_remove;
                                user_to_remove = transactions().process_delete(all_users, current_user_name);
                                if (user_to_remove != constants::EXIT_MENU_OPTION) {
                                  cout << "User deleted" << endl;
                                  utils().remove_user(user_to_remove, all_users);
                                  utils().remove_games(user_to_remove, all_games);

                                }
                            }
                            else if (user_menu_option == constants::LIST_ALL_USERS)
                             {
                                transactions().show_all_users(all_users);
                            }
                            else if (user_menu_option == constants::LIST_AVAILABLE_GAMES)
                            {
                                transactions().show_all_game_info(all_games);
                            } else if
                            (user_menu_option == constants::REFUND)
                             {
                                if (transactions().refund(all_users, all_games, all_games_collection) == constants::FAIL_OPTION)
                                 {
                                    cout << "Cannot issue refund, seller will have negative balance" << endl;
                                }
                                else
                                 {
                                    cout << "Refund Successfully" << endl;
                                }
                            }

                            else if (user_menu_option == constants::BUY)
                            {
                                if (transactions().process_buy(current_user_name, all_users, all_games, all_games_collection) == constants :: FAIL_OPTION)
                                {
                                cout << "Buy transaction unsuccessful" << endl;
                                }
                                else
                                {
                                cout << "Game has been bought" << endl;
                                cout << endl;
                                }
                            }

                            else if (user_menu_option == constants::ADD_CREDIT)
                            {
                              if(transactions().process_credit(user_input,all_users,current_user_name) == constants :: SUCESS_OPTION){
                                cout << "Sucessfully added credit amount to user" << endl;
                              }

                            }
                        }
                        else {
                            cout << "Invalid entry" << endl;
                            user_menu_option = "";
                        }
                    }
                    catch (const std::invalid_argument&)
                     {
                        cerr << "Invalid argument. Please enter a valid integer." << endl;
                        user_menu_option = "";
                    }
                    catch (const std::out_of_range&)
                    {
                        cerr << "Out of range. Please enter a smaller integer." << endl;
                        user_menu_option = "";
                    }
                } // end of user menu loop

                // User logout process

                cout << "LOGGED OUT" << endl;
                string log_entry;
                log_entry= constants::LOGOUT_CODE+" "+current_user_name+" "+current_user_type+" "+user_file_process().get_user_credit(all_users,current_user_name);
                utils().update_transction_log(log_entry,transaction_log);
                

                //utils().update_games_list(all_games, games_to_add);
            } // end of successful login
        } // end of login option processing

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } // end of home menu loop

    cout << "EXITS" << endl;
    transactions().process_logout(transaction_log);
    return 0;
}
