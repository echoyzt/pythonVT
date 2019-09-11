#-*-coding:UTF-8-*-
import os
import sys
import xlrd
import xlwt
import re

from xlutils.copy import copy
dict_unit_smee_to_si = {"mm": "m", "pm": "m", "nm": "m", "um": "m", "nm/ms": "m/s", "KHz": "Hz", "MHz": "Hz","mrad": "rad",
                        "urad": "rad", "nrad": "rad", "deg": "rad", "uJ": "J", "mJ/cm2": "J/m2", "mW/cm2": "W/m2","℃": "K",
                        "ms": "s", "us": "s", "min": "s", "hour": "s","h":"s","day":"s", "L/min": "m3/s","bar":"Pa"}
dict_precision_to_singleStep = {0.0: '1', 1.0: '0.1', 2.0: '0.01', 3.0: "0.001", 4.0: '0.0001', 5.0: '0.00001',6.0: '0.000001',
                                7.0: '0.0000001', 8.0: "0.00000001", 9.0: "0.000000001"}  # 根据精度确定步长。

param_basket = []
m_row_num = 0
fun_list_sh1 = []  # 记录sh1所有的函数列表.
fun_list_sh2 = []
set_fun_sh1 = set()
set_fun_sh2 = set()
bool_XX4A = False
bool_XX4T = False
#xlwt 时
#xlwt.easyxf()
styleRed = xlwt.XFStyle() #创建样式
pattern = xlwt.Pattern()
pattern.pattern=xlwt.Pattern.SOLID_PATTERN #实型，不能少
pattern.pattern_fore_colour=2#背景红色
styleRed.pattern = pattern #将pattern字体格式应用到styleRed上。

styleWhite = xlwt.XFStyle()
pattern1 = xlwt.Pattern()
pattern1.pattern=xlwt.Pattern.SOLID_PATTERN #实型，不能少
pattern1.pattern_fore_colour=1#背景白色
styleWhite.pattern = pattern1
font1 = xlwt.Font() #设置字体格式
font1.colour_index = 0 #0黑，1白，2红，3绿，4蓝，5黄，6紫
styleWhite.font=font1


#xultils时
#styleRed = xlwt.add_palette_colour("custom_bg_colour", 0x22)

#style1 = Font(color=colors.BLACK)  #定义一个可以共享的Styles  # 表格样式，字体黑底。
#style2 = PatternFill(fill_type='solid',start_color='FFFF8C00',end_color='FFFF8C00') # 表格样式，填充桔色底。错误
#style3 = PatternFill(fill_type='solid',start_color='FFFFFFFF',end_color='FFFFFFFF') # 表格样式，填充白底。
#style4 = PatternFill(fill_type='solid',start_color='FFFFFF00',end_color='FFFFFF00') # 表格样式，填充黄底。警告
# 收集信息：所有参数的输入输出属性，参数类型，单位，默认值，精度，范围，步长，单位转换。
def oldwsExcelInformation(sheet2,row_num,check_result):
    attribute = []
    param_type = []
    param_unit = []
    param_default_num = []
    param_precision = []
    param_range = []
    param_step = []
    param_unit_trans = []
    param_rowindex = []
    for num in range(3, row_num):# 从第4行开始检查
        attribute.append(((sheet2.cell(num, 2).value).strip()).upper())  # attribute得到所有IN,OUT 属性。
        param_type.append(((sheet2.cell(num, 4).value).strip()).upper())  # param_type 存所有参数的类型。int，double
        param_unit.append((sheet2.cell(num, 5).value).strip())  # param_unit存参数单位。
        param_default_num.append(str(sheet2.cell(num, 6).value).strip())  # param_default_num 默认值。
        param_precision.append(str(sheet2.cell(num, 7).value).strip())  # param_precision 参数精度
        param_range.append((sheet2.cell(num, 8).value).strip())  # param_range 参数范围
        param_step.append(sheet2.cell(num, 9).value)  # param_step 参数单位步长。
        param_unit_trans.append((sheet2.cell(num, 10).value).strip())  # param_unit_trans单位转换。
        param_rowindex.append(num+1)  #对应需求表格所在的行标，用于当表格为空行，且没有结束。
    global param_basket
    # zip 并行迭代。
    param_basket = []
    param_basket = list(
        zip(attribute, param_type, param_unit, param_default_num, param_precision, param_range, param_step,param_unit_trans,param_rowindex))
    #print ("param_basket = ",param_basket)
    #print ("len param_basket = ",len(param_basket))
    check_result.write("len param_basket = " + str(len(param_basket)) + '\n')

