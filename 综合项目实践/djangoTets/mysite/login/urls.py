from django.urls import path
# import login.views
from . import views
from django.contrib import admin
app_name = 'login'

urlpatterns = [
    path('', views.draw),
    path('draws/<int:pk>/', views.draw_detail,name = 'detail1'),
    path('', views.index),

    path('index/', views.index),
    path('login/', views.login),
    path('register/', views.register),
    path('logout/', views.logout),
    path('draw/', views.draw),
    path('launch/', views.launch_draw),
    path('launchsuccess/', views.launch_success),
    # path('drawdetail/', views.draw_detail),
    path('addsuccess/',views.add_success),
    path('modify_draw/<int:pk>/',views.modify_draw,name = 'modify_draw'),
]
