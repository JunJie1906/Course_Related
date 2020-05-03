import os
import threading
import ctypes
import time
import requests
import subprocess

from ffmpy3 import FFmpeg




def pre():

    ff = FFmpeg(inputs={'D://input.mp4': None, 'audio.mp4': None},
                outputs={'output.ts': '-c:v h264 -c:a ac3'})
    print(ff.cmd)
    ff.run()



def statrp():
    t=threading.Thread(target=pre,)
    t.start()
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

_async_raise(14764, SystemExit)
# stop_thread(t)