'''
精度:无论输入输出，非整型都有精度要求3或6。整型默认为0.枚举，char，bool--->none
单位:单位如果没有，补none。有单位，判断是否是国际单位

输入
    有范围
        有默认值且有步长
    无范围
        无默认值且无步长-->none
输出
    有无范围-->none，默认值，步长-->none
'''
def preProcessExcel(newws,check_result):
    for i in range(len(param_basket)):
        #对精度的处理，
        if 'SMEE_FLOAT' ==param_basket[i][1] or \
           'SMEE_DOUBLE' ==param_basket[i][1]:
            if param_basket[i][4] != "" :
                if float(param_basket[i][4]) < 0:
                    newws.write(i+3,7,param_basket[i][4],styleRed)
                    check_result.write("(%s,8)cell=%s :"%((i+4),param_basket[i][4])+'精度不能为负数\n')
                else:pass
            else:
                newws.write(i+3,7,'6',styleWhite)
        elif "SMEE_BOOL"==param_basket[i][1]or \
             "SMEE_CHAR"==param_basket[i][1]or \
             "_ENUM" in param_basket[i][1]:
            newws.write(i+3,7,'none',styleWhite)
        else:
            newws.write(i+3,7,'0',styleWhite)

    #对单位的处理
    for i in range(len(param_basket)):
        if not ("_ENUM" in param_basket[i][1]) and \
            "SMEE_BOOL" != param_basket[i][1] and \
            "SMEE_CHAR" != param_basket[i][1]:
            if param_basket[i][2] != "":  # 3 判断参数单位
                if "none" == param_basket[i][2]:  # 如果参数单位为 none,则单位转换栏补none
                    newws.write(i + 3, 10, 'none', styleWhite)
                else:  # 判断是不是国际单位。
                    if param_basket[i][2] in list(dict_unit_smee_to_si.values()):
                        newws.write(i + 3, 5, param_basket[i][2], styleRed)
                        check_result.write("(%s,6)cell=%s :" % ((i + 4), param_basket[i][2]) + '单位是国际单位，需要修改吗？\n')
                    else:
                        pass
            else:
                newws.write(i+3, 5, 'none', styleWhite)
        else:
            newws.write(i+3, 5, 'none', styleWhite)

    #对范围，默认值，步长的处理
    for i in range(len(param_basket)):
        # 参数属性为OUT时,无范围，无默认值，无单位步长
        if "OUT" == param_basket[i][0]:
            newws.write(i + 3, 6, 'none', styleWhite)
            newws.write(i + 3, 8, 'none', styleWhite)
            newws.write(i + 3, 9, 'none', styleWhite)

        elif ("IN" == param_basket[i][0]) or ("INOUT" == param_basket[i][0]):
            # 输入参数才有范围。
            if param_basket[i][5] != '':
                if param_basket[i][3] != '' and param_basket[i][6] != '':
                    pass
                else:
                    if param_basket[i][3] == '':
                        newws.write(i + 3, 6, '', styleRed)
                        check_result.write("(%d,7)cell=:" % (i + 4) + '有范围，默认值不能为空\n')
                    if param_basket[i][6] == '':
                        newws.write(i + 3, 9, '', styleRed)
                        check_result.write("(%d,10)cell='':" % ((i + 4) + '有范围，步长不能为空\n'))
            else:
                newws.write(i + 3, 6, 'none', styleWhite)
                newws.write(i + 3, 8, 'none', styleWhite)
                newws.write(i + 3, 9, 'none', styleWhite)
        else:
            newws.write(i + 3, 6, 'none', styleWhite)
            check_result.write("(%d,10)cell='':" % ((i + 4) + '有范围，步长不能为空\n'))


