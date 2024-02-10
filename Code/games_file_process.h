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
  






};

#endif
