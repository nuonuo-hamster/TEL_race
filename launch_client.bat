@echo off
echo Executing Python scripts...

@REM d435i client
start C:/Users/superuser/.virtualenvs/2024_TEL-tUU5St8O/Scripts/python.exe d:/TEL2024_Intergral/D435iClient.py
@REM buttom client
start C:/Users/superuser/.virtualenvs/2024_TEL-tUU5St8O/Scripts/python.exe d:/TEL2024_Intergral/ClientControl_button.py
@REM wheel client
start C:/Users/superuser/.virtualenvs/2024_TEL-tUU5St8O/Scripts/python.exe d:/TEL2024_Intergral/ClientControl_wheel.py

echo All scripts have been executed.
pause