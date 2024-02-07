#include <iostream>
#include <string>
#include "menus.h"


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

}

int menus:: get_num_home_options()
{
  return home_options.size();
}

string menus:: get_home_option(int index)
{
  return home_options[index];
}
