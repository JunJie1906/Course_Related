import sys
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtWebEngineWidgets import *
from PyQt5 import QtCore, QtGui , QAxContainer, QtWidgets

class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.setWindowTitle('MyLive')
        self.setGeometry(5,30,1355,730)
        self.browser=QWebEngineView()

        self.browser.load(QUrl('http://127.0.0.1:8000/'))
        self.setCentralWidget(self.browser)
        # self.setAttribute(QWebEngineSettings.PluginsEnabled)
        QPluginLoader


if __name__ == '__main__':
    app=QApplication(sys.argv)

    win=MainWindow()

    win.show()
    app.exit(app.exec_())