'''
Mostra valores da antena
'''

import serial

ser = serial.Serial('/dev/ttyUSB0')

while True:
    if ser.in_waiting:
        bs = ser.read(ser.in_waiting)

        bs = '/'.join([f'0x{b:x}' for b in bs])
        print(bs)

