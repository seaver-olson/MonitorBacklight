import serial, time, tkinter as tk, PIL.ImageGrab as ImageGrab
#get screen size
root = tk.Tk()
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()
#make sure every value in tuple is int
top_left = tuple(map(int, (0, 0, 0.5 * screen_width, 0.5 * screen_height)))
top_right = tuple(map(int, (0.5 * screen_width, 0, screen_width, 0.5 * screen_height)))
bottom_left = tuple(map(int, (0, 0.5 * screen_height, 0.5 * screen_width, screen_height)))
bottom_right = tuple(map(int, (0.5 * screen_width, 0.5 * screen_height, screen_width, screen_height)))
middle_left = tuple(map(int, (0, 0.25 * screen_height, 0.5 * screen_width, 0.75 * screen_height)))
middle_right = tuple(map(int, (0.5 * screen_width, 0.25 * screen_height, screen_width, 0.75 * screen_height)))
top_middle = tuple(map(int, (0.25 * screen_width, 0, 0.75 * screen_width, 0.5 * screen_height)))
bottom_middle = tuple(map(int, (0.25 * screen_width, 0.5 * screen_height, 0.75 * screen_width, screen_height)))
#rename the variables like your a pirate

# Define a function to calculate the average pixel color in a given section of the screen
def get_average_color(box):

    #take image of screen first and then crop
    pixels = ((ImageGrab.grab()).crop(box)).getdata()      
    num_pixels = len(pixels) 
    r = g = b = 0                  
    for pixel in pixels:
        r += pixel[0]             
        g += pixel[1]     
        b += pixel[2]   
    avg_r, avg_g, avg_b = [x // num_pixels for x in (r, g, b)]

    return str('%02x%02x%02x' % (avg_r, avg_g, avg_b))
    

def get_all_colors():return (get_average_color(top_left) + "|" + get_average_color(top_right) + "|" + get_average_color(bottom_left) + "|" + get_average_color(bottom_right) + "|" + get_average_color(middle_left) + "|" + get_average_color(middle_right) + "|" + get_average_color(top_middle) + "|" + get_average_color(bottom_middle))
#ex output of get_all_colors() = "ffffff|ffffff|ffffff|ffffff|ffffff|ffffff|ffffff|ffffff"
while True:
    #if serial port is available, send the data
    if serial.Serial('/dev/tty.usbmodem14201', 9600):
        ser = serial.Serial('/dev/tty.usbmodem14201', 9600)
        ser.write(get_all_colors().encode())
        ser.close()
    time.sleep(0.1)
