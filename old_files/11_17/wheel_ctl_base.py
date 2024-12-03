import serial
import time

class PID:
    def __init__(self, kp, ki, kd, max_output=None, min_output=None):
        self.kp = kp
        self.ki = ki
        self.kd = kd
        self.max_output = max_output
        self.min_output = min_output
        self.prev_error = 0
        self.integral = 0

    def calculate(self, setpoint, current_value):
        # 計算誤差
        error = setpoint - current_value

        # 比例項
        proportional = self.kp * error

        # 積分項
        self.integral += error
        integral = self.ki * self.integral

        # 微分項
        derivative = self.kd * (error - self.prev_error)

        # 計算 PID 輸出
        output = proportional + integral + derivative

        # 限制輸出範圍
        if self.max_output is not None and self.min_output is not None:
            output = max(min(output, self.max_output), self.min_output)

        # 存儲當前誤差
        self.prev_error = error

        return output
    
    def get_RPM(self, ser):
        # data_to_send = f'$5\n'
        # # print("set1")
        # ser.write(data_to_send.encode())
        # time.sleep(0.05)
        # # print("set2")
        # data = ser.readline().decode('utf-8', errors='ignore').strip()
        print("set3")
        if data:
            signal = [int(num) for num in data.split(",") if num.strip().isdigit()]
            # print(signal)
            # FL_a_value, FL_b_value, FR_a_value, FR_b_value, BL_a_value, BL_b_value, BR_a_value, BR_b_value
            if(len(signal) == 8):
                FL_rpm = (signal[0] + signal[0])/2
                FR_rpm = (signal[2] + signal[2])/2
                BL_rpm = (signal[4] + signal[4])/2
                BR_rpm = (signal[6] + signal[6])/2
                if (FL_rpm != None and FR_rpm != None and BL_rpm != None and BR_rpm != None):
                    print(f"rpm: {FL_rpm:.2f}, {FR_rpm:.2f}, {BL_rpm:.2f}, {BR_rpm:.2f}")
                    return (round(FL_rpm, 2), round(FR_rpm, 2), round(BL_rpm, 2), round(BR_rpm, 2))
        else:
            print("get RPM error...")
            return None

    def send_PWM(self, ser, wheel_number, option, pwm_value):
        data_to_send = f'${wheel_number} {option} {pwm_value}\n'
        ser.write(data_to_send.encode())

    def run_pid(self, ser, wheel_number, option, target_RPM):
        # 1.拿到轉速
        # 2.計算PWM
        # 3.傳送
        wheel_RPM = self.get_RPM(ser)
        if wheel_RPM is None:
            return
        current_RPM = wheel_RPM[wheel_number-1]
        old_RPM = current_RPM
        
        # print("input", current_RPM, end=" ,")
        current_PWM = self.calculate(target_RPM, current_RPM)
        # print("output", current_RPM)
        
        if (abs(current_PWM)>150): current_PWM = 150* current_PWM/abs(current_PWM)
    
        # print(f"目标 RPM: {target_RPM}, 当前 RPM: {old_RPM}, PWM: {current_PWM}")
        # print(f"---------------------------")
        self.send_PWM(ser, wheel_number, option, current_PWM)
 
def create_PID():
    pid_1 = PID(kp=0.2, ki=0.1, kd=0, max_output=255, min_output=0)
    pid_2 = PID(kp=0.2, ki=0.1, kd=0, max_output=255, min_output=0)
    pid_3 = PID(kp=0.2, ki=0.1, kd=0, max_output=255, min_output=0)
    pid_4 = PID(kp=0.2, ki=0.1, kd=0, max_output=255, min_output=0)

    return [pid_1, pid_2, pid_3, pid_4]

def delete_PID(arr):
    for pid in arr:
        del pid

def serOpen(port = 'COM5', rate = 9600):

    ser = serial.Serial(port, rate)

    return ser

def serClose(ser):
    ser.close()

def stop(ser):

    data_to_send_1 = f'$1 0 200\n'
    data_to_send_2 = f'$2 0 200\n'
    data_to_send_3 = f'$3 0 200\n'
    data_to_send_4 = f'$4 0 200\n'
    
    ser.write(data_to_send_1.encode())
    ser.write(data_to_send_2.encode())
    ser.write(data_to_send_3.encode())
    ser.write(data_to_send_4.encode())

