#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>

// custom classes
#include "menus.h"
#include "file_process.h"
#include "constants.h"

using namespace std;


const int MAX_USER_LENGTH=15;
const int USER_TYPE_CODE=2;
const int TOTAL_USER_CODE=28;


// custom functions
string pad_username(const string& input);



int main()
{
    string user_input;
    string menu_option="";
    int num_entry;
    int home_input;
    menus new_menu;
    file_process file_processor;
    vector<string> all_users;


  while(menu_option!=constants::EXIT)
    {
      new_menu.display_home_menu();
      cout<<"Enter an option:" ;
      cin>>user_input;

      try {
            num_entry =stoi(user_input);
            if(num_entry>0 && num_entry<=new_menu.get_num_home_options())
            {
              //valid_entry = true;
              menu_option=new_menu.get_home_option(num_entry-1);


            }
            else
            {
              cout<<"Invalid entry"<<endl;
            }
        } catch (const std::invalid_argument&) {
            cerr << "Invalid argument. Please enter a valid integer." << endl;
        } catch (const std::out_of_range&) {
            cerr << "Out of range. Please enter a smaller integer." << endl;
        }


        // LOGIN CODE
        if (menu_option== constants::LOGIN)
        {
          string user_name;
          cout<<"Login"<<endl;
          cout<<"Enter Username: ";
          cin>>user_name;
          user_name=pad_username(user_name);


          all_users=file_processor.get_all_users_info(constants::ALL_USER_FILE);

          while(!file_processor.check_user_names(all_users,user_name) && user_name!=constants::EXIT_OPTION)
          {
              cout<<"Invalid Login"<<endl;
              cout<<"Enter valid username or -1 to exit:";
              cin>>user_name;
              if(user_name!=constants::EXIT_OPTION)
              {
                user_name=pad_username(user_name);
              }
              else
              {
                cout<<"EXIT"<<endl;
              }


          }

          if (file_processor.check_user_names(all_users,user_name))
          {
            cout<<"LOGGED IN"<<endl;
          }








        }



      //Clear the input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout<<"EXITS"<<endl;






    //new_menu.display_user_menus("AA");

    return 0;
  }

string pad_username(const string& input)
 {
    string pad_input = input;
    if (pad_input.length() < constants::MAX_USER_LENGTH) {
        pad_input +=string(constants::MAX_USER_LENGTH - pad_input.length(), ' '); // Append spaces
    }
    return pad_input;
}
