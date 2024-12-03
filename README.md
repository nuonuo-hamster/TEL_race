## Windows
file 路徑: D:\TEL2024_Intergral\  
windows用的檔案有: ClientControl、D435iClient、.bat檔
### 用腳本開兩個Client: buttom和wheel
    launch_client.bat 直接雙擊左鍵就好
### 快速開啟VSCode
    openVS_windows.bat 直接雙擊左鍵就好

## Linux
file 路徑: /home/ical/Desktop/nuonuo/TEL2024_Integral  
Linux用的檔案有: ServerControl、D435iServer、.sh檔、Keyboard_directConnect
### 用腳本開兩個Server: buttom和wheel
    sh ./linux_launchserver.sh
### 快速開啟VSCode
    sh ./openVS_linux.sh

## 其他
1. 相機的程式現在都移出來了，為D435i_Server、D435i_Client  
AGX測試相機的 d435i . py 在 . / src
2. 現在兩邊有共用git，傳檔案直接push同步比較快
3. 搖桿的設定代碼從Client移到 . / src / controller_config
4. 程式碼如果要大改，建議先存副本到 . / old_files