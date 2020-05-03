from . import models,forms
from django.shortcuts import render, get_object_or_404,redirect
from django.contrib.auth.models import User
import time

def index(request):
    if not request.session.get('is_login', None):
        return redirect('/login/')
    print(request.session.get('user_name'))
    return render(request,'login/index.html')

def login(request):
    if request.session.get('is_login', None):
        return redirect('/index')
    if request.method=="POST":
        login_form = forms.UserForm(request.POST)

        if login_form.is_valid():
            username = login_form.cleaned_data.get('username')
            password = login_form.cleaned_data.get('password')

            try:
                user = models.User.objects.get(name=username)
                if user.password!=password:
                    message2 = '密码错误'
                    return render(request, 'login/login.html',locals())
            except:
                message1 = '用户不存在'
                return render(request, 'login/login.html',locals())
            request.session['is_login'] = True
            request.session['user_name'] = user.name

            print(user.name,user.id)
            # request.session['user_id'] = user.id
            return redirect('/index')

    login_form = forms.UserForm()
    return render(request,'login/login.html',locals())

def register(request):
    if request.method == "POST":
        register_form = forms.RegisterForm(request.POST)
        message = "请检查填写的内容！"
        if register_form.is_valid():  # 获取数据
            username = register_form.cleaned_data['username']
            password1 = register_form.cleaned_data['password1']
            password2 = register_form.cleaned_data['password2']
            email = register_form.cleaned_data['email']
            sex = register_form.cleaned_data['sex']
            print(username,password1,password2,email,sex)
            if password1 != password2:  # 判断两次密码是否相同
                message = "两次输入的密码不同！"
                return render(request, 'login/register.html', locals())
            else:
                same_name_user = models.User.objects.filter(name=username)
                if same_name_user:  # 用户名唯一
                    message = '用户已经存在，请重新选择用户名！'
                    return render(request, 'login/register.html', locals())
                same_email_user = models.User.objects.filter(email=email)
                if same_email_user:  # 邮箱地址唯一
                    message = '该邮箱地址已被注册，请使用别的邮箱！'
                    return render(request, 'login/register.html', locals())

                # 当一切都OK的情况下，创建新用户

                new_user = models.User()
                new_user.name = username
                new_user.password = password1
                new_user.sex = sex
                new_user.email = email
                new_user.save()
                return redirect('/login/')  # 自动跳转到登录页面
    register_form = forms.RegisterForm()
    return render(request, 'login/register.html', locals())

def logout(request):
    if not request.session.get('is_login', None):
        # 如果本来就未登录，也就没有登出一说
        return redirect("/index/")
    request.session.flush()
    return redirect('/index/')

def draw(request):
    if not request.session.get('is_login', None):
        return redirect('/login/')
    draw_list = models.Draw.objects.all().order_by('-c_time')

    return render(request, 'login/draw.html', context={'draw_list': draw_list})

def launch_draw(request):
    if not request.session.get('is_login', None):
        return redirect('/login/')

    if request.method == "POST":
        launch_form = forms.DrawForm(request.POST)
        if launch_form.is_valid():  # 获取数据
            Draw_name = launch_form.cleaned_data['Draw_name']
            Prize = launch_form.cleaned_data['Prize']
            ddl = launch_form.cleaned_data['DDL']

            try:
                new_draw = models.Draw()
                new_draw.Draw_name=Draw_name
                new_draw.Prize=Prize
                new_draw.onDoing='1'

                # initiator = models.User.objects.get(name=username)
                initiator_name = request.session.get('user_name')
                user = models.User.objects.get(name=initiator_name)
                new_draw.initiator=user
                new_draw.number=1
                new_draw.DDL = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
                new_draw.save()
                new_draw.participants.add(user)
                new_draw.save()
                return redirect('/launchsuccess/')
            except:
                message = "抽奖名已存在，请换个名字！"
                return render(request, 'login/launch.html',locals())
    launch_form = forms.DrawForm()
    return render(request, 'login/launch.html',locals())


def launch_success(request):
    if not request.session.get('is_login', None):
        return redirect('/login/')
    return render(request,'login/launch_success.html')

def add_success(request):
    if not request.session.get('is_login', None):
        return redirect('/login/')
    return render(request,'login/add_success.html')

def draw_detail(request,pk):
    if not request.session.get('is_login', None):
        return redirect('/login/')
    if request.method == "POST":
        draw = get_object_or_404(models.Draw, pk=pk)
        # return render(request, 'login/draw_detail.html', context={'draw': draw})
        userName = request.session.get('user_name')
        user = models.User.objects.get(name=userName)
        try:
            draw.participants.add(user)
            return redirect('/addsuccess/')
        except:
            return render(request, 'login/draw_detail.html', context={'draw': draw})
    draw = get_object_or_404(models.Draw, pk=pk)
    part_list = models.Draw.objects.get(Draw_name=draw.Draw_name).participants.all()
    init = models.Draw.objects.get(Draw_name=draw.Draw_name).initiator

    userName = request.session.get('user_name')
    added = False
    user = models.User.objects.get(name=userName)
    is_root = False
    if user == init:
        is_root = True
    if user in part_list:
        added = True
    return render(request,'login/draw_detail.html', context={'draw': draw,'part_list':part_list,'added':added,'is_root':is_root})

def modify_draw(request,pk):
    if not request.session.get('is_login', None):
        return redirect('/login/')
    if request.method == "POST":
        draw = get_object_or_404(models.Draw, pk=pk)


    draw = get_object_or_404(models.Draw, pk=pk)
    return render(request,'login/modify_draw.html',context={'draw':draw})
