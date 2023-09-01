#!/usr/bin/python3

import argparse
import pic_driver


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description = "Allows you to continuously read ADC values")
    parser.add_argument('-p', '--port', action='store',
                        dest="port", required=True,
                        help="Serial port that the module is connected to (ex:/dev/ttyUSB0)")
    args = parser.parse_args()


# Connect to the module
module = pic_driver.PIC(args.port)

module.close()
