#include <iostream>
#include <string>
#include <fstream>
#include "games_file_process.h"
#include "utils.h"
#include "constants.h"
#include <algorithm>
#include <cstring>


using namespace std;



utils::utils()
{

}






string utils::convert_to_lower(const std::string& str)
 {
    string result;
    for (char c : str) {
        result += tolower(c);
    }
    return result;
}

string utils:: pad_username(const string& input)
 {
    string pad_input = input;
    if (pad_input.length() < constants::MAX_USER_NAME_LENGTH) {
        pad_input +=string(constants::MAX_USER_NAME_LENGTH - pad_input.length(), ' ');
    }
    return pad_input;
}


string utils:: pad_game_name(const string& input)
 {
    string pad_input = input;
    if (pad_input.length() < constants::MAX_GAME_NAME_LENGTH) {
        pad_input +=string(constants::MAX_GAME_NAME_LENGTH - pad_input.length(), ' ');
    }
    return pad_input;
}

bool utils::check_alpha_numeric_space(const string& input)
{
  for (char c : input) {
        if (!isalnum(c) && !isspace(c)) {
            return false;
        }
    }
    return true;

}

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

string utils:: pad_credit_amount(const long& input)
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
