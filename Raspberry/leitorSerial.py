'''
Mostra valores da antena
'''

import serial
import mysql.connector

def write_to_db(tag):
        pass

if __name__ == "__main__":

        ser = serial.Serial('/dev/ttyUSB0')

        while True:
            if ser.in_waiting:
                #print("connected")
                bs = ser.read(ser.in_waiting)
                #print(bs)

                bs = '/'.join([f'0x{b:x}' for b in bs])
                #print(bs)
                bs = bs.removeprefix('0xcc/0xff/0xff/0x10/0x32/0xd/0x1/')
                lastchar = bs[-1]
                while lastchar != '/':
                        bs = bs[:-1]
                        lastchar = bs[-1]
                bs = bs[:-1] # remove '/'
                print(bs)
                bs = bs.removeprefix('0x')
                temp = bs.split('/0x')
                tag = ''
                for i in temp:
                        if len(i)<2:
                                tag+='0'
                        tag += i
                print(tag)
                write_to_db(tag)

