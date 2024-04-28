import serial
import time
import threading
import tkinter as tk
from tkinter import scrolledtext

# Setup for the serial ports (adjust according to your setup)
TRANSMITTER_PORT = 'COM3'
RECEIVER_PORT = 'COM4'
EOM = bytearray([0xED, 0xED]) # End Of MEssge
PREAMBLE = bytearray([0xFE, 0xFF]) # defined preamble outside of ascii value range

def open_serial_connection(port, baudrate=9600):
    return serial.Serial(port=port, baudrate=baudrate, bytesize=8, timeout=4, stopbits=1)

def send_gui(ser):
    root_send = tk.Tk()
    root_send.title("Li-Fi Transmitter")

    entry = tk.Entry(root_send, width=50)
    entry.pack(padx=20, pady=20)

    send_button = tk.Button(root_send, text="Send")
    text_area_send = scrolledtext.ScrolledText(root_send, width=60, height=10)
    text_area_send.pack(padx=20, pady=20)

    def on_send():
        message = entry.get()
        if message:
            send_message(message, ser, text_area_send)
            entry.delete(0, tk.END)

    send_button.config(command=on_send)
    send_button.pack(pady=10)

    def on_closing():
        ser.close()
        root_send.destroy()

    root_send.protocol("WM_DELETE_WINDOW", on_closing)
    root_send.mainloop()

def receive_gui(ser):
    root_receive = tk.Tk()
    root_receive.title("Li-Fi Receiver")

    text_area_receive = scrolledtext.ScrolledText(root_receive, width=60, height=10)
    text_area_receive.pack(padx=20, pady=20)

    def clear_text():
        text_area_receive.delete('1.0', tk.END)

    # added a clear button to receiver gui
    clear_button = tk.Button(root_receive, text="Clear", command=clear_text)
    clear_button.pack(pady=10)

    def update_received_message():
        buffer = bytearray() # read in all data here
        message = bytearray()  # accumulate message content here

        while True:
            data = ser.read(ser.in_waiting) # read what is currently available to be read
            if data:
                buffer.extend(data)

            
            while True:
                start = buffer.find(PREAMBLE) # search for preamble on dat read in
                if start != -1: # if preamble found
                    end = buffer.find(PREAMBLE, start + len(PREAMBLE)) # searching for subseqent preamble
                    if end == -1:
                        end = len(buffer) # if no subsequent preamble then use end of buffer
                    next_packet_start = buffer.find(EOM, start + len(PREAMBLE))
                    if next_packet_start == -1:
                        next_packet_start = end # if no EOM found assume end of packet is next preamble

                    packet = buffer[start+len(PREAMBLE):next_packet_start]
                    message.extend(packet)

                    if buffer[next_packet_start:next_packet_start+len(EOM)] == EOM:
                        # once EOM found then try decoding
                        try:
                            full_message = message.decode('utf-8')
                            text_area_receive.insert(tk.END, f'{full_message}\n')
                            message = bytearray()  # clear messag array
                        except UnicodeDecodeError:
                            text_area_receive.insert(tk.END, "Error decoding message.\n")
                        buffer = buffer[next_packet_start+len(EOM):]  # skip over the EOM
                    else:
                        # If no EOM continue along buffer
                        buffer = buffer[end:]
                        break
                else:
                    # preserev buffer if packets ends with start of preamble
                    buffer = buffer[-len(PREAMBLE):]
                    break

            if not data and not buffer:
                time.sleep(0.1) # 
            
            root_receive.update_idletasks()

    thread_receive = threading.Thread(target=update_received_message, daemon=True)
    thread_receive.start()

    def on_closing():
        ser.close()
        root_receive.destroy()

    root_receive.protocol("WM_DELETE_WINDOW", on_closing)
    root_receive.mainloop()

def send_message(message, ser, text_area):
    byte_message = message.encode('utf-8')
    max_data_length = 60  # need to account fo possible 4 bits (2 in preamble and 2 in eom)

    # split into packets
    for i in range(0, len(byte_message), max_data_length):
        packet = PREAMBLE + byte_message[i:i + max_data_length]
        if i + max_data_length >= len(byte_message):
            packet += EOM  # add the EOM tto only the last packet
        ser.write(packet)
        time.sleep(0.1) # this delay hepled fix the ser.in_waiting issues with multiple packets
        text_area.insert(tk.END, f'Sent packet: {packet}\n')

if __name__ == "__main__":
    ser1 = open_serial_connection(TRANSMITTER_PORT)
    ser2 = open_serial_connection(RECEIVER_PORT)

    thread_send = threading.Thread(target=send_gui, args=(ser1,))
    thread_receive_gui = threading.Thread(target=receive_gui, args=(ser2,))
    thread_send.start()
    thread_receive_gui.start()
    thread_send.join()
    thread_receive_gui.join()