def check_range_is_legal(ws,indexRow, indexColumn):
    str = param_basket[indexRow-4][5]
    sub_str = str[1:-1]
    list_sub_str = sub_str.split(',')  # list
    if (str.startswith('(') and str.endswith(')')) or \
       (str.startswith('(') and str.endswith(']')) or \
       (str.startswith('[') and str.endswith(')')) or \
       (str.startswith('[') and str.endswith(']')):
        if ("SMEE_INT32" == param_basket[indexRow-4][1])or("SMEE_UINT32"==param_basket[indexRow-4][1]) \
            or("SMEE_INT8" == param_basket[indexRow-4][1])or("SMEE_UINT8"==param_basket[indexRow-4][1]) \
            or("SMEE_INT16" == param_basket[indexRow-4][1])or("SMEE_UINT16"==param_basket[indexRow-4][1]) \
            or("SMEE_INT64" == param_basket[indexRow-4][1])or("SMEE_UINT64"==param_basket[indexRow-4][1]) \
            or("SMEE_ULONG32" == param_basket[indexRow-4][1])or("SMEE_LONG"==param_basket[indexRow-4][1]):
                #当输入参数类型是整型时，判断参数范围数也应该是整型。
                if (abs(int(float(list_sub_str[0])))==abs(float(list_sub_str[0]))) \
                    and (abs(int(list_sub_str[1])) == abs(float(list_sub_str[1]))):
                    return True
                else:
                    ws.write(indexRow-1,indexColumn-1,str,styleRed)
                    check_result.write("(%d,%d)cell=%s:参数类型应该是整型\n"%(indexRow,indexColumn,str))
                    return False
        else:return True
    else:
        ws.write(indexRow-1,indexColumn-1,str,styleRed)
        check_result.write("(%d,%d)cell=%s:参数格式应该是[a,b],[a,b),(a,b],(a,b)\n"%(indexRow,indexColumn,str))
        return False

#在调用此接口之前，已经调用了check_range_is_legal
# 故可以直接判断默认值是否在范围之内。无需考虑格式。
def  default_num_is_inRange(ws,indexRow,indexColumn,check_result):
    str = param_basket[indexRow-4][5]
    middle = float(param_basket[indexRow - 4][3])
    if isinstance(middle, float):
        if str.startswith('['):  # 左闭区间
            if str.endswith(']'):
                left = float(str[str.find('[') + 1:str.find(',')])
                right = float(str[str.find(',') + 1:str.find(']')])

                if left <= middle <= right:
                    return True
                else:
                    check_result.write('(%d,%d):cell=%s 默认值不在范围内\n.' % (indexRow, indexColumn, middle))
                    ws.write(indexRow - 1, indexColumn - 1, middle, styleRed)
                    return False
            else:  # 左闭右开区间
                if float(str[str.find('[') + 1:str.find(',')]) <= middle < float(
                        str[str.find(',') + 1:str.find(')')]):
                    return True
                else:
                    check_result.write('(%d,%d):cell=%s 默认值不在范围内\n.' % (indexRow, indexColumn, middle))
                    ws.write(indexRow - 1, indexColumn - 1, middle, styleRed)
                    return False
        elif str.startswith("("):  # 左开区间
            if str.endswith(']'):
                if float(str[str.find('(') + 1:str.find(',')]) < middle <= float(
                        str[str.find(',') + 1:str.find(']')]):
                    return True
                else:
                    check_result.write('(%d,%d):cell=%s 默认值不在范围内\n.' % (indexRow, indexColumn, middle))
                    ws.write(indexRow - 1, indexColumn - 1, middle, styleRed)
                    return False
            else:
                if float(str[str.find('(') + 1:str.find(',')]) < middle < float(
                        str[str.find(',') + 1:str.find(')')]):
                    return True
                else:
                    check_result.write('(%d,%d):cell=%s 默认值不在范围内\n.' % (indexRow, indexColumn, middle))
                    ws.write(indexRow - 1, indexColumn - 1, middle, styleRed)
                    return False
    else:
        check_result.write('(%d,%d):cell=%s\n.' % (indexRow, indexColumn, middle) + '检查默认值类型')
        ws.write(indexRow - 1, indexColumn - 1, middle, styleRed)


