import re,os
from xml.dom.minidom import Document  # ?
#from PyQt5.QtWidgets import *
#from xml.dom.minidom import parse
import xml.dom.minidom
import collectExcelInfo
import generateCodefile
from xlutils.copy import copy
dictBaseUnit = \
    {"mm": ["SMEE_SI_TO_MM","SMEE_MM_TO_SI"],
     "pm": ["SMEE_SI_TO_PM","SMEE_PM_TO_SI"],
     "nm": ["SMEE_SI_TO_NM","SMEE_NM_TO_SI"],
     "um": ["SMEE_SI_TO_UM","SMEE_UM_TO_SI"],
     "nm/ms":["SMEE_SI_TO_NM_PER_MS","SMEE_NM_PER_MS_TO_SI"],
     "KHz":["SMEE_SI_TO_KHZ","SMEE_KHZ_TO_SI"],
     "MHz":["SMEE_SI_TO_MHZ","SMEE_MHZ_TO_SI"],
     "mrad":["SMEE_SI_TO_MRAD","SMEE_MRAD_TO_SI"],#弧度
     "urad":["SMEE_SI_TO_URAD","SMEE_URAD_TO_SI"],
     "nrad":["SMEE_SI_TO_NRAD","SMEE_NRAD_TO_SI"],
     "deg":["SMEE_SI_TO_DEGREE","SMEE_DEGREE_TO_SI"], #角度
     "uJ": ["SMEE_SI_TO_UJ","SMEE_UJ_TO_SI"],
     "mJ/cm2": ["SMEE_SI_TO_MJCM","SMEE_MJCM_TO_SI"],
     "mW/cm2": ["SMEE_SI_TO_MWCM","SMEE_MWCM_TO_SI"],
     "℃":["SMEE_SI_TO_CELSIUS","SMEE_CELSIUS_TO_SI"],
     "ms":["SMEE_SI_TO_MS","SMEE_MS_TO_SI"],
     "us":["SMEE_SI_TO_US","SMEE_US_TO_SI"],
     "min":["SMEE_SI_TO_MINUTE","SMEE_MINUTE_TO_SI"],
     "hour":["SMEE_SI_TO_HOUR","SMEE_HOUR_TO_SI"],
     "h":["SMEE_SI_TO_HOUR","SMEE_HOUR_TO_SI"],
     "day":["SMEE_SI_TO_DAY","SMEE_DAY_TO_SI"],
     "bar":["SMEE_SI_TO_BAR","SMEE_BAR_TO_SI"],#?
     "psi":["SMEE_SI_TO_PSI","SMEE_PSI_TO_SI"],#?
     "ppm":["SMEE_SI_TO_PPM","SMEE_PPM_TO_SI"],
     "%":["SMEE_SI_TO_PCT","SMEE_PCT_TO_SI"],
     "L/min":["SMEE_SI_TO_LPM","SMEE_LPM_TO_SI"]}
dict_SIUnit =  ('m','m/s','Hz','rad','J''J/m2','K','s')

