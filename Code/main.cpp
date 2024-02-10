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


// custom FUNCTIONS
vector<string> update_games_to_add_vector(vector<string>& games_to_add_vec,string& new_game_to_sell);
vector<string> update_games_list(vector<string>& current_games,vector<string>& new_games);
vector<string> update_games_collection(vector<string>& games_collect, string& game_name,string& owner);
void remove_user(string user, vector<string>& all_users);

using namespace std;


const int MAX_USER_LENGTH=15;
const int USER_TYPE_CODE=2;
const int TOTAL_USER_CODE=28;


int main()
{
    vector<string> all_users;
    vector<string> all_games;
    vector<string> all_games_collection;
    vector<string> games_to_add;
    string current_user_type;

    string menu_option="";




    all_users=user_file_process().get_all_users_info(constants::ALL_USER_FILE);
    all_games=games_file_process().get_all_game_info(constants::AVAILABLE_GAMES);
    all_games_collection=games_file_process().get_all_game_info(constants::GAMES_COLLECTION);

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
                          string game_name=new_game_to_sell.substr(0,constants::MAX_GAME_NAME_LENGTH);

                          games_to_add=update_games_to_add_vector(games_to_add,new_game_to_sell);
                          all_games_collection=update_games_collection(all_games_collection,game_name,current_user_name);
                          // ADD THE LOGIC FOR THE DAILY TRANSACTION LOG VECTOR STUFF

                        }



                      } // end of sell menu

                      // create menu

                      else if(user_menu_option == constants::CREATE){

                        string new_user;
                        new_user = transactions().process_create(all_users);

                        if(new_user!= constants::EXIT_MENU_OPTION){
                          all_users.push_back(new_user);

                        }
                      }

                      else if(user_menu_option == constants::DELETE){

                        string user_to_remove;
                        user_to_remove = transactions().process_delete(all_users,current_user_name);

                        if(user_to_remove!= constants::EXIT_MENU_OPTION){
                          remove_user(user_to_remove, all_users);
                        }
                      }

                      else if(user_menu_option == constants::LIST_ALL_USERS)
                      {
                        transactions().show_all_users(all_users);
                      }
                      else if(user_menu_option == constants::LIST_AVAILABLE_GAMES)
                      {
                        transactions().show_all_game_info(all_games);
                      }
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

void remove_user(string user_to_remove,  vector<string>& all_users) {
  for(int i=0;i<all_users.size(); i++){

    string trimmed_user=utils().convert_to_lower(all_users[i].substr(0,user_to_remove.size()));
    if(trimmed_user==user_to_remove){
      cout << "user removed" << endl;
      all_users.erase(all_users.begin() + i);
    }
  }
  for(const auto& user: all_users ){

    cout << "user" <<  user << endl;

  }
}

// still need to add function for removing games that belong to a particlar user



// update games_collection vector
vector<string> update_games_collection(vector<string>& games_collect, string& game_name,string& owner )
{
  string new_entry;
  new_entry= game_name+" "+owner;
  games_collect.push_back(new_entry);

  return games_collect;
}
