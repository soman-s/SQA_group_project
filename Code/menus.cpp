#include <iostream>
#include <string>
#include "menus.h"
#include "constants.h"


using namespace std;



menus::menus()
{

}


void menus:: display_home_menu()
{
  vector<string> options;
  cout<<"HOME MENU"<<endl;
  options= home_options;

  for (int i = 0; i < options.size(); ++i) {
        cout << i + 1 << ")" << options[i] << endl;
    }
}
void menus:: display_user_menus(string user_type)
{
  vector<string> options;


  if (user_type==constants::ADMIN)
  {
    options= admin_options;
    cout<<"Admin Menu"<<endl;
  }

  else if (user_type==constants::FULL_STANDARD)
  {
    options= full_options;
    cout<<"Full Standard Menu"<<endl;
  }

  else if (user_type==constants::SELL_STANDARD)
  {
    options= sell_options;
    cout<<"Sell Standard Menu"<<endl;
  }

  else
  {
    options= buy_options;
    cout<<"Buy Standard Menu"<<endl;
  }



  for (int i = 0; i < options.size(); ++i) {
        cout << i + 1 << ")" << options[i] << endl;
    }

}

int menus:: get_num_menu_options(string user_type)
{
  if (user_type==constants::ADMIN)
  {

    return admin_options.size();

  }

  else if (user_type==constants::FULL_STANDARD)
  {
    return full_options.size();

  }

  else if (user_type==constants::SELL_STANDARD)
  {
    return sell_options.size();

  }

  else
  {
    return buy_options.size();

  }

  return 0;

}

string menus:: get_home_option(int index)
{
  return home_options[index];
}

int menus:: get_num_home_options()
{
  return home_options.size();
}

string menus:: get_user_menu_option(string user_type ,int index)
{
  if (user_type==constants::ADMIN)
  {

    return admin_options[index];

  }

  else if (user_type==constants::FULL_STANDARD)
  {
    return full_options[index];

  }

  else if (user_type==constants::SELL_STANDARD)
  {
    return sell_options[index];

  }

  else
  {
    return buy_options[index];

  }

  return " option not found";

}
