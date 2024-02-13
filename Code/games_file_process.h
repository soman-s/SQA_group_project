#ifndef GAMES_FILE_PROCESS
#define GAMES_FILE_PROCESS


#include <iostream>
#include <string>
#include <vector>

using namespace std;
class games_file_process {




public:
  games_file_process();
  vector<string> get_all_game_info(string game_file);
  bool check_valid_game_name(string& game_name);
  bool check_game_already_exists(vector<string>& game_info,string& game_name);
  bool check_user_owns_game(vector<string>& games_collection,string& game_name,string& user_name);
  bool check_user_sells_game(vector<string>& all_games,string& game_name,string& seller_name);
  bool is_game_price(vector<string>& all_games,string& game_name,float& game_price);
  void remove_game_from_user_collection(vector<string>& games_collection,string& game_name,string& user_name);
  float get_game_price(vector<string>& all_games, string& game_name);
  vector<string> update_games_collection(vector<string>& games_collect, string& game_name,string& owner);




};

#endif
