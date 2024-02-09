#ifndef TRANSACTIONS
#define TRANSACTIONS


#include <iostream>
#include <string>
#include <vector>

#include "menus.h"
#include "user_file_process.h"
#include "games_file_process.h"
#include "constants.h"
#include "utils.h"

using namespace std;
class transactions {




public:
  transactions();
  string process_sell(vector<string>& all_games, vector<string>& games_to_add,string current_user_name);








};

#endif
