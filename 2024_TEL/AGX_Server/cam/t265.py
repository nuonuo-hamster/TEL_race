import pyrealsense2 as rs
import transformations as tf
import numpy as np
import math as m

H_aeroRef_T265Ref = np.array([[0,0,-1,0],[1,0,0,0],[0,-1,0,0],[0,0,0,1]])
H_T265body_aeroBody = np.linalg.inv(H_aeroRef_T265Ref)

def cam_init():
   
    pipe = rs.pipeline()
    cfg = rs.config()
    cfg.enable_stream(rs.stream.pose)
    pipe.start(cfg)

    return pipe

def cam_close(pipe):
   
    pipe.stop()

def getPosition(pose_data):
    
    position = np.array([pose_data.translation.x, pose_data.translation.y, pose_data.translation.z])
    return position

def getRotation(pose_data):

    data = pose_data

    H_T265Ref_T265body = tf.quaternion_matrix([data.rotation.w, data.rotation.x,data.rotation.y,data.rotation.z]) # in transformations, Quaternions w+ix+jy+kz are represented as [w, x, y, z]!
    H_aeroRef_aeroBody = H_aeroRef_T265Ref.dot( H_T265Ref_T265body.dot( H_T265body_aeroBody ))
    rpy_rad = np.array( tf.euler_from_matrix(H_aeroRef_aeroBody, 'sxyz') ) # Rz(yaw)*Ry(pitch)*Rx(roll) body w.r.t. reference frame

    return rpy_rad

def poseProcess(pipe):
      
    frames = pipe.wait_for_frames()
    pose = frames.get_pose_frame()
    
    if pose:
        data = pose.get_pose_data()

        frame_number = pose.frame_number
        position = getPosition(data)
        rpy_rad = getRotation(data)

        return frame_number, position, rpy_rad
    else: 
        return None, None, None

def test():
    
    pipe = cam_init()

    for _ in range(5000):
        try:
            frame_number, position, rpy_rad = poseProcess(pipe)
            print("Frame #{}".format(frame_number))
            print("Axis [xyz]: {}".format(position))  # 相機的(x, y, z) -> 實際的(x, z, -y)
            print("RPY [deg]: {}".format(rpy_rad*180/m.pi)) # row(x), pitch(y), yaw(z) (應該是)
        except:
             print("T265 err")

    cam_close(pipe)

if __name__ == '__main__':

    test()