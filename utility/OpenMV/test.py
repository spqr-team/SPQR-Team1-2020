# color tracking with conic mirror - By: EmaMaker - wed 15 jan 2020
# Based on:
# color tracking - By: paolix - ven mag 18 2018

# Automatic RGB565 Color Tracking Example
#

import sensor, image, time, pyb, math

from pyb import UART
uart = UART(3,19200, timeout_char = 1000)

START_BYTE = chr(105) #'i'
END_BYTE = chr(115) #'s'
BYTE_UNKNOWN = chr(116) #'t'

y_found = False
b_found = False

#From Arduino Documentation at: https://www.arduino.cc/reference/en/language/functions/math/map/
def val_map(x, in_min, in_max, out_min, out_max):
    x = int(x)
    in_min = int(in_min)
    in_max = int(in_max)
    out_min = int(out_min)
    out_max = int(out_max)
    return int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)


# LED Setup ##################################################################
red_led = pyb.LED(1)
green_led = pyb.LED(2)
blue_led = pyb.LED(3)

red_led.off()
green_led.off()
blue_led.on()
##############################################################################


thresholds = [  (71, 100, -24, 12, 57, 99),    # thresholds yellow goal
                (38, 55, -33, -1, 0, 26)]  # thresholds blue goal (6, 31, -15, 4, -35, 0)

roi = (0, 6, 318, 152)

# Camera Setup ###############################################################
'''sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)         # must be turned off for color tracking
sensor.set_auto_whitebal(False)     # must be turned off for color tracking
sensor.set_auto_exposure(False, 10000) vbc
#sensor.set_backlight(1)
#sensor.set_brightness(+2)
#sensor.set_windowing(roi)
clock = time.clock()'''

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.set_contrast(3)
sensor.set_saturation(3)
sensor.set_brightness(0)
sensor.set_quality(0)
sensor.set_auto_whitebal(False)
sensor.set_auto_exposure(False, 5500)
sensor.set_auto_gain(True)
sensor.skip_frames(time = 300)

clock = time.clock()
##############################################################################


while(True):
    clock.tick()
    uart.write(42)

