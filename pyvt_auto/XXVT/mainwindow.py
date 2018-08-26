import ui_mainwindow
import sys
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import (QApplication, QMessageBox, QMainWindow, QPushButton)

class MainWindow(QMainWindow, ui_mainwindow.Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)

        self.prepare_qtb.clicked.connect(self.buttonclicked)  # buttonclicked()
        self.step1_qtb.clicked.connect(self.buttonclicked)
        self.step2_qtb.clicked.connect(self.buttonclicked)
        self.step3_qtb.clicked.connect(self.buttonclicked)
        self.step4_qtb.clicked.connect(self.buttonclicked)
        self.step5_qtb.clicked.connect(self.buttonclicked)
        self.step6_qtb.clicked.connect(self.buttonclicked)
        self.step7_qtb.clicked.connect(self.buttonclicked)
        self.step8_qtb.clicked.connect(self.buttonclicked)

        self.check_requirement_qpb.buttonClicked.connect(self.OperatorClickedSlot)

def createTempDir():

    def buttonclicked(self):
        sender = self.sender().text()
        if (sender=='准备工作'):
            self.stackedWidget.setCurrentIndex(0);
        if (sender == 'step1 检查需求表格规范'):
            self.stackedWidget.setCurrentIndex(1);
        if (sender == 'step2 收集表格信息'):
            self.stackedWidget.setCurrentIndex(2);
        if (sender =='step3 收集接口信息'):
            self.stackedWidget.setCurrentIndex(3);
        if (sender=='step4 生成通用代码文件'):
            self.stackedWidget.setCurrentIndex(4);
        if (sender=='step5 生成xml文件'):
            self.stackedWidget.setCurrentIndex(5);
        if (sender=='step6 生成各子页面头文件'):
            self.stackedWidget.setCurrentIndex(6);
        if (sender =='step7 生成代码文件'):
            self.stackedWidget.setCurrentIndex(7);
        if (sender =='step8 生成界面文件'):
            self.stackedWidget.setCurrentIndex(8);

    def OperatorClickedSlot(self):
        sender = self.sender().text()
        if (sender=='检查需求表格规范'):
            #excelCheck_debug.py
        if (sender==' 收集需求表格信息'):
            #collectExcelInfo.py
        if (sender=='No.2 创建文件夹'):
            createTempDir(ui->projectName_qle->text(),ui->componentName_qle->text());



if __name__ == "__main__":
    app = QApplication(sys.argv)
    mainWindow = MainWindow()
    mainWindow.show()
    sys.exit(app.exec_())