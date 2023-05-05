import serial, time, tkinter as tk, PIL.ImageGrab as ImageGrab,numpy as np,csv


root = tk.Tk()
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
root.destroy()
class Ordinator:
    """get the average color of 8 boxes on the screen so that I can do less math on arduino"""
    def __init__(self,sw,sh):
        self.screenW = sw
        self.n = 10
        self.screenH = sh
        self.top_left = tuple(map(int, (0, 0, 0.33 * self.screenW, 0.33 * self.screenH)))
        self.top_right = tuple(map(int, (0.66 * self.screenW, 0, self.screenW, 0.33 * self.screenH)))
        self.top_middle = tuple(map(int, (0.33 * self.screenW, 0, 0.66 * self.screenW, 0.33 * self.screenH)))
        self.middle_left = tuple(map(int, (0, 0.33 * self.screenH, 0.33 * self.screenW, 0.66 * self.screenH)))
        self.middle_right = tuple(map(int, (0.66 * self.screenW, 0.33 * self.screenH, self.screenW, 0.66 * self.screenH)))
        self.bottom_left = tuple(map(int, (0, 0.66 * self.screenH, 0.33 * self.screenW, self.screenH)))
        self.bottom_middle = tuple(map(int, (0.33 * self.screenW, 0.66 * self.screenH, 0.66 * self.screenW, self.screenH)))
        self.bottom_right = tuple(map(int, (0.66 * self.screenW, 0.66 * self.screenH, self.screenW, self.screenH)))
        self.boxes = [self.top_right,self.top_middle,self.top_left,self.middle_left,self.bottom_left,self.bottom_middle,self.bottom_right,self.middle_right]
    def get_average_color(self,box,pixels):
        print(box)
        """Uses PIL to get the average color of a box on the screen"""
        pixels = [pixels[x,y] for x in range(box[0],box[2],self.n) for y in range(box[1],box[3],self.n)]
        pixels = np.array(pixels)
        avg_r,avg_g,avg_b  =map(lambda x: x.zfill(3),[str(np.mean(pixels[:,0],dtype=np.int64)),str(np.mean(pixels[:,1],dtype=np.int64)),str(np.mean(pixels[:,2],dtype=np.int64))])
        return avg_r+ avg_g +avg_b
    #turn get_all_colors into a class method
    def get_all_colors(self,n: int):
        self.n = n
        """Returns a string of all the colors in the order of the boxes"""
        self.pixels = (ImageGrab.grab().load())
        return ''.join(map(self.get_average_color,self.boxes,[self.pixels]*8)).rstrip()
Ord = Ordinator(screen_width,screen_height)
ser = serial.Serial(port='/dev/tty.usbmodem14201', baudrate=9600)
time.sleep(2)
while True:
    x = (Ord.get_all_colors(10))
    ser.write(bytes(x, 'utf-8'))
    print(x)
    time.sleep(.8)
ser.close()

