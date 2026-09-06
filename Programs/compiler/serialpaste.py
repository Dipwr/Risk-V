import time, serial

ser = serial.Serial('/dev/ttyUSB1', 115200)

with open('./out/program.hex', 'r') as f:
    for char in f.read():
        ser.write(char.encode())
        time.sleep(0.01)  # delay gives CPU time to draw font