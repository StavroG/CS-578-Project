import threading
from transmitter import main as transmitter_main
from receiver import main as receiver_main

# Create threads for transmitter and receiver
transmitter_thread = threading.Thread(target=transmitter_main)
receiver_thread = threading.Thread(target=receiver_main)

# Start the threads
transmitter_thread.start()
receiver_thread.start()

# Wait for both threads to complete
transmitter_thread.join()
receiver_thread.join()

print("video feed ended...")
