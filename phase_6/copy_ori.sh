# Always coping back the original files for testing

echo "Copying back the Original Log Files"

source_folder=original_files
destination_folder=front_end/log_files
cp -rf "$source_folder"/* "$destination_folder"/ >/dev/null 2>&1