#判断单位步长，
#如果是整形参数，则默认步长为1，
#浮点型参数，如果没填，根据精度生成步长。
def checkStep(newws,rowNum, colNum):
    if ("SMEE_FLOAT" == param_basket[rowNum-2][1]) or ("SMEE_DOUBLE" == param_basket[rowNum-2][1]):
        if param_basket[rowNum-2][6] != "": pass
        else:
            singleStep = dict_precision_to_singleStep[param_basket[rowNum-2][4]]
            newws.write(rowNum-1, colNum-1, singleStep, styleWhite)

    elif not ("_ENUM" in param_basket[rowNum-2][1]) and \
        "SMEE_BOOL" != param_basket[rowNum-2][1] and \
        "SMEE_CHAR" != param_basket[rowNum-2][1]:
        if param_basket[rowNum-2][6] == "":
            newws.write(rowNum-1, colNum-1, '1', styleWhite)
        else:pass



def checkRange(ws,check_result):
    for i in range(len(param_basket)):
        #参数属性为输入时。
        #只有输入参数要判断参数范围。有范围才有精度,才有默认值。
        if ("IN" == (param_basket[i][0])) or ("INOUT" == param_basket[i][0]):
            if param_basket[i][5] != "" and param_basket[i][5]!='none':
                #范围格式是否正确
                if True == check_range_is_legal(ws,i+4,9):
                    #默认值
                    if param_basket[i][3] != "":
                        default_num_is_inRange(ws,i+4,7,check_result)
                    else:
                        ws.write(i + 3, 6, param_basket[i][3], styleRed)
                        check_result.write("(%d,7):cell=''" % (i + 4) + '有范围，默认值不能为空\n')
                    checkStep(ws,i+2,10)#检查步长
                else:pass
            else:pass
        else:pass


def funsIndex1(oldwb,CCNAME):
    sh1 = oldwb.sheet_by_index(1)
    rownumsh1=sh1.nrows
    #记录sh1所有接口。
    for num in range(5, rownumsh1):
        if sh1.cell(num, 4).value != "":
            fun_list_sh1.append(str(sh1.cell(num, 4).value).strip())
    global set_fun_sh1
    set_fun_sh1 = set(fun_list_sh1)  # 为所有sh1接口创建集合。

    # 用于判断头文件包含文件。
    for i in range(len(fun_list_sh1)):
        if CCNAME + "4A" == fun_list_sh1[i][0:4]:
            global bool_XX4A
            bool_XX4A = True
            continue
        else:pass
        if CCNAME + "4T" == fun_list_sh1[i][0:4]:
            global bool_XX4T
            bool_XX4T = True
            continue
        else:pass

def funsIndex2(oldwb,m_row_num):
    sh2 = oldwb.sheet_by_index(2)
    rownum2 = m_row_num


    for num in range(3, rownum2):  # 从第1行开始,获取sheet2页接口列表。
        if sh2.cell(num, 0).value != "":
            fun_list_sh2.append((sh2.cell(num, 0).value).replace('\n', ''))  # 有 \n .

    global set_fun_sh2
    set_fun_sh2 = set(fun_list_sh2)



