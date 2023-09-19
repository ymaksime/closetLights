#!/usr/bin/python3

import serial, sys, time

class PIC:

    def __init__(s, port, baud=115200, timeout=1):
        s._ser = serial.Serial()
        s._ser.baudrate = baud
        s._ser.port = port

        s._ser.parity = serial.PARITY_NONE
        s._ser.bytesize = serial.EIGHTBITS
        s._ser.stopbits = serial.STOPBITS_ONE
        s._ser.timeout = timeout

        try:
            s._ser.open()
            print("Connected to serial port")
        except:
            print("Unable to connect to serial port")
            sys.exit()

        # Make sure the echo is disabled
        s.disable_echo()

        # Also make sure the DAC is set to zero
        s.set_dac(0)


    def read(s, command):
        s._ser.write((command + '\r').encode())
        s._ser.flush()
        time.sleep(0.1)

        # readlines() return a list of one entry which is your string
        # take and remove the newline
        result = s._ser.readlines()[0].strip()
        return result.decode()

    def write(s, command):
        s._ser.write((command + '\r').encode())
        s._ser.flush()
        time.sleep(0.1)

    # Channel 5 = Photosensor
    def _select_adc_chan_5(s):
        s.write('ADC5')

    # Channel 7 = Input voltage
    def _select_adc_chan_7(s):
        s.write('ADC7')

    def read_power_source(s):
        """ Gets the latest value of ADC channel 7 which connected to the 12V
            power supply via a 200K-10K resistor divider.  The returned value
            is a HEX representation of the 10-bit ADC reading (1024).  The ADC is
            internally referenced to a 2048 mV source, which gives us the
            following conversion formula:

            val_mV = ADC_reading * (2048 mV / 1024) = ADC_reading * 2

            First, we need to select ADC channel 7 and then quiry the ADC reading
        """
        s._select_adc_chan_7()
        # The returned value here is a hex string
        val_string = s.read('ADCR')
        # Convert it to integer
        val_int = int(val_string, 16)
        return val_int * 2

    def read_sensor(s):
        """ Gets the latest value of ADC channel 5 which connected to the
            photo resistor divider.  The returned value is a HEX
            representation of the 10-bit ADC reading (1024).  The ADC is
            internally referenced to a 2048 mV source, which gives us the
            following conversion formula:

            val_mV = ADC_reading * (2048 mV / 1024) = ADC_reading * 2

            First, we need to select ADC channel 5 and then quiry the ADC reading
        """
        s._select_adc_chan_5()
        # The returned value here is a hex string
        val_string = s.read('ADCR')
        # Convert it to integer
        val_int = int(val_string, 16)
        return val_int * 2

    def get_version(s):
        return s.read('VERG')

    def disable_echo(s):
        s.write('ECHO 0')

    def enable_echo(s):
        s.write('ECHO 1')

    def set_dac(s, dac_value):
        """ Sets the DAC to the requested value.  Our DAC is 8-bit, so we need
            to make sure we stay within the boundaries.  The expected format
            is an unsigned 8-bit value.
        """
        if not isinstance(dac_value, int):
            raise TypeError("Expected an integer")
        if 0 <= dac_value <= 255:
            s.write('DACS ' + str(dac_value))
            print("dac value = {}".format(dac_value))
        else:
            raise ValueError("Expected an 8-bit value")


    def close(s):
        s._ser.close()
        print("Closed serial connection to " + s._ser.port)

    def __del__(s):
        s.close()
