import pyrealsense2 as rs
import time

# 創建管道對象
pipeline = rs.pipeline()

# 配置管道
config = rs.config()
# 嘗試啟動管道
try:
    pipeline.start(config)
    print("RealSense 裝置已啟動！")
    
    # 開始捕捉幾幀數據
    for i in range(10):
        frames = pipeline.wait_for_frames()  # 等待接收到幀數據
        color_frame = frames.get_color_frame()  # 獲取顏色幀
        depth_frame = frames.get_depth_frame()  # 獲取深度幀

        # 顯示一部分顏色幀的大小（例如深度或顏色幀的寬高）
        print(f"第 {i + 1} 幀: 顏色幀尺寸: {color_frame.get_width()}x{color_frame.get_height()}")
        time.sleep(1)

    pipeline.stop()  # 停止管道

except Exception as e:
    print(f"啟動 RealSense 裝置失敗: {e}")
