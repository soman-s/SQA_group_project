#!/bin/bash
#!/bin/sh


# before each run must copy back the original files
# copy back orginal files
# chmod +x copy_ori.sh(first time only)
# dos2unix copy_ori.sh
# ./copy_ori.sh

# Script to process 1 days worth of daily merged_daily_transactions
# To run DAILY SCRIPT
# chmod +x run_daily.sh (first time only)
# dos2unix run_daily.sh
# ./run_daily.sh day_1(sub with the folder you want to test)

custom_program="front_end.exe"
actual_output_file="../tests/$1/actual/outputs.bto"

day_inputs=()

echo " Getting inputs from $1 Sessions"
# Getting inputs from day 1 sessions
cd daily_sessions/"$1"

# Getting input path for day 1 session
for file in *; do
  if [ -f "$file" ]; then  # Check if it's a regular file
    dos2unix "$file" >/dev/null 2>&1
    input_path="../daily_sessions/$1/$file"
    day_inputs+=("$input_path")
  fi
done

# Go back to root directory
cd ../..





# Running Inputs with the front end
echo "Running $1  Sessions: Front End"
cd front_end


# Clear the output file before the loop
> "$actual_output_file"

for input_file in "${day_inputs[@]}"; do
  if [ -f "$input_file" ]; then
    echo "Running input file: $input_file"

    ./"$custom_program" < "$input_file">>"$actual_output_file"
    # ./"$custom_program" < "$input_file"
    sleep 0.75
  else
    echo "Input file not found: $input_file"
  fi
done

# copy files to the backend for processing
cd ..
echo "Copying Files into back end for Processing"

source_folder="front_end/log_files"
destination_folder="back_end/ori_log_files"


rsync -av --delete "$source_folder/" "$destination_folder/">/dev/null 2>&1
sleep 0.75


echo "Processing Backend for $1"
cd back_end
python main.py>/dev/null 2>&1
# python main.py

# moving back to root directory
cd ..


# Loop through all files in the directory
for file in *; do
  if [ -f "$file" ]; then
    dos2unix "$file" >/dev/null 2>&1
  fi
done
# Copying the modified files
source_folder="back_end/mod_log_files"
destination_folder="front_end/log_files"

rsync -av --delete "$source_folder/" "$destination_folder/">/dev/null 2>&1
sleep 0.75


# copying the data files to a  daily runs directoy
source_folder=back_end/mod_log_files
destination_folder=daily_runs_output_files/$1
cp -rf "$source_folder" "$destination_folder" >/dev/null 2>&1
sleep 0.75

source_folder="back_end/ori_log_files/merged_daily_transactions.etf"
destination_folder="daily_runs_output_files/$1"

cp -rf "$source_folder" "$destination_folder" >/dev/null 2>&1
sleep 0.75

source_folder="back_end/ori_log_files/merged_daily_transactions.etf"
destination_folder="tests/$1/actual/"
cp -rf "$source_folder" "$destination_folder" >/dev/null 2>&1
sleep 0.75
echo "Done Processing Sessions: $1 "

echo "Testing:$1"
# Testing portion

# Testing outputs
summary_output_file="tests/test_summary/output_diff_summary.txt"
output_diff_file="tests/$1/diff/diff_outputs.bto"
actual_output_file="tests/$1/actual/outputs.bto"
expected_output_file="tests/$1/expected/outputs.bto"

# comparing the actual and expected output files
{
    echo "Expected:"
    cat "$expected_output_file"
    echo "Actual:"
    cat "$actual_output_file"
    echo "Differences:"
    diff -Z "$expected_output_file" "$actual_output_file"
} > "$output_diff_file"

diff_output=$(diff -Z  "$actual_output_file" "$expected_output_file")
if [ -n "$diff_output" ]; then
  echo "Test: $1" >> "$summary_output_file"
  echo "Fail: Expected Output and Actual Output Do Not Match" >> "$summary_output_file"
  echo "Differences:" >> "$summary_output_file"
  diff "$expected_output_file" "$actual_output_file" >> "$summary_output_file"
  echo "===================================" >> "$summary_output_file"
  echo -e "\e[31mFail: Expected Output and Actual Output Do Not Match\e[0m"



else

    echo "Test: $1" >> "$summary_output_file"
    echo "Pass: Outputs match" >> "$summary_output_file"
    echo "===================================" >> "$summary_output_file"
    echo -e "\e[32mPass: Expected and Actual Output match\e[0m"
fi


# Testing merged transaction files
summary_transaction_file="tests/test_summary/merged_transactions_diff_summary.txt"
output_diff_transaction_file="tests/$1/diff/diff_transactions.etf"
actual_transaction_file="tests/$1/actual/merged_daily_transactions.etf"
expected_transaction_file="tests/$1/expected/merged_daily_transactions.etf"


# comparing the actual and expected merged transaction files
{
    echo "Expected:"
    cat "$expected_transaction_file"
    echo "Actual:"
    cat "$actual_transaction_file"
    echo "Differences:"
    diff "$expected_transaction_file" "$actual_transaction_file"
} > "$output_diff_transaction_file"


diff_output=$(diff "$actual_transaction_file" "$expected_transaction_file")
if [ -n "$diff_output" ]; then
  echo "Test: $1" >> "$summary_transaction_file"
  echo "Fail: Expected Output and Actual Output Do Not Match" >> "$summary_transaction_file"
  echo "Differences:" >> "$summary_transaction_file"
  diff "$expected_transaction_file" "$actual_transaction_file" >> "$summary_transaction_file"
  echo "===================================" >> "$summary_transaction_file"
  echo -e "\e[31mFail: Expected Merged Transaction File and Actual Merged Transaction File Do Not Match\e[0m"




else

    echo "Test: $1" >> "$summary_transaction_file"
    echo "Pass: Outputs match" >> "$summary_transaction_file"
    echo "===================================" >> "$summary_transaction_file"
    echo -e "\e[32mPass: Expected Merged Transaction File and Actual Merged Transaction File Match\e[0m"
fi
