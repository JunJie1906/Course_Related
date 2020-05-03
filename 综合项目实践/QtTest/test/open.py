import cv2
import numpy as np

cap = cv2.VideoCapture("rtmp://58.200.131.2:1935/livetv/hunantv")
print("ok")
while(1):
    # get a frame
    ret, frame = cap.read()
    # show a frame
    cv2.imshow("capture", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()
