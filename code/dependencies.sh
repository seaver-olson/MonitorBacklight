echo "Installing dependencies..."
sudo apt-get install python3-pip
sudo python3 -m pip install --upgrade pip setuptools wheel
sudo pip3 install pyserial
sudo pip3 install numpy
sudo pip3 install pillow
sudo pip3 install tkinter
sudo pip3 install csv
#if all dependencies installed without error print success message else print error message
if [ $? -eq 0 ]; then
    echo "Dependencies installed successfully"
else
    echo "Error installing dependencies"
fi

