#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <unordered_map>

#include "menus.h"
#include "user_file_process.h"
#include "games_file_process.h"
#include "constants.h"
#include "utils.h"
#include "transactions.h"


using namespace std;



transactions::transactions()
{

}

// logic for sell transaction
string transactions::process_sell(vector<string>& all_games,vector<string>& games_to_add, string current_user_name,vector<string>& transaction_log)
{

    string new_game_name;
    cout<<"Sell"<<endl;
    cout<<"Enter game name:";



    cin.ignore();
    getline(cin, new_game_name);
    new_game_name=utils().pad_game_name(new_game_name);
    cout<<endl;

    // checks if game name is valid and game name doesnt exists
    while ((games_file_process().check_valid_game_name(new_game_name) == false ||
              games_file_process().check_game_already_exists(all_games, new_game_name) ||
              games_file_process().check_game_already_exists(games_to_add, new_game_name)) &&
             new_game_name != constants::EXIT_MENU_OPTION)
    {
        new_game_name = "";
        cout << "Invalid Game Name or Game already Exists" << endl;
        cout << "Enter game name or -1 to exit: ";
        getline(cin, new_game_name);
        if (new_game_name != constants::EXIT_MENU_OPTION)
        {
            new_game_name = utils().pad_game_name(new_game_name);
        }

  }



  // getting price
  bool val_price=false;
  string text_new_game_price="";
  float  num_new_game_price=0.0;

  while(val_price==false && text_new_game_price!=constants::EXIT_MENU_OPTION && new_game_name != constants::EXIT_MENU_OPTION)
  {
    if (text_new_game_price==constants::ERROR_CODE)
    {
      cout<<"Invlaid Game Price"<<endl;
      text_new_game_price="";
    }

    cout<<"Enter Game price: ";
    cin>>text_new_game_price;
    cout<<endl;


    try {
        num_new_game_price =stof(text_new_game_price);

        if((num_new_game_price>0) && (num_new_game_price<=constants::MAX_GAME_PRICE))
        {
          val_price=true;
        }
        else
        {
          cout<<"Invlaid Game Price"<<endl;
          cout<<"Enter Game price or -1 to exit: "<<endl;

        }

    } catch (const std::invalid_argument& e) {

        text_new_game_price=constants::ERROR_CODE;

    } catch (const std::out_of_range& e) {
        text_new_game_price=constants::ERROR_CODE;
    }
  }



  if (text_new_game_price!=constants::EXIT_MENU_OPTION&&new_game_name != constants::EXIT_MENU_OPTION)
  {
    text_new_game_price=utils().pad_game_price(num_new_game_price);

    string log_entry;

    string new_game_to_sell=new_game_name+" "+current_user_name+" "+ text_new_game_price;

    log_entry= constants::SELL_GAME_CODE+" "+new_game_to_sell;
    utils().update_transction_log(log_entry,transaction_log);

    return new_game_to_sell;
  }


    return constants::FAIL_OPTION;
}

