from django.urls import path
# import login.views
from . import views
from django.contrib import admin
app_name = 'login'

urlpatterns = [
    path('', views.index),

    path('index/', views.index),
    path('login/', views.login),
    path('register/', views.register),
    path('logout/', views.logout),
]
