# xlrd,xlwt,xlutils 针对xls,xlwt需要新建文件写入。
# openpyxl = xlsx,但是合并单元格有问题
# xlsxWriter不支持读或者改现有的excel文件

#备注 VT 代码中涉及到的宏直接在刷代码之前就确定好，不在头文件中查找了。
#step 1. 检查需求表格sheet1 和sheet2 表格的接口名称和个数是否一致。
#step 2. 生成 temp_interfaces.txt,用于保存VT 需要刷代码的接口。
#step 3.收集信息，生成xml格式文件
#step 4.生成XXVT.*
#step 5.生成 xxvt.ui 和 xxvtCategory.ui
#coding:utf-8
import sys
import os
import xlrd
from xlutils.copy import copy
import time
import checkExcel
import generateCodefile
import parseheadfile
import excelToXML
import xmlToUi
set_enumUi = {}


if __name__ == '__main__':
    EXCELPATH = sys.argv[1] # 需求表格.xls
    CCNAME =  sys.argv[2]   #XX
    author = sys.argv[3] #作者
    curPath = os.getcwd()
    # G:\all_exercises\python_prjs\pyvt_auto0509\pyvt_auto
    #需求表格预处理
    log = open("check_result.txt", 'a+')

    oldwb=xlrd.open_workbook(EXCELPATH,formatting_info=True)#excel 多单元格合并
    newwb = copy(oldwb)
    newws = newwb.get_sheet('enum')

    log.write('step1.收集全局变量信息：\n')
    checkExcel.global_varibale(oldwb,CCNAME,log)
    log.write('step2.检查需求表格sheet1 和sheet2,接口名称和个数是否一致。\n')
    checkExcel.check_funs(log)


    checkExcel.read_excel_index1(oldwb, CCNAME,log)

    checkExcel.read_excel_index2(oldwb,log)

    print("step 3.temp_interfaces.txt,用于保存VT 需要刷代码的接口。")
    print('生成dict_funs列表')
    parseheadfile.preprocess_header_files(CCNAME,curPath)
    parseheadfile.generate_requirefuns_tempfile(CCNAME, curPath,log)

    print("step 4. 检查headFiles目录下头文件收集是否齐全。")
    if checkExcel.bool_XX4T:
        result = parseheadfile.check_headfile_all(curPath,CCNAME + '4T_if.h')
    if checkExcel.bool_XX4A:
        result1=parseheadfile.check_headfile_all(curPath,CCNAME + '4A_if.h')
    log.write('重要信息:完成此次刷代码需要的头文件：%s\n' %(set(result)|set(result1)))

    print("step 5. 解析头文件中的枚举和结构体。生成dict_enum，dict_struct")
    parseheadfile.collect_struct_enum(curPath, parseheadfile.headfile_list)
    print('step 6.将VT 界面接口需要的枚举提前写到excel 中。')
    #print('checkExcel.set_enumUi=', checkExcel.set_enumUi)

    set_enumUi = set(checkExcel.list_enumUi)
    parseheadfile.enumWriteToExcel(newws,parseheadfile.dict_enum,set_enumUi)
    os.remove(curPath+'/'+EXCELPATH)
    newwb.save(curPath+'/'+EXCELPATH)
    time.sleep(2)
    print("执行下一条步骤，请填充需求表格enmu 页 枚举值在界面的显示样式！")
    newwb=xlrd.open_workbook(curPath+'/'+EXCELPATH,formatting_info=True)#excel 多单元格合并
    parseheadfile.enumForUi(newwb,log) #将枚举收集到字典里


    print("step 7.生成XXVT.* 代码文件(各项目通用)。")
    generateCodefile.codefileUniversal(CCNAME, author, checkExcel.page_list1,curPath)

    print("step 8.生成各组件对应子页面头文件")
    print('step:待定：XXVT.h,XXVT.cpp,XXVT_if.h,XXVT_tc.h')
    generateCodefile.pageCodeHeadFiles(CCNAME,
                                       author,
                                       checkExcel.page_list1,
                                       checkExcel.bool_XX4T,
                                       checkExcel.bool_XX4A,
                                       checkExcel.dict_pages,
                                       parseheadfile.dict_funs,
                                       curPath,
                                       log)

    print("step 9.由excelsheet2 生成./XXVT/excelFunsXml.xml")
    excelToXML.excel_to_xml(curPath)
    print("step10.由excelsheet2 生成./XXVT/excelXmlForUi.xml")

    excelToXML.excelToXmlForUi(newwb,
                               checkExcel.dict_funSh1Index,
                               checkExcel.dict_layouttab,
                               checkExcel.dict_tab1Index,
                               checkExcel.dict_funsShee2,
                               parseheadfile.dict_enumForUi,
                               parseheadfile.dict_enum,
                               curPath)
   

    print("step 11.解析excelFunsXml.xml，生成cpp特有接口。")
    excelToXML.xmlToBottomCpp(CCNAME,curPath,
                              checkExcel.dict_pages,
                              parseheadfile.dict_enum,
                              parseheadfile.dict_funs,
                              checkExcel.dict_table_params,
                              curPath,
                              log)

    print("step 12.解析excelXmlForUi.xml，生成ui界面。")
    xmlToUi.xmlToUi(CCNAME,curPath,checkExcel.dict_pages)

    '''
    print("step 6.生成 xxvt.ui 和 xxvtCategory.ui")
    generateUIfiles.xxvt_ui(CCNAME)
    generateUIfiles.xxvtCategory_ui(CCNAME,checkExcel.page_list1)
   
    '''
#generateUIfiles.widgets_general(CCNAME,
#                                    checkExcel.page_list1)