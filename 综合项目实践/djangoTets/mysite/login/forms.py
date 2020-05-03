from django import forms
from captcha.fields import CaptchaField

class UserForm(forms.Form):
    username = forms.CharField(label="用户名", max_length=128, widget=forms.TextInput(attrs={'class': 'form-control'}))
    password = forms.CharField(label="密码", max_length=256, widget=forms.PasswordInput(attrs={'class': 'form-control'}))
    # captcha = CaptchaField(label='验证码')

class RegisterForm(forms.Form):
    gender = (
        ('male', "男"),
        ('female', "女"),
    )
    username = forms.CharField(label="用户名", max_length=128, widget=forms.TextInput(attrs={'class': 'form-control'}))
    password1 = forms.CharField(label="密码", max_length=256, widget=forms.PasswordInput(attrs={'class': 'form-control'}))
    password2 = forms.CharField(label="确认密码", max_length=256, widget=forms.PasswordInput(attrs={'class': 'form-control'}))
    sex = forms.ChoiceField(label='性别', choices=gender)
    email = forms.EmailField(label="电子邮箱",max_length=255, widget=forms.TextInput(attrs={'class': 'form-control'}))
    # captcha = CaptchaField(label='验证码')

class DrawForm(forms.Form):
    Draw_name = forms.CharField(label="抽奖名称",max_length=128,widget=forms.TextInput(attrs={'class': 'form-control'}))
    Prize = forms.CharField(label="奖品",max_length=128,widget=forms.TextInput(attrs={'class': 'form-control'}))
    DDL = forms.DateTimeField(label="开奖时间",widget=forms.DateTimeInput(attrs={'class': 'form-control'}))


class JoinDrawForm(forms.Form):
    UserName = forms.CharField()
    JoinTime = forms.DateTimeField()

class start_now(forms.Form):
    pass
