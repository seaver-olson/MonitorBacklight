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
TRavg = pyautogui.screenshot(region=(0,0,1920/2,1080/2)).getcolors()
TLavg = pyautogui.screenshot(region=(1920/2,0,1920/2,1080/2)).getcolors()
BRavg = pyautogui.screenshot(region=(0,1080/2,1920/2,1080/2)).getcolors()
BLavg = pyautogui.screenshot(region=(1920/2,1080/2,1920/2,1080/2)).getcolors()
Tavg = pyautogui.screenshot(region=(0,0,1920,1080/2)).getcolors()
Bavg = pyautogui.screenshot(region=(0,1080/2,1920,1080/2)).getcolors()
Lavg = pyautogui.screenshot(region=(0,0,1920/2,1080)).getcolors()
Ravg = pyautogui.screenshot(region=(1920/2,0,1920/2,1080)).getcolors()
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

