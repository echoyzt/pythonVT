import os,re
import xlrd
from xml.dom.minidom import Document
import xml.dom.minidom
from xlutils.copy import copy
import parseheadfile as phf


# 注意解析结构体和枚举,头文件统一在temp_HeaderFiles目录下。
# 生成 8funsInfoToExcel.xml。
def genaral_xml(ExcelPath):
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
            parseStructType(funs_value[params_num],
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


def parseStructType(funStruct,listStructMember,parameterlist,nodeAttribute,nodeMember,doc):
    #print("funStruct=", funStruct)
    if funStruct[0] in phf.dict_struct.keys():#説明是结构体。
        listStructMember.append(funStruct[1])
        for structValueNum in range(len(phf.dict_struct[funStruct[0]])):
            if phf.dict_struct[funStruct[0]][structValueNum][0] in phf.dict_struct.keys():#説明是结构体。
                parseStructType(phf.dict_struct[funStruct[0]][structValueNum],listStructMember,parameterlist,nodeAttribute,nodeMember,doc)
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

#8funsInfoToExcel.xml写到excel
def XMLwriteToExcel(xmlForExcel,excelPath,dict_pageToFuns):
    #excelPath='G:/all_exercises/python_prjs/pyvt_auto0630/PYVTUI/VTUI/temp_506VTEC/EDS_VTXX-V4.xls'
    oldwb = xlrd.open_workbook(excelPath, formatting_info=True)  # excel 多单元格合并
    newwb = copy(oldwb)
    sh1ws = newwb.get_sheet(1)
    sh2ws = newwb.get_sheet(2)
    #newws.write(5,4,'yuzt')
    #将8funsInfoToExcel.xml，信息写到excel需求表格中。
    # minidom 解析器打开 XML 文件。
    for m in range(5,1024):
        for n in range(11):
            sh1ws.write(m, n, "")
            sh2ws.write(m,n,"")

    DOMTree = xml.dom.minidom.parse(xmlForExcel)
    excelInfo = DOMTree.documentElement
    funNames = excelInfo.getElementsByTagName("fun_name")
    #print('pageNames =',pageNames)
    countrow=3
    rowsh1=5
    for key in dict_pageToFuns.keys():
        temprow = len(dict_pageToFuns[key])
        sh1ws.write(rowsh1, 0, key)
        for j in range(len(dict_pageToFuns[key])):
            sh1ws.write(rowsh1+j,4,dict_pageToFuns[key][j])
        rowsh1 = rowsh1 + temprow

    for funName in funNames:
        funname = funName.getAttribute("name")
        print("write fun ["+funname+"] to Excel...")
        sh2ws.write(countrow,0,funname)
        attributes=funName.getElementsByTagName('attribute')
        for attr in attributes:
            in_out=attr.getAttribute('attr')
            param_name=attr.getElementsByTagName('param_name')
            #param_type = param_name[0].getAttribute('type')
            members = (attr.getElementsByTagName("members")[0]).childNodes[0].data
            submems=re.sub('\s','',members)
            listmems=submems.split('[item]')
            listmems.remove('')
            print("listmembers in xml===" ,listmems)
            for listmem in listmems:
                if '|[' in listmem:
                    sh2ws.write(countrow, 1,listmem[:listmem.rfind('|[')])
                    sh2ws.write(countrow,4,listmem[listmem.rfind('|[')+2:-1])
                else:
                    sh2ws.write(countrow, 1, listmem)
                sh2ws.write(countrow, 2, in_out)
                countrow=countrow+1
            #print(listmems)
    newwb.save(excelPath)

if __name__ == "__main__":
    m_tempdir = 'C:/Users/Administrator/Desktop/pyvttest1128'.replace('/', '\\')
    gTempProDir = 'temp_506VTEC'
    ExcelPath = m_tempdir + '\\' + gTempProDir
    xmlForExcel = ExcelPath + '\\8funsInfoToExcelbak2.xml'
    XMLwriteToExcel(xmlForExcel,ExcelPath+'\\EDS_VTXX-V4.xls')