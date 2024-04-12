import serial
import cv2
import numpy as np

RECEIVER_PORT = '/dev/pts/2'  # change to whatever port you're using

# TODO: Still need to explore packet size management. I just set this up to establish live video through serial port

def main():
    ser = serial.Serial(RECEIVER_PORT, 9600)
    buffer = bytearray()

    try:
        while True:
            data = ser.read(4096) # will have to be set smaller in the future
            if data:
                buffer += data

                while True:
                    start = buffer.find(b'\xff\xd8')  # beginning of JPEG
                    end = buffer.find(b'\xff\xd9', start + 2)  # end of JPEG
                    
                    if start != -1 and end != -1:
                        jpg = buffer[start:end + 2]
                        buffer = buffer[end + 2:]

                        nparr = np.frombuffer(jpg, np.uint8)
                        frame = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
                        
                        if frame is not None:
                            cv2.imshow('Video', frame)
                            # waitKey() used to wait for exit command. Exit with 'q' command
                            if cv2.waitKey(1) & 0xFF == ord('q'):
                                raise Exception("Exited by receiver.") 
                                return
                        else:
                            print("Failed to decode frame.")
                    else:
                        break
    except Exception as e:
        print(e) 
    finally:
        ser.close()
        cv2.destroyAllWindows()
        print("Receiver ended conncetion.")

if __name__ == '__main__':
    main()
