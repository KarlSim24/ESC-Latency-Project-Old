import serial
import numpy as np
import matplotlib.pyplot as pyplot
import time

ser = serial.Serial('/dev/cu.usbmodem14101',9600)
# ser = serial.Serial('/dev/cu.Bluetooth-Incoming-Port',9600)

time.sleep(2)
ser.flushInput()
ser.flushOutput()

arm = 700

data = []

# to get time, use time.time()
t = time.time()
print(t)

# send command to arm motor
ser.write(str(arm).encode())
time.sleep(1)

# run at speed 1
speed1 = input("Enter value between 1000 and 2000")
while 1:
    ser.write(str(speed1).encode())

# time.sleep(10)

# # run at speed 2
# ser.write(str(speed2).encode())
# time.sleep(10)

# # stop motor
# ser.write(str(0).encode())
# print("done")
ser.close()
