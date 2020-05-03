from PyQt5 import QtCore,QtGui,QtWidgets,QtWebEngineWidgets

class WebEngineView(QtWebEngineWidgets.QWebEngineView):
    def createWindow(self,QWebEnginePage_WebWindowType):
        page = WebEngineView(self)
        page.urlChanged.connect(self.on_url_changed)
        return page
    def on_url_changed(self,url):
        self.setUrl(url)
if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    window = QtWidgets.QMainWindow()
    webbrowser = WebEngineView()
    webbrowser.load(QtCore.QUrl("http://127.0.0.1:8000"))
    window.setCentralWidget(webbrowser)
    window.show()
    sys.exit(app.exec_())