// logic for create transaction
string transactions::process_create(vector<string>& all_users, vector<string>& transaction_log){

  unordered_map <string, string> user_type_codes = {{"1","AA"},{"2","FS"},{"3","BS"},{"4","SS"}};

  string new_account;
  cout << "Create" << endl;

  cout << "Select type of account you want to create" << endl;

  menus().display_all_user_types();

  cout << "Enter account type: ";
  cin >> new_account;


  bool valid_account = false;

  int num = stoi(new_account);

  while(!valid_account){

    try {
      if(stoi(new_account) >= 1 && stoi(new_account) <= 4 ){
        break;

      }

      cout << "Please provide valid account type or -1 to go back to main menu " <<  endl;
      cout << "Enter account type: ";
      cin >> new_account;

      if (new_account == constants::EXIT_MENU_OPTION){
        return constants::EXIT_MENU_OPTION;
      }
    }

    catch (const std::invalid_argument& e) {
      cerr << "Invalid argument: " << e.what() << endl;
      cout << "Please provide valid account type: ";
      cin >> new_account;
    }

  }

  cout << "Account type selected" << endl;

  string username;
  cout << "Enter Username: ";
  cin >> username;

  username = utils().pad_username(username);


  while(user_file_process().check_user_names(all_users,username) || username.size() > constants::MAX_USER_NAME_LENGTH){

    if(user_file_process().check_user_names(all_users,username)){
      cout << "Username already exists please try again or -1 to exit" << endl;
      cout << "Enter valid Username: ";
    }

    else{
      cout << "Username length is too long please try again or -1 to exit" << endl;
      cout << "Enter valid Username: ";
    }
    cin >> username;


    if (username == constants::EXIT_MENU_OPTION){
      return constants::EXIT_MENU_OPTION;
    }

    username = utils().pad_username(username);
  }

  cout << "username selected" << endl;

  double credit_amount=0.0;
  string text_credit_amount;
  bool valid_credit_amount = false;

  cout << "Enter new credit amount: ";
  cin >> text_credit_amount;

  while(!valid_credit_amount){

    try{

      credit_amount = stod(text_credit_amount);

      if( credit_amount >= constants::MIN_CREDIT_AMOUNT && credit_amount <= constants::MAX_CREDIT_AMOUNT){
        cout << "Succesfully created new user " << endl;
        text_credit_amount = utils().pad_credit_amount(credit_amount);
        string log_entry = constants::CREATE_CODE+" "+username+ " " + user_type_codes[new_account] + " " + text_credit_amount;
        utils().update_transction_log(log_entry,transaction_log);
        return constants:: SUCESS_OPTION;
      }

      cout << "Please enter a valid credit amount or -1 to go back to main menu" << endl;
      cout << "Enter credit amount: ";
      cin >> text_credit_amount;


      if (text_credit_amount == constants::EXIT_MENU_OPTION){
        return constants::EXIT_MENU_OPTION;
      }

    }

    catch (const std::invalid_argument& e) {
      cerr << "Invalid argument: " << e.what() << endl;
      cout << "Please enter a valid credit amount or -1 to go back to main menu" << endl;
      cout << "Enter credit amount: ";
      cin>>text_credit_amount;

      if (text_credit_amount == constants::EXIT_MENU_OPTION){
        return constants::EXIT_MENU_OPTION;
      }

    }

  }


  return constants:: SUCESS_OPTION;


}

// logic for delete transactions
string transactions:: process_delete(vector<string>& all_users, string current_user,vector<string>& transaction_log){

  string user_to_remove;

  cout << "Delete" << endl;

  cout << "Enter username: ";

  cin >> user_to_remove;

  user_to_remove = utils().pad_username(user_to_remove);


  while(!user_file_process().check_user_names(all_users,user_to_remove) || user_to_remove==current_user){

    if(user_to_remove == current_user){
      cout << "user cannot remove itself please try again or -1 to exit" << endl;
      cout << "Enter username: ";
    }

    else{
      cout << "Username does not exist please try again or -1 to exit " << endl;
      cout << "Enter username: ";
    }

    cin >> user_to_remove;

    if (user_to_remove == constants::EXIT_MENU_OPTION){
      return constants::EXIT_MENU_OPTION;
    }

    user_to_remove = utils().pad_username(user_to_remove);

  }

  cout << "User sucessfully removed" << endl; 

  float user_amount = user_file_process().get_user_balance(all_users, user_to_remove);

  string log_entry = constants::DELETE_CODE+" "+user_to_remove+ " " + user_file_process().get_user_type(all_users, user_to_remove) + " " + to_string(user_amount);
  utils().update_transction_log(log_entry,transaction_log);

  return constants:: SUCESS_OPTION;;

}

// logic for show all users transaction
void transactions::show_all_users(vector<string>& all_users)
{
  cout<<"All Users"<<endl;
  cout << setw(14) << left << "User"
         << setw(5) << left << "Type" << "Balance"
         << endl;
  for(const auto& user: all_users ){

    cout<<user<< endl;

  }
}

