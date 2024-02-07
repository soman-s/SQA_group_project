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
  vector<string> admin_options = {"Create", "Delete", "Sell","Buy","Refund","List Available Games","List All Users","Logout"};
public:
    menus();
    void display_home_menu();
    void display_user_menus(string user_type);
    int get_num_home_options();
    string get_home_option(int index);


};

#endif
