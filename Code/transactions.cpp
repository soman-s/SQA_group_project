#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <unordered_map>

#include "menus.h"
#include "user_file_process.h"
#include "games_file_process.h"
#include "constants.h"
#include "utils.h"
#include "transactions.h"


using namespace std;



transactions::transactions()
{

}

string transactions::process_sell(vector<string>& all_games,vector<string>& games_to_add, string current_user_name)
{

    string new_game_name;
    cout<<"Sell"<<endl;
    cout<<"Enter game name:";


    cin.ignore();
    getline(cin, new_game_name);
    new_game_name=utils().pad_game_name(new_game_name);

    // checks if game name is valid and game name doesnt exists
    while ((games_file_process().check_valid_game_name(new_game_name) == false ||
              games_file_process().check_game_already_exists(all_games, new_game_name) ||
              games_file_process().check_game_already_exists(games_to_add, new_game_name)) &&
             new_game_name != constants::EXIT_MENU_OPTION)
    {
        new_game_name = "";
        cout << "Invalid Game Name or Game already Exists" << endl;


        cout << "Enter game name or -1 to exit:";
        getline(cin, new_game_name);
        if (new_game_name != constants::EXIT_MENU_OPTION)
        {
            new_game_name = utils().pad_game_name(new_game_name);
        }

  }



  // getting price
  bool val_price=false;
  string text_new_game_price;
  float  num_new_game_price=0.0;

  while(val_price==false && text_new_game_price!=constants::EXIT_MENU_OPTION && new_game_name != constants::EXIT_MENU_OPTION)
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
          cout<<"Enter Game price or -1 to exit:";
          cin>>text_new_game_price;
        }

    } catch (const std::invalid_argument& e) {
        cerr << "Invalid argument: " << e.what() << endl;
        cout<<"Enter Game price or -1 to exit:";
        cin>>text_new_game_price;

    } catch (const std::out_of_range& e) {
        cerr << "Out of range: " << e.what() << endl;
    }
  }

  text_new_game_price=utils().pad_game_price(num_new_game_price);
  if (text_new_game_price!=constants::EXIT_MENU_OPTION&&new_game_name != constants::EXIT_MENU_OPTION)
  {
    return new_game_name+" "+current_user_name+" "+ text_new_game_price;
  }


    return "-1";
}


string transactions::process_create(vector<string>& all_users){

  unordered_map <string, string> user_type_codes = {{"1","AA"},{"2","FS"},{"3","BS"},{"4","SS"}};

  string new_account;
  cout << "Create" << endl;

  cout << "Select type of account you want to create" << endl;

  menus().display_all_user_types();

  cout << "Enter account type: ";
  cin >> new_account;

  bool valid_account = false;

  int num = stoi(new_account);

  while(!valid_account){

    try {
      if(stoi(new_account) >= 1 && stoi(new_account) <= 4 ){
        break;

      }

      cout << "Please provide valid account type: ";
      cin >> new_account;
    }

    catch (const std::invalid_argument& e) {
      cerr << "Invalid argument: " << e.what() << endl;
      cout << "Please provide valid account type: ";
      cin >> new_account;
    }

  }


  string username;
  cout << "Enter Username: ";
  cin >> username;

  cout << username << endl;

  while(user_file_process().check_user_names(all_users,username) || username.size() > constants::MAX_USER_NAME_LENGTH){

    if(user_file_process().check_user_names(all_users,username)){
      cout << "Username already exists please try again or -1 to exit" << endl;
      cout << "Enter valid Username: ";
    }

    else{
      cout << "Username length is too long please try again or -1 to exit" << endl;
      cout << "Enter valid Username: ";
    }

    cin >> username;

    if (username == constants::EXIT_MENU_OPTION){
      return constants::EXIT_MENU_OPTION;
    }

  }

  username=utils().pad_username(username);


  float credit_amount=0.0;
  string text_credit_amount;
  bool valid_credit_amount = false;

  cout << "Enter new credit amount: ";
  cin >> text_credit_amount;


  while(!valid_credit_amount){

    try{

      credit_amount = stof(text_credit_amount);
      if(constants::MIN_CREDIT_AMOUNT <= credit_amount <= constants::MAX_CREDIT_AMOUNT){
        cout << "Succesfully created new user " << username << " with credit amount $" << credit_amount  << endl;
        text_credit_amount = utils().pad_credit_amount(credit_amount);
        return username + "_" + user_type_codes[new_account] + "_" + text_credit_amount;
      }

      cout << "Please enter a valid credit amount or -1 to go back to main menu: ";
      cin >> text_credit_amount;
      credit_amount = stof(text_credit_amount);
    }

    catch (const std::invalid_argument& e) {
      cerr << "Invalid argument: " << e.what() << endl;
      cout<<"Please enter a valid credit amount -1 to go back to main menu: ";
      cin>>text_credit_amount;

    }

  }


  return "-1";


}

string transactions:: process_delete(vector<string>& all_users, string current_user){

  string user_to_remove;

  cout << "Delete" << endl;

  cout << "Enter username: ";

  cin >> user_to_remove;

  while(user_file_process().check_user_names(all_users,user_to_remove) && user_to_remove!=current_user){

    if(user_to_remove == current_user){
      cout << "user cannot remove itself please try again or -1 to exit: ";
    }

    else{
      cout << "Username already exists please try again or -1 to exit: ";
    }

    cin >> user_to_remove;

    if (user_to_remove == constants::EXIT_MENU_OPTION){
      return constants::EXIT_MENU_OPTION;
    }

  }

  return user_to_remove;

}

void transactions::show_all_users(vector<string>& all_users)
{
  cout<<"All Users"<<endl;
  cout << setw(14) << left << "User"
         << setw(5) << left << "Type" << "Balance"
         << endl;
  for(const auto& user: all_users ){

    cout<<user<< endl;

  }
}

void transactions::show_all_game_info(vector<string>& all_games)
{
  cout<<"All Games Available"<<endl;
  cout << setw(26) << left << "Game Name"
         << setw(16) << left << "Seller" << "Price"
         << endl;
  for(const auto& game: all_games ){

    cout<<game<< endl;

  }
}
