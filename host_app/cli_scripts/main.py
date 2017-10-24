import serial
import time
import minimalmodbus

def main():
    print "Writing to COM Port"
    ser = serial.Serial("COM8", 9600)
    while True:
        ser.write("Hello World !!")

if __name__ == "__main__":
    main()
