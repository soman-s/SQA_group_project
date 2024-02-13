#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>

#include "utils.h"
#include "games_file_process.h"
#include "constants.h"


using namespace std;


utils utility;

games_file_process::games_file_process()
{

}

bool games_file_process::check_valid_game_name(string& game_name)
{


  if(utility.check_alpha_numeric_space(game_name) && game_name.length()<=25)
  {
    return true;
  }

  return false;
}


vector<string> games_file_process::get_all_game_info(string game_file)
{
  ifstream input_stream;
  vector<string> all_game_info;
  string line;

  input_stream.open(game_file);
  if(!input_stream.is_open())
  {
     cerr<<"ERROR OPEN FILE"<<endl;

  }

while(getline(input_stream, line))
 {
   all_game_info.push_back(line);

 }
  input_stream.close();

  all_game_info.pop_back();
  return all_game_info;
}

bool games_file_process::check_game_already_exists(vector<string>& game_info,string& game_name)
{

  utils utility;
  string current_game_info;
  string test_game_name=utility.convert_to_lower(game_name);

  for (int i = 0; i < game_info.size(); ++i)
  {

    current_game_info=game_info[i].substr(0,constants::MAX_GAME_NAME_LENGTH);
    current_game_info=utility.convert_to_lower(current_game_info);

    if (current_game_info==test_game_name)
    {
      return true;
    }

  }
  return false;
}

bool games_file_process:: check_user_owns_game(vector<string>& games_collection,string& game_name,string& buyer_name)
{

  utils utility;
  string current_entry;
  string test_entry;
  string test_game_name=utility.convert_to_lower(game_name);
  string test_user_name=utility.convert_to_lower(buyer_name);
  test_user_name=utility.pad_username(test_user_name);

  test_entry= test_game_name+" "+test_user_name;
  test_entry=utility.convert_to_lower(test_entry);

  //cout<<test_entry.length()<<endl;
  for (int i = 0; i <games_collection.size() ; ++i)
  {

    current_entry=utility.convert_to_lower(games_collection[i]);
    current_entry = current_entry.substr(0, current_entry.length() - 1);
    //cout<<current_entry.length()<<endl;

    if(current_entry==test_entry)
    {
      //cout<<"BUYER OWNS IT"<<endl;
      return true;
    }
  }
  return false;
}


bool games_file_process:: check_user_sells_game(vector<string>& all_games,string& game_name,string& seller_name)
{

  utils utility;
  string current_entry;
  string test_entry;
  string test_game_name=utility.convert_to_lower(game_name);
  string test_user_name=utility.convert_to_lower(seller_name);
  test_user_name=utility.pad_username(test_user_name);

  test_entry= test_game_name+" "+test_user_name;
  test_entry=utility.convert_to_lower(test_entry);


  for (int i = 0; i <all_games.size() ; ++i)
  {

    current_entry=utility.convert_to_lower(all_games[i]);
    current_entry = current_entry.substr(0, (constants::MAX_GAME_NAME_LENGTH+constants::MAX_USER_NAME_LENGTH+1));



    if(current_entry==test_entry)
    {
      return true;
    }
  }
  return false;
}



bool games_file_process::is_game_price(vector<string>& all_games,string& game_name,float& game_price)
{

  string test_text_game_price;
  string current_game_name;
  string test_game_name=utils().convert_to_lower(game_name);

  test_text_game_price=utils().pad_game_price(game_price);
  // cout<<test_text_game_price<<endl;
  // cout<<test_text_game_price.length()<<endl;

  for(int i=0; i<all_games.size();i++)
  {
    current_game_name=all_games[i].substr(0,constants::MAX_GAME_NAME_LENGTH);
    current_game_name=utility.convert_to_lower(current_game_name);
    if(current_game_name==game_name)
    {
      string current_game_price = all_games[i].substr((constants::MAX_GAME_NAME_LENGTH + constants::MAX_USER_NAME_LENGTH + 2), all_games[i].length());
      current_game_price=current_game_price.substr(0,current_game_price.length()-1);

      if(current_game_price==test_text_game_price)
      {
        //cout<<"SAME GAME PRICE ENTERED"<<endl;
        return true;
      }
      // cout<<current_game_price<<endl;
      // cout<<current_game_price.length()<<endl;

    }
  }


  return false;
}

void games_file_process::remove_game_from_user_collection(vector<string>& games_collection,string& game_name,string& user_name)
{
  utils utility;
  string current_entry;
  string test_entry;
  string test_game_name=utility.convert_to_lower(game_name);
  string test_user_name=utility.convert_to_lower(user_name);
  test_user_name=utility.pad_username(test_user_name);

  test_entry= test_game_name+" "+test_user_name;
  test_entry=utility.convert_to_lower(test_entry);

  //cout<<test_entry.length()<<endl;
  for (int i = 0; i <games_collection.size() ; ++i)
  {

    current_entry=utility.convert_to_lower(games_collection[i]);
    current_entry = current_entry.substr(0, current_entry.length() - 1);
    //cout<<current_entry.length()<<endl;

    if(current_entry==test_entry)
    {
      games_collection.erase(games_collection.begin() + i);

    }
  }

}


float games_file_process::get_game_price(vector<string>& all_games, string& game_name)
{
  string current_game_name;
  string current_game_price;

  for (int i = 0; i < all_games.size(); i++)
  {
    current_game_name = all_games[i].substr(0, constants :: MAX_GAME_NAME_LENGTH);
    current_game_name  = utility.convert_to_lower(current_game_name);

    if (current_game_name == game_name)
    {
      current_game_price = all_games[i].substr((constants::MAX_GAME_NAME_LENGTH + constants::MAX_USER_NAME_LENGTH + 2), all_games[i].length());
      current_game_price = current_game_price.substr(0, current_game_price.length() - 1);
      break;
    }
  }
  
  return stof(current_game_price);
}
