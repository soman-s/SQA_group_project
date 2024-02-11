#ifndef USER_FILE_PROCESS
#define USER_FILE_PROCESS


#include <iostream>
#include <string>
#include <vector>

using namespace std;
class user_file_process {




public:
  user_file_process();
  vector<string> get_all_users_info(string user_file);
  bool check_user_names(vector<string>& user_info,string& user_name);
  string get_user_type(vector<string>& user_info,string& user_name);
  float get_user_balance(vector<string>& user_info,string& user_name);
  void update_user_balance(vector<string>& user_info,string& user_name, float& credit_amount);







};

#endif
