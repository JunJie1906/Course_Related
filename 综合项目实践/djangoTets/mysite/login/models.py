from django.db import models
from django.urls import reverse
# Create your models here.
class User(models.Model):
    gender = (('male','男'),('female','女'))
    # hobbies = (
    #     ('1','羽毛球'),
    #     ('2','篮球'),
    # )

    name = models.CharField(max_length=10,unique=True)
    password = models.CharField(max_length=30)
    email = models.EmailField(unique=True)
    sex = models.CharField(max_length=100,choices=gender,default='男')
    c_time = models.DateTimeField(auto_now_add=True)
    # hobby = models.CharField(max_length=100,choices=hobbies,default='无')

    def __str__(self):
        return self.name

    class Meta:
        ordering = ["-c_time"]
        verbose_name = "用户"
        verbose_name_plural = "用户"


class Draw(models.Model):

    Choice = (
        ('1','是'),
        ('2','否'),
    )
    Draw_name = models.CharField(max_length=255,unique=True,default='抽奖')
    Prize = models.CharField(max_length=255,default='')
    initiator = models.ForeignKey(User,on_delete=models.DO_NOTHING,related_name='initiator_user')
    participants = models.ManyToManyField(User,related_name='participant_users')
    c_time = models.DateTimeField(auto_now_add=True)
    DDL = models.DateTimeField(default='2020-1-1')

    onDoing = models.CharField(max_length=2,choices=Choice)
    number=models.IntegerField(default=0)

    def __str__(self):
        return self.Draw_name

    def get_absolute_url(self):
        return reverse('login:detail1', kwargs={'pk': self.pk})

    def get_absolute_modify_url(self):
        return reverse('login:modify_draw', kwargs={'pk': self.pk})

    class Meta:
        ordering = ["-c_time"]
        verbose_name = "抽奖名称"
        verbose_name_plural = "抽奖名"


