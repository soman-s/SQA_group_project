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
    current_game_info=utility.convert_to_lower(game_info[i].substr(0,constants::MAX_GAME_NAME_LENGTH));

    if (current_game_info==test_game_name)
    {
      return true;
    }

  }
  return false;
}
