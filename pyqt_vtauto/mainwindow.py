#coding:utf-8

import ui_mainwindow
import ui_headerFileDialog
import excelCheck_debug
import collectExcelInfo
import parseheadfile
import generateCodefile
import excelToXML
import xmlToUi
import sys
import os
import time
import xlrd
from xlutils.copy import copy
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
#from PyQt5 import (QtCore, QtGui, QtWidgets,)
#from PyQt5.QtWidgets import (QApplication, QMessageBox, QMainWindow, QPushButton,QFileDialog,)
m_excelName=""
m_tempdir = ""
m_CCName = ""
m_headFilesList = []
gTempProDir=""
g_developer =""
existXX4A = False
existXX4T = False
dict_pageToFuns = {}
class MainWindow(QMainWindow, ui_mainwindow.Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)

        self.prepare_qtb.clicked.connect(self.stepButtonClicked)  # buttonclicked()
        self.step1_qtb.clicked.connect(self.stepButtonClicked)
        self.step2_qtb.clicked.connect(self.stepButtonClicked)
        self.step3_qtb.clicked.connect(self.stepButtonClicked)

        self.step5_qtb.clicked.connect(self.stepButtonClicked)

        self.step7_qtb.clicked.connect(self.stepButtonClicked)
        self.step8_qtb.clicked.connect(self.stepButtonClicked)


        self.check_requirement_qpb.clicked.connect(self.operatorButtonClicked)
        self.check_requirement_qpb2.clicked.connect(self.operatorButtonClicked)
        self.createTempDir_qpb.clicked.connect(self.operatorButtonClicked)
        self.addOtherPage_qpb.clicked.connect(self.operatorButtonClicked)
        self.displayfunsInfo_qpb.clicked.connect(self.operatorButtonClicked)
        self.headFileProcess_qpb.clicked.connect(self.operatorButtonClicked)
        self.addenum_qpb.clicked.connect(self.operatorButtonClicked)
        #self.displayfunsInfo_qpb.clicked.connect(self.operatorButtonClicked())
        self.headFileProcess_qpb.clicked.connect(self.operatorButtonClicked)
        self.generateUniversalvtfile_qpb.clicked.connect(self.operatorButtonClicked)
        self.generate_xmlfile_qpb.clicked.connect(self.operatorButtonClicked)
        self.generator_headfiles_qpb.clicked.connect(self.operatorButtonClicked)
        self.parse_excelFunsXml_qpb.clicked.connect(self.operatorButtonClicked)
        self.parse_excelXmlForUi_qpb.clicked.connect(self.operatorButtonClicked)

        self.tempdir_qpb.clicked.connect(self.fileButtonClicked)
        self.filebtn_1.clicked.connect(self.fileButtonClicked)
        self.copy_xlsfile_to_tempdir_qpb.clicked.connect(self.fileButtonClicked)


        self.importToTreeWidegt_qpb.clicked.connect(self.addFunsToTreeWidget_slot)
        self.deleteFromTreeWidegt_qpb.clicked.connect(self.deleteFromTreeWidget_slot)
        self.xmlindex_qcb.currentIndexChanged.connect(self.showxmlfiles)


        self.stackedWidget.setCurrentIndex(0)
        self.tabWidget_xuqiu_qtw.setCurrentIndex(0)
        self.tabWidget.setCurrentIndex(0)
        self.resultOutput_qte.setReadOnly(True)
        self.resultOutput_qte2.setReadOnly(True)
        self.xmldisplay_qte.setReadOnly(True)
        self.cppfiles_qte.setReadOnly(True)
        self.uifiles_qtb.setReadOnly(True)
        self.requirement_rule_qte.setReadOnly(True)

        self.InitializeTreeWidget()

        self.projectName_qle.setText('506')
        self.componentName_qle.setText('EC')
        self.development_engineer_qle.setText('yuzt')


    def stepButtonClicked(self):
        sender = self.sender().text()
        if sender == '准备工作':
            self.stackedWidget.setCurrentIndex(0)
        if  sender == 'step1 检查需求表格规范':
            self.stackedWidget.setCurrentIndex(1)
        if  sender == 'step2 收集表格信息':
            self.stackedWidget.setCurrentIndex(2)
        if  sender == 'step3 收集接口信息':
            self.stackedWidget.setCurrentIndex(3)

        if  sender == 'step5 生成xml文件':
            self.stackedWidget.setCurrentIndex(4)

        if  sender == 'step7 生成代码文件':
            self.stackedWidget.setCurrentIndex(5)
        if  sender == 'step8 生成界面文件':
            self.stackedWidget.setCurrentIndex(6)

    def fileButtonClicked(self):
        sender = self.sender().text()
        if sender == 'No.3 选择':
            fileName = QFileDialog.getOpenFileName(self, "Open File",
                                                          QDir.currentPath(),
                                                          "*.xls")
            if (fileName[0]!=''):
                print('fileName=',fileName[0])
                self.xlsfileName_qle.setText(fileName[0])

        if  sender == 'No.1 选择':
                if ('' == self.projectName_qle.text()  or  '' == self.componentName_qle.text()):
                    QMessageBox.critical(self, "Error", "Please select Project and Component First!!!\n")
                else:
                    dirstr = QFileDialog.getExistingDirectory(self, "Open Directory",
                                                              QDir.currentPath(),
                                                              QFileDialog.ShowDirsOnly | QFileDialog.DontResolveSymlinks)
                    if os.path.exists(dirstr):
                        self.tempdir_qle.setText(dirstr)
                        global m_tempdir
                        global gTempProDir
                        global g_developer
                        m_tempdir = dirstr
                        gTempProDir= 'temp_'+self.projectName_qle.text()+'VT'+self.componentName_qle.text()
                        g_developer = self.development_engineer_qle.text()




        if sender =='No.4 copy':
            xlsFileNamePath = self.xlsfileName_qle.text()
            print("xlsFileNamePath=", self.xlsfileName_qle.text())
            if xlsFileNamePath =='':
                QMessageBox.critical(self, "Error", "xls file is empty!\n")
                return

            excelName = xlsFileNamePath.split('/')[-1]
            indexNum = xlsFileNamePath.index(excelName)
            subXlsFilePath = xlsFileNamePath[:(indexNum - 1)]
            global m_excelName
            m_excelName = excelName
            print("excelName=%s" % (excelName))
            print("subXlsFilePath=", subXlsFilePath)  # 原需求表格所在位置
            if (m_tempdir != subXlsFilePath):
                # 将需求表格拷贝到temp_xxx目录

                xlsFile = m_tempdir + "/" +gTempProDir+'/'+ excelName

                if not os.path.exists(xlsFile):
                    result = QFile.copy(xlsFileNamePath, xlsFile)
                    print('result=',result)
                    if not result:
                        QMessageBox.critical(self, "Error", "xls file copy failed!\n")
                    else:
                        QMessageBox.warning(self, "Success", "xls file copy success!\n")
                else:
                    # 存在需求表格, 先删在拷
                    os.remove(xlsFile)
                    result = os.path.exists(xlsFile)

                    if result:
                        QMessageBox.critical(self, "Error", "xls file remove failed!\n")

                    else:
                        QMessageBox.warning(self, "success", "Tempdir xls file remove success!\n")
                        result = QFile.copy(xlsFileNamePath, xlsFile)
                        if not result:
                            QMessageBox.critical(self, "Error", "xlsfile exist,xls file copy failed!\n")
                        else:
                            QMessageBox.warning(self, "success", " xls file copy to tempdir success!\n")


    def operatorButtonClicked(self):
        CCName = m_CCName
        ExcelPath = m_tempdir + '/' + gTempProDir
        ExcelName = m_excelName
        sender = self.sender().text()

        if (sender == '检查需求表格规范'):
            oldwb = xlrd.open_workbook(ExcelPath + '/' + ExcelName, formatting_info=True)  # excel 多单元格合并
            check_result = open(ExcelPath + "/excelRuleCheckResult.txt", 'w')
            oldws = oldwb.sheet_by_index(2)  # 无write方法
            nrows = oldws.nrows
            ncols = oldws.ncols
            for i in range(3, nrows + 1):
                try:
                    row_value = oldws.row_values(i, 0, ncols)
                    if set(row_value) == {''}:
                        m_row_num = i
                        break
                    else:
                        pass
                except IndexError:
                    m_row_num = nrows
            check_result.write("显示检查结果：\n")
            check_result.write("--------------step1 检查需求表格规范------>start.\n")
            check_result.write("ExcelName = %s\n" % ExcelName)
            # check_result.write('tempdirpath=%s\n' %tempdirpath)
            check_result.write('m_row_num=%d,对应需求表格的行标\n' % m_row_num)  # 此与xls行标对应！！！

            newwb = copy(oldwb)
            newws = newwb.get_sheet(2)  # 有write方法。

            # 每次检查之前先使表格样式为白色。
            for i in range(3, m_row_num):
                for j in range(11):
                    cell_value = oldws.cell(i, (j + 1)).value
                    newws.write(i, (j + 1), cell_value, excelCheck_debug.styleWhite)

            excelCheck_debug.oldwsExcelInformation(oldws, m_row_num, check_result)
            excelCheck_debug.preProcessExcel(newws)  # 对精度，单位的处理，都可以先行检查。
            excelCheck_debug.checkRange(newws, check_result)  # 对范围进一步检查

            excelCheck_debug.funsIndex1(oldwb, CCName)
            excelCheck_debug.funsIndex2(oldwb, m_row_num)
            excelCheck_debug.funsCheck(check_result, ExcelPath)

            os.remove(ExcelPath + '/' + ExcelName)
            newwb.save(ExcelPath + '/' + ExcelName)
            check_result.write('--------------step1 检查需求表格规范------>end.\n')
            check_result.close()
            self.displayResult(sender)
            self.displayFunsToQlw() #???


        if (sender == ' 收集需求表格信息'):
            log = open(ExcelPath + "/excelInfos.txt", 'w')
            self.pageToFuns()

            wb = xlrd.open_workbook(ExcelPath + '/' + ExcelName, formatting_info=True)  # excel 多单元格合并
            collectExcelInfo.global_varibale(wb, CCName, log, ExcelPath)
            collectExcelInfo.read_excel_index1(wb, CCName, log)
            collectExcelInfo.read_excel_index2(wb, log)
            self.displayResult(sender)



        if (sender == 'No.2 创建文件夹'):
            self.createTempDir(self.projectName_qle.text(), self.componentName_qle.text())

        if (sender == 'Add Page'):
            if (self.addPageName_qle.text() == ''):
                QMessageBox.warning(self, "Add Page To Right", "页面名称不能为空。")
            else:
                newItem = QTreeWidgetItem(self.funs_treeWidget)
                newItem.setText(0, self.addPageName_qle.text())


        if (sender == '显示头文件列表'):
            filedialogInstance=HeaderFileDialog()
            filedialogInstance.openFileDialog(existXX4A,existXX4T)
            filedialogInstance.exec()
            self.checkHeaderFiles(existXX4A, existXX4T)
            print("m_headFilesList = ",m_headFilesList)
            self.displayHeaderFilesPathToUi()

        if (sender == '头文件预处理'):
            log = open(ExcelPath + "/headfileInfos.txt", 'w')
            parseheadfile.preprocess_header_files(m_CCName,ExcelPath,existXX4A,existXX4T)
            parseheadfile.generate_requirefuns_tempfile(m_CCName,ExcelPath,existXX4A,existXX4T,dict_pageToFuns,log)
            parseheadfile.collect_struct_enum(ExcelPath+'/'+'temp_HeaderFiles',m_headFilesList,ExcelPath)

        if (sender == '补充枚举到需求表格'):
            log = open(ExcelPath + "/enuminfo.txt", 'w')
            log.write('step.将VT 界面接口需要的枚举提前写到excel 中。')
            oldwb = xlrd.open_workbook(ExcelPath + '/' + ExcelName, formatting_info=True)  # excel 多单元格合并
            newwb = copy(oldwb)
            newws = newwb.get_sheet('enum')
            set_enumUi = set(collectExcelInfo.list_enumUi)
            parseheadfile.enumWriteToExcel(newws, parseheadfile.dict_enum, set_enumUi)
            os.remove(ExcelPath + '/' + ExcelName)
            newwb.save(ExcelPath + '/' + ExcelName)
            time.sleep(2)
            print("执行下一条步骤，请填充需求表格enmu 页 枚举值在界面的显示样式！")
            result = os.popen('cmd /c '+ExcelPath+'/'+ExcelName)
            print("cmd result=",result)
            newwb = xlrd.open_workbook(ExcelPath + '/' + ExcelName, formatting_info=True)  # excel 多单元格合并

            parseheadfile.enumForUi(newwb, log)  # 将枚举收集到字典里


        if (sender =='生成通用代码文件'):
                print("step 7.生成XXVT.* 代码文件(各项目通用)。")
                generateCodefile.codefileUniversal(m_CCName, g_developer, list(dict_pageToFuns.keys()), ExcelPath)
                self.cppfiles_qte.clear()
                for files in os.walk(ExcelPath+"/Outcodefiles"):
                    self.cppfiles_qte.append(str(files))
        if (sender =='生成各页面头文件'):
            print("step 8.生成各组件对应子页面头文件")
            print('step:待定：XXVT.h,XXVT.cpp,XXVT_if.h,XXVT_tc.h')
            log = open(ExcelPath + "/codeinfos.txt", 'w')
            generateCodefile.pageCodeHeadFiles(m_CCName,
                                                g_developer,
                                                list(dict_pageToFuns.keys()),
                                                existXX4T,
                                                existXX4A,
                                                dict_pageToFuns,
                                                parseheadfile.dict_funs,
                                                ExcelPath,
                                                log)

        if (sender == '生成xml文件'):
            print("step 9.由excelsheet2 生成excelFunsXml.xml")
            excelToXML.excel_to_xml(ExcelPath)
            print("step10.由excelsheet2 生成excelXmlForUi.xml")
            oldwb = xlrd.open_workbook(ExcelPath + '/' + ExcelName, formatting_info=True)  # excel 多单元格合并
            #newwb = copy(oldwb)
            excelToXML.excelToXmlForUi(oldwb,
                                       collectExcelInfo.dict_funSh1Index,
                                       collectExcelInfo.dict_layouttab,
                                       collectExcelInfo.dict_tab1Index,
                                       collectExcelInfo.dict_funsShee2,
                                       parseheadfile.dict_enumForUi,
                                       parseheadfile.dict_enum,
                                       ExcelPath)
            self.showxmlfiles()
        if (sender =='解析xml文件excelFunsXml'):
            print("step 11.解析excelFunsXml.xml，生成cpp特有接口。")
            log = open(ExcelPath + "/codeinfos.txt", 'w')
            excelToXML.xmlToBottomCpp(m_CCName,
                                      dict_pageToFuns,
                                      parseheadfile.dict_enum,
                                      parseheadfile.dict_funs,
                                      collectExcelInfo.dict_table_params,
                                      ExcelPath,
                                      log)

            self.cppfiles_qte.clear()
            for files in os.walk(ExcelPath + "/Outcodefiles"):
                self.cppfiles_qte.append(files)
        if (sender =='解析xml文件excelXmlForUi'):
            print("step 12.解析excelXmlForUi.xml，生成ui界面。")
            xmlToUi.xmlToUi(m_CCName, ExcelPath, dict_pageToFuns)
            self.cppfiles_qte.clear()
            for files in os.walk(ExcelPath + "/Outcodefiles"):
                self.uifiles_qtb.append(files)


    def displayHeaderFilesPathToUi(self):
        subFunNameList = []
        self.headfilespath_qtb.resizeColumnsToContents() # 根据内容自动调整给定列宽
        self.headfilespath_qtb.clear()
        self.headfilespath_qtb.setColumnCount(2)
        headers = ["所需头文件列表","头文件本地路径"]
        self.headfilespath_qtb.setHorizontalHeaderLabels(headers)
        for row,headfilename in enumerate(m_headFilesList):
            item = QTableWidgetItem(headfilename)
            item.setData(Qt.UserRole,headfilename)
            self.headfilespath_qtb.insertRow(row) #！！！
            self.headfilespath_qtb.setItem(row,0,item)
        QMessageBox.warning(self, "check files", "请确认头文件已是最新版本！")

    def InitializeTreeWidget(self):
        self.funs_treeWidget.clear()
        self.funs_treeWidget.setColumnCount(1)
        self.funs_treeWidget.setHeaderLabel("Layout Infomation")

        pageGeneral = QTreeWidgetItem(self.funs_treeWidget)
        pageGeneral.setText(0, "General")

        pageApp = QTreeWidgetItem(self.funs_treeWidget)
        pageApp.setText(0, "Application")

        pagePer = QTreeWidgetItem(self.funs_treeWidget)
        pagePer.setText(0, "Peripheral")

        pageMaintenance = QTreeWidgetItem(self.funs_treeWidget)
        pageMaintenance.setText(0, "Maintenance")

    def displayResult(self,sender):

        codec = QTextCodec.codecForName("GB2312");
        if sender == '检查需求表格规范':
            fileOut = m_tempdir +'/'+gTempProDir+ "/excelRuleCheckResult.txt"
            file = open(fileOut,'r')
            self.resultOutput_qte.clear()
            lines = file.readlines()
            for line in lines:
                #str = codec.toUnicode(self,line)
                self.resultOutput_qte.append(line)
            file.close()

        if sender == ' 收集需求表格信息':
            fileout2 = m_tempdir + '/'+gTempProDir+"/excelInfos.txt"
            file = open(fileout2,'r')
            self.resultOutput_qte2.clear()
            lines = file.readlines()
            for line in lines:
                tempstr = codec.toUnicode(codec.fromUnicode(line))
                self.resultOutput_qte2.append(tempstr)
            file.close()


    def displayFunsToQlw(self):
       for funsItem in excelCheck_debug.fun_list_sh1:
            self.funs_qlw.insertItem(0, funsItem)
            self.funs_qlw.setSelectionMode(QAbstractItemView.MultiSelection) # 设置选择模式

    def addFunsToTreeWidget_slot(self):
        list = ((self.funs_qlw.selectedItems()))  # listWidget.item(row).text()
        #print('list=',list)
        if (len(list)<= 0):
            QMessageBox.warning(self,
                    "Add Function to TreeWidget",
                    "Selected Interface(s) From Left first.")
        else:
            parent = self.funs_treeWidget.currentItem().parent()# 判断当前项目是否有父节点
            if (parent):
                QMessageBox.warning(self,
                        "Add Function to TreeWidget",
                        "Selected Item Is Not Top Level Drop.")
            else: #None
                for i in range(len(list)):
                    rowNum = self.funs_qlw.row(list[i])
                    interfaceName = self.funs_qlw.item(rowNum).text()
                    newItem = QTreeWidgetItem(self.funs_treeWidget.currentItem()) # !!!for 里面新建。
                    newItem.setText(0, interfaceName)
                    self.funs_qlw.takeItem(rowNum) # removeItemWidget(QListWidgetItem * item)
        self.funs_treeWidget.setItemsExpandable(True)
        self.funs_treeWidget.expandAll()


    def deleteFromTreeWidget_slot(self):
        parent = self.funs_treeWidget.currentItem().parent()
        if (parent): # parent != null
            index = parent.indexOfChild(self.funs_treeWidget.currentItem())
            print("delete index=" ,index)

            funName = parent.takeChild(index).text(0)
            parent.takeChild(index)

            rowlistwidget = self.funs_qlw.count() # 得到子项总数
            self.funs_qlw.insertItem(rowlistwidget + 1, funName)


        else: # 父节点上
            index = self.funs_treeWidget.indexOfTopLevelItem(self.funs_treeWidget.currentItem())
            print("index----=",index)
            self.funs_treeWidget.takeTopLevelItem(index)


    def createTempDir(self,projectName,componentName):
        #m_tempdir = self.tempdir_qle.text() + "/temp_" + projectName + "VT" + componentName
        global  m_CCName
        m_CCName=componentName

        exist = os.path.exists(m_tempdir+'/'+gTempProDir)
        if (exist):
            QMessageBox.warning(self, "创建文件夹", "文件夹temp_" + projectName + "VT" + componentName + "已经存在！")
        else:
            os.mkdir(m_tempdir+'/'+gTempProDir)
            ok = os.path.exists(m_tempdir+'/'+gTempProDir)
            if (ok):
                QMessageBox.warning(self, "创建文件夹", "---文件夹temp_" + projectName + "VT" + componentName + "创建成功")

            else:
                QMessageBox.critical(self, "创建文件夹", "---文件夹temp_" + projectName + "VT" + componentName + "创建失败！")


    def pageToFuns(self):
        global dict_pageToFuns
        global existXX4A
        global existXX4T
        pageList=[]

        self.funs_treeWidget.setCurrentItem(self.funs_treeWidget.topLevelItem(0))
        index =self.funs_treeWidget.currentIndex()
        index1 = self.funs_treeWidget.indexBelow(index)
        #print('---index=',index,type(index))
        while index.data():
            Item = index.data()
            #print('Item---=', Item)
            ParentItem = index.parent().data()
            #print('ParentItem=', ParentItem)

            if ParentItem == None:  # 父
                pageList.append(Item)
                index=self.funs_treeWidget.indexBelow(index)
            else:
                index=self.funs_treeWidget.indexBelow(index)
        print('pageList=',pageList)



        print("index1.data=",index1.data())
        for pageindex in range(len(pageList)):
            tempfunslist = []
            parentPage=""
            #print("parent=",index1.parent().data())
            while index1.parent().data():
                parentPage=index1.parent().data()
                #print("parentPage=",parentPage)
                tempfunslist.append(index1.data())
                if (str(index1.data())[0:4] == m_CCName + "4A"):  # 去字符串开头4个字符
                    existXX4A = True
                if (str(index1.data())[0:4] == m_CCName + "4T"):
                    existXX4T = True
                index1 = self.funs_treeWidget.indexBelow(index1)
            index1 = self.funs_treeWidget.indexBelow(index1)
            #print("tempfunslist=",tempfunslist)
            if tempfunslist !=[]:
                dict_pageToFuns[parentPage]=tempfunslist
        print("dict_pageToFuns=",dict_pageToFuns)
        print('existxx4a=%s,existxx4t=%s\n'%(existXX4A,existXX4T))


    def checkHeaderFiles(self, existXX4A, existXX4T):
        tempHeaderFilePath = m_tempdir + "/" + gTempProDir + "/temp_HeaderFiles"
        if (existXX4A):
            self.collectHeadFiles(tempHeaderFilePath, m_CCName + "4A_if.h")
        if (existXX4T):
            self.collectHeadFiles(tempHeaderFilePath, m_CCName + "4T_if.h")
    def collectHeadFiles(self,filepath,headfile):
        rx = QRegExp("^#include\\s*[:|<].*\\.h\\s*[:|>]")
        #headfilename = ""
        #rx.setPattern("^#include\\s*[:|<].*\\.h\\s*[:|>]") #include <xx.h>
        rx.setCaseSensitivity(QRegExp.caseSensitivity(rx))

        headfilepath = filepath+'/'+headfile
        fh = QFile(headfilepath)
        if (os.path.exists(headfilepath)):
            if (headfile not in m_headFilesList):
                m_headFilesList.append(headfile)
                if fh.open(QIODevice.ReadOnly):


                    stream = QTextStream(fh)
                    stream.setCodec("UTF-8")
                    while(not stream.atEnd()):
                        line = stream.readLine()

                        if (line.find("SMEE_EXPORT") or
                            line.find("typedef")):pass
                        if (rx.isValid()):
                            subline = line.replace("\"",":") #先把 “ 换成 ：，方便处理
                            if(-1!=rx.indexIn(subline)):


                                matchstrlist =[]
                                matchstrlist = rx.capturedTexts()
                                #print("matchstrlist=",matchstrlist)
                                if (-1 != matchstrlist[0].find(":")):#"xx.h"
                                    startMark = matchstrlist[0].find(":")
                                    endMark = matchstrlist[0].rfind(":")
                                    headfilename = matchstrlist[0][startMark+1:endMark]
                                    print("headfilename=",headfilename)

                                if (-1 != matchstrlist[0].find("<")):#<xx.h>
                                    startMark = matchstrlist[0].find("<")
                                    endMark = matchstrlist[0].rfind(">")
                                    headfilename = matchstrlist[0][startMark+1:endMark]
                                    print("headfilename=",headfilename)
                                self.collectHeadFiles(filepath,headfilename)
                        else:
                            QMessageBox.critical(self,"Error","regexp syntax error!\n")
                else:
                     QMessageBox.critical(self,"Error","Can't open the file ["+headfile+"]!\n")
        else:
            QMessageBox.critical(self,"Error","["+headfile+"]"+"can not exist in"+"["+filepath+"]")

    def showxmlfiles(self):
        self.xmldisplay_qte.clear()
        if self.xmlindex_qcb.currentIndex() ==0:
            fileOut = m_tempdir + '/' + gTempProDir + "/excelFunsXml.xml"
            file = open(fileOut, 'r')
            lines = file.readlines()
            for line in lines:
                self.xmldisplay_qte.append(line)
            file.close()
        if self.xmlindex_qcb.currentIndex() ==1:
            fileOut = m_tempdir + '/' + gTempProDir + "/excelXmlForUi.xml"
            file = open(fileOut, 'r')
            lines = file.readlines()
            for line in lines:
                self.xmldisplay_qte.append(line)
            file.close()


