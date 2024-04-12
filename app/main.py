import serial
import time
import string
import threading
import sys

from file_encoder import main as encode_file
from file_decoder import main as decode_file  # Assuming similar structure for file_decoder.py

if len(sys.argv) < 2:
    print("Usage: python main.py <path to MP4 file>")
    sys.exit(1)

# Change to whatever port locations you're using
TRANSMITTER_PORT = '/dev/pts/1'
RECEIVER_PORT = '/dev/pts/2'
input_mp4_path = sys.argv[1]

ser1 = serial.Serial(
    port=TRANSMITTER_PORT, baudrate=9600, bytesize=8, timeout=4, stopbits=1
)

ser2 = serial.Serial(
    port=RECEIVER_PORT, baudrate=9600, bytesize=8, timeout=4, stopbits=1
)

def write_to_serial(file_path, ser):
    with open(file_path, 'rb') as file:
        while True:
            data = file.read(60)  # doesn't read in preamble
            if not data:
                break

            # TODO: integrate with actual preamble
            packet = bytearray([0x00, 0x00, 0x00, 0x00])  # fake preamble
            packet.extend(data) # add 60 bits of actual data
            ser.write(packet)
            print(f'packet written:{len(packet)} bytes')

def read_from_serial(ser, output_path):
    with open(output_path, 'wb') as file:
        print("Ready to receive data...")
        while True:
            data = ser.read(64)  # read in packets -- including preamble
            if not data:
                break
            file.write(data[4:])  # skipping first 4 bytes when writing
            print(f'packet read:{len(data)-4} bytes of data')

encoded_file_path = encode_file(input_mp4_path)
received_file_path = encoded_file_path.replace("_encoded.bin", "_received.bin")

thread_write = threading.Thread(target=write_to_serial, args=(encoded_file_path, ser1))
thread_read = threading.Thread(target=read_from_serial, args=(ser2, received_file_path))
thread_write.start()
thread_read.start()
thread_write.join()
thread_read.join()

decoded_file_path = decode_file(received_file_path)
print(f"Decoding done, file is at: {decoded_file_path}")
