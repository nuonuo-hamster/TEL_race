#!/bin/bash

echo "Executing Python scripts..."

# d435i server
gnome-terminal -- bash -c "sudo /home/ical/.local/share/virtualenvs/2024_TEL-YxRACiM0/bin/python "/home/ical/Desktop/nuonuo/TEL2024_Integral/D435iServer.py"; echo 'press any key to exit...'; read"
# buttom server
gnome-terminal -- bash -c "/home/ical/.local/share/virtualenvs/2024_TEL-YxRACiM0/bin/python "/home/ical/Desktop/nuonuo/TEL2024_Integral/ServerControl_button.py"; echo 'press any key to exit...'; read"
# wheel server
gnome-terminal -- bash -c "/home/ical/.local/share/virtualenvs/2024_TEL-YxRACiM0/bin/python "/home/ical/Desktop/nuonuo/TEL2024_Integral/ServerControl_wheel.py"; echo 'press any key to exit...'; read"

echo "All scripts have been executed."

read -p "Press any key to continue..."