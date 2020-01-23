# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'headerFileDialog.ui'
#
# Created by: PyQt5 UI code generator 5.6
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_headerFileDialog(object):
    def setupUi(self, headerFileDialog):
        headerFileDialog.setObjectName("headerFileDialog")
        headerFileDialog.resize(760, 442)
        self.gridLayout = QtWidgets.QGridLayout(headerFileDialog)
        self.gridLayout.setObjectName("gridLayout")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem)
        self.pushButton_ok = QtWidgets.QPushButton(headerFileDialog)
        self.pushButton_ok.setObjectName("pushButton_ok")
        self.horizontalLayout.addWidget(self.pushButton_ok)
        self.pushButton_cancel = QtWidgets.QPushButton(headerFileDialog)
        self.pushButton_cancel.setObjectName("pushButton_cancel")
        self.horizontalLayout.addWidget(self.pushButton_cancel)
        self.gridLayout.addLayout(self.horizontalLayout, 5, 0, 1, 5)
        self.label_2 = QtWidgets.QLabel(headerFileDialog)
        self.label_2.setObjectName("label_2")
        self.gridLayout.addWidget(self.label_2, 0, 0, 1, 1)
        self.projectName_qle = QtWidgets.QLineEdit(headerFileDialog)
        self.projectName_qle.setObjectName("projectName_qle")
        self.gridLayout.addWidget(self.projectName_qle, 0, 1, 1, 1)
        self.label_4 = QtWidgets.QLabel(headerFileDialog)
        self.label_4.setObjectName("label_4")
        self.gridLayout.addWidget(self.label_4, 1, 0, 1, 3)
        self.tempdir_qpb = QtWidgets.QPushButton(headerFileDialog)
        self.tempdir_qpb.setMinimumSize(QtCore.QSize(100, 0))
        self.tempdir_qpb.setMaximumSize(QtCore.QSize(120, 16777215))
        self.tempdir_qpb.setObjectName("tempdir_qpb")
        self.gridLayout.addWidget(self.tempdir_qpb, 2, 4, 1, 1)
        self.label_3 = QtWidgets.QLabel(headerFileDialog)
        self.label_3.setObjectName("label_3")
        self.gridLayout.addWidget(self.label_3, 0, 2, 1, 1)
        self.headfiles_qpb = QtWidgets.QPushButton(headerFileDialog)
        self.headfiles_qpb.setMaximumSize(QtCore.QSize(120, 16777215))
        self.headfiles_qpb.setObjectName("headfiles_qpb")
        self.gridLayout.addWidget(self.headfiles_qpb, 3, 4, 1, 1)
        self.tempdir_qle = QtWidgets.QLineEdit(headerFileDialog)
        self.tempdir_qle.setObjectName("tempdir_qle")
        self.gridLayout.addWidget(self.tempdir_qle, 2, 0, 1, 3)
        self.headfilexx4x_if_qle = QtWidgets.QLineEdit(headerFileDialog)
        self.headfilexx4x_if_qle.setObjectName("headfilexx4x_if_qle")
        self.gridLayout.addWidget(self.headfilexx4x_if_qle, 3, 0, 1, 3)
        spacerItem1 = QtWidgets.QSpacerItem(338, 79, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.gridLayout.addItem(spacerItem1, 4, 0, 1, 2)
        spacerItem2 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout.addItem(spacerItem2, 2, 3, 1, 1)
        spacerItem3 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout.addItem(spacerItem3, 3, 3, 1, 1)
        self.componentName_qle = QtWidgets.QLineEdit(headerFileDialog)
        self.componentName_qle.setObjectName("componentName_qle")
        self.gridLayout.addWidget(self.componentName_qle, 0, 3, 1, 2)

        self.retranslateUi(headerFileDialog)
        QtCore.QMetaObject.connectSlotsByName(headerFileDialog)

    def retranslateUi(self, headerFileDialog):
        _translate = QtCore.QCoreApplication.translate
        headerFileDialog.setWindowTitle(_translate("headerFileDialog", "Prepare"))
        self.pushButton_ok.setText(_translate("headerFileDialog", "OK"))
        self.pushButton_cancel.setText(_translate("headerFileDialog", "Cancel"))
        self.label_2.setText(_translate("headerFileDialog", "项目名(eg:506,301c)"))
        self.label_4.setText(_translate("headerFileDialog", "确定临时文件夹路径,统一存放本次操作的生成文件(格式:temp_项目名+\'VT\'+组件名,eg:temp_506VTAE)"))
        self.tempdir_qpb.setText(_translate("headerFileDialog", "1.文件夹路径"))
        self.label_3.setText(_translate("headerFileDialog", "组件名(eg:AE,WS)"))
        self.headfiles_qpb.setText(_translate("headerFileDialog", "头文件路径可多选(4A/4T)"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    headerFileDialog = QtWidgets.QDialog()
    ui = Ui_headerFileDialog()
    ui.setupUi(headerFileDialog)
    headerFileDialog.show()
    sys.exit(app.exec_())

