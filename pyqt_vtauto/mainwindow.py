#coding:utf-8

import ui_mainwindow
import ui_headerFileDialog
import excelCheck_debug
import collectExcelInfo
import parseheadfile as phf
import EDS_VTXX
import generateCodefile
import excelToXML
import xmlToUi
import sys,re,time,xlrd,shutil,os
from xlutils.copy import copy
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *

m_excelName=""
m_tempdir = ""
m_CCName = ""
m_headFilesList = []
tempheadfilelist = []
gTempProDir=""
g_developer =""
ExcelPath=""
destinationDir=""
existXX4A = False
existXX4T = False
dict_pageToFuns = {}
#dict_pageToFuns是页面得来，dict_pages从需求表格得来。
class MainWindow(QMainWindow, ui_mainwindow.Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)
        #---------------navigation-----------------------
        self.step1_qtb.clicked.connect(self.stepButtonClicked)
        self.step2_qtb.clicked.connect(self.stepButtonClicked)
        self.step3_qtb.clicked.connect(self.stepButtonClicked)


        #-----------------operator---------------------
        self.check_requirement_qpb.clicked.connect(self.operatorButtonClicked)
        self.check_requirement_qpb2.clicked.connect(self.operatorButtonClicked)
        self.addOtherPage_qpb.clicked.connect(self.operatorButtonClicked)
        self.displayfunsInfo_qpb.clicked.connect(self.operatorButtonClicked)
        self.headFileProcess_qpb.clicked.connect(self.operatorButtonClicked)
        self.addenum_qpb.clicked.connect(self.operatorButtonClicked)
        self.headFileProcess_qpb.clicked.connect(self.operatorButtonClicked)
        self.generateUniversalvtfile_qpb.clicked.connect(self.operatorButtonClicked)
        self.generate_xmlfile_qpb.clicked.connect(self.operatorButtonClicked)
        self.generator_headfiles_qpb.clicked.connect(self.operatorButtonClicked)
        self.parse_excelFunsXml_qpb.clicked.connect(self.operatorButtonClicked)
        self.parse_excelXmlForUi_qpb.clicked.connect(self.operatorButtonClicked)
        self.parseheaderfile_qpb.clicked.connect(self.operatorButtonClicked)
        self.copyexcelmodel_qtb.clicked.connect(self.operatorButtonClicked)
        self.update_excelinfo_qpb.clicked.connect(self.operatorButtonClicked)
        self.funsToExcelXml_qtb.clicked.connect(self.operatorButtonClicked)
        self.createExcelsheet_qpb.clicked.connect(self.operatorButtonClicked)
        self.updateexcel_qpb.clicked.connect(self.operatorButtonClicked)
        self.checkexcel_qpb.clicked.connect(self.operatorButtonClicked)
        self.closeExcel_qpb.clicked.connect(self.operatorButtonClicked)
        self.changeTocurrent6_qpb.clicked.connect(self.operatorButtonClicked)

        #-------------------file operator-------------------
        self.filebtn_1.clicked.connect(self.fileButtonClicked)
        self.excelcollect_btn.clicked.connect(self.fileButtonClicked)

        #treewidget-----
        self.importToTreeWidegt_qpb.clicked.connect(self.addFunsToTreeWidget_slot)
        self.deleteFromTreeWidegt_qpb.clicked.connect(self.deleteFromTreeWidget_slot)
        self.xmlindex_qcb.currentIndexChanged.connect(self.showxmlfiles)


        #initialize setting
        self.stackedWidget.setCurrentIndex(0)
        self.tabWidget_xuqiu_qtw.setCurrentIndex(0)
        self.tabWidget.setCurrentIndex(0)
        self.resultOutput_qte.setReadOnly(True)
        self.resultOutput_qte2.setReadOnly(True)
        self.xmldisplay_qte.setReadOnly(True)
        self.cppfiles_qte.setReadOnly(True)
        self.requirement_rule_qte.setReadOnly(True)
        self.InitializeTreeWidget()
        self.development_engineer_qle.setText('yuzt')
        self.opstype_qtw.setCurrentIndex(0)

        filedialogInstance=HeaderFileDialog()
        filedialogInstance.exec()


    def stepButtonClicked(self):
        sender = self.sender().text()
        if sender == '1需求表格更新':
            self.stackedWidget.setCurrentIndex(1)
        if  sender == '2需求表格检查':
            self.stackedWidget.setCurrentIndex(2)
        if  sender == 'step1 收集表格信息':
            self.stackedWidget.setCurrentIndex(3)
            self.tabWidget.setCurrentIndex(1)
        if  sender == 'step2 生成xml文件':
            self.stackedWidget.setCurrentIndex(5)
        if  sender == 'step3 生成代码/界面文件':
            self.stackedWidget.setCurrentIndex(4)
            self.groupBox_2.hide()


    #def GlobalInitialize(self):

    def fileButtonClicked(self):
        sender = self.sender().text()
        if sender == '选择':
            global m_excelName
            fileName = QFileDialog.getOpenFileName(self, "Open File",
                                                          QDir.currentPath(),
                                                          #"*.txt;;*.h;;*.cpp;;*.xls")
                                                            "*.xls")
            if (fileName[0]!=''):
                print('fileName=',fileName[0])
                self.xlsfileName_qle.setText(fileName[0].replace("/","\\"))
            xlsFileNamePath = self.xlsfileName_qle.text()
            excelName = xlsFileNamePath.split('\\')[-1]
            m_excelName = excelName
            print("m_excelName=%s" % (excelName))
        if sender=="选择需求表格":
            fileName = QFileDialog.getOpenFileName(self, "Open File",
                                                   QDir.currentPath(),
                                                   # "*.txt;;*.h;;*.cpp;;*.xls")
                                                   "*.xls")
            if (fileName[0] != ''):
                self.excelcollectPath_qle.setText(fileName[0].replace("/", "\\"))
            xlsFileNamePath = self.excelcollectPath_qle.text()
            excelName = xlsFileNamePath.split('\\')[-1]
            m_excelName = excelName
            print("m_excelName=%s" % (excelName))


    def operatorButtonClicked(self):
        sender = self.sender().text()
        if (sender=='1需求表格更新'):
            self.stackedWidget.setCurrentIndex(1)
        if (sender=='2需求表格检查'):
            self.stackedWidget.setCurrentIndex(2)


        if (sender=='获取接口列表'):
            log = open(ExcelPath + "\\2excelInfos.txt", 'w')
            headertemplist = []
            self.funs_qlw.clear()
            for file in tempheadfilelist:
                headertemplist.append(destinationDir+'\\'+'temp_HeaderFiles'+'\\'+(file.replace("/","\\")).split('\\')[-1])
            print("headertemplist=",headertemplist)
            for file in headertemplist:
                if os.path.exists(file):
                    filename = open(file, 'r')
                    file1_line_infos = filename.readlines()
                    for line in file1_line_infos:
                        if line != '\n':
                            #m = re.search(r'^SMEE_EXPORT.*SMEE_INT32.*\($', line)
                            m = re.search(r'^SMEE_EXPORT', line)
                            if m:
                                tline2=(line[line.find('SMEE_EXPORT')+11:line.rfind('(')]).strip()
                                #print("tline2=", tline2)
                                tline3=(tline2[tline2.find('SMEE_INT32')+10:]).strip()
                                #print("tline3=", tline3)
                                if ("_req" in tline3) or ("_wait" in tline3) or ("_fcn" in tline3):pass
                                else:
                                    #写到列表中
                                    self.funs_qlw.insertItem(0, tline3)
                                    self.funs_qlw.setSelectionMode(QAbstractItemView.MultiSelection)  # 设置选择模式
                        else:pass
                    filename.close()
                else:print("no the file")
            log.close()


        if (sender == '拷贝需求表格模板'):
            global  m_excelName
            dirstr = QFileDialog.getOpenFileName(self, "Excel File",QDir.currentPath(),"*.xls")
            if (dirstr[0] != ''):
                tempdirName = dirstr[0].replace("/", "\\")
                print("excel name=",tempdirName)
                try:
                    shutil.copy(tempdirName, m_tempdir+ '\\' + gTempProDir)
                    excelName = tempdirName.split('\\')[-1]
                    m_excelName = excelName
                    print("m_excelName=%s" % (excelName))
                except PermissionError:
                    QMessageBox.warning(self, "Warning", "The Excel File Is Open,Close And Again!\n")


        if (sender == '检查需求表格规范'):
            xlsFileNamePath = self.xlsfileName_qle.text()
            if xlsFileNamePath == '':
                QMessageBox.critical(self, "Error", "xls file is empty!\n")
                return
            oldwb = xlrd.open_workbook(ExcelPath + '\\' + m_excelName, formatting_info=True)  # excel 多单元格合并
            check_result = open(ExcelPath + "\\1excelRuleCheckResult.txt", 'w')
            oldws = oldwb.sheet_by_index(2)  # 无write方法
            nrows = oldws.nrows
            ncols = oldws.ncols
            for i in range(3, nrows + 1):
                try:
                    row_value = oldws.row_values(i, 0, ncols)
                    if set(row_value) == {''}:
                        m_row_num = i
                        break
                    else:pass
                except IndexError:
                    m_row_num = nrows
            check_result.write("显示检查结果：\n")
            check_result.write("--------------step检查需求表格规范------>start.\n")
            check_result.write("ExcelName = %s\n" % m_excelName)
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
            excelCheck_debug.preProcessExcel(newws,check_result)  # 对精度，单位的处理，都可以先行检查。
            excelCheck_debug.checkRange(newws, check_result)  # 对范围进一步检查

            excelCheck_debug.funsIndex1(oldwb, m_CCName)
            excelCheck_debug.funsIndex2(oldwb, m_row_num)
            excelCheck_debug.funsCheck(check_result, ExcelPath)

            os.remove(ExcelPath + '\\' + m_excelName)
            newwb.save(ExcelPath + '\\' + m_excelName)
            check_result.write('--------------step检查需求表格规范------>end.\n')
            check_result.close()
            self.displayResult(sender)
            self.displayFunsToQlw() #???


        if (sender == '收集需求表格信息'):
            xlsFileNamePath = self.excelcollectPath_qle.text()
            if xlsFileNamePath == '':
                QMessageBox.critical(self, "Error", "xls file is empty!\n")
                return
            log = open(ExcelPath + "\\2excelInfos.txt", 'a+') # a+可追加可写
            wb = xlrd.open_workbook(ExcelPath + '\\' + m_excelName, formatting_info=True)  # excel 多单元格合并
            collectExcelInfo.global_varibale(wb,log,dict_pageToFuns)
            collectExcelInfo.read_excel_index1(wb, log)
            collectExcelInfo.read_excel_index2(wb, log)
            phf.dict_pageToFuns_fromExcel(collectExcelInfo.funs_list_sh1,ExcelPath,log )
            log.close()
            self.displayResult(sender)

        if (sender == 'Add Page>>>'):
            if (self.addPageName_qle.text() == ''):
                QMessageBox.warning(self, "Add Page To Right", "页面名称不能为空。")
            else:
                newItem = QTreeWidgetItem(self.funs_treeWidget)
                newItem.setText(0, self.addPageName_qle.text())

        if(sender=='确定'):
            self.pageToFuns()
            self.stackedWidget.setCurrentIndex(4)

        if (sender == '显示头文件列表'):
            self.checkHeaderFiles(existXX4A, existXX4T)
            print("m_headFilesList = ",m_headFilesList)
            self.displayHeaderFilesPathToUi()

        if (sender == '头文件预处理'):
            log = open(ExcelPath + "\\2excelInfos.txt", 'a+')
            log.write('此次需要的头文件列表如下：\n')
            log.write('m_headFilesList=%s\n'%(m_headFilesList))
            phf.preprocess_header_files(m_CCName,ExcelPath,existXX4A,existXX4T)
            phf.generate_requirefuns_tempfile(ExcelPath,dict_pageToFuns,log)
            phf.collect_struct_enum(ExcelPath+'\\'+'temp_HeaderFiles',m_headFilesList,ExcelPath)
            log.close()
        if(sender =='===>'):
            self.stackedWidget.setCurrentIndex(6)

        if (sender == 'funsToExcel.xml'):
            print("genaral funsToExcel.xml ...")
            EDS_VTXX.genaral_xml(ExcelPath)
            print("genaral funsToExcel.xml finish.")
        if (sender =='生成需求表格'):
            xmlForExcel=ExcelPath+'\\8funsInfoToExcel.xml'
            EDS_VTXX.XMLwriteToExcel(xmlForExcel,ExcelPath+'\\'+m_excelName,dict_pageToFuns)
            #result = os.popen('cmd /c ' + ExcelPath + '/' + m_excelName)
            #print("cmd result=", result)
        if (sender == '补充枚举到需求表格'):
            print("补充枚举到需求表格")
            list_enumUi=[]
            oldwb = xlrd.open_workbook(ExcelPath + '\\' + m_excelName, formatting_info=True)  # excel 多单元格合并
            sh2 = oldwb.sheet_by_index(2)
            newwb = copy(oldwb)
            newws = newwb.get_sheet('enum')
            #sh2 = newwb.get_sheet(2)
            trownum2 = sh2.nrows
            for i in range(3, trownum2):
                if '_ENUM' in sh2.cell(i, 4).value:
                            list_enumUi.append(str((sh2.cell(i, 4).value)).strip(' '))
            print("list_enumUi=", list_enumUi)
            set_enumUi = set(list_enumUi)
            if len(set_enumUi) != 0:
                phf.enumWriteToExcel(newws, phf.dict_enum, set_enumUi)
                os.remove(ExcelPath + '\\' + m_excelName)
                newwb.save(ExcelPath + '\\' + m_excelName)
                time.sleep(2)
                result = os.popen('cmd /c '+ExcelPath+'/'+m_excelName)
                print("cmd result=",result)

        if (sender == '补充枚举信息'):
            log = open(ExcelPath + "\\2excelInfos.txt", 'a+')
            log.write('=================The Information in Excel Sheet enum :==================\n')
            log.write('step.将VT界面接口需要用到的枚举，保存在字典 dict_enumForUi。\n')
            newwb = xlrd.open_workbook(ExcelPath + '\\' + m_excelName, formatting_info=True)  # excel 多单元格合并
            phf.enumForUi(newwb, log)  # 将枚举收集到字典里
            log.close()

        if (sender == '生成xml文件'):
            print("step7.由ExcelSheet2页面信息 生成10excelFunsForCpp.xml，用于生成cpp文件")
            excelToXML.excel_to_xml(ExcelPath)

            # EDS_VTXX.genaral_xml(ExcelPath)
            print("step8.由ExcelSheet2页面信息 生成11excelXmlForUi.xml")
            oldwb = xlrd.open_workbook(ExcelPath + '\\' + m_excelName, formatting_info=True)  # excel 多单元格合并
            # newwb = copy(oldwb)
            excelToXML.excelToXmlForUi(oldwb,
                                       collectExcelInfo.dict_funSh1Index,
                                       collectExcelInfo.dict_layouttab,
                                       collectExcelInfo.dict_tab1Index,
                                       collectExcelInfo.dict_funsShee2,
                                       phf.dict_enumForUi,
                                       phf.dict_enum,
                                       ExcelPath)
            self.showxmlfiles()

        if (sender =='生成通用代码文件'):
                print("step 9.生成VT_if.h,VT_if.cpp,VT.h,VT.cpp 代码文件(各项目通用)。")
                generateCodefile.codefileUniversal(m_CCName, g_developer, list(dict_pageToFuns.keys()), ExcelPath)
                self.cppfiles_qte.clear()
                for files in os.walk(ExcelPath+"\\Outcodefiles"):
                    self.cppfiles_qte.append(str(files))
        if (sender =='生成各页面头文件'):
            print("step 10.生成各组件对应子页面头文件(XXVTGeneral.h,XXVTApplication.h...)")
            log = open(ExcelPath + "\\2excelInfos.txt", 'a+')
            #log = open(ExcelPath + "\\codeinfos.txt", 'w')
            generateCodefile.pageCodeHeadFiles(m_CCName,
                                                g_developer,
                                                list(dict_pageToFuns.keys()),
                                                existXX4T,
                                                existXX4A,
                                                dict_pageToFuns,
                                                phf.dict_funs,
                                                ExcelPath,
                                                log)

        if (sender =='解析10excelFunsForCpp'):
            print("step 解析10excelFunsForCpp.xml，生成cpp特有接口。")
            log = open(ExcelPath + "\\12codeinfos.txt", 'w')
            fileslist=[]
            excelToXML.xmlToBottomCpp(m_CCName,
                                      dict_pageToFuns, #从页面收集得来
                                      phf.dict_enum,
                                      phf.dict_funs,
                                      phf.dict_enumForUi,
                                      collectExcelInfo.dict_table_params,
                                      ExcelPath,
                                      log)
            self.cppfiles_qte.clear()
            for file in os.walk(ExcelPath + "\\Outcodefiles"):
                fileslist.append(str(file)+'\n')
            for i in range(len(fileslist)):
                self.cppfiles_qte.append(fileslist[i])
                #self.cppfiles_qte.append(str(files)+'\n')

        if (sender =='解析11excelXmlForUi'):
            print("step.解析11excelXmlForUi.xml，生成ui界面。")
            xmlToUi.xmlToUi(m_CCName, ExcelPath)
            self.cppfiles_qte.clear()
            for files in os.walk(ExcelPath + "\\Outcodefiles"):
                self.cppfiles_qte.append(str(files)+'\n')


    def displayHeaderFilesPathToUi(self):
        subFunNameList = []
        self.headfilespath_qtb.resizeColumnsToContents() # 根据内容自动调整给定列宽
        self.headfilespath_qtb.clear()
        self.headfilespath_qtb.setColumnCount(2)
        headers = ["所需头文件列表","头文件本地路径"]
        self.headfilespath_qtb.setHorizontalHeaderLabels(headers)
        for row,headfilename in enumerate(m_headFilesList):
            print ("row=",row)
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
            fileOut = m_tempdir +'\\'+gTempProDir+ "\\1excelRuleCheckResult.txt"
            file = open(fileOut,'r')
            self.resultOutput_qte.clear()
            lines = file.readlines()
            for line in lines:
                #str = codec.toUnicode(self,line)
                self.resultOutput_qte.append(line)
            file.close()

        if sender == '收集需求表格信息':
            fileout2 = m_tempdir + '\\'+gTempProDir+"\\2excelInfos.txt"
            print("fileout2=",fileout2)
            file = open(fileout2,'r')
            self.resultOutput_qte2.clear()
            lines = file.readlines()
            for line in lines:
                #tempstr = codec.toUnicode(codec.fromUnicode(line))
                #self.resultOutput_qte2.append(tempstr)
                self.resultOutput_qte2.append(line)
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

    def pageToFuns(self):
        global dict_pageToFuns
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

                index1 = self.funs_treeWidget.indexBelow(index1)
            index1 = self.funs_treeWidget.indexBelow(index1)
            #print("tempfunslist=",tempfunslist)
            if tempfunslist !=[]:
                dict_pageToFuns[parentPage]=tempfunslist
        print("来自页面的信息：dict_pageToFuns=",dict_pageToFuns)

    def checkHeaderFiles(self, existXX4A, existXX4T):
        tempHeaderFilePath = m_tempdir + "\\" + gTempProDir + "\\temp_HeaderFiles"
        if (existXX4A):
            self.collectHeadFiles(tempHeaderFilePath, m_CCName + "4A_if.h")
        if (existXX4T):
            self.collectHeadFiles(tempHeaderFilePath, m_CCName + "4T_if.h")
    def collectHeadFiles(self,filepath,headfile):
        rx = QRegExp("^#include\\s*[:|<].*\\.h\\s*[:|>]")
        #headfilename = ""
        #rx.setPattern("^#include\\s*[:|<].*\\.h\\s*[:|>]") #include <xx.h>
        rx.setCaseSensitivity(QRegExp.caseSensitivity(rx))

        headfilepath = filepath+'\\'+headfile
        fh = QFile(headfilepath)
        if (os.path.exists(headfilepath)):
            if (headfile not in m_headFilesList):
                m_headFilesList.append(headfile)
                if fh.open(QIODevice.ReadOnly):
                    stream = QTextStream(fh)
                    stream.setCodec("UTF-8")
                    while(not stream.atEnd()):
                        line = stream.readLine()
                        if (line.find("SMEE_EXPORT") or line.find("typedef")):pass
                        if (rx.isValid()):
                            subline = line.replace("\"",":") #先把 “ 换成 ：，方便处理
                            if(-1 != rx.indexIn(subline)): #结果为 -1，表示匹配失败。成功返回匹配的位置索引

                                matchstrlist = []
                                matchstrlist = rx.capturedTexts() #提取匹配的字符串
                                print("matchstrlist=",matchstrlist)
                                if (-1 != matchstrlist[0].find(":")):#"xx.h"
                                    startMark = matchstrlist[0].find(":")
                                    endMark = matchstrlist[0].rfind(":")
                                    headfilename = matchstrlist[0][startMark+1:endMark]
                                    #print("headfilename=",headfilename)

                                if (-1 != matchstrlist[0].find("<")):#<xx.h>
                                    startMark = matchstrlist[0].find("<")
                                    endMark = matchstrlist[0].rfind(">")
                                    headfilename = matchstrlist[0][startMark+1:endMark]
                                    #print("headfilename=",headfilename)
                                self.collectHeadFiles(filepath,headfilename)
                        else:QMessageBox.critical(self,"Error","regexp syntax error!\n")
                else:QMessageBox.critical(self,"Error","Can't open the file ["+headfile+"]!\n")
            else:pass
        else:QMessageBox.warning(self,"Warning","["+headfile+"]"+"Not Exist in\n"+"["+filepath+"]\n"+"please copy it to==>"+filepath)

    def showxmlfiles(self):
        self.xmldisplay_qte.clear()
        if self.xmlindex_qcb.currentIndex() ==0:
            fileOut = m_tempdir + '\\' + gTempProDir + "\\10excelFunsForCpp.xml"
            if os.path.exists(fileOut):
                with open(fileOut,'r') as f:
                    for line in f:
                        self.xmldisplay_qte.append(line)
            else:
                QMessageBox.warning(self, "Warning",fileOut+"Not Exist!" )
        if self.xmlindex_qcb.currentIndex() ==1:
            fileOut = m_tempdir + '\\' + gTempProDir + "\\11excelXmlForUi.xml"
            if os.path.exists(fileOut):
                with open(fileOut,'r') as f:
                    for line in f:
                        self.xmldisplay_qte.append(line)
            else:
                QMessageBox.warning(self, "Warning", fileOut + "Not Exist!")

