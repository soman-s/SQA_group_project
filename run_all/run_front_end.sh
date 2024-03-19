#!/bin/bash

cd ..
cd Code

echo "Compling Front End"
g++ -o front_end.exe main.cpp menus.cpp user_file_process.cpp constants.cpp games_file_process.cpp utils.cpp transactions.cpp

echo "Runing Front End"
./front_end.exe