def excel_to_xml(curpath):
    fp = open((os.sep).join([curpath,'10excelFunsForCpp.xml']), 'w')
    doc = Document()  # 在内存中创建dom文档
    fun_info_root = doc.createElement('fun_info')  # 创建根节点fun_info
    doc.appendChild(fun_info_root)  # 根节点添加到dom树。

    for index in range(len(collectExcelInfo.funs_list_sh1_tuple)):#第一层循环，接口个数。
        nodeFunName = doc.createElement('fun_name')
        funName = list(collectExcelInfo.dict_funsSheet2.keys())[index]
        print("writting ["+funName+"] to 10excelFunsForCpp.xml...")
        nodeFunName.setAttribute('name', funName)
        funs_value = collectExcelInfo.dict_funsSheet2[funName]
        #codeStr = 'u_param.param_' + funName
        #nodeParameter = doc.createElement('parameter')
        for params_num in range(len(funs_value)):  # 第二层循环，参数个数
            parameterlist = []
            #parameterlist.append(codeStr)
            # 给节点attribute设置文本节点
            nodeAttribute = doc.createElement('attribute')
            #nodeAttribute.appendChild(doc.createTextNode(funs_value[params_num][1]))
            nodeAttribute.setAttribute('value',funs_value[params_num][1])
            if funs_value[params_num][1] == 'IN':
                nodeRange = doc.createElement('interval')
                nodeRange.appendChild(doc.createTextNode(funs_value[params_num][7]))
                nodeRange.setAttribute('default', str(funs_value[params_num][5]))

                nodeStep = doc.createElement('step')
                if str(funs_value[params_num][6])=='none':
                    nodeStep.appendChild(doc.createTextNode('none'))
                else:
                    nodeStep.appendChild(doc.createTextNode('1E'+str(funs_value[params_num][6])))
            else:pass

            nodeType = doc.createElement('type')
            nodeType.appendChild(doc.createTextNode(funs_value[params_num][3]))
            nodeLabel = doc.createElement('label')
            nodeLabel.appendChild(doc.createTextNode(funs_value[params_num][2]))
            nodeLabel.setAttribute('unit',funs_value[params_num][4])

            nodePrecision = doc.createElement('precision')
            nodePrecision.appendChild(doc.createTextNode(str(funs_value[params_num][6])))

            nodeMember = doc.createElement('members')
            if '->' in funs_value[params_num][0]:
                parameterlist.append(str(funs_value[params_num][0]).replace('->','.',5))
            else:
                parameterlist.append(funs_value[params_num][0])
            nodeMember.appendChild(doc.createTextNode('.'.join(parameterlist)))

            # nodeParameter.appendChild(nodeAttribute)
            nodeAttribute.appendChild(nodeType)
            if funs_value[params_num][1] == 'IN':
                nodeAttribute.appendChild(nodeRange)
                nodeAttribute.appendChild(nodeStep)
            else:pass

            nodeAttribute.appendChild(nodeLabel)
            nodeAttribute.appendChild(nodePrecision)
            nodeAttribute.appendChild(nodeMember)

            # 将各叶子节点添加到父节点nodeParameter中
            nodeFunName.appendChild(nodeAttribute)
        fun_info_root.appendChild(nodeFunName)
    doc.writexml(fp, indent="", addindent='\t', newl='\n')
    fp.close()


