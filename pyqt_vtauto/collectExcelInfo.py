# 此文件用于检查需求表格sheet1 和sheet2 表格的接口名称和个数是否一致。
#import time
# sheet_by_index(1),用于ini文件格式分类 app，general，maintenance...
import re,os,sys,copy,xlrd
from PyQt5.QtWidgets import *
#set_enumUi = {} #收集ui接口需要表示的枚举。
#page_list_tuple1 = ()  # 元祖，不可变，作为key ,取出第5行开始，第0列的索引.
funs_list_sh1_tuple = ()

set_page = set()
set_tabs = set()
funs_list_sh1 = []  # 记录sh1所有的函数列表.
funs_list_sh2 = []
set_fun_sh1 = set()
m_row_num=0
m_row_num2=0
dict_funsSheet2 = {}
dict_table_params = {}
dict_firstTabs = {}
dict_funSh1Index = {}
dict_tab1Index = {} # 需求表sh1第2列
dict_layouttab = {}
dict_page_fun = {}
list_enumUi = []


'''
dict_firstTabs[label2]=[['Disconnect Net', 'CE4T_disconnect_net'], ['Connect Net', 'CE4T_connect_net']]
dict_firstTabs[label1]=[['Get Tw As Heater Setpoint Limits', 'CE4T_get_Tw_as_heater_setpoint_limits'], ['Set Tw As Heater Setpoint Limits', 'CE4T_set_Tw_as_heater_setpoint_limits']]
dict_firstTabs= {'label2': [['Disconnect Net', 'CE4T_disconnect_net'], ['Connect Net', 'CE4T_connect_net']], 'label1': [['Get Tw As Heater Setpoint Limits', 'CE4T_get_Tw_as_heater_setpoint_limits'], ['Set Tw As Heater Setpoint Limits', 'CE4T_set_Tw_as_heater_setpoint_limits']]}
dict_layouttab= {'TCM': ['label2', 'label1']}
dict_funs ={'CE4T_get_as_heater_PID_params': [['OUT', 'CE4T_PID_PARAMS_STRUCT', 'parameters)']], 'CE4T_set_as_heater_PID_params': [['IN', 'CE4T_PID_PARAMS_STRUCT', 'parameters)']]}
'''
def global_varibale(workbook,log,m_CCName,existXX4A,existXX4T):
    log.write('================记录的信息是全局变量：==============\n')
    page_list1 = []  # app,maintenance,...
    tablist=[]
    global set_page ,set_tabs  ,m_row_num,m_row_num2,dict_firstTabs,dict_page_fun
    sh1 = workbook.sheet_by_index(1)
    sh2 = workbook.sheet_by_index(2)
    rownum1 = sh1.nrows
    colnum1 = sh1.ncols
    rownum2 = sh2.nrows
    colnum2 = sh2.ncols
    print ('colnum2=',colnum2)

    for i in range(5,rownum1+1):
        try:
            row_value = sh1.row_values(i,1,colnum1)
            if set(row_value) == {''}:
                m_row_num = i
                break
            else:pass
        except IndexError:
            m_row_num = rownum1
    print("m_row_num=", m_row_num)
    print("colnum1=", colnum1)
    for i in range(3,rownum2+1):
        try:
            row_value = sh2.row_values(i,0, colnum2)#从0开始，防止最后一个接口是无参接口
            if set(row_value) == {''}:
                m_row_num2 = i
                break
            else:pass
        except IndexError:
            m_row_num2 = rownum2
    #---------------------------------------------------------------
    for num in range(5, m_row_num):  # 从第5行开始
        if sh1.cell(num, 0).value != "":
            page_list1.append(sh1.cell(num, 0).value)
        if sh1.cell(num,1).value != "":
            tablist.append(sh1.cell(num,1).value)

        funs_list_sh1.append(sh1.cell(num, 4).value)
    set_page = set(page_list1)
    set_tabs = set(tablist)
    #page_list_tuple1 = tuple(page_list1)  # 做字典key
    #----------------------------------------------------------------

    for tab in set_tabs:
        tlist=[]
        for row in range(5, m_row_num):
            if (sh1.cell(row, 1).value) == tab:
                tlist.append([sh1.cell(row, col).value for col in range(3, 5)])#列表推导式

        dict_firstTabs[tab] = tlist
        print('dict_firstTabs[%s]=%s' %(tab,dict_firstTabs[tab]))
    print('dict_firstTabs=', dict_firstTabs)

    for page in set_page:
        tlist=[]
        for row in range(5, m_row_num):
            if (sh1.cell(row,0).value) == page:
                dict_layouttab[page]=\
                tlist.append(sh1.cell(row,1).value)
        dict_layouttab[page]=list(set(tlist))
    print ('dict_layouttab=',dict_layouttab)

    global set_fun_sh1
    global funs_list_sh1_tuple
    set_fun_sh1 = set(funs_list_sh1)  # 为所有sh1接口创建集合。
    funs_list_sh1_tuple = tuple(funs_list_sh1)
    #print("set_fun_sh1 = ", set_fun_sh1)


    for num in range(3, m_row_num2):  # 从第3行开始,获取sheet2页接口列表。
        if sh2.cell(num, 0).value != "":
            funs_list_sh2.append((sh2.cell(num, 0).value).strip())  # 有 \n .
    for fun  in set(funs_list_sh2):
        temp_list = []
        for num in range(3,m_row_num2):
            if (sh2.cell(num ,0).value).strip() == fun:
                temp_list.append(sh2.row_values(num, 1, 10))
        dict_funsSheet2[fun] = temp_list
        print('dict_funsSheet2[%s]=%s'%(fun,temp_list))
    for fun in dict_funsSheet2.keys():
        for index in range(len(dict_funsSheet2[fun])):
            macroStr = dict_funsSheet2[fun][index][0]
            m = re.search(r'\[.*\]', macroStr)  # ?file[128]
            if m:
                macro = macroStr[macroStr.find('[') + 1:macroStr.find(']')]

    for page in dict_layouttab.keys():
        tlist=[]
        for label in dict_layouttab[page]:
            for items in dict_firstTabs[label]:
                tlist.append(items[1])
        dict_page_fun[page]=tlist
        print ('dict_page_fun[%s]=%s'%(page,tlist))

    print('确定需要的头文件，为cpp头文件include做准备\n')
    for pages in dict_page_fun.keys():
        for funs in dict_page_fun[pages]:
            if ((funs.split('/')[-1])[0:4] == m_CCName + "4A"):  # 取字符串开头4个字符
                existXX4A = True
            if ((funs.split('/')[-1])[0:4] == m_CCName + "4T"):
                existXX4T = True
    log.write('1.m_row_num=%d\n m_row_num2=%d\n' % (m_row_num, m_row_num2))
    log.write('2.len=%d,funs_list_sh1= %s\n' % (len(funs_list_sh1), funs_list_sh1))
    log.write('3.len=%d,funs_list_sh2 = %s\n' % ((len(funs_list_sh2), funs_list_sh2)))
    log.write('4.Page Name=%s\n' % set_page)
    log.write('5.set_fun_sh1 =%s\n' % (set_fun_sh1))
    log.write('6.dict_layouttab=%s\n' %(dict_layouttab))
    log.write('7.dict_firsttabs=%s\n' % (dict_firstTabs))
    log.write('8.dict_page_fun=%s\n' % (dict_page_fun))
    log.write("重要信息 接口参数详细信息，从需求表格来:\n dict_funsSheet2=%s\n" % (dict_funsSheet2))  # 包含接口参数为1或多个的信息。



if __name__ == '__main__':
    '''
    CCName = sys.argv[1]
    ExcelPath = sys.argv[2]
    ExcelName = sys.argv[3]
    '''
    CCName = 'CE'
    ExcelPath = "Z:\\newWork\\temp_012DVTCE"
    ExcelName = "EDS_VTXX-V4.xls"

    log = open(ExcelPath + "./2excelInfos.txt", 'w')
    wb = xlrd.open_workbook(ExcelPath+'/'+ExcelName, formatting_info=True)  # excel 多单元格合并
    global_varibale(wb,log)















