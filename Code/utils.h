#ifndef UTILS
#define UTILS


#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>


using namespace std;
class utils {




public:
  utils();
  string convert_to_lower(const string& str);
  string pad_username(const string& input);
  bool check_alpha_numeric_space(const string& input);
  string pad_game_name(const string& input);
  string pad_game_price(const float& input);
  string pad_credit_amount(const long& input);
};

#endif