def funsCheck(log,ExcelPath):
    if len(set_fun_sh1) != len(fun_list_sh1):
        log.write("error:sheet1 页存在重复的接口！\n")


    if len(set_fun_sh2) != len(fun_list_sh2):
        log.write("error:sheet2 页存在重复的接口！\n")
    if (set_fun_sh1 - set_fun_sh2) == set():
        log.write("sh1 和sh2 接口一致。\n")
    else:
        log.write("sh1 独有的接口：%s\n"%(set_fun_sh1 - set_fun_sh2))
        log.write("sh2 独有的接口：%s\n"%(set_fun_sh2 - set_fun_sh1))
        log.write("error!接口不一致，请检查确认\n")  # 不一致


if __name__ == '__main__':
#传参一律以需求表格对应行，列标为准，防止混淆。！！！！！！！！！！！！！！！！！！

    CCName = sys.argv[1]
    ExcelPath = sys.argv[2]
    ExcelName = sys.argv[3]
    '''
    CCName = 'EC'
    ExcelPath = "G:/all_exercises/python_prjs/pyvt_auto0604/PYVTUI/VTUI/temp_506VTEC"
    ExcelName = "S314_SW_EDS_VTEC-V4.xls"
    '''

    check_result = open(ExcelPath + "/excelRuleCheckResult.txt", 'w')
    oldwb = xlrd.open_workbook(ExcelPath+'/'+ExcelName, formatting_info=True)  # excel 多单元格合并
    oldws = oldwb.sheet_by_index(2) #无write方法
    nrows = oldws.nrows
    ncols = oldws.ncols
    for i in range(3,nrows+1):
        try:
            row_value = oldws.row_values(i,0,ncols)
            if set(row_value)=={''}:
                m_row_num=i
                break
            else:pass
        except IndexError:
            m_row_num=nrows
    check_result.write("显示检查结果：\n")
    check_result.write("--------------step1 检查需求表格规范------>start.\n")
    check_result.write("ExcelName = %s\n" %ExcelName)
    #check_result.write('tempdirpath=%s\n' %tempdirpath)
    check_result.write('m_row_num=%d,对应需求表格的行标\n'%m_row_num)#此与xls行标对应！！！

    newwb = copy(oldwb)
    newws = newwb.get_sheet(2)#有write方法。


    #每次检查之前先使表格样式为白色。
    for i in range(3,m_row_num):
        for j in range(11):
            cell_value = oldws.cell(i, (j + 1)).value
            newws.write(i, (j + 1), cell_value, styleWhite)

    oldwsExcelInformation(oldws,m_row_num)
    preProcessExcel(newws)#对精度，单位的处理，可以先行检查。
    checkRange(newws)#对范围进一步检查


    funsIndex1(oldwb,CCName)
    funsIndex2(oldwb,m_row_num)
    funsCheck(check_result,ExcelPath)

    os.remove(ExcelPath+'/'+ExcelName)
    newwb.save(ExcelPath+'/'+ExcelName)
    check_result.write('--------------step1 检查需求表格规范------>end.\n')
    check_result.close()
'''
#ws.cell有两种方式，行号列号从1开始
d = ws.cell(row = 4, column = 2).value #获取表格内容，是从第一行第一列是从1开始的，注意不要丢掉 .value
d = ws.cell(row = 4, column = 2) #行列读写,
d = ws.cell('A4') 
写入cell值
    ws.cell(row = 4, column = 2).value = 'test'
    ws.cell(row = 4, column = 2, value = 'test') 
1.若没有单位，填none
2.整型参数，精度填0
3.输出默认值为none
4.输入参数默认值必填，不能填none。
# 合并单元格formatting_info = True，
# xlrd,xlwt 只可解析 xls。
# openpyxl 可以解析xlsx
# xlutils = xlrd+xlwt
'''
