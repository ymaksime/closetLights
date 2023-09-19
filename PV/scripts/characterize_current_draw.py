#!/usr/bin/env python3

'''Characterizes the current draw of the module at different voltage levels.

Usage:
    1. Make sure you have the latest pyteq repo available
    2. Run 'export PYTHONPATH="${PYTHONPATH}:/path/to/pyteq/"'
    3. Connect to Keithley DC power supply to the board
    4. Run the script

YAML files:
    An example of a YAML can be found in pyteq/examples
    product_info:
        vendor: 'Keithley'
        model: '2280S'
    connection:
        type: 'lan'
        ip_addr: '10.205.94.224'
        port: '5025'

Test vectors:
    V = {10:1:30}
    Amax = 215mA
'''

import time
import argparse
import os
import csv

from pyteq.instrument.devicemap import DeviceMap

import pic_driver

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description = "Characterizes LED current")
    parser.add_argument('-p', '--port', action='store',
                        dest="port", required=True,
                        help="Serial port that the module is connected to (ex:/dev/ttyUSB0)")
    parser.add_argument('-d', '--config_dc', action="store",
                        dest="config_dc", required=True,
                        help="This is a YAML config files for Keithely DC Power supply")
    parser.add_argument('-o', '--out_file', action="store",
                        dest="filename", required=True,
                        help="CSV file to store the data")
    args = parser.parse_args()


# Connect to the module
module = pic_driver.PIC(args.port)

# Connect to the DC Power supply and prep it
dc_supply = DeviceMap.connect(args.config_dc)

def collect_trace():
    #dc_supply.output_off()
    # Clear the trace
    dc_supply.trace_clear()
    # Find out how deep is the buffer
    bufferLength = dc_supply.trace_points()
    # Make sure the feed control is set to ALWAYS
    dc_supply.trace_set_feed_control_always()
    # Enable the output
    dc_supply.trigger_continuous_on()
    #dc_supply.output_on()

def hw_setup():
    # Disable the output
    dc_supply.output_off()
    # Before we begin, make sure teh power source is at zero
    dc_supply.set_voltage(0)
    # Also cap the current at 250mA
    dc_supply.set_current(0.250)
    # Set resolution to 5.5 digits (mid point)
    dc_supply.set_resolution_concurrent(5)
    # Enable the output before altering the settings
    dc_supply.output_on()
    # Turn ON the auto clear for the trace
    dc_supply.trace_clear_auto_enable()
    # Use SENSE as our source for the trace
    dc_supply.trace_set_feed_sense()
    # Set the depth of the trace
    dc_supply.trace_set_points(200)
    # Collect a couple of points before the trigger
    dc_supply.trace_set_trigger_offset(2)
    # Use rising current as our trigger
    dc_supply.trace_trigger_current_rise()
    dc_supply.trace_set_trigger_current_level(0.007)
    dc_supply.trace_trigger_current_enable()
    # Setup the statistical functions
    # We need only the MAX readings
    dc_supply.stats_set_format(["MAXIMUM"])
    # We need both the value and the index in the array
    dc_supply.stats_set_format_elements(["READ","RNUM"])
    # We need only the current measurements
    dc_supply.stats_set_function_current()
    dc_supply.stats_enable()
    time.sleep(1)

def get_max_current():
    # Find out the maximum reading for the current measurement
    currentMax = dc_supply.stats_immediate().split(",")
    rnumber = int(currentMax[1][1:5])
    current = float(currentMax[0])
    # Return in milliampts
    return current * 1000

def get_voltage():
    currentMax = dc_supply.stats_immediate().split(",")
    rnumber = int(currentMax[1][1:5])
    current = float(currentMax[0])
    voltage = float(dc_supply.trace_get_item(rnumber, ["SOURCE"]))
    return voltage

def test_config(volts):
    dc_supply.output_off()
    dc_supply.set_voltage(volts)
    dc_supply.trigger_continuous_on()
    dc_supply.output_on()
    time.sleep(2)


def run_acquisition(csvwriter):
    temp_list = []
    # Out test vector for DAC is {0:1:30}
    dac_list = range(1,30,1)

    # First get the current consumption when the lights are OFF
    module.set_dac(0)
    time.sleep(0.2)
    collect_trace()
    idle_current = get_max_current()

    for i in dac_list:
        print("---> Setting DAC at {} counts".format(i))
        temp_list.clear()
        temp_list.append(i)
        module.set_dac(i)
        time.sleep(0.2)

        collect_trace()

        voltage = get_voltage()
        temp_list.append(voltage)
        # Get the current reading and subtract the "idle" current
        max_current = get_max_current() - idle_current
        temp_list.append(max_current)

        print("### Voltage = {}V, Current = {}A".format(voltage, max_current))
        csvwriter.writerow(temp_list)

        # Do not go over 215mA
        if max_current >= 215:
            return
        time.sleep(1)


# prep the file
if os.path.exists(args.filename):
    append_write = 'a' # append to the existing file
else:
    append_write = 'w'

with open(args.filename, append_write, newline='') as csvfile:
    writer = csv.writer(csvfile, delimiter=',')
    # prep the hardware
    hw_setup()
    # Our test vector for voltages is {10:1:30}
    voltage_list = range(10,20,1)
    for v in voltage_list:
        print("Testing at {}V".format(v))
        # Set the voltage
        test_config(v)
        # Prep the header for this run of tests
        csvfile.write("Setting voltage to {}V\r\n".format(v))
        csvfile.write("DAC, Voltage V, Current A\r\n")
        # Get the readings
        run_acquisition(writer)
        csvfile.write("\r\n\r\n")
        time.sleep(5)


module.set_dac(0)
module.close()

dc_supply.set_voltage(0)
dc_supply.output_off()
