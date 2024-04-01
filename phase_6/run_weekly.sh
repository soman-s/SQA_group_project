#!/bin/bash
#!/bin/sh


# Always coping back the original files for testing

echo "Copying back the Original Log Files"

source_folder="original_files"
destination_folder="front_end/log_files"
# Copy all contents from source to destination


cp -rf "$source_folder"/* "$destination_folder"/

cd daily_sessions

# Loop through each folder in the current directory
for folder in *; do
    # Check if the item is a directory
    if [ -d "$folder" ]; then
        # Add the folder name to the array
        daily_sessions+=("$folder")
    fi
done

cd ..


for session_folder in "${daily_sessions[@]}"; do
  dos2unix run_daily.sh >/dev/null 2>&1
  ./run_daily.sh $session_folder
done
