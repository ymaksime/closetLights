#!/usr/bin/python3

import serial, sys

class PIC:

    def __init__(s, port, baud=115200, timeout=1):
        s._ser = serial.Serial()
        s._ser.bautdrate = baud
        s._ser.port = port

        s._ser.parity = serial.PARITY_NONE
        s._ser.bytesize = serial.EIGHTBITS
        s._ser.stopbits = serial.STOPBITS_ONE
        s._ser.timeout = timeout

        s._version = {'CPU':0}

        try:
            s._ser.open()
            print("Connected to serial port")
        except:
            print("Unable to connect to serial port")
            sys.exit()

    def close(s):
        s._ser.close()

    def __del__(s):
        s.close()
