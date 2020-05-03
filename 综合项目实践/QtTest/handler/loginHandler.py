import views.login
from PyQt5.QtWidgets import QWidget,QApplication

if __name__ == '__main__':

    app = QApplication([])
    window = QWidget()
    ui = views.login.Ui_Form()
    ui.setupUi(window)
    window.show()
    app.exec()