// logic for show all game info transaction
void transactions::show_all_game_info(vector<string>& all_games)
{
  cout<<"All Games Available"<<endl;
  cout << setw(26) << left << "Game Name"
         << setw(16) << left << "Seller" << "Price"
         << endl;
  for(const auto& game: all_games ){

    cout<<game<< endl;

  }
}

// logic for refund transaction
string transactions:: refund(vector<string>& all_users,vector<string>& all_games,vector<string>& game_collec,vector<string>& transaction_log)
  {

    utils utility;
    cout<<"Refund"<<endl;
    string refund_game_name;

    cout<<"Enter Game name: ";
    cin.ignore();
    getline(cin,refund_game_name);
    refund_game_name=utility.pad_game_name(refund_game_name);
    cout<<endl;

    while (games_file_process().check_game_already_exists(all_games,refund_game_name)==false)
    {
      cout<<"Invalid game name or Game name doesn't exist"<<endl;
      cout<<"Enter Game name or -1 to quit: ";
      getline(cin,refund_game_name);

      if (refund_game_name!=constants::EXIT_MENU_OPTION)
      {

        refund_game_name=utils().pad_game_name(refund_game_name);
      }
      else
      {
        return constants::FAIL_OPTION;
      }
    }

    string seller_name;
    cout<<"Enter seller name: ";
    cin>>seller_name;
    cout<<endl;
    while(games_file_process().check_user_sells_game(all_games,refund_game_name,seller_name)==false)
    {
      cout<<"Invalid Seller name or Seller doesn't Sell Game"<<endl;
      cout<<"Enter Seller name or -1 to quit: ";
      cin>>seller_name;
      cout<<endl;

      if (seller_name==constants::EXIT_MENU_OPTION)
      {
        return constants::FAIL_OPTION;
      }

    }

    string buyer_name;
    cout<<"Enter buyer name: ";
    cin>>buyer_name;
    cout<<endl;
    while((games_file_process().check_user_owns_game(game_collec,refund_game_name,buyer_name)==false) ||
        utils().convert_to_lower(buyer_name)==utils().convert_to_lower(seller_name))
    {
      cout<<"Invalid Buyer name or Buyer doesn't Own Game"<<endl;
      cout<<"Enter Buyer name or -1 to quit: ";
      cin>>buyer_name;
      cout<<endl;


      if (buyer_name==constants::EXIT_MENU_OPTION)
      {
        return constants::FAIL_OPTION;
      }

    }

    string text_refund_price;
    float  num_refund_price=0.0;
    bool val_price=false;

    while(val_price==false && text_refund_price!=constants::EXIT_MENU_OPTION)
    {

      if (text_refund_price==constants::ERROR_CODE)
      {
        cout << "Invalid argument: "<< endl;
        cout<<"Enter Refund price or -1 to exit: "<<endl;
        text_refund_price="";

      }

      cout<<"Enter Refund Amount: ";
      cin>>text_refund_price;
      cout<<endl;

      if (text_refund_price==constants::EXIT_MENU_OPTION)
      {
        return constants::FAIL_OPTION;
      }

      try {
          num_refund_price =stof(text_refund_price);

          if(num_refund_price>0 && games_file_process().is_game_price(all_games,refund_game_name,num_refund_price))
          {
            val_price=true;
          }
          else
          {
            cout<<"Invlaid Refund Price or Refund price entered is not equal to game amount"<<endl;
            cout<<"Enter Refund price or -1 to exit: "<<endl;



          }

      } catch (const std::invalid_argument& e) {


          text_refund_price=constants::ERROR_CODE;


      } catch (const std::out_of_range& e) {
          cerr << "Out of range: " << e.what() << endl;
          text_refund_price=constants::ERROR_CODE;
      }
    }

    // proccessing the refund

    float seller_credit_balance=user_file_process().get_user_balance(all_users,seller_name);
    float buyer_credit_balance=user_file_process().get_user_balance(all_users,buyer_name);


    if ((seller_credit_balance-num_refund_price)<0)
    {

      return constants::FAIL_OPTION;

    }

    else
    {

      seller_credit_balance=seller_credit_balance-num_refund_price;
      buyer_credit_balance=buyer_credit_balance+num_refund_price;

      // DON'T UPDATE ANY BALANCES
      // ONLY WRITE TO DAILY TRANSACTION FILE

      // games_file_process().remove_game_from_user_collection(game_collec,refund_game_name,buyer_name);
      // user_file_process().update_user_balance(all_users,seller_name,seller_credit_balance);
      // user_file_process().update_user_balance(all_users,buyer_name,buyer_credit_balance);

      string log_entry;
      string log_seller_name=utils().pad_username(seller_name);
      string log_buyer_name=utils().pad_username(buyer_name);
      string log_text_refund_price=utils().pad_credit_amount(num_refund_price);

      log_entry=constants::REFUND_CODE+" "+log_buyer_name+" "+log_seller_name+" "+log_text_refund_price;
      utils().update_transction_log(log_entry,transaction_log);
    }


    return constants:: SUCESS_OPTION;


  }

