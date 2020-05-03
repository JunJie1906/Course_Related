import subprocess as sp
import cv2
import pyaudio
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import wave
import os
from threading import Thread


rtmpUrl = "rtmp://localhost:1935/live/home"
camera_path = ""
cap = cv2.VideoCapture(0)

# Get video information
fps = int(cap.get(cv2.CAP_PROP_FPS))
width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

# ffmpeg command
command = ['ffmpeg',
           '-y',
           '-f', 'rawvideo',
           '-vcodec', 'rawvideo',
           '-pix_fmt', 'bgr24',
           '-s', "{}x{}".format(width, height),
           '-r', str(fps),
           '-i', '-',
           '-c:v', 'libx264',
           '-pix_fmt', 'yuv420p',
           '-preset', 'ultrafast',
           '-f', 'flv',
           rtmpUrl]
command1 = ['ffmpeg',

           '-f', 'gdigrab',
           '-vcodec', 'rawvideo',
           '-pix_fmt', 'yuv420p',
           ''
           '-r', str(fps),
           '-i', '-',
           '-c:v', 'libx264',
           '-pix_fmt', 'yuv420p',
           '-preset', 'ultrafast',
           '-f', 'flv',
           rtmpUrl]

ffmpeg -f gdigrab -video_size 1024x768
-framerate 15 -i desktop -pix_fmt yuv420p
-codec:v libx264 -bf 0 -g 300 -f flv

# 管道配置
p = sp.Popen(command, stdin=sp.PIPE)

# read webcamera
while (cap.isOpened()):
    ret, frame = cap.read()
    if not ret:
        print("Opening camera is failed")
        break

    p.stdin.write(frame.tostring())













#
#
# rtmpUrl = "rtmp://localhost:1935/live/home"
# camera_path = ""
# cap = cv2.VideoCapture(0)
#
# # Get video information
# fps = int(cap.get(cv2.CAP_PROP_FPS))
# width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
# height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
#
#
# command = ['ffmpeg',
#            '-y',
#            '-f', 'rawvideo',
#            '-vcodec', 'rawvideo',
#            '-c:v', 'libx264',
#            '-pix_fmt', 'yuv420p',
#            '-preset', 'ultrafast',
#            '-f', 'flv',
#            rtmpUrl]
#
# rtmpUrl1 = "rtmp://localhost:1935/live/home1"
# command1 = ['ffmpeg',
#            '-y',
#            '-f', 'rawvideo',
#            '-vcodec', 'rawvideo',
#            '-c:v', 'libx264',
#            '-pix_fmt', 'yuv420p',
#            '-preset', 'ultrafast',
#            '-f', 'flv',
#            rtmpUrl1]
#
# # 管道配置
# p = sp.Popen(command, stdin=sp.PIPE)
# p1 = sp.Popen(command, stdin=sp.PIPE)
#
# def get_audio():
#     CHUNK = 2**12  # 定义数据流块
#     FORMAT = pyaudio.paInt16  # 量化位数（音量级划分）
#     CHANNELS = 1  # 声道数;声道数：可以是单声道或者是双声道
#     RATE = 2**16  # 采样率;采样率：一秒内对声音信号的采集次数，常用的有8kHz, 16kHz, 32kHz, 48kHz, 11.025kHz, 22.05kHz, 44.1kHz
#     stream = pyaudio.PyAudio().open(format=FORMAT,
#                     channels=CHANNELS,
#                     rate=RATE,
#                     input=True,
#                     frames_per_buffer=CHUNK)
#     return stream
#
#
#
# def Video():
#     while (cap.isOpened()):
#         ret, frame = cap.read()
#         if not ret:
#             print("Opening camera is failed")
#             break
#
#         # write to pipe
#         p.stdin.write(frame.tostring())
#
# audio_stream = get_audio()
# audio_stream.start_stream()
# def Audio():
#     while True:
#         data = audio_stream.read(2**12)
#         # print(data)
#         p1.stdin.write(data)
#     # print(audio_stream.read(256))
#
# # Audio()
#
# Video()
#
# # t1 = Thread(target=Video())
# # t2 = Thread(target=Audio())
# # t1.start()
# # t2.start()