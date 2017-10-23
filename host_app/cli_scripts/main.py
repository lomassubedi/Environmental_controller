import serial
import time
import minimalmodbus

def main():
    print "Writing to COM Port"
    # ser = serial.Serial("COM8", 9600)

    while True:


        instrument = minimalmodbus.Instrument('COM8', 1)  # port name, slave address (in decimal)
        instrument.serial.baudrate = 9600  # Baud

        # Read a random register
        randReg = instrument.read_register(0, 0)  # Registernumber, number of decimals
        print "Register Value: ", randReg

        time.sleep(1)
    pass


if __name__ == "__main__":
    main()
