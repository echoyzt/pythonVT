# 此文件用于检查需求表格sheet1 和sheet2 表格的接口名称和个数是否一致。
#import time
# sheet_by_index(1),用于ini文件格式分类 app，general，maintenance...
import re
import os
import sys
import copy
import xlrd
page_list1 = []  # app,maintenance,...
page_list_tuple1 = ()  # 元祖，不可变，作为key ,取出第5行开始，第0列的索引.
funs_list_sh1_tuple = ()
funsListtuple=()
merge1 = []
merge_filter1 = []
merge_filter2 = []

merge2 = []
merge_filter2_multi_param = []
set_page = set()
funs_list_sh1 = []  # 记录sh1所有的函数列表.
funs_list_sh2 = []
set_fun_sh1 = set()
set_fun_sh2 = set()
functions_list_sh2_multi_param_merge = []
set_fun_multi_params_sh2 = set()
dict_pages = {}  # general,app,maintance页面对应的接口列表，页面类型为key。！！！
bool_XX4A = False
bool_XX4T = False
m_row_num=0
m_row_num2=0
dict_funsShee2 = {}
dict_table_params = {}
dict_firstTabs = {}
dict_funSh1Index = {}
dict_tab1Index = {} # 需求表sh1第2列
dict_funSh1SingleIndex = {}
dict_funSh1MultiParam = {}
dict_funSh1SingleParam = {}
dict_layouttab = {}
dict_page_fun = {}
list_enumUi = []
funslist = []

#set_enumUi = {} #收集ui接口需要表示的枚举。

def global_varibale(workbook,CCNAME,log,ExcelPath):
    sh1 = workbook.sheet_by_index(1)
    sh2 = workbook.sheet_by_index(2)
    global m_row_num
    global m_row_num2

    rownum1 = sh1.nrows
    colnum1 = sh1.ncols
    rownum2 = sh2.nrows
    colnum2 = sh2.ncols
    for i in range(5,rownum1+1):
        try:
            row_value = sh1.row_values(i,1,colnum1)
            if set(row_value) == {''}:
                m_row_num = i+1
                break
            else:pass
        except IndexError:
            m_row_num = rownum1

    for i in range(3,rownum2+1):
        try:
            row_value = sh2.row_values(i,0, colnum2)#从0开始，防止最后一个接口是无参接口
            if set(row_value) == {''}:
                m_row_num2 = i+1
                break
            else:pass
        except IndexError:
            m_row_num2 = rownum2
    #---------------------------------------------------------------
    for num in range(5, m_row_num):  # 从第3行开始
        if sh1.cell(num, 0).value != "":
            page_list1.append(sh1.cell(num, 0).value)
    set_page = set(page_list1)
    page_list_tuple1 = tuple(page_list1)  # 做字典key


    for num in range(5, m_row_num):# 从第3行开始,获取sheet1页接口列表。
        funs_list_sh1.append(sh1.cell(num, 4).value)
    #print("funs_list_sh1 = ",funs_list_sh1)

    global set_fun_sh1
    global funs_list_sh1_tuple
    set_fun_sh1 = set(funs_list_sh1)  # 为所有sh1接口创建集合。
    funs_list_sh1_tuple = tuple(funs_list_sh1)
    #print("set_fun_sh1 = ", set_fun_sh1)


    for num in range(3, m_row_num2):  # 从第1行开始,获取sheet2页接口列表。
        if sh2.cell(num, 0).value != "":
            funs_list_sh2.append((sh2.cell(num, 0).value).strip())  # 有 \n .
    #print("len = %d,funs_list_sh2 = %s\n"%((len(funs_list_sh2),funs_list_sh2)))
    log.write('len = %d,funs_list_sh2 = %s\n'%((len(funs_list_sh2),funs_list_sh2)))
    global set_fun_sh2
    set_fun_sh2 = set(funs_list_sh2)
