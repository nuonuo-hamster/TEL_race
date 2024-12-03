1. "camera_control" node調整相機角度\
使用camera_angle.msg進行控制 topic 名稱 "/dynamixel/camera_angle"\
預設初始角度為120度，增加向上減少向下轉\
if = 0 角度向下轉置100度\
if = 1 角度向下轉置110度\
if = 2 角度轉置120度（預設）\
if = 3 角度向上轉置130度\
if = 4 角度向上轉置140度\
if = 5 角度向上轉置150度\
if = 6 角度向上轉置160度\
if = 7 查看當前角度\

2. "laser_control" node控制下面2根laser支架\
使用wheel_laser.msg進行控制 topic名稱 "/dynamixel/wheel_laser"\
if bool=1 支架展開,if bool=0 支架收起

3. "trunk" node控制夾爪與擋板,自動化夾取與堆疊\
使用arm_trunk.msg進行控制 topic名稱 "/dynamixel/arm_storage"\
if = 1 木板傾斜\
if = 2 夾爪夾取動作\
if = 3 積木放置於木板\
if = 4 夾爪回到前面夾取位置\
if = 5 積木放置堆疊\
if = 6 回到初始位置
