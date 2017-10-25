import serial
import time
import crc16
# import minimalmodbus


def main():
    print "Writing to COM Port"
    # ser = serial.Serial("COM8", 9600)
    ser_packet = chr(0x01) + chr(20) + chr(0) + chr(10)
    # print ser_packet
    crc = crc16.crc16xmodem(ser_packet)
    print hex(crc)
    # ser_packet.append(crc)
    # print ser_packet

    # while True:
    #     # Sleep some time
    #     time.sleep(2)
    #
    #     print ser.read(8)

    # while True:
    #     ser.write("Hello World !!")

if __name__ == "__main__":
    main()
