#send strings to arduinio serial port
import os
import serial
#import module to read color of pixels on screen
os.environ['DISPLAY'] = ':0'
import pyautogui

#divide screen into 8 sections
#TR, TL, BR, BL, T, B, L, R
#TR = top right, TL = top left, BR = bottom right, BL = bottom left, T = top, B = bottom, L = left, R = right
#each section is 1/8 of the screen
#find average color of each section


#find average color of each section
TRavg = pyautogui.screenshot(region=(0,0,1920/2,1080/2))
TLavg = pyautogui.screenshot(region=(1920/2,0,1920/2,1080/2))
BRavg = pyautogui.screenshot(region=(0,1080/2,1920/2,1080/2))
BLavg = pyautogui.screenshot(region=(1920/2,1080/2,1920/2,1080/2))
Tavg = pyautogui.screenshot(region=(0,0,1920,1080/2))
Bavg = pyautogui.screenshot(region=(0,1080/2,1920,1080/2))
Lavg = pyautogui.screenshot(region=(0,0,1920/2,1080))
Ravg = pyautogui.screenshot(region=(1920/2,0,1920/2,1080))
TRavg, TLavg, BRavg, BLavg, Tavg, Bavg, Lavg, Ravg = TRavg.getcolors(TRavg.size[0]*TRavg.size[1]), TLavg.getcolors(TLavg.size[0]*TLavg.size[1]), BRavg.getcolors(BRavg.size[0]*BRavg.size[1]), BLavg.getcolors(BLavg.size[0]*BLavg.size[1]), Tavg.getcolors(Tavg.size[0]*Tavg.size[1]), Bavg.getcolors(Bavg.size[0]*Bavg.size[1]), Lavg.getcolors(Lavg.size[0]*Lavg.size[1]), Ravg.getcolors(Ravg.size[0]*Ravg.size[1])
#print all colors
print(TRavg)
print(TLavg)
print(BRavg)
print(BLavg)
print(Tavg)
print(Bavg)
print(Lavg)
print(Ravg)



ser = serial.Serial('/dev/ttyACM0', 9600)

