#include <iostream>
#include <string>
#include <fstream>
#include "games_file_process.h"
#include "utils.h"
#include "constants.h"
#include <algorithm>
#include <cstring>


using namespace std;

// Implementation of the utils class functions...

/**
 * @brief Default constructor for the utils class.
 */
utils::utils()
{

}





// convert characters in string to lower case
string utils::convert_to_lower(const std::string& str)
 {
    string result;
    for (char c : str) {
        result += tolower(c);
    }
    return result;
}

// pad usernames with spaces if its less than 15 characters
string utils:: pad_username(const string& input)
 {
    string pad_input = input;
    if (pad_input.length() < constants::MAX_USER_NAME_LENGTH) {
        pad_input +=string(constants::MAX_USER_NAME_LENGTH - pad_input.length(), ' ');
    }
    return pad_input;
}

// pad game name with spaces if it is less then 25 characters
string utils:: pad_game_name(const string& input)
 {
    string pad_input = input;
    if (pad_input.length() < constants::MAX_GAME_NAME_LENGTH) {
        pad_input +=string(constants::MAX_GAME_NAME_LENGTH - pad_input.length(), ' ');
    }
    return pad_input;
}

// checks to see if all characters in the string are either a number, letter or a spaces
// no special characters other than spaces are allowed
bool utils::check_alpha_numeric_space(const string& input)
{
  for (char c : input) {
        if (!isalnum(c) && !isspace(c)) {
            return false;
        }
    }
    return true;

}

// pad game prices with 0 in front if total length is less then 6 characters
string utils:: pad_game_price(const float& input)
{


    stringstream ss;
    ss << fixed << setprecision(2) << input;
    string price_str = ss.str();

    // Splitting the price into integral and decimal parts
    size_t decimal_pos = price_str.find('.');
    string integral_part = price_str.substr(0, decimal_pos);
    string decimal_part = price_str.substr(decimal_pos + 1);

    // Pad the integral part with leading zeros if it's less than 3 digits
    if (integral_part.size() < 3) {
        integral_part = string(3 - integral_part.size(), '0') + integral_part;
    }
    return integral_part+'.'+decimal_part;

}

// pad game prices with 0 in front if total length is less then 9 characters
string utils:: pad_credit_amount(const float& input)
{

    stringstream ss;
    ss << fixed << setprecision(2) << input;
    string price_str = ss.str();

    size_t decimal_pos = price_str.find('.');
    string integral_part = price_str.substr(0, decimal_pos);
    string decimal_part = price_str.substr(decimal_pos + 1);

    if(price_str.find('.') == std::string::npos){
        integral_part = string(6 - integral_part.size(), '0') + integral_part;
        return integral_part + ".00";
    }

    integral_part = string(6 - integral_part.size(), '0') + integral_part;

    return integral_part+'.'+decimal_part;
}



void utils::update_games_to_add_vector(vector<string>& games_to_add_vec, string& new_game_to_sell)
 {

    games_to_add_vec.push_back(new_game_to_sell);



      //return games_to_add_vec;
  }

void utils::update_games_list(vector<string>& current_games,vector<string>& new_games)
{
  for(int i=0; i<new_games.size();i++)
  {

    current_games.push_back(new_games[i]);
  }
  //return current_games;
}

void utils::remove_user(string user_to_remove,  vector<string>& all_users) {
  for(int i=0;i<all_users.size(); i++)
  {
    string trimmed_user=utils().convert_to_lower(all_users[i].substr(0,user_to_remove.size()));
    if(trimmed_user==utils().convert_to_lower(user_to_remove)){
      all_users.erase(all_users.begin() + i);
    }
  }
}

void utils::remove_games(string user,vector<string>& current_games)
{
  for(int i=0;i<current_games.size();i++){
    if(current_games[i].find(user) != std::string::npos){
      current_games.erase(current_games.begin() + i);
    }
  }

}


// update games_collection vector
void utils::update_games_collection(vector<string>& games_collect, string& game_name,string& owner )
{
  string new_entry;
  new_entry= game_name+" "+owner;
  games_collect.push_back(new_entry);

  //return games_collect;
}
