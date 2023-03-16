from PIL import ImageGrab

# Define the coordinates for each section of the screen
top_left = (0, 0, 640, 360)      # top left
top_right = (640, 0, 1280, 360)  # top right
bottom_left = (0, 360, 640, 720) # bottom left
bottom_right = (640, 360, 1280, 720) # bottom right
middle_left = (0, 180, 320, 540) # middle left
middle_right = (960, 180, 1280, 540) # middle right

# Define a function to calculate the average pixel color in a given section of the screen
def get_average_color(box):
    im = ImageGrab.grab(bbox=box)  
    pixels = im.getdata()         
    num_pixels = len(pixels)   
    r = g = b = 0                  
    for pixel in pixels:
        r += pixel[0]              # Add up the red values of all the pixels
        g += pixel[1]              # Add up the green values of all the pixels
        b += pixel[2]              # Add up the blue values of all the pixels
    avg_r = r // num_pixels        # Divide the total red value by the number of pixels to get the average
    avg_g = g // num_pixels        # Divide the total green value by the number of pixels to get the average
    avg_b = b // num_pixels        # Divide the total blue value by the number of pixels to get the average
    return (avg_r, avg_g, avg_b)   # Return the average RGB values as a tuple

# Call the function for each section of the screen and print the results
print("Top left:", get_average_color(top_left))
print("Top right:", get_average_color(top_right))
print("Bottom left:", get_average_color(bottom_left))
print("Bottom right:", get_average_color(bottom_right))
print("Middle left:", get_average_color(middle_left))
print("Middle right:", get_average_color(middle_right))
