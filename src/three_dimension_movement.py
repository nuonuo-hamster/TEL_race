forward   =  [ 1, 1, 1, 1]
backward  =  [-1,-1,-1,-1]
shiftLeft =  [-1, 1, 1,-1]
shiftRight = [ 1,-1,-1, 1]
turnLeft  =  [-1, 1,-1, 1]
turnRight =  [ 1,-1, 1,-1]

def send_control_message(client_socket, server_address, message=''):
    try:
        client_socket.sendto(message.encode(), server_address)
    except Exception as e:
        print(f"Error sending message: {e}")

# 映射
def map_value(value, from_min, from_max, to_min, to_max):
    return to_min + (value - from_min) * (to_max - to_min) / (from_max - from_min)

# 發送
def send_car_instruct(car_instruct, client_socket, server_address):

    global ser
    data_to_send = [0]*4

    # print(car_instruct)
    for i in range(4):
        if car_instruct[i] > 0:
            data_to_send[i] = f'${i+1} 1 {car_instruct[i]}\n'
        elif car_instruct[i] < 0:
            data_to_send[i] = f'${i+1} 2 {car_instruct[i]}\n'
        elif car_instruct[i] == 0:
            data_to_send[i] = f'${i+1} 0 0\n'
        else:
            data_to_send[i] = f'$10\n'
    
    for msg in data_to_send:
        # print(msg, end='')
        # arduino.write(msg.encode())
        send_control_message(client_socket, server_address, message=msg)

# 3D疊加之後給send_car_instruct
def ThreeD_Movement(FB, sLR, tLR, client_socket, server_address, max_value):

    FB_arr  = [i*FB  for i in forward]
    sLR_arr = [i*sLR for i in shiftRight]
    tLR_arr = [i*tLR for i in turnRight]
    car_instruct = [0]*4

    orverflow = False
    orverflow_max_value = 0
    for i in range(4):
        car_instruct[i] = FB_arr[i] + sLR_arr[i] + tLR_arr[i]
        if car_instruct[i]>max_value and car_instruct[i]>orverflow_max_value:
            orverflow = True
            orverflow_max_value = car_instruct[i]
    
    if orverflow:
        car_instruct  = [round(map_value(i, 0, orverflow_max_value, 0, max_value), 2) for i in car_instruct]

    send_car_instruct(car_instruct, client_socket, server_address)

    return car_instruct

# 映射處理後給ThreeD_Movement
def car_move(FB, sLR, tLR, map_controller, map_Movement, client_socket, server_address):

    mapped_FB = map_value(FB, map_controller[0], map_controller[1], map_Movement[0], map_Movement[1])
    mapped_sLR = map_value(sLR, map_controller[0], map_controller[1], map_Movement[0], map_Movement[1])
    mapped_tLR = map_value(tLR, map_controller[0], map_controller[1], map_Movement[0], map_Movement[1])

    if abs(mapped_FB)>map_Movement[1]: mapped_FB = map_Movement[1]*mapped_FB/abs(mapped_FB)
    if abs(mapped_sLR)>map_Movement[1]: mapped_sLR = map_Movement[1]*mapped_sLR/abs(mapped_sLR)
    if abs(mapped_tLR)>map_Movement[1]: mapped_tLR = map_Movement[1]*mapped_tLR/abs(mapped_tLR)

    car_instruct = ThreeD_Movement(mapped_FB, mapped_sLR, mapped_tLR, client_socket, server_address, max_value=map_Movement[1])

    return car_instruct

def car_move_wrap(map_controller, map_Movement, client_socket, server_address):
    map_origin = map_controller
    map_target = map_Movement

    def inner_func(FB, sLR, tLR):
        car_instruct = car_move(FB, sLR, tLR, map_origin, map_target, client_socket, server_address)
        return car_instruct

    return inner_func