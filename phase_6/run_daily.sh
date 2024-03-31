#!/bin/bash
#!/bin/sh

custom_program="front_end.exe"

day_inputs=()

# Always coping back the original files for testing

echo "Copying back the Original Log Files"

source_folder="original_files"
destination_folder="front_end/log_files"



# Copy all contents from source to destination
cp -rf "$source_folder"/* "$destination_folder"/

echo " Getting inputs from Day 1 Sessions"
# Getting inputs from day 1 sessions
cd daily_sessions/day_1

# Getting input path for day 1 session
for file in *; do
  if [ -f "$file" ]; then  # Check if it's a regular file
    dos2unix "$file" >/dev/null 2>&1
    input_path="../daily_sessions/day_1/$file"
    day_inputs+=("$input_path")
  fi
done

# Go back to root directory
cd ../..

# Running Inputs with the front end
echo "Running Day 1 Sessions: Front End"
cd front_end

for input_file in "${day_inputs[@]}"; do
  if [ -f "$input_file" ]; then
    echo "Running input file: $input_file"

    ./"$custom_program" < "$input_file" >/dev/null 2>&1
    sleep 0.75
  else
    echo "Input file not found: $input_file"
  fi
done

# copy files to the backend for processing
cd ..
ls
echo "Copying Files into back end for Processing"

source_folder="front_end/log_files"
destination_folder="back_end/ori_log_files"


rsync -av --delete "$source_folder/" "$destination_folder/">/dev/null 2>&1


echo "Processing Backend for Day 1"
cd back_end
python main.py

cd ..

source_folder="back_end/mod_log_files"
destination_folder="front_end/log_files"

rsync -av --delete "$source_folder/" "$destination_folder/">/dev/null 2>&1

echo "Done Processing Sessions: Day 1"
