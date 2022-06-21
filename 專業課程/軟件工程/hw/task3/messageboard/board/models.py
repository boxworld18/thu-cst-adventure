from django.db import models
from django.forms import ModelForm

class User(models.Model):
    name = models.CharField(unique=True, max_length=20)
    register_date = models.DateTimeField(auto_now_add=True)
    avatar = models.ImageField(upload_to='avatars', blank=True) # AVATAR

    def __str__(self):
        return self.name
    

class Message(models.Model):
    # ----------------------------------------------------------------
    # 完善Message模型的代码，共有四个字段
    # user: ForeignKey, on_delete策略使用CASCADE
    # title: CharField, max_length=100
    # content: CharField, max_length=500
    # pub_date: DateTimeField, auto_now_add=True
    # ----------------------------------------------------------------
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    title = models.CharField(max_length=100)
    content = models.CharField(max_length=500)
    pub_date = models.DateTimeField(auto_now_add=True)
    pass
