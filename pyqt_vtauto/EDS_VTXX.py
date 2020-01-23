import os,re
import xlrd
from xml.dom.minidom import Document
import xml.dom.minidom
from xlutils.copy import copy
import parseheadfile as phf
from PyQt5.QtWidgets import *


dict_unit_smee_to_si = {"mm": "m", "pm": "m", "nm": "m", "um": "m", "nm/ms": "m/s", "KHz": "Hz", "MHz": "Hz","mrad": "rad",
                        "urad": "rad", "nrad": "rad", "deg": "rad", "uJ": "J", "mJ/cm2": "J/m2", "mW/cm2": "W/m2","℃": "K",
                        "ms": "s", "us": "s", "min": "s", "hour": "s","h":"s","day":"s", "L/min": "m3/s","bar":"Pa"}
dict_precision_to_singleStep = {'0': '1', '1': '0.1', '2': '0.01', '3': "0.001", '4': '0.0001', '5': '0.00001','6': '0.000001',
                                '7': '0.0000001', '8': "0.00000001", '9': "0.000000001"}  # 根据精度确定步长。


# 注意解析结构体和枚举,头文件统一在temp_HeaderFiles目录下。
# 生成 8funsInfoToExcel.xml。
class VTXXUI(QMainWindow):
    def parseStructType(self,funStruct,listStructMember,parameterlist,nodeAttribute,nodeMember,doc): #递归调用
        #print("funStruct=", funStruct)
        if funStruct[0] in phf.dict_struct.keys():#説明是结构体。
            listStructMember.append(funStruct[1])
            for structValueNum in range(len(phf.dict_struct[funStruct[0]])):
                if phf.dict_struct[funStruct[0]][structValueNum][0] in phf.dict_struct.keys():#説明是结构体。
                    self.parseStructType(phf.dict_struct[funStruct[0]][structValueNum],listStructMember,parameterlist,nodeAttribute,nodeMember,doc)
                else:
                    listStructMember.append(phf.dict_struct[funStruct[0]][structValueNum][1]+'|['+phf.dict_struct[funStruct[0]][structValueNum][0]+']')

                    #print("listStructMember=",listStructMember)
                    parameterlist.append('.'.join(listStructMember))
                    nodeMember.appendChild(doc.createTextNode('.'.join(parameterlist)))
                    nodeAttribute.appendChild(nodeMember)
                    del listStructMember[-1]
                    del parameterlist[-1]
            del listStructMember[-1]

        else:
            listStructMember.append(funStruct[1]+'|['+funStruct[0]+']')
            #print("2---------------", listStructMember)
            parameterlist.append('.'.join(listStructMember))
            nodeMember.appendChild(doc.createTextNode('.'.join(parameterlist)))
            nodeAttribute.appendChild(nodeMember)

    def general_xml(self,ExcelPath):
        curPath = ExcelPath
        fp = open((os.sep).join([curPath,'8funsInfoToExcel.xml']), 'w')
        funs_key = list(phf.dict_funs.keys())  # 获取所有的接口。
        doc = Document()  #在内存中创建dom文档
        fun_info_root = doc.createElement('fun_info')  # 创建根节点fun_info
        doc.appendChild(fun_info_root)  # 根节点添加到dom树。

        for index in range(len(phf.dict_funs)):#第一层循环，接口个数。
            nodeFunName = doc.createElement('fun_name')
            nodeFunName.setAttribute('name', funs_key[index])
            funs_value = phf.dict_funs[funs_key[index]]  # 获取 funs_key[i]的值列表
            codeStr = '[item]u_param.param_' + funs_key[index]
            #print ('funs_value=%s'%(funs_value))
            for params_num in range(len(funs_value)):  # 第二层循环，参数个数
                parameterlist = []
                parameterlist.append(codeStr)
                #给节点attribute设置文本节点
                nodeAttribute = doc.createElement('attribute')
                nodeAttribute.setAttribute('attr', funs_value[params_num][0])
                del funs_value[params_num][0] #删除第一个元素，使其只有两个元素的列表，传给递归函数
                nodeParamsName = doc.createElement('param_name')
                nodeParamsName.appendChild(doc.createTextNode(funs_value[params_num][1]))
                nodeParamsName.setAttribute('type', funs_value[params_num][0])

                nodeAttribute.appendChild(nodeParamsName)
                nodeFunName.appendChild(nodeAttribute)
                nodeMember = doc.createElement('members')

                listStructMember = []
                self.parseStructType(funs_value[params_num],
                                        listStructMember,
                                        parameterlist,
                                        nodeAttribute,
                                        nodeMember,
                                        doc)


            # 将各叶子节点添加到父节点nodeAttribute中
            #nodeFunName.appendChild(nodeAttribute)
            fun_info_root.appendChild(nodeFunName)
        doc.writexml(fp, indent="", addindent='\t', newl='\n')
        fp.close()





    def check_range_is_legal(self,itemRange,itemAttr,line,errInfo,warnInfo):
        str1 = itemRange
        sub_str = str1[1:-1]
        list_sub_str = sub_str.split(',')  # list
        if (str1.startswith('(') and str1.endswith(')')) or \
           (str1.startswith('(') and str1.endswith(']')) or \
           (str1.startswith('[') and str1.endswith(')')) or \
           (str1.startswith('[') and str1.endswith(']')):
            if ("SMEE_INT32" == itemAttr)or("SMEE_UINT32"==itemAttr) \
                or("SMEE_INT8" == itemAttr)or("SMEE_UINT8"==itemAttr) \
                or("SMEE_INT16" == itemAttr)or("SMEE_UINT16"==itemAttr) \
                or("SMEE_INT64" == itemAttr)or("SMEE_UINT64"==itemAttr) \
                or("SMEE_ULONG32" == itemAttr)or("SMEE_LONG"==itemAttr):
                    #当输入参数类型是整型时，判断参数范围数也应该是整型。
                    if (abs(int(float(list_sub_str[0])))==abs(float(list_sub_str[0]))) \
                        and (abs(int(list_sub_str[1])) == abs(float(list_sub_str[1]))):
                        return True
                    else:
                        errInfo += '[' + str(line) + ',8]->参数类型应该是整型 error!\n'
            elif itemAttr=='?':
                warnInfo+='[' + str(line) + ',8]->确认是否无范围，无则填none\n'
            else:pass
                #浮点型数据，只判断格式.

        else:

            errInfo += '[' + str(line) + ',8]->参数格式应该是[a,b],[a,b),(a,b],(a,b) error!+\n'
            print('errInfo=',errInfo)

    # 对范围，默认值，步长的处理
    # #判断单位步长，
    # 如果是整形参数，则默认步长为1，
    # 浮点型参数，如果没填，根据精度生成步长。
    def range_default_stepLength(self,sheet2tab,line,item,errInfo,warnInfo,precision):
        try:
            item3 = sheet2tab.item(line, 2).text()
            #print('item3=' + item3)
            if 'OUT' == item3:
                sheet2tab.setItem(line, 6, QTableWidgetItem('none'))
                sheet2tab.setItem(line, 8, QTableWidgetItem('none'))
                sheet2tab.setItem(line, 9, QTableWidgetItem('none'))
            elif ("IN" == item3) or ("INOUT" == item3):
                try:
                    item4 = sheet2tab.item(line, 8).text()  # 输入参数才有范围。
                    print('item4=' + item4)
                    if ("none" != item4):
                        # 判断范围格式[x,y]
                        self.check_range_is_legal(item4, item, line, errInfo,warnInfo)
                        try:
                            item5 = sheet2tab.item(line, 6).text()
                            print('item5=' + item5)
                            if("none" != item5):
                                self.default_num_is_inRange(item4, item5, line, errInfo)
                            else:
                                errInfo += '[' + str(line) + ',6]->' + item5 + '输入参数有范围,默认值不能为none error +\n'
                            try:
                                item6 = sheet2tab.item(line, 9).text()  # 步长
                                singleStep = dict_precision_to_singleStep[precision]
                                if singleStep == item6:pass
                                else:
                                    sheet2tab.setItem(line, 9, QTableWidgetItem(singleStep))
                            except AttributeError:
                                if 'SMEE_FLOAT' == item or 'SMEE_DOUBLE' == item:
                                    sheet2tab.setItem(line, 9, QTableWidgetItem('0.000001'))
                                elif ("SMEE_INT32" == item) or ("SMEE_UINT32" == item) \
                                        or ("SMEE_INT8" == item) or ("SMEE_UINT8" == item) \
                                        or ("SMEE_INT16" == item) or ("SMEE_UINT16" == item) \
                                        or ("SMEE_INT64" == item) or ("SMEE_UINT64" == item) \
                                        or ("SMEE_ULONG32" == item) or ("SMEE_LONG" == item):
                                    sheet2tab.setItem(line, 9, QTableWidgetItem('1'))
                        except AttributeError:
                            errInfo += '[' + str(line) + ',8]->' + item4 + '输入参数有范围,默认值不能为空 error +\n'
                except AttributeError:
                    sheet2tab.setItem(line, 8, QTableWidgetItem('?'))
                    sheet2tab.setItem(line, 6, QTableWidgetItem('none'))
            else:
                errInfo += '[' + str(line) + ',2]->' + item3 + 'IN/OUT/INOUT is right, other is error +\n'
        except AttributeError:
            errInfo += '[' + str(line) + ',2]->item 确认参数类型 error +\n'
    #在调用此接口之前，已经调用了check_range_is_legal
    # 故可以直接判断默认值是否在范围之内。无需考虑格式。
    def  default_num_is_inRange(self,itemRange,itemDefaultNum,line,errInfo):
        str = itemRange
        middle = float(itemDefaultNum)
        if isinstance(middle, float):
            if str.startswith('['):  # 左闭区间
                if str.endswith(']'):
                    left = float(str[str.find('[') + 1:str.find(',')])
                    right = float(str[str.find(',') + 1:str.find(']')])
                    if left <= middle <= right:pass
                    else:
                        errInfo+='[' + str(line) + ',6]->item='+itemDefaultNum+' 默认值不在范围内 error!+\n'
                else:  # 左闭右开区间
                    if float(str[str.find('[') + 1:str.find(',')]) <= middle < float(
                            str[str.find(',') + 1:str.find(')')]):pass
                    else:
                        errInfo += '[' + str(line) + ',6]->item=' + itemDefaultNum + ' 默认值不在范围内 error!+\n'
            elif str.startswith("("):  # 左开区间
                if str.endswith(']'):
                    if float(str[str.find('(') + 1:str.find(',')]) < middle <= float(
                            str[str.find(',') + 1:str.find(']')]):pass
                    else:
                        errInfo += '[' + str(line) + ',6]->item=' + itemDefaultNum + ' 默认值不在范围内 error!+\n'
                else:
                    if float(str[str.find('(') + 1:str.find(',')]) < middle < float(
                            str[str.find(',') + 1:str.find(')')]):pass
                    else:
                        errInfo += '[' + str(line) + ',6]->item=' + itemDefaultNum + ' 默认值不在范围内 error!+\n'
        else:
            errInfo += '[' + str(line) + ',6]->item=' + itemDefaultNum + ' 检查默认值是否符合要求 error!+\n'

    def writeToUISheet2(self,sheet2tab):
        errInfo=""
        warningInfo=""
        precision=""
        for line in range(sheet2tab.rowCount()):
            # 对精度的处理，浮点型3或6，默认6，整型0，其他 none
            try:
                item=sheet2tab.item(line,4).text()
                if 'SMEE_FLOAT' == item or 'SMEE_DOUBLE' == item:
                    try:
                        precision=sheet2tab.item(line,7).text()
                        if int(precision)<0:
                            errInfo+='['+str(line)+',7]->item<0 error!+\n'
                    except AttributeError:
                        sheet2tab.setItem(line, 7, QTableWidgetItem('6'))
                elif "SMEE_BOOL" == item or "SMEE_CHAR" == item or "_ENUM" in item:
                    sheet2tab.setItem(line, 7, QTableWidgetItem('none'))
                else:
                    sheet2tab.setItem(line, 7, QTableWidgetItem('0'))
            except AttributeError:
                errInfo+='['+str(line)+',4]->item not float，int，bool，char,enum error!\n'
            # 对单位,单位转换，的处理
            if  ("_ENUM" not in item) and ("SMEE_BOOL" != item) and ("SMEE_CHAR" != item):
                try :
                    item2 = sheet2tab.item(line, 5).text()
                    #print('item2='+item2)
                    if item2 !='none':
                        if item2 in list(dict_unit_smee_to_si.values()):#判断是不是国际单位,是则警告
                            warningInfo+='['+str(line)+',5]->the item unit is 国际单位 warning\n'
                        elif item2 == "?":
                            errInfo += '[' + str(line) + ',5]->请确认单位。没有单位填 none \n'
                    else:#单位转换栏补none
                        sheet2tab.setItem(line, 10, QTableWidgetItem('none'))

                    self.range_default_stepLength(sheet2tab,line,item,errInfo,warningInfo,precision)
                except AttributeError:
                    sheet2tab.setItem(line, 5, QTableWidgetItem('?'))
                    sheet2tab.setItem(line, 10, QTableWidgetItem('?'))
                    self.range_default_stepLength(sheet2tab,line,item,errInfo,warningInfo,precision)
            else:
                sheet2tab.setItem(line, 5, QTableWidgetItem('none'))
                sheet2tab.setItem(line, 10, QTableWidgetItem('none'))

        print ('errinfo='+errInfo)
        if warningInfo=="":pass
        else:
            QMessageBox.warning(self, "Warn", warningInfo)
        if errInfo == "":pass
        else:
            QMessageBox.critical(self, "Error", errInfo)



    def XMLwriteToUi(self,xmlForExcel, sheet1tab,sheet2tab, dict_pageToFuns):
        # minidom 解析器打开 XML 文件。
        DOMTree = xml.dom.minidom.parse(xmlForExcel)
        excelInfo = DOMTree.documentElement
        funNames = excelInfo.getElementsByTagName("fun_name")
        countrow = 0
        rowsh1 = 0
        for key in dict_pageToFuns.keys():
            for j in range(len(dict_pageToFuns[key])):
                sheet1tab.insertRow(rowsh1+j)
                sheet1tab.setItem(rowsh1+j, 0, QTableWidgetItem(key))
                sheet1tab.setItem(rowsh1+j, 1, QTableWidgetItem("label1"))
                sheet1tab.setItem(rowsh1+j, 2, QTableWidgetItem("label2"))
                sheet1tab.setItem(rowsh1+j, 3, QTableWidgetItem(' '.join(dict_pageToFuns[key][j].split('_')[1:]).title()))
                sheet1tab.setItem(rowsh1+j, 4, QTableWidgetItem(dict_pageToFuns[key][j]))

        for funName in funNames:
            funname = funName.getAttribute("name")
            print("write fun [" + funname + "] to table...")
            attributes = funName.getElementsByTagName('attribute')
            if len(attributes)==0: #表示该接口无参数
                sheet2tab.insertRow(countrow)
                sheet2tab.setItem(countrow, 0, QTableWidgetItem(funname))
                for i in range(1,12):
                    sheet2tab.setItem(countrow, i, QTableWidgetItem("none"))
                countrow+=1
            else:
                for attr in attributes:
                    in_out = attr.getAttribute('attr')
                    param_name = attr.getElementsByTagName('param_name')
                    # param_type = param_name[0].getAttribute('type')
                    members = (attr.getElementsByTagName("members")[0]).childNodes[0].data
                    submems = re.sub('\s', '', members)
                    listmems = submems.split('[item]')
                    listmems.remove('')
                    print("listmembers in xml===", listmems)
                    for listmem in listmems:
                        sheet2tab.insertRow(countrow)
                        sheet2tab.setItem(countrow, 0, QTableWidgetItem(funname))
                        if '|[' in listmem:
                            sheet2tab.setItem(countrow, 1, QTableWidgetItem(listmem[:listmem.rfind('|[')]))
                            tParam=listmem[:listmem.rfind('|[')]
                            sheet2tab.setItem(countrow, 3, QTableWidgetItem(list(tParam.split("."))[-1].capitalize()))
                            sheet2tab.setItem(countrow, 4, QTableWidgetItem(listmem[listmem.rfind('|[') + 2:-1]))
                            if '_ENUM' in listmem[listmem.rfind('|[') + 2:-1]:
                                sheet2tab.setItem(countrow, 6, QTableWidgetItem("none"))
                                sheet2tab.setItem(countrow, 8, QTableWidgetItem("none"))
                                sheet2tab.setItem(countrow, 9, QTableWidgetItem("none"))
                        else:
                            sheet2tab.setItem(countrow, 1, QTableWidgetItem(listmem))

                        sheet2tab.setItem(countrow, 2, QTableWidgetItem(in_out))
                        countrow = countrow + 1

        self.writeToUISheet2(sheet2tab)


    def UItabWriteToExcel(self,excelPath,sheet1tab,sheet2tab):
        oldwb = xlrd.open_workbook(excelPath, formatting_info=True)  # excel 多单元格合并
        newwb = copy(oldwb)
        sh1ws = newwb.get_sheet(1)
        sh2ws = newwb.get_sheet(2)
        for m in range(5,1024):
            for n in range(11):
                sh1ws.write(m, n, "")
                sh2ws.write(m,n,"")
        countrow=3
        rowsh1=5
        for line in range(sheet1tab.rowCount()):
            for col in range(sheet1tab.columnCount()):
                try:
                    sh1ws.write(rowsh1+line,col,sheet1tab.item(line,col).text())
                except AttributeError:
                    sh1ws.write(rowsh1 + line, col, "")
        for line in range(sheet2tab.rowCount()):
            for col in range(sheet2tab.columnCount()):
                try:
                    sh2ws.write(countrow+line,col,sheet2tab.item(line,col).text())
                except AttributeError:
                    sh2ws.write(countrow + line, col, "")
        newwb.save(excelPath)
        print('write to EDS_VTXX-V4.xls success')


if __name__ == "__main__":
    m_tempdir = 'C:/Users/Administrator/Desktop/pyvttest1128'.replace('/', '\\')
    gTempProDir = 'temp_506VTEC'
    ExcelPath = m_tempdir + '\\' + gTempProDir
    xmlForExcel = ExcelPath + '\\8funsInfoToExcelbak2.xml'
    XMLwriteToExcel(xmlForExcel,ExcelPath+'\\EDS_VTXX-V4.xls')