class HeaderFileDialog(QDialog, ui_headerFileDialog.Ui_headerFileDialog):
    def __init__(self, parent=None):
        super(QDialog, self).__init__(parent)
        self.setupUi(self)
        self.xx4a_qpb.clicked.connect(self.fileButtonClicked)
        self.xx4t_qpb.clicked.connect(self.fileButtonClicked)
        self.copyToTempDir_qpb.clicked.connect(self.copyHeaderFilesToDir)

    def fileButtonClicked(self):

        fileName=""
        sender = self.sender().text()
        if sender=='XX4A':
            fileName = QFileDialog.getOpenFileName(self, "Open File",
                                                    QDir.currentPath(),
                                                          "*4A_if.h")
            if (fileName[0]!=''):
                self.xx4a_qle.setText(fileName[0])
        if sender=='XX4T':
            fileName = QFileDialog.getOpenFileName(self,"Open File",
                                                          QDir.currentPath(),
                                                          "*4T_if.h")
            if (fileName[0]!=''):
                self.xx4t_qle.setText(fileName[0])

    def openFileDialog(self,xx4a,xx4t):
        if(not xx4a):
            self.xx4a_qle.hide()
            self.xx4a_qpb.hide()
            self.xx4a_qle.setEnabled(False)

        if(not xx4t):
            self.xx4t_qle.hide()
            self.xx4t_qpb.hide()
            self.xx4t_qle.setEnabled(False)

    def copyHeaderFilesToDir(self):
        self.slot_copyHeaderFileToTempDir()
    def slot_copyHeaderFileToTempDir(self):
        consttempdir = m_tempdir+"/"+gTempProDir+"/temp_HeaderFiles"
        print("dir temp_HeaderFiles=",consttempdir)
        exist =os.path.exists(consttempdir)
        if (exist):
            if(self.xx4a_qle.isEnabled() and self.xx4a_qle.text()==""):
                QMessageBox.warning(self,"拷贝文件","XX4A头文件，路径名不能为空")

            if(self.xx4t_qle.isEnabled() and self.xx4t_qle.text()==""):
                QMessageBox.warning(self,"拷贝文件","XX4T头文件，路径名不能为空")
            if(self.xx4a_qle.isEnabled() and (not self.xx4a_qle.text()=="")):
                result = False
                #将头文件拷贝到HeaderFiles目录
                strlist = self.xx4a_qle.text().split("/")
                xx4aFileName = strlist[len(strlist)-1]
                xx4aFile=consttempdir+"/"+xx4aFileName
                if (not os.path.exists(xx4aFile)):
                   result = QFile.copy(self.xx4a_qle.text(),consttempdir+"/"+xx4aFileName)
                   if(not result):
                      QMessageBox.critical(self,"Error","xx4a file copy failed!\n")
                   else:
                       QMessageBox.warning(self,"success","xx4a file copy success!\n")
                else:
                    #存在xx4a,先删在拷
                    os.remove(consttempdir+"/"+xx4aFileName)
                    if (not os.path.exists(consttempdir+"/"+xx4aFileName)):
                        QMessageBox.warning(self,"Success","xx4afile remove success!\n")
                        result = QFile.copy(self.xx4a_qle.text(),consttempdir+"/"+xx4aFileName)
                        if(not result):
                           QMessageBox.critical(self,"Error","xx4afile exist,xls file copy failed!\n")
                        else:
                           QMessageBox.warning(self,"Success","xx4afile  copy success!\n")
                    else:
                        QMessageBox.critical(self,"Error","xx4a file remove failed!\n")
            if(self.xx4t_qle.isEnabled() and (not self.xx4t_qle.text()=="")):
                result = False
                #将头文件拷贝到HeaderFiles目录
                strlist = self.xx4t_qle.text().split("/")
                xx4tFileName = strlist[len(strlist)-1]
                xx4tFile=consttempdir+"/"+xx4tFileName
                if (not os.path.exists(xx4tFile)):
                   result = QFile.copy(self.xx4t_qle.text(),consttempdir+"/"+xx4tFileName)
                   if(not result):
                      QMessageBox.critical(self,"Error","xx4t file copy failed!\n")
                   else:
                       QMessageBox.warning(self,"success","xx4t file copy success!\n")
                else:
                    #存在xx4t,先删在拷
                    os.remove(consttempdir+"/"+xx4tFileName)
                    if (not os.path.exists(consttempdir+"/"+xx4tFileName)):

                        QMessageBox.warning(self,"Success","xx4T file remove success!\n")
                        result = QFile.copy(self.xx4t_qle.text(),consttempdir+"/"+xx4tFileName)
                        if(not result):
                           QMessageBox.critical(self,"Error","xx4tfile exist,xls file copy failed!\n")
                        else:
                             QMessageBox.warning(self,"success","xx4t file  copy success!\n")
                    else:
                        QMessageBox.critical(self,"Error","xx4t file remove failed!\n")

        else:
            os.mkdir(consttempdir)
            if (os.path.exists(consttempdir)):
                QMessageBox.warning(self,"创建文件夹","文件夹temp_HeaderFiles创建成功,请再执行一次拷贝操作")
            else:
                QMessageBox.warning(self,"创建文件夹","文件夹HeaderFiles创建失败！")

#m_tempdir=G:/all_exercises/python_prjs/pyvt_auto0630/PYVTUI/VTUI
#gTempProDir=temp_506VTEC
if __name__ == "__main__":
    app = QApplication(sys.argv)
    mainWindow = MainWindow()
    mainWindow.show()

    sys.exit(app.exec_())