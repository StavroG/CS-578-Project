import serial
import cv2
import time

TRANSMITTER_PORT = '/dev/pts/1'  # Change to whatever port you're using

# TODO: still need to manage max packet sizes. this is just to get a working serial port transmission to keep working on
def main():

    # Establishes a video capture through webcam
    cap = cv2.VideoCapture(0)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)
    ser = serial.Serial(TRANSMITTER_PORT, 9600) # may need to experiment with higher baud rates

    try:
        while True:
            # Captures a frame from webcam
            ret, frame = cap.read()
            if ret:
                _, buffer = cv2.imencode('.jpg', frame) # encodes to jpeg image (will experiment with other encodings)
                data = buffer.tobytes()
                ser.write(data)
                time.sleep(0.1)  # will capture 10 frames per second

                # TODO: still need to implement waitKey() comand to quit appliction. was breaking feed on initial attempts
            else:
                break
    finally:
        cap.release()
        ser.close()
        print("Transmitter closed.")

if __name__ == '__main__':
    main()