def excelToXmlForUi(workbook,
                    dictlayout,
                    dict_pageToFuns,
                    dict_funsNameToShow,
                    dicFunInfoSh2,
                    dict_enumForUi,
                    dicEnum,
                    curpath):
    sh1 = workbook.sheet_by_index(1)
    fp = open((os.sep).join([curpath,'11excelXmlForUi.xml']), 'w')
    doc = Document()  # 在内存中创建dom文档
    fun_info_root = doc.createElement('pageInfo')  # 创建根节点fun_info
    doc.appendChild(fun_info_root)  # 根节点添加到dom树。
    for pageIndex in range(len(list(dictlayout.keys()))):  # 第一层循环，page个数。
        nodePageName = doc.createElement('pageName')
        pageName = list(dictlayout.keys())[pageIndex]
        nodePageName.setAttribute('pageId', pageName)

        for labelIndex in range(len(dictlayout[pageName])):
            nodeTab = doc.createElement('firstTab')
            nodeTab.setAttribute('tableName', dictlayout[pageName][labelIndex])

            tfunslist= dict_pageToFuns[pageName]
            print('tfunslist=',tfunslist)
            for funIndex in range(len(tfunslist)):
                nodeFunName = doc.createElement('funName')
                funName=tfunslist[funIndex]
                nodeFunName.setAttribute('funId', dict_funsNameToShow[funName])
                nodeFunName.setAttribute('funLabelId', dict_funsNameToShow[funName])
                print ('funName=',funName)
                print(dicFunInfoSh2[funName])

                for paramIndex in range(len(dicFunInfoSh2[funName])):
                    nodeParamLabel = doc.createElement('paramLabel')
                    paramLabel = dicFunInfoSh2[funName][paramIndex][2]
                    nodeParamLabel.setAttribute('paramLabelId', paramLabel)
                    #以需求表格中参数标签一栏信息是否为none，决定后续信息是否写到xml 中。为生成ui文件做准备。
                    if paramLabel !='none':
                        nodeParamObjectName = doc.createElement('paramObjectName')
                        paramObjectName = funName+'_'+ dicFunInfoSh2[funName][paramIndex][0]
                        regular_mode = re.sub('->|\.','_', paramObjectName)
                        nodeParamObjectName.appendChild(doc.createTextNode(regular_mode))

                        nodeParamUnit = doc.createElement('paramUnit')
                        paramUnit = dicFunInfoSh2[funName][paramIndex][4]
                        nodeParamUnit.appendChild(doc.createTextNode(paramUnit))


                        nodeParamAttr = doc.createElement('paramAttr')
                        paramAttr = dicFunInfoSh2[funName][paramIndex][1]
                        nodeParamAttr.appendChild(doc.createTextNode(paramAttr))

                        nodeParamPrecision = doc.createElement('ParamPrecision')
                        paramPrecision = dicFunInfoSh2[funName][paramIndex][6]
                        nodeParamPrecision.appendChild(doc.createTextNode(str(paramPrecision)))


                        nodeParamType = doc.createElement('paramType')
                        paramType = dicFunInfoSh2[funName][paramIndex][3]
                        if '_ENUM' not in paramType:
                            nodeParamType.appendChild(doc.createTextNode(paramType))
                        else:
                            nodeParamType.setAttribute('enumName', paramType)
                            if paramType in dicEnum.keys():
                                #print('paramType = ', paramType)
                                for enumIndex in range(1,len(dicEnum[paramType])-1):
                                    nodeEnumMember = doc.createElement('enumMember')
                                    enumMember = dicEnum[paramType][enumIndex]
                                    if enumMember in dict_enumForUi.keys():
                                        enumMemberUi = dict_enumForUi[enumMember]
                                        nodeEnumMember.appendChild(doc.createTextNode(enumMemberUi))
                                        nodeParamType.appendChild(nodeEnumMember)
                                    else:
                                        nodeEnumMember.appendChild(doc.createTextNode(enumMember))
                                        nodeParamType.appendChild(nodeEnumMember)
                            else:pass

                        nodeParamLabel.appendChild(nodeParamObjectName)
                        nodeParamLabel.appendChild(nodeParamUnit)
                        nodeParamLabel.appendChild(nodeParamAttr)
                        nodeParamLabel.appendChild(nodeParamPrecision)
                        nodeParamLabel.appendChild(nodeParamType)
                    nodeFunName.appendChild(nodeParamLabel)
                    nodeTab.appendChild(nodeFunName)
            nodePageName.appendChild(nodeTab)
        fun_info_root.appendChild(nodePageName)
    doc.writexml(fp, indent="", addindent='\t', newl='\n')
    fp.close()

