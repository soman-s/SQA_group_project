#!/bin/bash
#!/bin/sh


# Script to process 1 days worth of daily merged_daily_transactions
# To run DAILY SCRIPT
# chmod +x run_daily.sh
# dos2unix run_daily.sh
# ./run_daily.sh day_1(sub with the folder you want to test)

custom_program="front_end.exe"

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

for input_file in "${day_inputs[@]}"; do
  if [ -f "$input_file" ]; then
    echo "Running input file: $input_file"

    ./"$custom_program" < "$input_file" >/dev/null 2>&1
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


echo "Processing Backend for $1"
cd back_end
python main.py>/dev/null 2>&1
# python main.py

cd ..

# Copying the modified files
source_folder="back_end/mod_log_files"
# Loop through all files in the directory
for file in *; do
  if [ -f "$file" ]; then
    dos2unix "$file" >/dev/null 2>&1
  fi
done

destination_folder="front_end/log_files"

rsync -av --delete "$source_folder/" "$destination_folder/">/dev/null 2>&1


# copying the data files to a directory
source_folder=back_end/mod_log_files
destination_folder=daily_runs_output_files/$1
cp -rf "$source_folder" "$destination_folder" >/dev/null 2>&1

source_folder="back_end/ori_log_files/merged_daily_transactions.etf"
destination_folder="daily_runs_output_files/$1"

cp -rf "$source_folder" "$destination_folder" >/dev/null 2>&1




echo "Done Processing Sessions: $1 "