class HeaderFileDialog(QDialog, ui_headerFileDialog.Ui_headerFileDialog):
    def __init__(self, parent=None):
        super(QDialog, self).__init__(parent)
        self.setupUi(self)
        self.projectName_qle.setText('505')
        self.componentName_qle.setText('LB')

        self.tempdir_qpb.clicked.connect(self.fileButtonClicked)
        self.headfiles_qpb.clicked.connect(self.fileButtonClicked)
        self.pushButton_ok.clicked.connect(self.fileButtonClicked)
        self.pushButton_cancel.clicked.connect(self.fileButtonClicked)

    def createTempDir(self):
        exist = os.path.exists(m_tempdir + '\\' + gTempProDir)
        if (exist):
            QMessageBox.warning(self, "创建文件夹", "文件夹" + gTempProDir + "之前已经创建！\n所有中间文件生成在" + gTempProDir + "目录下")
        else:
            os.mkdir(m_tempdir + '\\' + gTempProDir)
            ok = os.path.exists(m_tempdir + '\\' + gTempProDir)
            if (ok):
                os.mkdir(m_tempdir + '\\' + gTempProDir + '\\' + 'temp_HeaderFiles')
                os.mkdir(m_tempdir + '\\' + gTempProDir + '\\' + 'Outcodefiles')
                QMessageBox.warning(self, "创建文件夹", "---文件夹" + gTempProDir + "在目录" + m_tempdir + "创建成功")
            else:
                QMessageBox.critical(self, "创建文件夹", "---文件夹" + gTempProDir + "在目录" + m_tempdir + "创建失败！")

    def fileButtonClicked(self):
        global m_tempdir  # G:/all_exercises/python_prjs/pyvt_auto0630/PYVTUI/VTUI
        global gTempProDir  # temp_506VTEC
        global g_developer
        global m_CCName
        global ExcelPath
        global destinationDir

        sender = self.sender().text()
        if sender=='1.文件夹路径':
            if ('' == self.projectName_qle.text() or '' == self.componentName_qle.text()):
                QMessageBox.critical(self, "Error", "Please select Project and Component First!!!\n")
            else:
                dirstr = QFileDialog.getExistingDirectory(self, "Open Directory",
                                                          QDir.currentPath(),
                                                          QFileDialog.ShowDirsOnly | QFileDialog.DontResolveSymlinks)
                m_tempdir = dirstr.replace('/', '\\')
                self.tempdir_qle.setText(m_tempdir)
                gTempProDir = 'temp_' + self.projectName_qle.text() + 'VT' + self.componentName_qle.text()
                ExcelPath = m_tempdir + '\\' + gTempProDir
                destinationDir = m_tempdir + '\\' + gTempProDir
                m_CCName = self.componentName_qle.text()
                self.createTempDir()
        if (sender=='头文件路径(4A/4T)'):
            fileNames = QFileDialog.getOpenFileNames(self, "Open File",QDir.currentPath(),"*_if.h")
            if len(fileNames[0]) !=0:
                global  tempheadfilelist
                global  existXX4A
                global  existXX4T
                tempheadfilelist=fileNames[0]
                self.headfilexx4x_if_qle.setText(str(fileNames[0]))
                for file in fileNames[0]:
                    print('file=',file)
                    try:
                        shutil.copy(file.replace("/","\\"), m_tempdir+'\\'+gTempProDir+'\\'+'temp_HeaderFiles')
                    except shutil.SameFileError:
                        QMessageBox.information(self, "Same File", "你所选的头文件和你要拷贝的目录在同一个位置,操作成功。\n")

                    if ((file.split('/')[-1])[0:4] == m_CCName + "4A"):  # 取字符串开头4个字符
                        existXX4A = True
                    if ((file.split('/')[-1])[0:4] == m_CCName + "4T"):
                        existXX4T = True
            else:QMessageBox.warning(self, "No File", "文件选择不能为空\n")

        if(sender=='OK'):
            if (self.headfilexx4x_if_qle.text() == ""):
                QMessageBox.warning(self, "No File", "文件选择不能为空\n")
            else:self.reject()
        if(sender=='Cancel'):
            self.reject() #关闭对话框

#m_tempdir=G:/all_exercises/python_prjs/pyvt_auto0630/PYVTUI/VTUI
#gTempProDir=temp_506VTEC
if __name__ == "__main__":
    app = QApplication(sys.argv)
    mainWindow = MainWindow()
    mainWindow.show()
    sys.exit(app.exec_())