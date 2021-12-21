import serial
import time
from cal import *

ser = serial.Serial('/dev/serial/by-id/usb-Arduino__www.arduino.cc__0043_75830333438351C08092-if00',9600)
speed = 0
flag=0


def dir_Cal():
    try:
        cmd, flag = cal()
        cmd = cmd.encode('ascii')        
    except:
        cmd = 'B'.encode('ascii')
        flag = 0
    
    return cmd, flag
    

while True:
    cmd, flag = dir_Cal()
    print(flag)
    if(flag == 1):
        time.sleep(3)
        ser.write(cmd)
        print("QR")

        continue
    
    print("My cmd is %s" % cmd)
    ser.write(cmd)
    time.sleep(0.1)

    
