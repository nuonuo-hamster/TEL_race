import pyrealsense2 as rs

def get_connected_devices():
    # 創建一個 Context 物件
    ctx = rs.context()

    # 取得所有連接的設備
    devices = ctx.query_devices()

    if not devices:
        print("沒有偵測到任何相機！")
        return

    print("已連接的設備:")
    
    for device in devices:
        # 顯示設備的名稱及序號
        device_name = device.get_info(rs.camera_info.name)
        device_serial = device.get_info(rs.camera_info.serial_number)
        
        print(f"設備名稱: {device_name}, 序號: {device_serial}")

if __name__ == "__main__":
    get_connected_devices()
