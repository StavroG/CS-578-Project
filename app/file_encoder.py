import sys
import time
import os
import numpy as np

# Gets the byte data from the file
def read_mp4_file(file_path):
    with open(file_path, 'rb') as file:
        byte_data = file.read()

    return byte_data

# Convert the entire array of bytes to bits
def bytes_to_bits(mp4_data):
    binary_data = np.unpackbits(np.frombuffer(mp4_data, dtype=np.uint8))
    return binary_data

def encode_and_write(file_name, byte_data):
    output_directory = "encoded/"
    output_file_path = os.path.join(output_directory, file_name + "_encoded.bin")

    # Create the output directory if it doesn't exist
    os.makedirs(output_directory, exist_ok=True)

    # Convert byte data to bits
    bit_data = bytes_to_bits(byte_data)

    # Write the bits to a new or existing .bin file
    with open(output_file_path, "wb") as file:
        file.write(bit_data)

# Driver code for the encoder
# Check to make sure the user provides the path to the file they want to encode
if len(sys.argv) != 2:
    print("Usage: python file_encoder.py \"path to file\"")
    sys.exit(1)
else:
    start_time = time.time()

    mp4_file_path = sys.argv[1]
    file_name, file_extension = os.path.splitext(os.path.basename(mp4_file_path))

    # Make sure the user only passes in a .mp4 file
    if(file_extension != ".mp4"):
        print("Error: The input must be a .mp4 file")
        sys.exit(1)

    byte_data = read_mp4_file(mp4_file_path)
    encode_and_write(file_name, byte_data)
    
    end_time = time.time()

    print("Elapsed time:", end_time - start_time, "seconds")
