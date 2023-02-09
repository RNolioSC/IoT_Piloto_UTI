'''
Mostra valores da antena
'''

import serial
from time import sleep

ser = serial.Serial('/dev/ttyUSB0')

try:
    while True:
        input('Aperte enter para enviar')

        bs = b'\x7c\xff\xff\x10\x32\x00\x43'
        ser.write(bs)

        print(f'Enviado: {bs.hex("/")}')

        sleep(0.1)

        if not ser.in_waiting:
            print('Nao recebi nada')
        else:
            bs = ser.read(ser.in_waiting)

            print(f'Recebido: {bs.hex("/")}')

        print()
except:
    ser.close()