#--------------------------------------------------------------------
    # 用于判断头文件包含文件。
    file= open(ExcelPath + "/temp_funsToPage.txt", 'r')
    lines=file.readlines()
    global funslist
    for line in lines:
        key = line[:line.find(':')]
        value = list(line[line.find(':')+1:-2].split(','))
        dict_page_fun[key] = value;
        funslist+=value
    print("dict_page_fun=",dict_page_fun)
    global funsListtuple
    funsListtuple=tuple(funslist)
    for i in range(len(funslist)):
        if CCNAME + "4A" == funslist[i][0:4]:
            global bool_XX4A
            bool_XX4A = True
            continue
        else:
            pass
        if CCNAME + "4T" == funslist[i][0:4]:
            global bool_XX4T
            bool_XX4T = True
            continue
        else:
            pass
    print("bool_XX4A=", bool_XX4A)
    print("bool_XX4T=", bool_XX4T)


#----------------------------------------------------------------

    # general,app,maintance页面对应的接口列表，页面类型为key。
    for (row, row_range, col, col_range) in sh1.merged_cells:
        merge1.append([row, row_range, col, col_range])
    #print("merge1 = ", merge1)
    # print("len merge1 = ", len(merge1)) #11
    merge1.sort()
    # 筛选出含多个接口的page
    for lens in range(len(merge1)):
        if merge1[lens][2] == 0 and merge1[lens][0] > 4:  # 取第0列的下标列表。
            merge_filter1.append([merge1[lens][0], merge1[lens][1], merge1[lens][2], merge1[lens][3]])
        if merge1[lens][2] == 1 and merge1[lens][0] > 4:
            merge_filter2.append([merge1[lens][0], merge1[lens][1], merge1[lens][2], merge1[lens][3]])

    merge_filter1.sort()
    merge_filter2.sort()
#--------------------------------------------------------------------
    for (row, row_range, col, col_range) in sh2.merged_cells:
        merge2.append([row, row_range, col, col_range])
    merge2.sort()
    #print("merge2=", merge2)
    for lens in range(len(merge2)):
        # 筛选出函数参数为多个的函数。
        if (merge2[lens][2] == 0) and merge2[lens][0] > 2:
            merge_filter2_multi_param.append([merge2[lens][0], merge2[lens][1], merge2[lens][2], merge2[lens][3]])
    #print("len =%d,merge_filter2_multi_param =%s\n "%(len(merge_filter2_multi_param),merge_filter2_multi_param))
    log.write("len =%d,merge_filter2_multi_param =%s\n "%(len(merge_filter2_multi_param),merge_filter2_multi_param))
    merge_filter2_multi_param.sort()

    log.write('m_row_num=%d\n m_row_num2=%d\n page_list1=%s\n'%(m_row_num,m_row_num2,page_list1))
    log.write('set_fun_sh1 =%s\n set_fun_sh2=%s\n'%(set_fun_sh1,set_fun_sh2))
#-----------------------------------------------------------------


