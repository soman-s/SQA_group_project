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

// custom FUNCTIONS
vector<string> update_games_to_add_vector(vector<string>& games_to_add_vec, const string& user_name, const string& game_name, const string& game_price);
vector<string> update_games_list(vector<string>& current_games,vector<string>& new_games);

using namespace std;


const int MAX_USER_LENGTH=15;
const int USER_TYPE_CODE=2;
const int TOTAL_USER_CODE=28;


int main()
{


    utils utility;

    menus new_menu;
    user_file_process user_file;
    games_file_process game_file;

    vector<string> all_users;
    vector<string> all_games;
    vector<string> games_to_add;
    string current_user_type;

    string menu_option="";


    all_users=user_file.get_all_users_info(constants::ALL_USER_FILE);
    all_games=game_file.get_all_game_info(constants::AVAILABLE_GAMES);

  while(menu_option!=constants::EXIT)
    {
      string user_menu_input;
      string user_input;
      int num_entry;

      new_menu.display_home_menu();
      cout<<"Enter an option:" ;
      cin>>user_input;

      try {
            num_entry =stoi(user_input);
            if(num_entry>0 && num_entry<=new_menu.get_num_home_options())
            {
              //valid_entry = true;
              menu_option=new_menu.get_home_option(num_entry-1);


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
          current_user_name=utility.pad_username(current_user_name);


          while(!user_file.check_user_names(all_users,current_user_name) && current_user_name!=constants::EXIT_MENU_OPTION)
          {
              cout<<"Invalid Login"<<endl;
              cout<<"Enter valid username or -1 to exit:";
              cin>>current_user_name;
              if(current_user_name!=constants::EXIT_MENU_OPTION)
              {
                current_user_name=utility.pad_username(current_user_name);
              }
              else
              {
                cout<<"EXIT"<<endl;
              }


          }

          if (user_file.check_user_names(all_users,current_user_name))
          {

            string user_menu_input;
            int num_user_menu_input;
            string user_menu_option="";
            cout<<"Logged IN"<<endl;

            while(user_menu_option!= constants::LOGOUT)
            {



              current_user_type=user_file.get_user_type(all_users,current_user_name);
              new_menu.display_user_menus(current_user_type);

              cout<<"Enter an option:" ;
              cin>>user_menu_input;

              try {
                    num_user_menu_input =stoi(user_menu_input);
                    if(num_user_menu_input>0 && num_user_menu_input<=new_menu.get_num_menu_options(current_user_type))
                    {

                      user_menu_option=new_menu.get_user_menu_option(current_user_type,num_user_menu_input-1);

                      // LOGIC FOR ALL MENU FUNCTIONS GO HERE
                      if (user_menu_option==constants::SELL)
                      {




                        string new_game_name;
                        cout<<"Sell"<<endl;
                        cout<<"Enter game name:";


                        cin.ignore();
                        getline(cin, new_game_name);
                        new_game_name=utility.pad_game_name(new_game_name);




                        // checks if game name is valid and game name doesnt exists
                        while ((game_file.check_valid_game_name(new_game_name) == false ||
                                  game_file.check_game_already_exists(all_games, new_game_name) ||
                                  game_file.check_game_already_exists(games_to_add, new_game_name)) &&
                                 new_game_name != constants::EXIT_MENU_OPTION)
                      {
                            new_game_name = "";
                            cout << "Invalid Game Name or Game already Exists" << endl;


                            cout << "Enter game name or -1 to exit:";
                            getline(cin, new_game_name);
                            if (new_game_name != constants::EXIT_MENU_OPTION)
                            {
                                new_game_name = utility.pad_game_name(new_game_name);
                            }
                      }

                      // getting price
                      bool val_price=false;
                      string text_new_game_price;
                      float  num_new_game_price=0.0;

                      while(val_price==false)
                      {
                        cout<<"Enter Game price:";
                        cin>>text_new_game_price;


                        try {
                            num_new_game_price =stof(text_new_game_price);

                            if((num_new_game_price>0) && (num_new_game_price<=constants::MAX_GAME_PRICE))
                            {
                              val_price=true;
                            }
                            else
                            {
                              cout<<"Invlaid Game Price"<<endl;
                            }

                        } catch (const std::invalid_argument& e) {
                            cerr << "Invalid argument: " << e.what() << endl;

                        } catch (const std::out_of_range& e) {
                            cerr << "Out of range: " << e.what() << endl;
                        }
                    }

                    text_new_game_price=utils().pad_game_price(num_new_game_price);
                    games_to_add=update_games_to_add_vector(games_to_add,current_user_name,new_game_name,text_new_game_price);







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
vector<string> update_games_to_add_vector(vector<string>& games_to_add_vec, const string& user_name, const string& game_name, const string& game_price)
 {
    string entry_to_add;
    entry_to_add=game_name+" "+user_name+" "+ game_price;
    games_to_add_vec.push_back(entry_to_add);



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