// logic for buy transaction
string transactions::process_buy(string buyer_name, vector<string>& all_users, vector<string>& all_games, vector<string>& game_collec, vector<string>& transaction_log)
{
    utils utility;

    cout<<"Buy"<<endl;
    string game_name;

    cout<<"Enter Game name: ";
    cin.ignore();
    getline(cin, game_name);
    game_name = utility.pad_game_name(game_name);

    // check if game exists
    while (games_file_process().check_game_already_exists(all_games, game_name) == false)
    {
      cout << "Invalid game name or Game name doesn't exist" << endl;
      cout << "Enter Game name or -1 to quit: ";
      getline(cin, game_name);

      if (game_name != constants::EXIT_MENU_OPTION)
      {
        game_name = utils().pad_game_name(game_name);
      }
      else
      {
        return constants::FAIL_OPTION;
      }
    }

    // check if buyer already owns the requested game
    while (games_file_process().check_user_owns_game(game_collec, game_name, buyer_name) == true)
    {
      cout << buyer_name << " already owns " << game_name <<endl;
      cout << "Enter another game or enter -1 to quit: ";
      getline(cin, game_name);

      if (game_name != constants :: EXIT_MENU_OPTION)
      {
        game_name = utils().pad_game_name(game_name);
      }
      else
      {
        return constants::FAIL_OPTION;
      }
    }


    string seller_name;
    cout << "Enter seller name: ";
    cin >> seller_name;
    cout << endl;

    // check if seller sells the requested game
    while(games_file_process().check_user_sells_game(all_games, game_name, seller_name) == false)
    {
      cout << "Invalid Seller name or Seller doesn't Sell Game"<<endl;
      cout << "Enter Seller name or -1 to quit: ";
      cin >> seller_name;
      cout << endl;

      if (seller_name == constants :: EXIT_MENU_OPTION)
      {
        return constants::FAIL_OPTION;
      }
    }

    // update buyer and seller balances
    float seller_credit_balance=user_file_process().get_user_balance(all_users, seller_name);
    float buyer_credit_balance=user_file_process().get_user_balance(all_users, buyer_name);

    cout<< "BALANCE BEFORE PURCHASE" << endl;
    cout<< "SELLER " << seller_credit_balance << endl;
    cout<< "BUYER " << buyer_credit_balance << endl;
    cout << endl;

    game_name = utils().convert_to_lower(game_name);
    float game_price = games_file_process().get_game_price(all_games, game_name);

    if (game_price > buyer_credit_balance)
    {
      cout << "You do not have enough credits to buy this game. You will return to the previous menu." << endl;

      return constants :: FAIL_OPTION;
    }
    else
    {
      buyer_credit_balance = buyer_credit_balance - game_price;
      seller_credit_balance = seller_credit_balance + game_price;

      user_file_process().update_user_balance(all_users, buyer_name, buyer_credit_balance);
      user_file_process().update_user_balance(all_users, seller_name, seller_credit_balance);

      // cout << "GAMES COLLECTION BEFORE BUY TRANSACTION" << endl;
      // for (int i = 0; i < game_collec.size(); i++)
      // {
      //   cout << game_collec[i] << endl;
      // }
      // cout << endl;

      games_file_process().update_games_collection(game_collec, game_name, buyer_name);

      // cout << "GAMES COLLECTION AFTER BUY TRANSACTION" << endl;
      // for (int i = 0; i < game_collec.size(); i++)
      // {
      //   cout << game_collec[i] << endl;
      // }
      // cout << endl;

      cout<< "BALANCE AFTER PURCHASE" << endl;
      cout<< "SELLER " << seller_credit_balance << endl;
      cout<< "BUYER " << buyer_credit_balance << endl;
      // cout << endl;


      // update daily transaction file
      string log_entry;
      string log_game_name = utils().pad_game_name(game_name);
      string log_seller_name = utils().pad_username(seller_name);
      string log_buyer_name = utils().pad_username(buyer_name);
      string log_text_buy_price = utils().pad_credit_amount(game_price);

      log_entry = constants::BUY_CODE + " " + log_game_name + " " + log_seller_name + " " + log_buyer_name + " " + log_text_buy_price;
      utils().update_transction_log(log_entry, transaction_log);
    }

    return constants:: SUCESS_OPTION;
}

