#ifndef FILE_PROCESS
#define FILE_PROCESS


#include <iostream>
#include <string>
#include <vector>

using namespace std;
class file_process {




public:
  file_process();
  vector<string> get_all_users_info(string user_file);
  bool check_user_names(vector<string>& user_info,string& user_name);
  string convert_to_lower(const std::string& str);





};

#endif
