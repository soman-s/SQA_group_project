
#!/bin/bash
#!/bin/sh

summary_bto_differences_file="../Tests/test_summary/bto_diff_summary.txt"
summary_daily_transaction_differences_file="../Tests/test_summary/daily_transactions_diff_summary.txt"
summary_available_games_differences_file="../Tests/test_summary/available_games_diff_summary.txt"
summary_games_collection_differences_file="../Tests/test_summary/games_collection_diff_summary.txt"
summary_users_differences_file="../Tests/test_summary/users_diff_summary.txt"
custom_program="front_end.exe"

cd ..
test_inputs=()
output_bto=()
expected_output_paths=()
differences_paths=()


# This script does both running the program with the inputs
# and does comparions for the expected/ actual bto files
# and the expected and actual daily transaction file

echo "Running Tests"

# GETS ALL THE INPUTS FROM TESTS
# Change into the Tests directory
cd Tests || exit 1  # Exit if cd fails
# Loop through each test subdirectory in "Tests" excluding the summary folder
# for subdir in login logout refund sell add_credit create delete buy all_user available_games;
for subdir in login logout refund sell add_credit create delete buy all_user available_games; do
    subdir="${subdir%/}"
    # Change into the subdirectory
    cd "$subdir" || { echo "Failed to enter subdirectory: $subdir"; continue; }
    # Loop through each folder in the subdirectory
    for folder in */; do
        folder="${folder%/}"  # Remove trailing slash

        # Change into the folder
        cd "$folder" || { echo "Failed to enter folder: $folder"; continue; }

        # GET OUTPUT PATH FOR BTO FILES
        bto_paths="../Tests/$subdir/$folder/outputs/actual/"
        output_bto+=("$bto_paths")

        # getting all the paths for the expected_output
        expected_path="../Tests/$subdir/$folder/outputs/expected/"
        expected_output_paths+=("$expected_path")

        #getting all the differences path
        differences="../Tests/$subdir/$folder/differences/"
        differences_paths+=("$differences")

        # Navigate into the "inputs" folder
        cd inputs || { echo "Failed to enter inputs folder"; continue; }
        inputs_path="../Tests/$subdir/$folder/inputs/"
        for file in *.inp; do
        if [ -e "$file" ]; then

          dos2unix "$file" >/dev/null 2>&1
           inputs_path="../Tests/$subdir/$folder/inputs/./$file"
           test_inputs+=("$inputs_path")


        else
            echo "Input file $file does not exist."
            echo "../Tests/$subdir/$folder/inputs/./$file"
        fi
            done
        # Move back to the parent directory (folder)
        cd ..
        # Move back to the parent directory (subdirectory)
        cd ..
    done
    # Move back to the parent directory (Tests)
    cd ..
done

# Running THE Programs
cd ..
cd Code

# Writing to the Summary.bto Files and Log Differnce files
rm "$summary_bto_differences_file"
touch "$summary_bto_differences_file"

rm "$summary_daily_transaction_differences_file"
touch "$summary_daily_transaction_differences_file"

passed_transaction_tests=0
failed_transaction_tests=0
passed_output_tests=0
failed_output_tests=0

