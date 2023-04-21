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
        #print every pixel 
    #turn get_average_color into a class method
    def get_average_color_3(self,box):
        """Uses PIL to get the average color of a box on the screen"""
        #get screenshot with all windows that are pulled up not just background
        pixels = np.array(ImageGrab.grab().crop(box).getdata())
        #reshape to box      
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
    def get_average_color(self,box,pixels):
        """Uses PIL to get the average color of a box on the screen"""
        #get screenshot with all windows that are pulled up not just background
        #crop to box
        pixels = np.array(pixels.crop(box))
        #get the average color of the box
        #remove 4th value in array
        pixels = pixels[:,0:3]
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
        print(self.pixels)
        #print top_left of self.pixels
        return (self.get_average_color(self.top_right,self.pixels)+self.get_average_color(self.top_middle,self.pixels) +  self.get_average_color(self.top_left,self.pixels) + self.get_average_color(self.middle_left,self.pixels) +self.get_average_color(self.bottom_left,self.pixels) +  self.get_average_color(self.bottom_middle,self.pixels) + self.get_average_color(self.bottom_right,self.pixels) +  self.get_average_color(self.middle_right,self.pixels))
    #example output 255  ffffff|ffffff|ffffff|ffffff|ffffff|ffffff|ffffff|ffffff
    #or 255255255255255255255255255255255255255255255255255255255255255255255255
Ord = Ordinator(screen_width,screen_height)

while True:
    #ser = serial.Serial('/dev/tty.usbmodem14201', 230400)
    #ser.write(Ord.get_all_colors().encode())
    print(Ord.get_all_colors())
    #ser.close()
    time.sleep(0.2)
