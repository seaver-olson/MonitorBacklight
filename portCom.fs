open System.IO.Ports

let portName = "COM3" // Replace with the name of your Arduino's serial port
let baudRate = 9600

// Create a new SerialPort object with the specified port name and baud rate
let port = new SerialPort(portName, baudRate)

// Open the serial port
port.Open()

// Write the string to the serial port
port.Write("hello world")

// Close the serial port
port.Close()
