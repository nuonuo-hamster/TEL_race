#!/bin/bash

echo "Executing Python scripts..."

# d435i server
# gnome-terminal -- bash -c "sudo /home/ical/.virtualenvs/TEL_race-FYbzsy1B/bin/python "/home/ical/Desktop/TEL_race/D435iServer.py"; echo 'press any key to exit...'; read"
# button server
gnome-terminal -- bash -c "sudo /home/ical/.virtualenvs/TEL_race-FYbzsy1B/bin/python "/home/ical/Desktop/TEL_race/ServerControl_button.py"; echo 'press any key to exit...'; read"
# wheel server
gnome-terminal -- bash -c "/home/ical/.virtualenvs/TEL_race-FYbzsy1B/bin/python "/home/ical/Desktop/TEL_race/ServerControl_wheel.py"; echo 'press any key to exit...'; read"

echo "All scripts have been executed."

read -p "Press any key to continue..."