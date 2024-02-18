#ifndef USER_FILE_PROCESS
#define USER_FILE_PROCESS


#include <iostream>
#include <string>
#include <vector>

using namespace std;
class user_file_process {




public:
    /**
    * @brief Default constructor for the user_file_process class.
    */
    user_file_process();

    /**
     * @brief Grab all the current users of the application
     *
     * @param user_file File to grab the users from
     * @return list of current users.
     */
    vector<string> get_all_users_info(string user_file);

    /**
     * @brief Validate if username already exists.
     *
     * @param user_info Vector containing all users.
     * @param user_name Username to check if it exists in application or not.
     * @return A boolean indicating if a user exists or not.
     */
    bool check_user_names(vector<string>& user_info,string& user_name);

    /**
     * @brief Grab the user type for a user.
     *
     * @param user_info Vector containing all users.
     * @param user_name The name of the current user.
     * @return The user type
     */
    string get_user_type(vector<string>& user_info,string& user_name);

    /**
     * @brief Grab the the total balance/credit of a user
     *
     * @param user_info Vector containing all users.
     * @param user_name The name of the current user.
     * @return The current user's balance.
     */
    float get_user_balance(vector<string>& user_info,string& user_name);

    /**
     * @brief Update the user's balance/credit amount
     *
     * @param user_info Vector containing all users.
     * @param user_name The name of the current user.
     * @param credit_amount The credit amount for the current user.
     */
    void update_user_balance(vector<string>& user_info,string& user_name, float& credit_amount);

};

#endif
