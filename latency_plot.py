import pyserial
import time
import matplotlib.pyplot as pyplot
import numpy as np

ser = serial.Serial('/dev/cu.usbmodem14101',9600)
time.sleep(2)

data = []
stop = 0;

# TODO: adjust millis() to allow python to start motor
ser.write(b'start'); #begin arduino loop

# while stop == 0:
for i in range(100):
    byte = ser.readline()
    value = byte.decode()
    if value == 'stop':
        stop = 1; #stop plotting
    value = value.strip()
    data.append(val)
ser.close
plt.plot(data)

    
    


