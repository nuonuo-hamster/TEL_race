# To run d435i.py in terminal, use " sudo /home/ical/.local/share/virtualenvs/2024_TEL-YxRACiM0/bin/python d435i.py "
# 
import pyrealsense2 as rs
import numpy as np
import cv2
import math

def realsense_init(width, height):

    pipe = rs.pipeline()
    cfg  = rs.config()

    cfg.enable_stream(rs.stream.color, width,height, rs.format.bgr8, 30)
    cfg.enable_stream(rs.stream.depth, width,height, rs.format.z16, 30)

    cfg.enable_stream(rs.stream.accel)
    cfg.enable_stream(rs.stream.gyro)

    pipe.start(cfg)

    return pipe

def get_yaw_pitch(accel_data):
    pitch = math.atan2(accel_data[1], math.sqrt(accel_data[0] ** 2 + accel_data[2] ** 2))
    yaw = math.atan2(-accel_data[0], math.sqrt(accel_data[1] ** 2 + accel_data[2] ** 2))

    pitch = math.degrees(pitch)
    yaw = math.degrees(yaw)
    return yaw, pitch

def realsense_run(pipe):

    frame = pipe.wait_for_frames()
    depth_frame = frame.get_depth_frame()
    color_frame = frame.get_color_frame()

    accel_data = None
    for f in frame:
        if f.is_motion_frame():
            if f.profile.stream_type() == rs.stream.accel:
                accel_frame = f.as_motion_frame()
                accel_data = np.array([accel_frame.get_motion_data().x, 
                                       accel_frame.get_motion_data().y, 
                                       accel_frame.get_motion_data().z])
                break
    
    if accel_data is None:
        print("No accelerometer data found.")
        return depth_frame, color_image, depth_cm, None, None

    depth_image = np.asanyarray(depth_frame.get_data())
    color_image = np.asanyarray(color_frame.get_data())
    depth_cm = cv2.applyColorMap(cv2.convertScaleAbs(depth_image, 
                                alpha = 0.5), cv2.COLORMAP_JET)
    
    color_image = cv2.transpose(color_image)
    color_image = cv2.flip(color_image, flipCode=1)  # flipCode=1 means horizontal flip

    yaw, pitch = get_yaw_pitch(accel_data)
    
    return depth_frame, color_image, depth_cm, yaw, pitch

def put_text(color_image, flag, info, dir_x, dir_y):
    if flag == 1:
        cv2.putText(color_image, f"Yaw: {info:.2f}", (dir_x, dir_y), cv2.FONT_HERSHEY_SIMPLEX, 
                    0.6, (0, 255, 0), 2, cv2.LINE_AA)
    elif flag == 2:
        cv2.putText(color_image, f"Pitch: {info:.2f}", (dir_x, dir_y), cv2.FONT_HERSHEY_SIMPLEX, 
                    0.6, (0, 255, 0), 2, cv2.LINE_AA)

def main():
    pipe = realsense_init(width=640, height=480)
    
    while(True):
        depth_frame, color_image, depth_cm, yaw, pitch = realsense_run(pipe)
        
        put_text(color_image, 1, yaw, 10, 30)
        put_text(color_image, 2, pitch, 10, 60)
        
        cv2.imshow('RGB Frame', color_image)
        if cv2.waitKey(1) == 27: # esc
            break
    
    cv2.destroyAllWindows()
    pipe.stop()

if __name__ == '__main__':
    main()
