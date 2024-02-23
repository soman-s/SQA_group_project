
#!/bin/bash
# Move back one directory from the current directory

custom_program="prototype_a.exe"
cd ..
# Print the current working directory to verify the change
echo "Current directory: $(pwd)"

test_inputs=()

# GETS ALL THE INPUTS FROM TESTS
# Change into the Tests directory
cd Tests || exit 1  # Exit if cd fails
# Loop through each subdirectory in "Tests"
# for subdir in */; do
for subdir in  login logout; do
    subdir="${subdir%/}"  # Remove trailing slash
    echo "Entering subdirectory: $subdir"
    # Change into the subdirectory
    cd "$subdir" || { echo "Failed to enter subdirectory: $subdir"; continue; }
    # Loop through each folder in the subdirectory
    for folder in */; do
        folder="${folder%/}"  # Remove trailing slash

        # Change into the folder
        cd "$folder" || { echo "Failed to enter folder: $folder"; continue; }
        # Navigate into the "inputs" folder
        cd inputs || { echo "Failed to enter inputs folder"; continue; }
        inputs_path="../Tests/$subdir/$folder/inputs/"
        for file in *.inp; do
        if [ -e "$file" ]; then

          dos2unix "$file" >/dev/null 2>&1
           inputs_path="../Tests/$subdir/$folder/inputs/./$file"
           test_inputs+=("$inputs_path")

            #run_custom_program "$file"
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

# Loop through each test input file
for input_file in "${test_inputs[@]}"; do
    # Run custom program with input from the current test file
    echo "Running custom program with input from $input_file..."
    if [ -r "$input_file" ]; then
        # Run the custom program with input from the current test file
        ./"$(basename "$custom_program")" < "$input_file"
    else
        echo "$input_file is not readable or does not exist."
    fi
done
