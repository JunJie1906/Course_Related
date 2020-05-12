from django.test import TestCase

# Create your tests here.
import psutil
lst = psutil.pids()

for i in lst:
    process = psutil.Process(i)
    if process.name()=='ffmpeg.exe':
        process.kill()
        break

