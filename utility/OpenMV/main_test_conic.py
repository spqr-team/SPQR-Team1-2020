# color tracking with conic mirror - By: EmaMaker - wed 15 jan 2020
# Based on:
# color tracking - By: paolix - ven mag 18 2018

# Automatic RGB565 Color Tracking Example
#
import sensor, image, time, pyb, math

from pyb import UART
uart = UART(3,19200, timeout_char = 1000)


# LED Setup ##################################################################

red_led = pyb.LED(1)
green_led = pyb.LED(2)
blue_led = pyb.LED(3)

red_led.off()
green_led.off()
blue_led.on()
##############################################################################


#thresholds = [  (30, 100, 15, 127, 15, 127),    # generic_red_thresholds
#                (30, 100, -64, -8, -32, 32),    # generic_green_thresholds
#                (0, 15, 0, 40, -80, -20)]       # generic_blue_thresholds

#thresholds = [  (54, 93, -10, 25, 55, 70),    # thresholds yellow goal
#                (30, 45, 1, 40, -60, -19)]    # thresholds blue goal
#
thresholds = [  (30, 70, -12, 19, 41, 68)  ,    # thresholds yellow goal
                (0, 70, -2, 34, -59, -21)]  # thresholds blue goal (6, 31, -15, 4, -35, 0)

roi = (0, 6, 318, 152)

# Camera Setup ###############################################################
'''sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)         # must be turned off for color tracking
sensor.set_auto_whitebal(False)     # must be turned off for color tracking
sensor.set_auto_exposure(False, 10000)
#sensor.set_backlight(1)
#sensor.set_brightness(+2)
#sensor.set_windowing(roi)
clock = time.clock()'''

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.set_contrast(+2)
sensor.set_saturation(+1)
sensor.set_brightness(-2)
sensor.set_quality(0)
sensor.set_auto_exposure(False, 6000)
sensor.set_auto_gain(True)
sensor.skip_frames(time = 300)

clock = time.clock()
##############################################################################



# [] list
# () tupla

'''while(True):
    clock.tick()
    img = sensor.snapshot()'''

while(True):
    clock.tick()

    blue_led.off()

    tt_yellow = [(0,999,0,1)]     ## creo una lista di tuple per il giallo, valore x = 999 : non trovata
    tt_blue = [(0,999,0,2)]       ## creo una lista di tuple per il blue, valore x = 999 : non trovata

    img = sensor.snapshot()
    for blob in img.find_blobs(thresholds, pixels_threshold=150, area_threshold=150, merge = True):
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())

        if (blob.code() == 1):
            tt_yellow = tt_yellow +  [ (blob.area(),blob.cx(),blob.cy(),blob.code() ) ]
        if (blob.code() == 2):
            tt_blue = tt_blue +  [ (blob.area(),blob.cx(),blob.cy(),blob.code() ) ]

    tt_yellow.sort(key=lambda tup: tup[0])  ## ordino le liste
    tt_blue.sort(key=lambda tup: tup[0])    ## ordino le liste

    ny = len(tt_yellow)
    nb = len(tt_blue)

    '''Yellow'''
    area,cx,cy,code = tt_yellow[ny-1]    # coordinata x del piu' grande y se montata al contrario
    cx = img.width() / 2 - cx
    cy = img.height() / 2 - cy
    angle = math.pi/2 - math.atan2(cy, cx)
    dist = math.sqrt(cx*cx + cy*cy)
    string_yellow = "Y"+str(cx)+" | "+str(cy)+" | "+str(angle)+" | "+str(dist)+str(area)+"y"
    print (string_yellow)   # test on serial terminal

    '''Blue'''
    area,cx,cy,code = tt_blue[nb-1]    # coordinata x del piu' grande y se montata al contrario
    cx = img.width() / 2 - cx
    cy = img.height() / 2 - cy
    angle = math.pi/2 - math.atan2(cy, cx)
    dist = math.sqrt(cx*cx + cy*cy)
    string_blue = "B"+str(cx)+" | "+str(cy)+" | |"+str(angle)+" | "+str(dist)+str(area)+"b"
    print (string_blue)   # test on serial terminal

    #print ("..................................")

print(clock.fps())
