#!/bin/bash

echo "Executing Python scripts..."

gnome-terminal -- code . --no-sandbox

echo "All scripts have been executed."

read -p "Press any key to continue..."