#dom 解析10excelFunsXml.xml,用于生成cpp文件。
# updateWindowData,performButtonClickedSlot,ini,m_exec_...
def xmlToBottomCpp(CCNAME,
                   dict_layouttab,
                   dict_page_fun,
                   dict_funsSheet2,
                   dict_enum,
                   dict_enumForUi,
                   dict_funs,
                   curpath,
                   log):

    # minidom 解析器打开 XML 文件。
    DOMTree = xml.dom.minidom.parse(curpath+"\\"+"10excelFunsForCpp.xml")
    funInfo = DOMTree.documentElement
    funNames = funInfo.getElementsByTagName("fun_name")
    #print('funNames=',funNames[0])
    temp_outpath=curpath+ "\\Outcodefiles"
    if os.path.exists(temp_outpath):pass
    else:
        os.mkdir(temp_outpath)
        if (os.path.exists(temp_outpath)):
            print("Outcodefiles 创建成功")
            #QMessageBox.warning(self, "创建文件夹", "文件夹Outcodefiles创建成功.")
        else:
            print("Outcodefiles 创建失败")
            #QMessageBox.warning(self, "创建文件夹", "文件夹Outcodefiles创建失败！")

    fileIni = open((os.sep).join([curpath, "Outcodefiles", "VT" + CCNAME + '.ini']), 'w')
    fileIni.write('#属性值,    最大最小值,   默认值,  精度,   singleStep\n')
    if len(dict_layouttab.keys()) == 0:
        dict_layouttab=collectExcelInfo.dict_layouttab

    for pageIndex in range(len(list(dict_layouttab.keys()))):
        pages = list(dict_layouttab.keys())[pageIndex]
        print('=======正在生成导航页 %s 的 cpp代码文件...========' %(pages))
        log.write('=======正在生成导航页 %s 的 cpp代码文件...========\n' %(pages))
        bottomFile = open((os.sep).join([curpath, "Outcodefiles", "bottom"+CCNAME + "VT" + pages + ".cpp"]), 'a+')#可读可写
        fileRange = open((os.sep).join([curpath, "Outcodefiles", 'temp_rangeCheck.txt']), 'a+')
        fileButtonClick = open((os.sep).join([curpath, "Outcodefiles", 'performButtonClickedSlot.txt']), 'a+')
        fileExec = open((os.sep).join([curpath, "Outcodefiles", 'm_exec.txt']), 'a+')

        fileRange.write('void %sVT%s::param_range_check() \n\t{\n' % (CCNAME, pages))
        bottomFile.write('''
//刷新界面数据
void %sVT%s::updateWindowData()//slot
{
    switch (m_func)
    {
'''%(CCNAME,pages))
        fileButtonClick.write('''void %sVT%s::performButtonClickedSlot(int button_id)\n\t{ 
	\tswitch (button_id)\n\t\t{\n'''%(CCNAME,pages))
        fileIni.write('#%s\n' % pages)
        #for i in range(len(dict_layoutlab[pages])):

        for i in range(len(dict_page_fun[pages])):
            tfunName=(dict_page_fun[pages][i])
            tfunUpper=tfunName.upper()
            bottomFile.write('\tcase %s:\n' % (tfunUpper))
            fileExec.write('''void %sVT%s::m_exec_%s()\n\t{       
        int error_code = OK;
        QString func_name = "%s";
        //输出信息到输出栏
        outputStart(func_name);\n'''%(CCNAME,pages,tfunName,(' '.join(tfunName.split('_'))).title()))
            for funname in funNames:
                fun = funname.getAttribute("name") #可以改进否？

                if fun == tfunName:
                    log.write("此导航页包含的接口有：\nfun= %s\n"%(fun))
                    templistCheckIsValid = []
                    attribute = funname.getElementsByTagName("attribute")
                    for attr in attribute:
                        paramAttr = attr.getAttribute("value")
                        #print("paramAttr= %s" % paramAttr)
                        type = (attr.getElementsByTagName('type')[0]).childNodes[0].data
                        labels = attr.getElementsByTagName('label')
                        if paramAttr.upper() == 'OUT':
                            precision = (attr.getElementsByTagName('precision')[0]).childNodes[0].data
                            member = (attr.getElementsByTagName('members')[0]).childNodes[0].data
                            member1 = member[14:]
                            member2 = member1.replace('.', '_')

                            for label in labels:
                                unit = label.getAttribute('unit')
                                #print('unit=', unit)
                                if unit in dictBaseUnit.keys():
                                    bottomFile.write('\t\t%s_qle->setText(QString("%%1").arg(%s(%s),0,\'f\',%s));\n'
                                                % (member2, dictBaseUnit[unit][0], member, precision))
                                elif unit == 'none':
                                    if '_ENUM' in type:
                                        bottomFile.write('\t\tswitch(%s)\n\t\t{\n' %(member))
                                        for enum in dict_enum[type]:
                                            try:
                                                tenum = enum.split('=')[0]
                                                print('tenum =', tenum)
                                                if 'MIN' not in tenum and 'MAX' not in tenum:
                                                    bottomFile.write('\t'*3 +'case %s:\n'%(tenum))
                                                    bottomFile.write('\t'*4+'%s_qle->setText("%s");\n' %(member2,dict_enumForUi[enum]))
                                                    bottomFile.write('\t'*4+'break;\n')
                                            except KeyError:pass

                                        bottomFile.write('\t'*3+'default:\n'+'\t'*4+member2+'_qle->setText("Unknown");\n'+'\t'*4+'break;\n}')

                                    elif 'BOOL' in type.upper():
                                        bottomFile.write('''\t\tif (%s):
                                        %s_qle->setText("True");
                                    else:
                                        %s_qle->setText("False");
                                        ''' %(member,member2,member2))
                                    else:
                                        bottomFile.write('\t\t%s_qle->setText(QString("%%1").arg(%s);\n' % (member2, member))


                        elif paramAttr.upper() == 'IN':
                            paramRange = (attr.getElementsByTagName('interval')[0]).childNodes[0].data
                            precision = (attr.getElementsByTagName('precision')[0]).childNodes[0].data
                            step = (attr.getElementsByTagName('step')[0]).childNodes[0].data
                            intervals = attr.getElementsByTagName('interval')
                            print ('intervals=' ,intervals)
                            member = (attr.getElementsByTagName('members')[0]).childNodes[0].data
                            member1 = member[14:]
                            member2 = member1.replace('.', '_')
                            m = re.search(r'\[.*\]',member)

                            if '_ENUM' in type:
                                firstEnum = (dict_enum[type.strip()][0]).split('=')[1]
                                num = (re.search('\d',firstEnum)).group()
                                print ('first enum number start =',num)
                                if int(num) == 0:
                                    fileExec.write('\t\t%s = (%s)(%s_qcb->currentIndex()+1);\n' % (member, type, member2))
                                else:
                                    fileExec.write('\t\t%s = (%s)(%s_qcb->currentIndex());\n' % (member, type, member2))
                            elif 'SMEE_BOOL' in type:
                                fileExec.write('\t\t%s = %s_qckb->isChecked();\n' % (member, member2))
                            else:
                                if paramRange != 'none':  # ini,
                                    # precision = (attr.getElementsByTagName('precision')[0]).childNodes[0].data
                                    templistCheckIsValid.append(member2+'_qsb')
                                    fileRange.write('\t\tm_spinBoxAgent->RegisterSpinBox(%s_qsb,\"%s\");\n' % (member2, member2))

                                    for label in labels:
                                        unit = label.getAttribute('unit')
                                        #print('unit=', unit)
                                        if unit in dictBaseUnit.keys():
                                            fileExec.write('\t\t%s = (%s)(%s_qlb->value(),0,\'f\',%s);\n' % (
                                            member, dictBaseUnit[unit][1], member2, precision))
                                        else:
                                            fileExec.write('\t\t%s = %s_qlb->value();\n' % (member, member2))
                                    for interval in intervals:
                                        default = interval.getAttribute('default')
                                    fileIni.write('%s,\t%s,\t%s,\t%s,\t%s\n' % (
                                    member2, paramRange, default, precision, step))

                                else:
                                    for label in labels:
                                        unit1 = label.getAttribute('unit')
                                        #print('unit=', unit1)
                                        if unit1 in dictBaseUnit.keys():
                                            fileExec.write('\t\t%s = (%s)(%s_qlb->value());\n' % (member, dictBaseUnit[unit1][1], member2))
                                        else:fileExec.write('\t\t%s = %s_qlb->value();\n' % (member, member2))

                    if len(templistCheckIsValid)!=0:
                        fileButtonClick.write('\t\t\tcase (int)%s:\n' % str(fun).upper())
                        fileButtonClick.write('\t\t\t\tif(\n' )
                        for index in range(len(templistCheckIsValid)-1):
                            fileButtonClick.write('\t\t\t\t\tm_spinBoxAgent->CheckIsValid(%s)&&\n' % templistCheckIsValid[index])
                        fileButtonClick.write('\t\t\t\t\tm_spinBoxAgent->CheckIsValid(%s))\n' % templistCheckIsValid[-1])
                        fileButtonClick.write('''
                    {
                        m_func=%s;
                        emit performFuncSignal(button_id);
                    }
                else
                    {
                        SMEE::MessageBox::critical(this,"Error","The red value is out of range.");
                    }
                break;\n''' % (str(fun).upper()))
                    else:
                        fileButtonClick.write('\t\t\tcase (int)%s:\n'%str(fun).upper())
                        fileButtonClick.write('\t\t\t\tm_func=%s;\n'%str(fun).upper())
                        fileButtonClick.write('\t\t\t\temit performFuncSignal(button_id);\n')
                        fileButtonClick.write('\t\t\t\tbreak;\n')

            bottomFile.write('\n\t\tbreak;\n')
            fileExec.write('\t\t//执行函数\n')
            fileExec.write('\t\terror_code = %s('%(dict_page_fun[pages][i]))
            tempfun=dict_page_fun[pages][i]
            params = dict_funs[tempfun]
            print('params=' %(params))
            params_num = len(dict_funs[tempfun])
            if params_num != 0:
                for j in range(params_num-1):
                    if 'IN' in params[j][0] :
                        fileExec.write('\t'*8+'u_param.param_%s.%s,\n'%(dict_page_fun[pages][i],params[j][2]))
                    else:
                        fileExec.write('\t' * 8 + '&u_param.param_%s.%s,\n' % (dict_page_fun[pages][i], params[j][2]))
                if 'IN' in params[params_num-1][0]:
                    fileExec.write('\t'*8+'u_param.param_%s.%s);\n'%(dict_page_fun[pages][i],params[params_num-1][2]))
                else:
                    fileExec.write('\t' * 8 + '&u_param.param_%s.%s);\n' % (dict_page_fun[pages][i], params[params_num - 1][2]))
            else:fileExec.write(');\n') #接口参数为空时。

            fileExec.write('\t\t//更新界面\n')
            fileExec.write('\t\toutputEnd(func_name,error_code);\n\t}\n')

        bottomFile.write('\tdefault:')
        bottomFile.write('\n\t\tbreak;')
        bottomFile.write('\n\t}')
        bottomFile.write('\n}')
        fileRange.write('\n\t}\n')
        fileButtonClick.write('\t\t\tdefault:\n')
        fileButtonClick.write('\t\t\t\tm_func=button_id;\n')
        fileButtonClick.write('\t\t\t\temit performFuncSignal(button_id);')
        fileButtonClick.write('\n\t\t\t\tbreak;\n\t\t}\n\t}')
        fileIni.write('#end\n')
        cppfilepath = generateCodefile.pageTopCppCode(CCNAME,curpath,dict_page_fun,dict_funsSheet2,pages)
        print('cppfilepath = ',cppfilepath)
        copyFunsToCpp(cppfilepath,
                      bottomFile,
                      fileRange,
                      fileButtonClick,
                      fileExec,
                      curpath,
                      CCNAME,
                      pages,
                      curpath)


