from django.test import TestCase

# Create your tests here.
import sys
from PyQt5 import QtWidgets,QtCore

out=sys.stdout
sys.stdout=open("QWidget.txt","w")
help(QtWidgets)
sys.stdout.close()
sys.stdout=out

