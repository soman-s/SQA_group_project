#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>

#include "user_file_process.h"
#include "constants.h"
#include "utils.h"

using namespace std;



user_file_process::user_file_process()
{

}

vector<string> user_file_process::get_all_users_info(string user_file)
{
    ifstream input_stream;
    vector<string> all_user_info;
    string line;



    input_stream.open(user_file);
    if(!input_stream.is_open())
    {
       cerr<<"ERROR OPEN FILE"<<endl;

    }

  while(getline(input_stream, line))
   {
     all_user_info.push_back(line);

   }
    input_stream.close();

    all_user_info.pop_back();
    return all_user_info;
}

bool user_file_process::check_user_names(vector<string>& user_info,string& user_name)
{

  utils utility;
  string current_user_info;
  string test_user_name=utility.convert_to_lower(user_name);

  for (int i = 0; i < user_info.size(); ++i)
  {
    current_user_info=utility.convert_to_lower(user_info[i].substr(0,constants::MAX_USER_NAME_LENGTH));

    if (current_user_info==test_user_name)
    {
      return true;
    }

  }


  return false;
}

string user_file_process::get_user_type(vector<string>& user_info,string& user_name)
{
  utils utility;
  string current_user_name;
  string test_user_name=utility.convert_to_lower(user_name);
  for (int i = 0; i < user_info.size(); ++i)
  {
    current_user_name=utility.convert_to_lower(user_info[i].substr(0,constants::MAX_USER_NAME_LENGTH));

    if (current_user_name==test_user_name)
    {
      string user_type;
      user_type=user_info[i].substr(constants::MAX_USER_NAME_LENGTH+1,2);
      return user_type;


    }


  }

  return "";
}