// process for updating a credit amount for a specific user
string transactions::process_credit(string menu_option,vector<string>& all_users, string user,vector<string>& transaction_log){

  cout << "Add Credit" << endl;

  if(menu_option == "6"){

    cout << "Enter username: ";

    cin >> user;

    user = utils().pad_username(user);

    while(!user_file_process().check_user_names(all_users,user)){

      cout << "Username does not exist please try again or -1 to exit " << endl;
      cout << "Enter username: ";

      cin >> user;


      if (user == constants::EXIT_MENU_OPTION){
        return constants::EXIT_MENU_OPTION;
      }

      user = utils().pad_username(user);

    }
  }

  cout << "username selected" << endl;

  cout << "Enter credit amount to add: ";

  float credit_amount=0.0;
  string text_credit_amount;

  cin >> text_credit_amount;

  float user_balance=user_file_process().get_user_balance(all_users, user);

  bool valid_credit_amount = false;


  while(!valid_credit_amount){

    try{

      credit_amount = stof(text_credit_amount);

      if(user_balance + credit_amount > constants::MAX_CREDIT_AMOUNT){
        cout << "credit amount added wil exceed maximum limit of $999,999 please pick appropriate credit amount to add or -1 to exit " <<  endl;
        cout << "Enter credit amount to add: ";

      }

      else if(credit_amount < constants::MIN_ADD_CREDITS || credit_amount  > constants::MAX_ADD_CREDITS) {
        cout << "Please enter a valid credit amount or -1 to go back to main menu " << endl;
        cout << "Enter credit amount to add: ";
      }

      else{
        break;
      }

      cin >> text_credit_amount;


      if (text_credit_amount == constants::EXIT_MENU_OPTION){
        return constants::EXIT_MENU_OPTION;
      }
    }

    catch (const std::invalid_argument& e) {
      cerr << "Invalid argument: " << e.what() << endl;
      cout<<"Please enter a valid credit amount or -1 to go back to main menu " << endl;
      cout << "Enter credit amount to add: ";
      cin>>text_credit_amount;
      if (text_credit_amount == constants::EXIT_MENU_OPTION){
        return constants::EXIT_MENU_OPTION;
      }
    }

  }

  user_balance+=credit_amount;

  string user_balance_padded = utils().pad_credit_amount(user_balance);

  string log_entry = constants::ADD_CREDIT_CODE+" "+user+ " " + user_file_process().get_user_type(all_users, user) + " " + user_balance_padded;
  utils().update_transction_log(log_entry,transaction_log);


  return constants:: SUCESS_OPTION;
}


void transactions::process_logout(vector<string>& transaction_log)
{
  ofstream output_stream;
  output_stream.open("log_files/daily_transactions.etf");

  for (const string& transaction : transaction_log) {
       output_stream << transaction << std::endl;
   }


  output_stream.close();


  return;
}
