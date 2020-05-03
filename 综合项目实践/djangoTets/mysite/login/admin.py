from django.contrib import admin
from . import models
# Register your models here.
admin.site.register(models.User)
admin.site.register(models.Draw)
# admin.site.register(models.Draw_participant)
# admin.site.register(models.Draw_initiator)