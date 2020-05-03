from django.shortcuts import render,redirect,get_object_or_404
from . import forms
import os
import threading
import inspect
import ctypes

import login.models,liveapp.models

def gen_9_numbers(s):
    return str(abs(hash(s)))[:9]

def ffmpeg(id):
    os.system('ffmpeg -f dshow -i video="HD Webcam"  '

              '-vcodec libx264 -preset:v ultrafast -tune:v zerolatency '
              '-f flv '
              'rtmp://localhost:1935/live/'+id)


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


def live(request,pk):
    if not request.session.get('is_login', None):
        return redirect('/login/')
    username = request.session.get('user_name')

    live = get_object_or_404(liveapp.models.Live, pk=pk)
    is_main = False
    if username == live.creater.name:
        is_main = True
    roomID = live.roomId
    request.session["cur_roomId"] = roomID
    return render(request,'liveapp/live.html',context={'Live':live,'is_main':is_main})


def openCamera(request):
    if not request.session.get('is_login', None):
        return redirect('/login/')
    username = request.session.get('user_name')
    creater = login.models.User.objects.get(name=username)
    live = liveapp.models.Live.objects.get(creater=creater)
    id = live.roomId
    t = threading.Thread(target=ffmpeg, args=(id,))
    t.start()
    request.session['camera']=t.ident
    return redirect(live.get_absolute_url())

def closeCamera(request):
    if not request.session.get('is_login', None):
        return redirect('/login/')
    username = request.session.get('user_name')
    creater = login.models.User.objects.get(name=username)
    live = liveapp.models.Live.objects.get(creater=creater)
    tid = request.session.get('camera')
    _async_raise(tid, SystemExit)
    return redirect(live.get_absolute_url())

def launch(request):
    if not request.session.get('is_login', None):
        return redirect('/login/')

    if request.method=="POST":
        launchForm = forms.launchForm(request.POST)

        if launchForm.is_valid():
            username = request.session.get('user_name')
            creater = login.models.User.objects.get(name=username)
            LiveName = launchForm.cleaned_data.get('LiveName')
            roomID = gen_9_numbers(username+LiveName)
            same_roomID = liveapp.models.Live.objects.filter(roomId=roomID)
            if same_roomID:
                roomID = gen_9_numbers(username)
                same_roomID = liveapp.models.Live.objects.filter(roomId=roomID)
            try:
                newLive = liveapp.models.Live()
                newLive.creater = creater
                newLive.roomId = roomID
                newLive.roomName = LiveName
                newLive.save()
                # t = threading.Thread(target=ffmpeg(roomID))
                # t.start()

            except:
                erro_msg = "您已经有一个正在直播的直播间了！！"
                return render(request,'liveapp/launch.html',locals())

            return redirect(newLive.get_absolute_url())

    launchForm = forms.launchForm()
    return render(request,'liveapp/launch.html',locals())


def FindLive(request):
    if not request.session.get('is_login',None):
        return redirect('/login/')

    if request.method=="POST":
        RoomForm = forms.getRoomForm(request.POST)
        if RoomForm.is_valid():

            roomID = RoomForm.cleaned_data.get('roomID')

            try:
                room = liveapp.models.Live.objects.get(roomId=roomID)
            except:
                erro_message = '不存在此房间！请重新输入'
                return render(request, 'liveapp/FindLive.html',locals())
            request.session["cur_roomId"] = roomID
            return redirect(room.get_absolute_url())

    RoomForm = forms.getRoomForm()
    return render(request,'liveapp/FindLive.html',locals())

def MyLive(request):
    if not request.session.get('is_login',None):
        return redirect('/login/')
    username = request.session.get('user_name')
    user = login.models.User.objects.get(name=username)
    try:
        live = liveapp.models.Live.objects.get(creater=user)
    except:
        return redirect('/launch/')
    return redirect(live.get_absolute_url())

def closelive(request):
    if not request.session.get('is_login',None):
        return redirect('/login/')

    roomId=request.session.get('cur_roomId')
    try:
        room = liveapp.models.Live.objects.get(roomId=roomId)
    except:
        return redirect('/mylive/')
    room.delete()
    return redirect('/launch/')

