import serial, time, tkinter as tk, PIL.ImageGrab as ImageGrab,numpy as np


root = tk.Tk()
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
root.destroy()
class Ordinator:
    """get the average color of 8 boxes on the screen so that I can do less math on arduino"""
    def __init__(self,sw,sh):
        self.screenW = sw
        self.screenH = sh
        self.top_left = tuple(map(int, (0, 0, 0.5 * self.screenW, 0.5 * self.screenH)))
        self.top_right = tuple(map(int, (0.5 * self.screenW, 0, self.screenW, 0.5 * self.screenH)))
        self.bottom_left = tuple(map(int, (0, 0.5 * self.screenH, 0.5 * self.screenW, self.screenH)))
        self.bottom_right = tuple(map(int, (0.5 * self.screenW, 0.5 * self.screenH, self.screenW, self.screenH)))
        self.middle_left = tuple(map(int, (0, 0.25 * self.screenH, 0.5 * self.screenW, 0.75 * self.screenH)))
        self.middle_right = tuple(map(int, (0.5 * self.screenW, 0.25 * self.screenH, self.screenW, 0.75 * self.screenH)))
        self.top_middle = tuple(map(int, (0.25 * self.screenW, 0, 0.75 * self.screenW, 0.5 * self.screenH)))
        self.bottom_middle = tuple(map(int, (0.25 * self.screenW, 0.5 * self.screenH, 0.75 * self.screenW, self.screenH)))
        self.boxes = [self.top_right,self.top_middle,self.top_left,self.middle_left,self.bottom_left,self.bottom_middle,self.bottom_right,self.middle_right]
    def get_average_color(self,box,pixels):
        """Uses PIL to get the average color of a box on the screen"""
        pixels = [pixels[x,y] for x in range(box[0],box[2],2) for y in range(box[1],box[3],2)]
        pixels = np.array(pixels)

        #get the average color of the box
        avg_r = int(np.mean(pixels[:,0]))
        avg_g = int(np.mean(pixels[:,1]))
        avg_b = int(np.mean(pixels[:,2]))
        #if var doesnt have 3 digits add 0s in front
        if len(str(avg_r)) < 3:
            avg_r = str(avg_r).zfill(3)
        if len(str(avg_g)) < 3:
            avg_g = str(avg_g).zfill(3)
        if len(str(avg_b)) < 3:
            avg_b = str(avg_b).zfill(3)
        #return as rgb ex: 255010255
        return str(avg_r) + str(avg_g) + str(avg_b)
    #turn get_all_colors into a class method
    def get_all_colors(self):
        """Returns a string of all the colors in the order of the boxes"""
        self.pixels = (ImageGrab.grab().load())
        return ''.join(map(self.get_average_color,self.boxes,[self.pixels]*8))

Ord = Ordinator(screen_width,screen_height)

while True:
    #ser = serial.Serial('/dev/tty.usbmodem14201', 230400)
    #ser.write(Ord.get_all_colors().encode())
    print(Ord.get_all_colors())
    #ser.close()
