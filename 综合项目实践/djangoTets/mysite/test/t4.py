import os
import threading
import ctypes
import time
import requests
import subprocess


def ffmpeg(id):
    os.system('ffmpeg -f dshow -i video="HD Webcam"  '

              '-vcodec libx264 -preset:v ultrafast -tune:v zerolatency '
              '-f flv '
              'rtmp://localhost:1935/live/'+id)


def pre():
    while True:
        print(1)
global tid
def statrp():
    t=threading.Thread(target=ffmpeg,args='2')
    t.start()
    global tid
    tid  =t.ident
    print('tid:',t.ident)

import inspect
import ctypes

def _async_raise(tid, exctype):
    """raises the exception, performs cleanup if needed"""
    tid = ctypes.c_long(tid)
    if not inspect.isclass(exctype):
        exctype = type(exctype)
    res = ctypes.pythonapi.PyThreadState_SetAsyncExc(tid, ctypes.py_object(exctype))
    if res == 0:
        raise ValueError("invalid thread id")
    elif res != 1:
        # """if it returns a number greater than one, you're in trouble,
        # and you should call it again with exc=NULL to revert the effect"""
        ctypes.pythonapi.PyThreadState_SetAsyncExc(tid, None)
        raise SystemError("PyThreadState_SetAsyncExc failed")
def stop_thread(thread):

    _async_raise(thread.ident, SystemExit)
    print(999)


t = threading.Thread(target=ffmpeg, args='2')
t.start()

tid = t.ident
print('tid:', t.ident)

time.sleep(2)
print(tid)
stop_thread(t)
# stop_thread(t)