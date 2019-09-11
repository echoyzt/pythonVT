# 此文件用于检查需求表格sheet1 和sheet2 表格的接口名称和个数是否一致。
#import time
# sheet_by_index(1),用于ini文件格式分类 app，general，maintenance...
import re,os,sys,copy,xlrd
from PyQt5.QtWidgets import *
page_list1 = []  # app,maintenance,...
#page_list_tuple1 = ()  # 元祖，不可变，作为key ,取出第5行开始，第0列的索引.
funs_list_sh1_tuple = ()
merge1 = []
mergecol0_filter1 = []
mergecol1_filter1 = []
merge2 = []
merge_filter2_multi_param = []
set_page = set()
funs_list_sh1 = []  # 记录sh1所有的函数列表.
funs_list_sh2 = []
set_fun_sh1 = set()
functions_list_sh2_multi_param_merge = []
set_fun_multi_params_sh2 = set()
dict_pages = {}  # general,app,maintance页面对应的接口列表，页面类型为key。！！！

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


#set_enumUi = {} #收集ui接口需要表示的枚举。

def global_varibale(workbook,log,dict_pageToFuns):
    log.write('================记录的信息是全局变量：==============\n')
    global set_page
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
    set_page = set(page_list1)
    #page_list_tuple1 = tuple(page_list1)  # 做字典key
    #----------------------------------------------------------------

    for num in range(5, m_row_num):# 从第5行开始,获取sheet1页接口列表。
        funs_list_sh1.append(sh1.cell(num, 4).value)
    #print("funs_list_sh1 = ",funs_list_sh1)

    global set_fun_sh1
    global funs_list_sh1_tuple
    set_fun_sh1 = set(funs_list_sh1)  # 为所有sh1接口创建集合。
    funs_list_sh1_tuple = tuple(funs_list_sh1)
    #print("set_fun_sh1 = ", set_fun_sh1)


    for num in range(3, m_row_num2):  # 从第3行开始,获取sheet2页接口列表。
        if sh2.cell(num, 0).value != "":
            funs_list_sh2.append((sh2.cell(num, 0).value).strip())  # 有 \n .
    #print("len = %d,funs_list_sh2 = %s\n"%((len(funs_list_sh2),funs_list_sh2)))
#----------------------------------------------------------------
    # general,app,maintance页面对应的接口列表，页面类型为key。
    for (row, row_range, col, col_range) in sh1.merged_cells:
        merge1.append([row, row_range, col, col_range])

    merge1.sort()
    # 筛选出含多个接口的page
    for lens in range(len(merge1)):
        if merge1[lens][2] == 0 and merge1[lens][0] > 4:  # 取第0列的下标列表。
            mergecol0_filter1.append([merge1[lens][0], merge1[lens][1], merge1[lens][2], merge1[lens][3]])
        if merge1[lens][2] == 1 and merge1[lens][0] > 4:
            mergecol1_filter1.append([merge1[lens][0], merge1[lens][1], merge1[lens][2], merge1[lens][3]])

    mergecol0_filter1.sort()
    mergecol1_filter1.sort()

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
    merge_filter2_multi_param.sort()
    log.write('1.m_row_num=%d\n m_row_num2=%d\n'%(m_row_num,m_row_num2))
    log.write('2.len=%d,funs_list_sh1= %s\n'%(len(funs_list_sh1),funs_list_sh1))
    log.write('3.len=%d,funs_list_sh2 = %s\n' % ((len(funs_list_sh2), funs_list_sh2)))
    log.write('4.page_list1=%s\n'%page_list1)
    log.write('5.set_fun_sh1 =%s\n'%(set_fun_sh1))
    log.write("6.筛选出函数参数为多个的函数在sh2页的位置：\n  len =%d,merge_filter2_multi_param =%s\n"%(len(merge_filter2_multi_param),merge_filter2_multi_param))
    print('mergecol0_filter1=', mergecol0_filter1)
    if len(dict_pageToFuns)==0:
        if 0 !=len(mergecol0_filter1):
            for j in range(len(mergecol0_filter1)):
                listValue=[]
                tkey = sh1.cell_value(mergecol0_filter1[j][0], 0)
                for k in range(mergecol0_filter1[j][0], mergecol0_filter1[j][1]):
                    tvalue = sh1.cell_value(k, 4)
                    listValue.append(tvalue)
                dict_pageToFuns[tkey]=listValue
        else:
            for rowindex in range(5, m_row_num):
                key=sh1.cell_value(rowindex,0)
                dict_pageToFuns[key] = [(sh1.cell(rowindex, 4).value).strip()]
        log.write("7.从Excel获取的信息:dict_pageToFuns= %s\n" % (dict_pageToFuns))

