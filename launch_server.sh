#!/bin/bash

echo "Executing Python scripts..."

# gnome-terminal -- bash -c "/home/ical/.local/share/virtualenvs/2024_TEL-YxRACiM0/bin/python "/home/ical/Desktop/nuonuo/TEL2024_Integral/ServerControl_button.py"; echo 'press any key to exit...'; read"
gnome-terminal -- bash -c "/home/ical/.local/share/virtualenvs/2024_TEL-YxRACiM0/bin/python "/home/ical/Desktop/nuonuo/TEL2024_Integral/ServerControl_wheel.py"; echo 'press any key to exit...'; read"

echo "All scripts have been executed."

read -p "Press any key to continue..."