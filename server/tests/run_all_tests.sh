#!/bin/bash

# Initialize an empty array to store all .py files
all_files=()

# Loop through each .py file in the current directory
for file in *.py; do
    # Add the file to the all_files array
    all_files+=("$file")
done

# Print all the .py files found
echo "All .py files found:"
for file in "${all_files[@]}"; do
    echo "$(basename "$file")"
done

# Check if there are any .py files
if [ ${#all_files[@]} -eq 0 ]; then
    echo "No .py files found."
else
    # Run pytest for all .py files
    echo "Running pytest for all files..."
    pytest "${all_files[@]}"

    # Run pytest with coverage for all .py files
    echo "Running pytest with coverage for all files..."
    coverage run -m pytest "${all_files[@]}"

    # Generate coverage report
    echo "Generating Coverage Report"
    coverage report -m
fi