# Loop through each index in the array of test input files
for index in "${!test_inputs[@]}"; do
    # Access the input file at the current index
    input_file="${test_inputs[$index]}"

    # PATHS AND OUTPUT FROM THE ACTUAL TESTS
    output_path="${output_bto[$index]}"
    test_name=$(basename "$(dirname "$(dirname "$output_path")")")
    output_bto="${output_bto[$index]}$test_name.bto"

    #PATHS AND OUTPUT FROM THE EXPECTED DIRECTOTY
    expected_path="${expected_output_paths[$index]}"
    expected_log_files_path="${expected_output_paths[$index]}log_files"
    expected_bto="$expected_path$test_name.bto"

    # GETTING The Paths for the Difference bto
    bto_differences="${differences_paths[$index]}"
    bto_differences_file="$bto_differences"$test_name"_bto_diff.txt"
    # Check if the file exists
    if [ ! -e "$bto_differences_file" ]; then

        touch "$bto_differences_file"
    fi

    # GETTING The Paths for the Difference LOG FILES
    expected_transaction="$expected_log_files_path/daily_transactions.etf"
    actual_transaction="${output_path}log_files/daily_transactions.etf"


    # GETTING The Paths for the Difference
    log_file_differences="${differences_paths[index]}"
    log_file_differences_file="${log_file_differences}${test_name}_log_files_diff.txt"

    # Check if the file exists
    if [ ! -e "$log_file_differences_file" ]; then
        touch "$log_file_differences_file"
    fi

    # GETTING The Paths for the avaiable_Games Files
    expected_available_games="$expected_log_files_path/available_games.etf"
    actual_avaiable_games="${output_path}log_files/available_games.etf"

    # GETTING The Paths for the avaiable_Games Files
    expected_users="$expected_log_files_path/current_users.etf"
    actual_users="${output_path}log_files/current_users.etf"

    # GETTING The Paths for games collection
    expected_game_collection="$expected_log_files_path/game_collection.etf"
    actual_game_collection="${output_path}log_files/game_collection.etf"


    temp_file=$(mktemp)

    # Run custom program with input from the current test file and output to the corresponding path
    echo "Running Test $test_name"
    if [ -r "$input_file" ]; then
        # Run the custom program with input from the current test file and output to the corresponding path
        ./"$(basename "$custom_program")" < "$input_file" > "$output_bto"

        mapfile -t lines < "$input_file"
        index=0

        while IFS= read -r line; do
            # Process each line here
            if [[ "$line" == *":"* ]]; then
                # Find the position of the first colon
                semicolon_pos=$(expr index "$line" ":")

                # Extract the substring from the beginning of the line up to the colon
                before_colon=${line:0:$((semicolon_pos))}
                after_colon=${line:$semicolon_pos+1}

                # Define the new value to append after the colon position
                new_value=${lines[index]}

                # Combine the substring before the colon with the new value
                new_line="${before_colon} ${new_value}"

                # Output the new line
                echo "$new_line"
                echo "$after_colon"

                ((index+=1))
            else
                echo "$line"

            fi

        done < "$output_bto" >> "$temp_file"

        mv "$temp_file" "$output_bto"

        # comparing the actual and expected output files
        {
            echo "Expected:"
            cat "$expected_bto"
            echo "Actual:"
            cat "$output_bto"
            echo "Differences:"
            diff -Z "$expected_bto" "$output_bto"
        } > "$bto_differences_file"


        diff_output=$(diff -Z  "$expected_bto" "$output_bto")

        if [ -n "$diff_output" ]; then
        # If there are differences, save them to the differences file
        ((failed_output_tests++))
        echo "Test: $test_name" >> "$summary_bto_differences_file"
        echo "Fail: Expected Output and Actual Output Do Not Match" >> "$summary_bto_differences_file"
        echo "Differences:" >> "$summary_bto_differences_file"
        diff "$expected_bto" "$output_bto" >> "$summary_bto_differences_file"
        echo "===================================" >> "$summary_bto_differences_file"
        echo -e "\e[31mFail: Expected Output and Actual Output Do Not Match\e[0m"








    else
        # If there are no differences, indicate that in the summary file
        ((passed_output_tests++))
        echo "Test: $test_name" >> "$summary_bto_differences_file"
        echo "Pass: Outputs match" >> "$summary_bto_differences_file"
        echo "===================================" >> "$summary_bto_differences_file"
        echo -e "\e[32mPass: Expected and Actual Output match\e[0m"
    fi






        # Copying Log Files to Test directories
        cp -r ./log_files "$output_path"



        # comparing the DAILY TRANSACTION FILES expected vs actual
        # Run the diff command and redirect its output to the differences file
        {
            echo "Expected:"
            cat "$expected_transaction"
            echo
            echo "Actual:"
            cat "$actual_transaction"
            echo
            echo "Differences:"
            diff "$expected_transaction" "$actual_transaction"
        } > "$log_file_differences_file"

        diff_output_transaction=$(diff "$expected_transaction" "$actual_transaction")

        if [ -n "$diff_output_transaction" ]; then
            # If there are differences, save them to the differences file
            ((failed_transaction_tests++))
            echo "Test: $test_name" >> "$summary_daily_transaction_differences_file"
            echo "Fail: Expected Daily Transactions File and Actual Daily Transactions File Do Not Match" >> "$summary_daily_transaction_differences_file"
            echo "Differences:" >> "$summary_daily_transaction_differences_file"
            diff "$expected_transaction" "$actual_transaction" >> "$summary_daily_transaction_differences_file"
            echo "==================================" >> "$summary_daily_transaction_differences_file"
            echo -e "\e[31mFail: Expected Daily Transactions File and Actual Daily Transactions File Do Not Match\e[0m"








        else
            # If there are no differences, indicate that in the summary file
            ((passed_transaction_tests++))
            echo "Test: $test_name" >> "$summary_daily_transaction_differences_file"
            echo "Pass: Expected Daily Transactions File and Actual Daily Transactions File Match" >> "$summary_daily_transaction_differences_file"
            echo "===================================" >> "$summary_daily_transaction_differences_file"
            echo -e "\e[32mPass: Expected Daily Transactions File and Actual Daily Transactions File Match\e[0m"
        fi



    else
        echo "$input_file is not readable or does not exist."
    fi



done


# Define color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Display summary statistics for transaction tests
echo -e " Summary for Transaction Tests:${NC}"
echo -e "Total transaction tests: $((passed_transaction_tests + failed_transaction_tests))${NC}"
echo -e "${GREEN}Passed transaction tests: $passed_transaction_tests${NC}"
echo -e "${RED}Failed transaction tests: $failed_transaction_tests${NC}"

# Display summary statistics for output tests
echo -e " Summary for Output Tests:${NC}"
echo -e "Total output tests: $((passed_output_tests + failed_output_tests))${NC}"
echo -e "${GREEN}Passed output tests: $passed_output_tests${NC}"
echo -e "${RED}Failed output tests: $failed_output_tests${NC}"
