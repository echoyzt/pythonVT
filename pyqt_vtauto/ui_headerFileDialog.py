# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'headerFileDialog.ui'
#
# Created by: PyQt5 UI code generator 5.10.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_headerFileDialog(object):
    def setupUi(self, headerFileDialog):
        headerFileDialog.setObjectName("headerFileDialog")
        headerFileDialog.resize(400, 213)
        self.gridLayout = QtWidgets.QGridLayout(headerFileDialog)
        self.gridLayout.setObjectName("gridLayout")
        self.lineEdit = QtWidgets.QLineEdit(headerFileDialog)
        self.lineEdit.setEnabled(False)
        self.lineEdit.setObjectName("lineEdit")
        self.gridLayout.addWidget(self.lineEdit, 0, 0, 1, 1)
        self.xx4a_qle = QtWidgets.QLineEdit(headerFileDialog)
        self.xx4a_qle.setObjectName("xx4a_qle")
        self.gridLayout.addWidget(self.xx4a_qle, 1, 0, 1, 2)
        self.xx4a_qpb = QtWidgets.QPushButton(headerFileDialog)
        self.xx4a_qpb.setObjectName("xx4a_qpb")
        self.gridLayout.addWidget(self.xx4a_qpb, 1, 2, 1, 1)
        self.xx4t_qle = QtWidgets.QLineEdit(headerFileDialog)
        self.xx4t_qle.setObjectName("xx4t_qle")
        self.gridLayout.addWidget(self.xx4t_qle, 2, 0, 1, 2)
        self.xx4t_qpb = QtWidgets.QPushButton(headerFileDialog)
        self.xx4t_qpb.setObjectName("xx4t_qpb")
        self.gridLayout.addWidget(self.xx4t_qpb, 2, 2, 1, 1)
        spacerItem = QtWidgets.QSpacerItem(338, 79, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.gridLayout.addItem(spacerItem, 3, 0, 1, 3)
        spacerItem1 = QtWidgets.QSpacerItem(263, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout.addItem(spacerItem1, 4, 0, 1, 1)
        self.copyToTempDir_qpb = QtWidgets.QPushButton(headerFileDialog)
        self.copyToTempDir_qpb.setObjectName("copyToTempDir_qpb")
        self.gridLayout.addWidget(self.copyToTempDir_qpb, 4, 2, 1, 1)

        self.retranslateUi(headerFileDialog)
        QtCore.QMetaObject.connectSlotsByName(headerFileDialog)

    def retranslateUi(self, headerFileDialog):
        _translate = QtCore.QCoreApplication.translate
        headerFileDialog.setWindowTitle(_translate("headerFileDialog", "Dialog"))
        self.lineEdit.setText(_translate("headerFileDialog", "接口头文件位置："))
        self.xx4a_qpb.setText(_translate("headerFileDialog", "XX4A"))
        self.xx4t_qpb.setText(_translate("headerFileDialog", "XX4T"))
        self.copyToTempDir_qpb.setText(_translate("headerFileDialog", "拷贝到临时文件夹"))