def read_excel_index1(workbook, CCNAME,log):
    sh1 = workbook.sheet_by_index(1)
    listMerge = [merge_filter1, merge_filter2]
    log.write("listMerge = %s\n"%(listMerge))
    #记录的是page含多个接口
    for colNum in range(0,2):
        sh1_pageMulti = []
        for lens in range(len(listMerge[colNum])):
            if sh1.cell_value(listMerge[colNum][lens][0],listMerge[colNum][lens][2]) == '':
                sh1_pageMulti.append('none')
            else:
                sh1_pageMulti.append(sh1.cell_value(listMerge[colNum][lens][0],listMerge[colNum][lens][2]))
        tupleSh1_pageMulti = tuple(sh1_pageMulti)
        #log.write("界面包含多个接口的导航页名称：\nsh1_pageMulti=\n%s\n"%(sh1_pageMulti))

        if len(sh1_pageMulti) != 0:
            if colNum == 0:
                for j in range(len(sh1_pageMulti)):
                    dict_funSh1Index[tupleSh1_pageMulti[j]]=listMerge[colNum][j]
                setPageMultiParam = set(list(dict_funSh1Index.keys()))

                # 记录page含一个接口时的情况,用集合概念
                setFunSingleSh1 = set_page - setPageMultiParam
                #print('setFunSingleSh1=', setFunSingleSh1)
                for m in range(len(setFunSingleSh1)):
                    for lineIndex in range(3, m_row_num):
                        if list(setFunSingleSh1)[m].lower() in (str(sh1.row_values(lineIndex))).lower():
                            tempLineIndex = lineIndex
                            break
                    dict_funSh1SingleIndex[list(setFunSingleSh1)[m]] = [tempLineIndex, tempLineIndex + 1, 0, 1]


                for index1 in range(len(dict_funSh1Index.keys())):
                    fun_list_temp1 = []  # 每次for 循环都重新分配空间！！！
                    for index in range(list(dict_funSh1Index.values())[index1][0],list((dict_funSh1Index.values()))[index1][1]):
                        fun_list_temp1.append(sh1.cell(index, 4).value)
                    dict_funSh1MultiParam[list(dict_funSh1Index.keys())[index1]]=fun_list_temp1
                #print("dict_funSh1MultiParam=",dict_funSh1MultiParam)
                dict_funSh1Index.update(dict_funSh1SingleIndex)
                #print('重要信息：dict_funSh1Index=', dict_funSh1Index)
                log.write("界面包含多个接口的导航页名称：\ndict_funSh1Index=\n%s\n" %(dict_funSh1Index))
                for i in range(len(setFunSingleSh1)):
                    tempSinglepage = []
                    for lineIndex in range(3, m_row_num):
                        if list(setFunSingleSh1)[i].lower() in (str(sh1.row_values(lineIndex))).lower():
                            print("lineIndex=", lineIndex)
                            tempLineIndex = lineIndex
                            break
                    tempSinglepage.append(sh1.cell_value(tempLineIndex,4))
                    dict_funSh1SingleParam[list(setFunSingleSh1)[i]] = tempSinglepage

                dict_pages.update(dict_funSh1MultiParam)
                dict_pages.update(dict_funSh1SingleParam)
                #print('重要信息：dict_page1=',dict_pages)
                dict_pagesForui = copy.deepcopy(dict_pages)#深拷贝，互不影响

                for pageIndex in range(len(dict_pagesForui.keys())):
                    pagename = list(dict_pagesForui.keys())[pageIndex]
                    for funIndex in range(len(dict_pagesForui[pagename])):
                        for line in range(5,m_row_num):
                            if dict_pagesForui[pagename][funIndex] == sh1.cell_value(line,4):
                                dict_pagesForui[pagename][funIndex] = dict_pagesForui[pagename][funIndex]+'-'+sh1.cell_value(line,3)
                log.write('重要信息：接口对应在界面的标题显示\n %s\n'%(dict_pagesForui))
                #print('重要信息：dict_page1=', dict_pages)
            elif colNum == 1:#记录一级tab列的信息，不能用集合概念，出现none两次的情况
                for j in range(len(sh1_pageMulti)):
                    if sh1_pageMulti[j] != 'none':
                        dict_tab1Index[tupleSh1_pageMulti[j]]=listMerge[colNum][j]
                    else:pass

                #考虑tab页只有一个接口的情况
                for k in range(len(dict_tab1Index.keys())-1):
                    for p in range(list(dict_tab1Index.values())[k][1],list(dict_tab1Index.values())[k+1][0]) :
                        temp_dict = {}
                        strtab1 = sh1.cell_value(list(dict_tab1Index.values())[k][1],1)
                        print('strtab1 = ',strtab1)
                        if strtab1 != '':
                            temp_dict[strtab1] = [list(dict_tab1Index.values())[k][1],list(dict_tab1Index.values())[k][1]+1,1,2]
                            dict_tab1Index.update(temp_dict)

                #当tab页一个接口在需求表格最后几行时。
                for L in range(merge_filter2[-1][1],m_row_num):
                    strtab1 = sh1.cell_value(L, 1)
                    print('strtab1 === ', strtab1)
                    temp_dict[strtab1] = [L,L+1, 1, 2]
                    dict_tab1Index.update(temp_dict)
                log.write('重要信息:界面布局，一个Tab只有一个接口：\n%s\n'%(dict_tab1Index))#包含一个tab一个接口情况


                for i in range(len(dict_funSh1Index.keys())):
                    list_layouttab = []
                    minPageIndex = list(dict_funSh1Index.values())[i][0]
                    maxPageIndex = list(dict_funSh1Index.values())[i][1]
                    for j in range(len(dict_tab1Index.keys())):
                        minTab1Index = list(dict_tab1Index.values())[j][0]
                        maxTab1Index = list(dict_tab1Index.values())[j][1]
                        if minTab1Index >= minPageIndex and maxTab1Index <= maxPageIndex:
                            #由value 得到key
                            element = list(dict_tab1Index.keys())[list(dict_tab1Index.values()).index(list(dict_tab1Index.values())[j])]
                            #print('element=',element)
                            if element !='':
                                list_layouttab.append(element)
                            else:list_layouttab.append('none')
                    dict_layouttab[list(dict_funSh1Index.keys())[i]] =  list_layouttab

                for pageIndex in range(len(dict_layouttab.keys())):
                    if dict_layouttab[list(dict_layouttab.keys())[pageIndex]] ==[]:
                        dict_layouttab[list(dict_layouttab.keys())[pageIndex]]=['none']
                log.write('重要信息：dict_layouttab =%s\n '%(dict_layouttab))

