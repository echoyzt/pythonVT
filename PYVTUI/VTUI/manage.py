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
import excelCheck_debug
import collectExcelInfo
import parseheadfile
#import excelToXML
#import xmlToUi
set_enumUi = {}


if __name__ == '__main__':

    CCName = sys.argv[1]
    ExcelPath = sys.argv[2]
    ExcelName = sys.argv[3]
    NO = sys.argv[4]

    '''
    CCName = 'EC'
    ExcelPath = "G:/all_exercises/python_prjs/pyvt_auto0604/PYVTUI/VTUI/temp_506VTEC"
    ExcelName = "S314_SW_EDS_VTEC-V4.xls"
    NO = "NO3"
    '''
    if NO == "NO1":
        check_result = open(ExcelPath + "/check_result.txt", 'w')
        oldwb = xlrd.open_workbook(ExcelPath + '/' + ExcelName, formatting_info=True)  # excel 多单元格合并
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

        excelCheck_debug.oldwsExcelInformation(oldws, m_row_num,check_result)
        excelCheck_debug.preProcessExcel(newws)  # 对精度，单位的处理，都可以先行检查。
        excelCheck_debug.checkRange(newws,check_result)  # 对范围进一步检查

        excelCheck_debug.funsIndex1(oldwb, CCName)
        excelCheck_debug.funsIndex2(oldwb, m_row_num)
        excelCheck_debug.funsCheck(check_result,ExcelPath)

        os.remove(ExcelPath + '/' + ExcelName)
        newwb.save(ExcelPath + '/' + ExcelName)
        check_result.write('--------------step1 检查需求表格规范------>end.\n')
        check_result.close()
    if NO == "NO2":
        log = open(ExcelPath + "/check_result2.txt", 'w')

        wb = xlrd.open_workbook(ExcelPath + '/' + ExcelName, formatting_info=True)  # excel 多单元格合并
        collectExcelInfo.global_varibale(wb, CCName, log,ExcelPath)
        collectExcelInfo.read_excel_index1(wb, CCName, log)
        collectExcelInfo.read_excel_index2(wb, log)
    if NO == "NO3":
        log = open(ExcelPath + "/check_result.txt", 'a+')
        oldwb = xlrd.open_workbook(ExcelPath + '/' + ExcelName, formatting_info=True)  # excel 多单元格合并
        newwb = copy(oldwb)
        newws = newwb.get_sheet('enum')

        file = open(ExcelPath + "/temp_headfilelist.txt", 'w')
        # print("os.listdir= ",os.listdir(ExcelPath + "/temp_HeaderFiles"))
        for headfile in os.listdir(ExcelPath + "/temp_HeaderFiles"):
            if os.path.isfile(ExcelPath + "/temp_HeaderFiles/" + headfile):
                parseheadfile.headfile_list.append(headfile)
                file.write(headfile + '\n')
        file.close()

        parseheadfile.preprocess_header_files(CCName, ExcelPath + "/temp_HeaderFiles")
        parseheadfile.generate_requirefuns_tempfile(CCName, ExcelPath, log)
        parseheadfile.collect_struct_enum(ExcelPath + "/temp_HeaderFiles", parseheadfile.headfile_list,ExcelPath)
        
		
		log.write('step.将VT 界面接口需要的枚举提前写到excel 中。')
        set_enumUi = set(collectExcelInfo.list_enumUi)
        parseheadfile.enumWriteToExcel(newws, parseheadfile.dict_enum, set_enumUi)
        os.remove(ExcelPath + '/' + ExcelName)
        newwb.save(ExcelPath + '/' + ExcelName)








