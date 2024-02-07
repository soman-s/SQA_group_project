#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class menus {
  string admin = "AA";
  string full_standard = "FS";
  string sell_standard = "SS";
  string buy_standard= "BS";
  string unknown = "-1";


  vector<string> home_options = {"Login", "Exit"};
  vector<string> admin_options = {"Create", "Delete", "Sell","Buy","Refund","Add Credit","View All Users","View Available Games","Logout"};
  vector<string> full_options = {"Sell","Buy","Add Credit","View Available Games","Logout"};
  vector<string> buy_options = {"Buy","Add Credit","View Available Games","Logout"};
  vector<string> sell_options = {"Sell","Add Credit","View Available Games","Logout"};
public:

    menus();
    void display_home_menu();
    void display_user_menus(string user_type);
    int get_num_home_options();
    string get_home_option(int index);
    int get_num_menu_options(string user_type);
    string get_user_menu_option(string user_type ,int index);


};

#endif
