@echo off
echo Executing Python scripts...

@REM 設置 IP 並寫入 ip.txt
echo ip='192.168.0.119' > d:/TEL2024_Intergral/ip.txt
@REM d435i client
@REM start C:/Users/superuser/.virtualenvs/2024_TEL-tUU5St8O/Scripts/python.exe d:/TEL2024_Intergral/D435iClient.py
@REM buttom client
start C:/Users/superuser/.virtualenvs/2024_TEL-tUU5St8O/Scripts/python.exe d:/TEL2024_Intergral/ClientControl_button.py
@REM wheel client
start C:/Users/superuser/.virtualenvs/2024_TEL-tUU5St8O/Scripts/python.exe d:/TEL2024_Intergral/ClientControl_wheel.py

echo All scripts have been executed.
pause