#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>

// custom classes
#include "menus.h"
#include "user_file_process.h"
#include "games_file_process.h"
#include "constants.h"
#include "utils.h"
#include "transactions.h"


// custom FUNCTIONS
vector<string> update_games_to_add_vector(vector<string>& games_to_add_vec,string& new_game_to_sell);
vector<string> update_games_list(vector<string>& current_games,vector<string>& new_games);

using namespace std;


const int MAX_USER_LENGTH=15;
const int USER_TYPE_CODE=2;
const int TOTAL_USER_CODE=28;


int main()
{
    vector<string> all_users;
    vector<string> all_games;
    vector<string> games_to_add;
    string current_user_type;

    string menu_option="";


    all_users=user_file_process().get_all_users_info(constants::ALL_USER_FILE);
    all_games=games_file_process().get_all_game_info(constants::AVAILABLE_GAMES);

  while(menu_option!=constants::EXIT)
    {
      string user_menu_input;
      string user_input;
      int num_entry;

      menus().display_home_menu();
      cout<<"Enter an option:" ;
      cin>>user_input;

      try {
            num_entry =stoi(user_input);
            if(num_entry>0 && num_entry<=menus().get_num_home_options())
            {
              //valid_entry = true;
              menu_option=menus().get_home_option(num_entry-1);


            }
            else
            {
              cout<<"Invalid entry"<<endl;
              menu_option="";
            }
        } catch (const std::invalid_argument&) {
            cerr << "Invalid argument. Please enter a valid integer." << endl;
            menu_option="";
        } catch (const std::out_of_range&) {
            cerr << "Out of range. Please enter a smaller integer." << endl;
            menu_option="";
        }



        if (menu_option== constants::LOGIN)
        {
          string current_user_name;
          cout<<"Login"<<endl;
          cout<<"Enter Username: ";
          cin>>current_user_name;
          current_user_name=utils().pad_username(current_user_name);


          while(!user_file_process().check_user_names(all_users,current_user_name) && current_user_name!=constants::EXIT_MENU_OPTION)
          {
              cout<<"Invalid Login"<<endl;
              cout<<"Enter valid username or -1 to exit:";
              cin>>current_user_name;
              if(current_user_name!=constants::EXIT_MENU_OPTION)
              {
                current_user_name=utils().pad_username(current_user_name);
              }
              else
              {
                cout<<"EXIT"<<endl;
              }


          }

          if (user_file_process().check_user_names(all_users,current_user_name))
          {

            string user_menu_input;
            int num_user_menu_input;
            string user_menu_option="";
            cout<<"Logged IN"<<endl;

            while(user_menu_option!= constants::LOGOUT)
            {



              current_user_type=user_file_process().get_user_type(all_users,current_user_name);
              menus().display_user_menus(current_user_type);

              cout<<"Enter an option:" ;
              cin>>user_menu_input;

              try {
                    num_user_menu_input =stoi(user_menu_input);
                    if(num_user_menu_input>0 && num_user_menu_input<=menus().get_num_menu_options(current_user_type))
                    {

                      user_menu_option=menus().get_user_menu_option(current_user_type,num_user_menu_input-1);

                      // LOGIC FOR ALL MENU FUNCTIONS GO HERE
                      if (user_menu_option==constants::SELL)
                      {

                          string new_game_to_sell;
                          new_game_to_sell=transactions().process_sell(all_games,games_to_add,current_user_name);

                        if(new_game_to_sell!="-1")
                        {

                          games_to_add=update_games_to_add_vector(games_to_add,new_game_to_sell);
                          // ALSO NEED TO UPDATE AVAIABLE GAMES LIST

                        }


                  } // end of sell menu


                    }
                    else
                    {
                      cout<<"Invalid entry"<<endl;
                      user_menu_option="";
                    }
                } catch (const std::invalid_argument&) {
                    cerr << "Invalid argument. Please enter a valid integer." << endl;
                    user_menu_option="";
                } catch (const std::out_of_range&) {
                    cerr << "Out of range. Please enter a smaller integer." << endl;
                    user_menu_option="";
                }
              }

              // ADD LOGOUT PROCESSING STUFF HERE
              if (user_menu_option== constants::LOGOUT)
              {
                cout<<"LOGGED OUT"<<endl;
                all_games=update_games_list(all_games,games_to_add);


              }
            } // user menus

          } // login menu







        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } // home menu

    // SYSTEM EXITS PROCESSES
    cout<<"EXITS"<<endl;

  return 0;
  }
vector<string> update_games_to_add_vector(vector<string>& games_to_add_vec, string& new_game_to_sell)
 {

    games_to_add_vec.push_back(new_game_to_sell);



      return games_to_add_vec;
  }

  vector<string> update_games_list(vector<string>& current_games,vector<string>& new_games)
  {
    for(int i=0; i<new_games.size();i++)
    {

      current_games.push_back(new_games[i]);
    }
    return current_games;
  }
