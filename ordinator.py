from PIL import ImageGrab#used to take screenshot
import tkinter as tk#used to get screen size

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
    #convert rgb to hex
    return '{:02x}{:02x}{:02x}'.format(avg_r, avg_g, avg_b)
    
 

#function that combines all average colors into string in hex format ex : ffffff|ffffff|ffffff|ffffff|ffffff|ffffff|ffffff|ffffff
def get_all_colors():
    return (get_average_color(top_left) + "|" + 
            get_average_color(top_right) + "|" + get_average_color(bottom_left) 
        + "|" + get_average_color(bottom_right) + "|" + get_average_color(middle_left) 
        + "|" + get_average_color(middle_right) + "|" + get_average_color(top_middle) 
        + "|" + get_average_color(bottom_middle))
print(get_all_colors())