#-----------------------------------------------------------------
def read_excel_index1(workbook,log):
    sh1 = workbook.sheet_by_index(1)
    listMerge = [mergecol0_filter1, mergecol1_filter1]
    #log.write("listMerge = %s\n"%(listMerge))
    #记录的是page含多个接口
    log.write("=================The Information in Excel sheet1:==================\n")
    if 0 != len(mergecol0_filter1): #一定page含多个接口，page可能含一个接口
        sh1_pageMulti = []
        for colNum in range(0,2): #分别对mergecol0_filter1，mergecol1_filter1遍历
            if colNum == 0:
                for lens in range(len(listMerge[colNum])):
                    if sh1.cell_value(listMerge[colNum][lens][0], listMerge[colNum][lens][2]) == '':
                        print("page name is NULL in Excel !")
                        # sh1_pageMulti.append('none')
                        # QMessageBox.warning(self, "check files", "请确认头文件已是最新版本！")
                    else:
                        print('sh1.cell_value(listMerge[colNum][lens][0],listMerge[colNum][lens][2]=',
                              sh1.cell_value(listMerge[colNum][lens][0], listMerge[colNum][lens][2]))
                        sh1_pageMulti.append(sh1.cell_value(listMerge[colNum][lens][0], listMerge[colNum][lens][2]))
                tupleSh1_pageMulti = tuple(sh1_pageMulti)
                # log.write("界面包含多个接口的导航页名称：\nsh1_pageMulti=\n%s\n"%(sh1_pageMulti))

                for j in range(len(sh1_pageMulti)):
                    dict_funSh1Index[tupleSh1_pageMulti[j]] = listMerge[colNum][j]

                # page只有一个接口的集合
                temp_set=set_page - set(dict_funSh1Index.keys())
                #获取接口所在的行号。
                for signalfun in temp_set:
                    for line in range(5, m_row_num):
                        if signalfun==sh1.cell(line,4).value:
                            dict_funSh1SingleIndex[signalfun]=[line,line+1,4,5]
                            break
                        else:pass


                for index1 in range(len(dict_funSh1Index.keys())):
                    fun_list_temp1 = []  # 每次for 循环都重新分配空间！！！
                    funIndexStart=list(dict_funSh1Index.values())[index1][0]
                    funIndexEnd=list(dict_funSh1Index.values())[index1][1]
                    for index in range(funIndexStart,funIndexEnd):
                        fun_list_temp1.append(sh1.cell(index, 4).value)
                    dict_funSh1MultiParam[list(dict_funSh1Index.keys())[index1]] = fun_list_temp1
                # print("dict_funSh1MultiParam=",dict_funSh1MultiParam)
                dict_funSh1Index.update(dict_funSh1SingleIndex)
                # print('重要信息：dict_funSh1Index=', dict_funSh1Index)
                log.write("界面包含多个接口的导航页名称：\ndict_funSh1Index=%s\n" % (dict_funSh1Index))

                dict_pages.update(dict_funSh1MultiParam)
                dict_pages.update(dict_funSh1SingleParam)
                # print('重要信息：dict_page1=',dict_pages)
                dict_pagesForui = copy.deepcopy(dict_pages)  # 深拷贝，互不影响

                for pageIndex in range(len(dict_pagesForui.keys())):
                    pagename = list(dict_pagesForui.keys())[pageIndex]
                    for funIndex in range(len(dict_pagesForui[pagename])):
                        for line in range(5, m_row_num):
                            if dict_pagesForui[pagename][funIndex] == sh1.cell_value(line, 4):
                                dict_pagesForui[pagename][funIndex] = dict_pagesForui[pagename][funIndex] + '-' + sh1.cell_value(line, 3)
                log.write('重要信息：接口在ui界面的groupName:\n dict_pagesForui=%s\n' % (dict_pagesForui))
                # print('重要信息：dict_page1=', dict_pages)



            elif colNum == 1:  # 记录一级tab列的信息，不能用集合概念，可能出现none两次的情况
                '''
                print('sh1_pageMulti=',sh1_pageMulti)
                for j in range(len(sh1_pageMulti)):
                    if sh1_pageMulti[j] != 'none':
                        dict_tab1Index[tupleSh1_pageMulti[j]] = listMerge[colNum][j]
                    else:pass
                '''
                if (0 == len(listMerge[colNum])):#说明tab1没有合并的接口。
                    dict_tab1Index
                else:

                    # 考虑tab页只有一个接口的情况
                    print('dict_tab1Index=',dict_tab1Index)
                    for k in range(len(dict_tab1Index.keys()) - 1):
                        for p in range(list(dict_tab1Index.values())[k][1], list(dict_tab1Index.values())[k + 1][0]):
                            temp_dict = {}
                            strtab1 = sh1.cell_value(list(dict_tab1Index.values())[k][1], 1)
                            print('strtab1 = ', strtab1)
                            if strtab1 != '':
                                temp_dict[strtab1] = [list(dict_tab1Index.values())[k][1],list(dict_tab1Index.values())[k][1] + 1, 1, 2]
                                dict_tab1Index.update(temp_dict)
                    '''
                # 当tab页一个接口在需求表格最后几行时。
                for L in range(mergecol1_filter1[-1][1], m_row_num):
                    strtab1 = sh1.cell_value(L, 1)
                    print('strtab1 === ', strtab1)
                    if strtab1:
                        temp_dict[strtab1] = [L, L + 1, 1, 2]
                        dict_tab1Index.update(temp_dict)
                log.write('重要信息:界面布局，一个Tab只有一个接口：\n%s\n' % (dict_tab1Index))  # 包含一个tab一个接口情况
                '''
                for i in range(len(dict_funSh1Index.keys())):
                    list_layouttab = []
                    minPageIndex = list(dict_funSh1Index.values())[i][0]
                    maxPageIndex = list(dict_funSh1Index.values())[i][1]

                    for j in range(len(dict_tab1Index.keys())):
                        minTab1Index = list(dict_tab1Index.values())[j][0]
                        maxTab1Index = list(dict_tab1Index.values())[j][1]
                        if minTab1Index >= minPageIndex and maxTab1Index <= maxPageIndex:
                            # 由value 得到key
                            temp=list(dict_tab1Index.values())[j]
                            print('temp=',temp)
                            element = list(dict_tab1Index.keys())[list(dict_tab1Index.values()).index(temp)]
                            # print('element=',element)
                            if element != '':
                                list_layouttab.append(element)
                            else:
                                list_layouttab.append('none')
                    dict_layouttab[list(dict_funSh1Index.keys())[i]] = list_layouttab
                log.write('重要信息：dict_layouttab =%s\n ' % (dict_layouttab))

    else:
        # 记录需求表格里 page都只含一个接口时的情况,用集合概念
        for rowindex in range(5, m_row_num):
            key = (sh1.cell(rowindex, 0).value).strip()
            dict_funSh1Index[key] = [rowindex, rowindex + 1, 0, 1]
            if ''==(sh1.cell(rowindex,1).value).strip():
                dict_layouttab[key] =['none']
            else:dict_layouttab[key]=(sh1.cell(rowindex,1).value).strip()
            dict_pages[key]=[(sh1.cell(rowindex,4).value).strip()]
        log.write("界面是单个接口的导航页名称：\ndict_funSh1Index=%s\n" % (dict_funSh1Index))
        log.write('重要信息：dict_layouttab =%s\n ' % (dict_layouttab))
    log.write('重要信息：dict_pages=%s\n' % (dict_pages))


