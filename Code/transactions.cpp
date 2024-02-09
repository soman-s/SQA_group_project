#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>

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
