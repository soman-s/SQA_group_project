#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>

#include "user_file_process.h"
#include "constants.h"
#include "utils.h"

using namespace std;


/**
 * @brief Default constructor for the user_file_process class.
 */
user_file_process::user_file_process()
{

}

// Grab all the current users of the application
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

// Validate if username already exists 
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

// Grab the user type for a user
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

// Grab the the total balance/credit of a user
float user_file_process::get_user_balance(vector<string>& user_info,string& user_name)
{
  string current_user_info;
  string test_user= utils().convert_to_lower(user_name);
  test_user=utils().pad_username(test_user);
  for (int i=0; i<user_info.size();i++)
  {

    current_user_info=utils().convert_to_lower(user_info[i].substr(0,constants::MAX_USER_NAME_LENGTH));
      if (current_user_info==test_user)
    {

      float num_credit_amount;
      string credit_amount = user_info[i].substr(constants::MAX_USER_NAME_LENGTH + constants::MAX_ACCOUNT_TYPE_LENGTH + 2);
      credit_amount=credit_amount.substr(0,credit_amount.length()-1);
      num_credit_amount=stof(credit_amount);
      return num_credit_amount;



    }

  }

  return 0;
}

// Update the user's balance/credit amount. 
void user_file_process::update_user_balance(vector<string>& user_info,string& user_name, float&credit_amount)
{
  string current_user_info;
  string test_user= utils().convert_to_lower(user_name);
  test_user=utils().pad_username(test_user);
  for (int i=0; i<user_info.size();i++)
  {
    current_user_info=utils().convert_to_lower(user_info[i].substr(0,constants::MAX_USER_NAME_LENGTH));
      if (current_user_info==test_user)
    {
      int starting_pos=constants::MAX_USER_NAME_LENGTH + constants::MAX_ACCOUNT_TYPE_LENGTH + 2;
      int len= (user_info[i].length()+1)- starting_pos;
      string new_credit_amount;
      string replacement_credit;
      new_credit_amount=utils().pad_credit_amount(credit_amount);
      replacement_credit=new_credit_amount+"\r";

      user_info[i].replace(starting_pos,len,replacement_credit);

    }

  }


}