def copyFunsToCpp(cppfilepath,
                  bottomFile,
                  fileRange,
                  fileButtonClick,
                  fileExec,
                  filepath,
                  CCNAME,
                  pages,
                  curpath):
    file = open(cppfilepath,'a+')

    fileRange.seek(0);fileButtonClick.seek(0);fileExec.seek(0)
    rangeCheckLineInfo = fileRange.readlines()
    performButtonClickedSlotLineInfo = fileButtonClick.readlines()
    execInfo = fileExec.readlines()
    bottomFile.write('\n')
    for line in rangeCheckLineInfo:
        if line != '\n':bottomFile.write(line)
        else:pass
    bottomFile.write('\n')
    for line in performButtonClickedSlotLineInfo:
        if line != '\n':bottomFile.write(line)
        else:pass
    bottomFile.write('\n')
    for line in execInfo:
        if line != '\n':bottomFile.write(line)
        else:pass
    file.write('\n');bottomFile.seek(0)
    bottomFileInfo = bottomFile.readlines()
    for line in bottomFileInfo:
        if line != '\n': file.write(line)
        else:pass

    fileRange.close();fileButtonClick.close();fileExec.close();bottomFile.close(),file.close()
    os.remove((os.sep).join([curpath,"Outcodefiles/temp_rangeCheck.txt"]))
    os.remove((os.sep).join([curpath,"Outcodefiles/performButtonClickedSlot.txt"]))
    os.remove((os.sep).join([curpath,"Outcodefiles/m_exec.txt"]))
    os.remove((os.sep).join([filepath, "Outcodefiles", "bottom" + CCNAME + "VT" + pages + ".cpp"]))

