import serial, time, tkinter as tk, PIL.ImageGrab as ImageGrab


root = tk.Tk()
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
root.destroy()
class Ordinator:
    """get the average color of 8 boxes on the screen so that I can do less math on arduino"""
    def __init__(self,screen_width,screen_height):
        self.screenW = screen_width
        self.screenH = screen_height
        self.top_left = tuple(map(int, (0, 0, 0.5 * self.screenW, 0.5 * self.screenH)))
        self.top_right = tuple(map(int, (0.5 * self.screenW, 0, self.screenW, 0.5 * self.screenH)))
        self.bottom_left = tuple(map(int, (0, 0.5 * self.screenH, 0.5 * self.screenW, self.screenH)))
        self.bottom_right = tuple(map(int, (0.5 * self.screenW, 0.5 * self.screenH, self.screenW, self.screenH)))
        self.middle_left = tuple(map(int, (0, 0.25 * self.screenH, 0.5 * self.screenW, 0.75 * self.screenH)))
        self.middle_right = tuple(map(int, (0.5 * self.screenW, 0.25 * self.screenH, self.screenW, 0.75 * self.screenH)))
        self.top_middle = tuple(map(int, (0.25 * self.screenW, 0, 0.75 * self.screenW, 0.5 * self.screenH)))
        self.bottom_middle = tuple(map(int, (0.25 * self.screenW, 0.5 * self.screenH, 0.75 * self.screenW, self.screenH)))
    #turn get_average_color into a class method
    def get_average_color(self,box):
        """Uses PIL to get the average color of a box on the screen"""
        pixels = ((ImageGrab.grab()).crop(box)).getdata()
        num_pixels = len(pixels)
        r = g = b = 0
        for pixel in pixels:
            r += pixel[0]
            g += pixel[1]
            b += pixel[2]
        avg_r, avg_g, avg_b = [x // num_pixels for x in (r, g, b)]
        return str('%02x%02x%02x' % (avg_r, avg_g, avg_b))
    #turn get_all_colors into a class method
    def get_all_colors(self):
        """Returns a string of all the colors in the order of the boxes"""
        return (self.get_average_color(self.top_left) + "|" + self.get_average_color(self.top_right) + "|" + self.get_average_color(self.bottom_left) + "|" + self.get_average_color(self.bottom_right) + "|" + self.get_average_color(self.middle_left) + "|" + self.get_average_color(self.middle_right) + "|" + self.get_average_color(self.top_middle) + "|" + self.get_average_color(self.bottom_middle))
    
Ord = Ordinator(screen_width,screen_height)
while True:
    ser = serial.Serial('/dev/tty.usbmodem14201', 9600)
    ser.write(Ord.get_all_colors().encode())
    ser.close()
    time.sleep(5)