def read_excel_index2(workbook,log):
    #fun_list_sh2 = []  # 所有接口名称集合。
    excelshee2_info = []
    tempLineIndex = 0
    log.write("The Information Of Excel Index2:\n")
    sh2 = workbook.sheet_by_index(2)
    colnum2 = sh2.ncols
    for i in range(3,m_row_num2) :
        temp_excelshee2 = []
        for j in range(1,colnum2):
            if sh2.cell(i,j).value =='':
                temp_excelshee2.append('none')
            else:
                temp_excelshee2.append(str((sh2.cell(i,j).value)).strip(' '))
                if j == 4:
                    if '_ENUM' in sh2.cell(i,4).value:
                        #print('sh2.cell(i,4).value = ',sh2.cell(i,4).value)
                        list_enumUi.append(str((sh2.cell(i,j).value)).strip(' '))

        if len(set(temp_excelshee2)) != 1:
            excelshee2_info.append(temp_excelshee2)
        else :
            if len(set(temp_excelshee2)) == 1 and sh2.cell(i,0).value != '':#接口无参数的情况
                excelshee2_info.append(temp_excelshee2)
            else:break

    #set_enumUi = set(list_enumUi)
    #print('set_enumUi = ',set_enumUi)
    log.write("len excelshee2_info=%d\n"%(len(excelshee2_info)))
    log.write("重要信息:excelshee2_info=%s\n"%(excelshee2_info))
