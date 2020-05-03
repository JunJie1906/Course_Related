import subprocess
from ffmpy3 import FFmpeg

import cv2

cap = cv2.VideoCapture(0)

ff = FFmpeg(
    inputs={'pipe:0': '-f rawvideo -pix_fmt rgb24 -s:v 640x480'},
    outputs={'pipe:1': '-c:v h264 -f flv rtmp://localhost:1935/live/home1'}
)

stdout, stderr = ff.run(input_data=open('input.mp4', 'rb').read(), stdout=subprocess.PIPE)


