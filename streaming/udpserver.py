import socket
import time
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
server.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
# Set a timeout so the socket does not block
# indefinitely when trying to receive data.
server.settimeout(0.5)
server.bind(("", 44444))
while True:
    print(time.time())
    time.sleep(1)
    # str = str(time.time())
    str = 'asd'.encode()
    server.sendto(str, ('<broadcast>', 37020))



# # def sendframe(frame):

# #     while True:
# #         message = frame[]
# #         server.sendto(message, ('<broadcast>', 37020))
# #     print("message sent!")
    
    



# import numpy as np
# import cv2

# cap = cv2.VideoCapture(0)

# # while(True):
#     # Capture frame-by-frame
# ret, frame = cap.read()
# print(len(frame.tobytes())/1024)
    
#     # sendframe(frame)
#     # Display the resulting frame
#     # cv2.imshow('frame',frame)
#     # if cv2.waitKey(1) & 0xFF == ord('q'):
#     #     break

# # When everything done, release the capture
# cap.release()
# cv2.destroyAllWindows()