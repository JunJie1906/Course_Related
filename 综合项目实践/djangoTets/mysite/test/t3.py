#-*-conding:utf-8-*-
from threading import Thread
import os
import subprocess as sp
import _thread


def t2():
    print('t2begin===================\n========================')
    val2 = os.system('ffmpeg -f dshow -i video="HD Webcam"  '

                     '-vcodec libx264 -preset:v ultrafast -tune:v zerolatency '
                     '-f flv '
                     'rtmp://localhost:1935/live/test')
    print('t2===================\n========================')

def t1():
    print('t1begin===================\n========================')
    val1 = os.system('ffmpeg -f dshow -i video="HD Webcam"  '
                    
                    '-vcodec libx264 -preset:v ultrafast -tune:v zerolatency '
                    '-f flv '
                    'rtmp://localhost:1935/live/home')
    print('t1===================\n========================')