#------------------------------------------------------------------

    #记录函数参数为多个的函数
    for i in range(len(merge_filter2_multi_param)):
        temp_list = []
        for funsIndex in range(merge_filter2_multi_param[i][0], merge_filter2_multi_param[i][1]):
            temp_list.append(sh2.row_values(funsIndex,1,10))  # excelshee2_info[0]=excel第1行开始！！！
        dict_funsShee2[funs_list_sh2[i]] = temp_list
    for i in range(len(merge_filter2_multi_param)):
        functions_list_sh2_multi_param_merge.append\
            (sh2.cell_value(merge_filter2_multi_param[i][0],
                            merge_filter2_multi_param[i][2]).replace('\n', ''))
    fun_list_sh2_multi_param_tuple = tuple(functions_list_sh2_multi_param_merge)  # 取第0列的下标列表。记录函数参数为多个的函数。
    '''
    dict_fun_sh2_multi_param = {}
    for i in range(len(fun_list_sh2_multi_param_tuple)):
        # 此为函数参数为多个的情况。用于后续对各参数添加范围代码
        dict_fun_sh2_multi_param[fun_list_sh2_multi_param_tuple[i]] = merge_filter2_multi_param[i]
    print("dict_fun_sh2_multi_param = ", dict_fun_sh2_multi_param)
    '''

    # 为函数参数为多个的接口创建集合。
    global set_fun_multi_params_sh2
    set_fun_multi_params_sh2 = set(functions_list_sh2_multi_param_merge)
    #print("set_fun_multi_params_sh2 = ", set_fun_multi_params_sh2)

    #此处获取单行接口信息列表
    temp_single_set = funs_single_null_param()
    log.write("temp_single_set=%s\n"%(list(temp_single_set)))
    for i in range(len(temp_single_set)):
        tempSingle = []
        for lineIndex in range(3,m_row_num2):
            if list(temp_single_set)[i].lower() in (str(sh2.row_values(lineIndex))).lower():
                #print("lineIndex=",lineIndex)
                tempLineIndex = lineIndex
                break
        tempSingle.append(sh2.row_values(tempLineIndex,1,10))
        dict_funsShee2[list(temp_single_set)[i]]= tempSingle
    #print("重要信息:dict_funsSheet2=", dict_funsShee2)#包含接口参数为1或多个的信息。

    #获取表格参数信息
    for funIndex in range(len(dict_funsShee2.keys())):
        key = list(dict_funsShee2.keys())[funIndex]
        temp_list1 = []
        for i in range(len(dict_funsShee2[key])):
            temp_list = []
            m = re.search(r'\[.*\]',dict_funsShee2[key][i][0])#?file[128]
            macroStr = dict_funsShee2[key][i][0]
            if m :
                if '->' in macroStr:
                    temp_list.append(str(dict_funsShee2[key][i][0]).replace('->', '.', 5))
                    temp_list.append(dict_funsShee2[key][i][4])
                    temp_list.append(dict_funsShee2[key][i][6])
                else:
                    temp_list.append(dict_funsShee2[key][i][0])
                    temp_list.append(dict_funsShee2[key][i][4])
                    temp_list.append(dict_funsShee2[key][i][6])
                temp_list1.append(temp_list)

        if len(temp_list1) != 0:
            list_macro_cache = []
            for j,mark in enumerate(temp_list1):
                #log.write('统计接口参数含有数组的参数：\ntemp_list1[%d]=%s\n'%(j,temp_list1[j]))
                macro = temp_list1[j][0][temp_list1[j][0].find('[') + 1:temp_list1[j][0].find(']')]
                list_macro_cache.append(macro) #接口不止一个表格
            list_enum = list(enumerate(list_macro_cache,0))
            #print('list_enum = ',list_enum)
            set_macro = set(list_macro_cache)
            if len(set_macro) ==1: #一个宏情况
                if list_macro_cache.count(list(set_macro)[0]) == 1:pass
                else:
                    dict_table_params[key] = temp_list1
            else:
                temp_macro = []
                for num in range(len(set_macro)):
                    if list_macro_cache.count(list(set_macro)[num]) ==1:pass
                    else:
                        for p in range(len(temp_list1)):
                            if list(set_macro)[num] == list_enum[p][1]:
                                temp_macro.append(temp_list1[list_enum[p][0]])
                            else:pass
                dict_table_params[key] = temp_macro
    log.write('重要信息：统计接口参数含有数组的参数\n dict_table_params = \n %s\n'%(dict_table_params))

def funs_single_null_param():
    temp_set = set_fun_sh1 - set_fun_multi_params_sh2
    return temp_set

if __name__ == '__main__':

    CCName = sys.argv[1]
    ExcelPath = sys.argv[2]
    ExcelName = sys.argv[3]


    '''
    CCName = 'EC'
    ExcelPath = "G:/all_exercises/python_prjs/pyvt_auto0604/PYVTUI/VTUI/temp_506VTEC"
    ExcelName = "S314_SW_EDS_VTEC-V4.xls"
    '''

    log = open(ExcelPath + "/check_result2.txt", 'w')

    wb = xlrd.open_workbook(ExcelPath+'/'+ExcelName, formatting_info=True)  # excel 多单元格合并
    global_varibale(wb,CCName,log,ExcelPath)
    read_excel_index1(wb,CCName,log)
    read_excel_index2(wb,log)














