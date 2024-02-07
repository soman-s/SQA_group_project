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
#include "user_file_process.h"
#include "constants.h"

using namespace std;


const int MAX_USER_LENGTH=15;
const int USER_TYPE_CODE=2;
const int TOTAL_USER_CODE=28;


// custom functions
string pad_username(const string& input);



int main()
{


    string menu_option="";
    menus new_menu;
    user_file_process user_file;
    vector<string> all_users;
    string current_user_type;


  while(menu_option!=constants::EXIT)
    {
      string user_menu_input;
      string user_input;
      int num_entry;

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
              menu_option="";
            }
        } catch (const std::invalid_argument&) {
            cerr << "Invalid argument. Please enter a valid integer." << endl;
            menu_option="";
        } catch (const std::out_of_range&) {
            cerr << "Out of range. Please enter a smaller integer." << endl;
            menu_option="";
        }


        // LOGIN CODE
        if (menu_option== constants::LOGIN)
        {
          string user_name;
          cout<<"Login"<<endl;
          cout<<"Enter Username: ";
          cin>>user_name;
          user_name=pad_username(user_name);


          all_users=user_file.get_all_users_info(constants::ALL_USER_FILE);

          while(!user_file.check_user_names(all_users,user_name) && user_name!=constants::EXIT_OPTION)
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

          if (user_file.check_user_names(all_users,user_name))
          {

            string user_menu_input;
            int num_user_menu_input;
            string user_menu_option="";
            cout<<"Logged IN"<<endl;

            while(user_menu_option!= constants::LOGOUT)
            {
              current_user_type=user_file.get_user_type(all_users,user_name);
              new_menu.display_user_menus(current_user_type);

              cout<<"Enter an option:" ;
              cin>>user_menu_input;

              try {
                    num_user_menu_input =stoi(user_menu_input);
                    if(num_user_menu_input>0 && num_user_menu_input<=new_menu.get_num_menu_options(current_user_type))
                    {

                      user_menu_option=new_menu.get_user_menu_option(current_user_type,num_user_menu_input-1);
                      cout<<user_menu_option<<endl;

                    }
                    else
                    {
                      cout<<"Invalid entry"<<endl;
                      user_menu_option="";
                    }
                } catch (const std::invalid_argument&) {
                    cerr << "Invalid argument. Please enter a valid integer." << endl;
                    user_menu_option="";
                } catch (const std::out_of_range&) {
                    cerr << "Out of range. Please enter a smaller integer." << endl;
                    user_menu_option="";
                }
              }
            }








        }

        cout<<"LOGGED OUT"<<endl;
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
    if (pad_input.length() < constants::MAX_USER_NAME_LENGTH) {
        pad_input +=string(constants::MAX_USER_NAME_LENGTH - pad_input.length(), ' '); // Append spaces
    }
    return pad_input;
}
