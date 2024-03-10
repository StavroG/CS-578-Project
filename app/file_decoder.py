import sys
import time
import os
import numpy as np

# Gets the binary data from the file
def read_binary_file(file_path):
    with open(file_path, 'rb') as file:
        binary_data = file.read()
        
    return binary_data

# Convert the binary data back to bytes
def bits_to_bytes(binary_data):
    byte_data = np.packbits(np.frombuffer(binary_data, dtype=np.uint8))
    return byte_data

def decode_and_write(file_name, binary_data):
    output_directory = "decoded/"
    output_file_path = os.path.join(output_directory, file_name + "_decoded.mp4")

    # Create the output directory if it doesn't exist
    os.makedirs(output_directory, exist_ok=True)

    # Convert binary data back to bytes
    byte_data = bits_to_bytes(binary_data)

    # Write the bytes to a new or existing .mp4 file
    with open(output_file_path, "wb") as file:
        file.write(byte_data)

# Driver code for the decoder
# Check to make sure the user provides the path to the file they want to decode
if len(sys.argv) != 2:
    print("Usage: python file_decoder.py \"path to binary file\"")
    sys.exit(1)
else:
    start_time = time.time()

    binary_file_path = sys.argv[1]
    file_name, file_extension = os.path.splitext(os.path.basename(binary_file_path))

    # Make sure the user only passes in a .bin file
    if(file_extension != ".bin"):
        print("Error: The input must be a .bin file")
        sys.exit(1)

    binary_data = read_binary_file(binary_file_path)
    decode_and_write(file_name, binary_data)

    end_time = time.time()

    print("Elapsed time:", end_time - start_time, "seconds")
