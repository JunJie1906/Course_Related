from django.db import models

# Create your models here.
class User(models.Model):
    gender = (('male','男'),('female','女'))
    hobbies = (
        ('1','羽毛球'),
        ('2','篮球'),
    )

    name = models.CharField(max_length=10,unique=True)
    password = models.CharField(max_length=30)
    email = models.EmailField(unique=True)
    sex = models.CharField(max_length=100,choices=gender,default='男')
    c_time = models.DateTimeField(auto_now_add=True)
    hobby = models.CharField(max_length=100,choices=hobbies,default='无')

    def __str__(self):
        return self.name

    class Meta:
        ordering = ["-c_time"]
        verbose_name = "用户"
        verbose_name_plural = "用户"