def forward(ser, pid_array):
    
    pid_1, pid_2, pid_3, pid_4 = pid_array
    PWM_1 = pid_1.run_pid(ser, 1, 1, target_RPM=200)
    # RPM_2, PWM_2 = pid_2.run_pid(ser, 2, 1, target_RPM=200)
    PWM_3 = pid_3.run_pid(ser, 3, 1, target_RPM=200)
    PWM_4 = pid_4.run_pid(ser, 4, 1, target_RPM=200)
    # PWM2 = PWM_1
    # data_to_send_2 = f'$2 1 {PWM2}\n'
    # ser.write(data_to_send_2.encode())

def backward(ser, pid_array):

    pid_1, pid_2, pid_3, pid_4 = pid_array
    PWM_1 = pid_1.run_pid(ser, 1, 2, target_RPM=200)
    # RPM_2, PWM_2 = pid_2.run_pid(ser, 2, 2, target_RPM=200)
    PWM_3 = pid_3.run_pid(ser, 3, 2, target_RPM=200)
    PWM_4 = pid_4.run_pid(ser, 4, 2, target_RPM=200)
    
    PWM2 = PWM_1
    data_to_send_2 = f'$2 2 {PWM2}\n'
    ser.write(data_to_send_2.encode())

def turnLeft(ser, pid_array):

    pid_1, pid_2, pid_3, pid_4 = pid_array
    PWM_1 = pid_1.run_pid(ser, 1, 2, target_RPM=200)
    # RPM_2, PWM_2 = pid_2.run_pid(ser, 2, 1, target_RPM=200)
    PWM_3 = pid_3.run_pid(ser, 3, 1, target_RPM=200)
    PWM_4 = pid_4.run_pid(ser, 4, 2, target_RPM=200)

    PWM2 = PWM_1
    data_to_send_2 = f'$2 1 {PWM2}\n'
    ser.write(data_to_send_2.encode())

def turnRight(ser, pid_array):

    pid_1, pid_2, pid_3, pid_4 = pid_array
    PWM_1 = pid_1.run_pid(ser, 1, 1, target_RPM=200)
    # RPM_2, PWM_2 = pid_2.run_pid(ser, 2, 2, target_RPM=200)
    PWM_3 = pid_3.run_pid(ser, 3, 2, target_RPM=200)
    PWM_4 = pid_4.run_pid(ser, 4, 1, target_RPM=200)

    PWM2 = PWM_1
    data_to_send_2 = f'$2 2 {PWM2}\n'
    ser.write(data_to_send_2.encode())

def shiftLeft(ser, pid_array):

    pid_1, pid_2, pid_3, pid_4 = pid_array
    PWM_1 = pid_1.run_pid(ser, 1, 2, target_RPM=200)
    # RPM_2, PWM_2 = pid_2.run_pid(ser, 2, 1, target_RPM=200)
    PWM_3 = pid_3.run_pid(ser, 3, 2, target_RPM=200)
    PWM_4 = pid_4.run_pid(ser, 4, 1, target_RPM=200)

    PWM2 = PWM_1
    data_to_send_2 = f'$2 1 {PWM2}\n'
    ser.write(data_to_send_2.encode())

def shiftRight(ser, pid_array):

    pid_1, pid_2, pid_3, pid_4 = pid_array
    PWM_1 = pid_1.run_pid(ser, 1, 1, target_RPM=200)
    # RPM_2, PWM_2 = pid_2.run_pid(ser, 2, 2, target_RPM=200)
    PWM_3 = pid_3.run_pid(ser, 3, 1, target_RPM=200)
    PWM_4 = pid_4.run_pid(ser, 4, 2, target_RPM=200)

    PWM2 = PWM_1
    data_to_send_2 = f'$2 2 {PWM2}\n'
    ser.write(data_to_send_2.encode())

def recieveMessage(ser):

    received_data = ser.readline().decode().strip()
    print(received_data, type(received_data))

def main():

    pass

if __name__ == '__main__':

    main()