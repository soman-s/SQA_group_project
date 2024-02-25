
#!/bin/bash
#!/bin/sh

summary_bto_differences_file="../Tests/test_summary/bto_diff_summary.txt"
custom_program="prototype_a.exe"
cd ..
test_inputs=()
output_bto=()
expected_output_paths=()
differences_paths=()

# clear the old summary logs



# GETS ALL THE INPUTS FROM TESTS
# Change into the Tests directory
cd Tests || exit 1  # Exit if cd fails
# Loop through each subdirectory in "Tests"
# for subdir in */; do
for subdir in create; do
    subdir="${subdir%/}"  # Remove trailing slash
    echo "Entering subdirectory: $subdir"
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

# Writing to the Summary.bto Files
rm "$summary_bto_differences_file"
touch "$summary_bto_differences_file"

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
    expected_bto="$expected_path$test_name.bto"

    # GETTING The Paths for the Difference
    bto_differences="${differences_paths[$index]}"
    bto_differences_file="$bto_differences"$test_name"_diff.txt"
    # Check if the file exists
    if [ ! -e "$bto_differences_file" ]; then
        # Create the file if it doesn't exist
        touch "$bto_differences_file"
    fi







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

        # comparing the differences between the bto
        # Run the diff command and redirect its output to the differences file
        {
            echo "Expected:"
            cat "$expected_bto"
            echo "Actual:"
            cat "$output_bto"
            echo "Differences:"
            diff "$expected_bto" "$output_bto"
        } > "$bto_differences_file"


        diff_output=$(diff "$expected_bto" "$output_bto")



        if [ -n "$diff_output" ]; then
            # If there are differences, save them to the differences file
            echo "Test: $test_name" >> "$summary_bto_differences_file"
            echo "Expected Output and Actual Output Do Not Match" >> "$summary_bto_differences_file"
            echo "Differences:" >> "$summary_bto_differences_file"
            diff "$expected_bto" "$output_bto" >> "$summary_bto_differences_file"
            echo "===================================" >> "$summary_bto_differences_file"
        else
            # If there are no differences, indicate that in the summary file
            echo "Test: $test_name" >> "$summary_bto_differences_file"
            echo "Expected Output and Actual Output Match" >> "$summary_bto_differences_file"
            echo "===================================" >> "$summary_bto_differences_file"
        fi





        # Copying Log Files to Test directories
        cp -r ./log_files/ "$output_path"
    else
        echo "$input_file is not readable or does not exist."
    fi



done
