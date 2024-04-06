#!/bin/bash
#!/bin/sh


# Always coping back the original files for testing

echo "Copying back the Original Log Files"
dos2unix copy_ori.sh
sleep 0.25
./copy_ori.sh
sleep 0.25



# Compling the front end
echo "Compling Front End"
cd front_end
g++ -o front_end.exe main.cpp menus.cpp user_file_process.cpp constants.cpp games_file_process.cpp utils.cpp transactions.cpp
cd ..
sleep 0.75


cd daily_sessions

# Loop through each folder in the current directory
for folder in *; do
    # Check if the item is a directory
    if [ -d "$folder" ]; then
        # Add the folder name to the array
        daily_sessions+=("$folder")
        sleep 0.25
    fi
done

# back in the root directory
cd ..

# Clearing Summary files before each run
summary_output_file="tests/test_summary/output_diff_summary.txt"
summary_transaction_file="tests/test_summary/merged_transactions_diff_summary.txt"
> "$summary_output_file"
> "$summary_transaction_file"

for session_folder in "${daily_sessions[@]}"; do
  dos2unix run_daily.sh  >/dev/null 2>&1
  ./run_daily.sh $session_folder

  sleep 0.75

  source_folder="back_end/mod_log_files"
  destination_folder="weekly_runs_output_files/$session_folder"
  cp -rf "$source_folder"/* "$destination_folder"/
  sleep 0.75

  source_folder=back_end/ori_log_files/merged_daily_transactions.etf
  destination_folder=weekly_runs_output_files/$session_folder

  cp -f "$source_folder" "$destination_folder" >/dev/null 2>&1
  sleep 0.75

done

echo "Done Processing Weekly Session"