def read_excel_index2(workbook,log):
    #fun_list_sh2 = []  # 所有接口名称集合。
    excelshee2_info = []
    tempLineIndex = 0
    log.write("====================The Information in Excel sheet2:==================\n")
    sh2 = workbook.sheet_by_index(2)
    colnum2 = sh2.ncols
    for i in range(3,m_row_num2):
        for j in range(1,colnum2):
            if j == 4:
                if '_ENUM' in sh2.cell(i, 4).value:
                    list_enumUi.append(str((sh2.cell(i, j).value)).strip(' '))
    print("list_enumUi=",list_enumUi)


#------------------------------------------------------------------
    # 记录函数参数为多个的函数
    for i in range(len(merge_filter2_multi_param)):
        temp_list = []
        funsNameMultiParams=sh2.cell_value(merge_filter2_multi_param[i][0], merge_filter2_multi_param[i][2]).replace('\n', '')
        for funsIndex in range(merge_filter2_multi_param[i][0], merge_filter2_multi_param[i][1]):
            temp_list.append(sh2.row_values(funsIndex, 1, 10))  # 读整行的内容。excelshee2_info[0]=excel第4行开始！！！
        dict_funsShee2[funsNameMultiParams] = temp_list
        functions_list_sh2_multi_param_merge.append(sh2.cell_value(merge_filter2_multi_param[i][0], merge_filter2_multi_param[i][2]).replace('\n', ''))
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
    # print("set_fun_multi_params_sh2 = ", set_fun_multi_params_sh2)








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
    log.write("重要信息(包含接口参数为1或多个的信息):\n dict_funsShee2=%s\n"%(dict_funsShee2))#包含接口参数为1或多个的信息。

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
    log = open(ExcelPath + "/2excelInfos.txt", 'w')
    wb = xlrd.open_workbook(ExcelPath+'/'+ExcelName, formatting_info=True)  # excel 多单元格合并
    global_varibale(wb,CCName,log,ExcelPath)
    read_excel_index1(wb,CCName,log)
    read_excel_index2(wb,log)














