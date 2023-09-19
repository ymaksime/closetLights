#!/usr/bin/env python3

'''
    mA = 7.818(DAC) + 5.649
'''

import matplotlib.pyplot as plt
import numpy as np

# x axis values
# These are the DAC values (8-bit DAC)
x = np.linspace(0,255,256)
x2 = np.linspace(0,1999, 2000)

# y axis value
# These are corresponding mA values for DAC setting
a = 7.814
b = -1.065
y = a * x + b
y2 = (x2 - b) / a

# Get the look-up table of ints
lookup_milli_amps = np.rint(y)
lookup_milli_amps = lookup_milli_amps.astype(int)


lookup_dacs = np.floor(y2)
lookup_dacs = lookup_dacs.astype(int)

lookup_dacs.tofile('dacs.txt', sep=', ')
lookup_milli_amps.tofile('milli_amps.txt', sep=', ')


plt.figure(1)
# plotting the points
plt.plot(x,y)

# naming the axis
plt.xlabel('DAC Value')
# naming the y axis
plt.ylabel('milli Amps')

# giving a title to the plot
plt.title('DAC vs mA')

plt.figure(2)
plt.plot(x2,lookup_dacs)
plt.xlabel('milli Amps')
plt.ylabel('DAC Value')
plt.title('mA vs DAC')

# function to show the plot
plt.show()

