target_link_libraries(arm_node
arm_lib
dynamixel_lib
${DYNAMIXEL_LIBRARIES}
${catkin_LIBRARIES}
)

target_link_libraries(trunk_node
trunk_lib
arm_lib
dynamixel_lib
${DYNAMIXEL_LIBRARIES}
${catkin_LIBRARIES}
)

target_link_libraries(control_node
control_lib
laser_control_lib
arm_lib
trunk_lib
camera_control_lib
dynamixel_lib
${DYNAMIXEL_LIBRARIES}
${catkin_LIBRARIES}
)

target_link_libraries(laser_control_node
laser_control_lib
dynamixel_lib
${DYNAMIXEL_LIBRARIES}
${catkin_LIBRARIES}
)

target_link_libraries(camera_control_node
camera_control_lib
dynamixel_lib
${DYNAMIXEL_LIBRARIES}
${catkin_LIBRARIES}
)

target_link_libraries(udp_trunk_node
udp_trunk_lib
arm_lib
dynamixel_lib
${DYNAMIXEL_LIBRARIES}
${catkin_LIBRARIES}
)