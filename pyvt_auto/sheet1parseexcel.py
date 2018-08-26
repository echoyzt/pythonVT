import xlrd

if __name__ == '__main__':
    page_list1 = []
    merge1 = []
    merge_filter1 = []
    merge_filter2 = []
    merge_filter3 = []
    funs_sh1_multi_param = []
    dict_pages = {}
    dict_funSh1Index = {}
    dict_tab1Index = {}
    dict_tab2Index = {}
    dict_funSh1MultiParam = {}
    dict_funSh1SingleIndex = {}
    workbook = xlrd.open_workbook('../S314_SW_EDS_VTCE.xls', formatting_info=True)  # excel 多单元格合并
    sh1 = workbook.sheet_by_index(1)
    sh2 = workbook.sheet_by_index(2)
    rownum1 = sh1.nrows
    rownum2 = sh2.nrows
    allnows = 0
    for lineIndex in range(5, rownum1):
        if sh1.cell(lineIndex,4).value == '':
            allnows = lineIndex
            break
    print("allnows = ", allnows)# 有的时候行数不准
    print("rownum1 = ", rownum1)  # 8
    print("rownum2 = ", rownum2)
    for num in range(5, rownum1):  # 从第5行开始
        if sh1.cell(num, 0).value != "":
            page_list1.append(sh1.cell(num, 0).value)
    set_page = set(page_list1)
    for (row, row_range, col, col_range) in sh1.merged_cells:
        merge1.append([row, row_range, col, col_range])
    merge1.sort()
    #筛选出含多个接口的page
    for lens in range(len(merge1)):
        if merge1[lens][2] == 0 and merge1[lens][0] > 4:  # 取第0列的下标列表。
            merge_filter1.append([merge1[lens][0], merge1[lens][1], merge1[lens][2], merge1[lens][3]])
        if  merge1[lens][2] == 1 and merge1[lens][0] > 4:
            merge_filter2.append([merge1[lens][0], merge1[lens][1], merge1[lens][2], merge1[lens][3]])
        if  merge1[lens][2] == 2 and merge1[lens][0] > 4:
            merge_filter3.append([merge1[lens][0], merge1[lens][1], merge1[lens][2], merge1[lens][3]])
    merge_filter1.sort()
    merge_filter2.sort()
    merge_filter3.sort()
    print("merge_filter1 = ", merge_filter1)  #!!!对于单一的单元格，此列表不显示
    print("merge_filter2 = ", merge_filter2)
    print("merge_filter3 = ", merge_filter3)
    listMerge = [merge_filter1,merge_filter2,merge_filter3]
    print("listMerge = ", listMerge)

    #记录第1~3列含多个接口
    for i in range(0,3):
        sh1_multi = []
        for lens in range(len(listMerge[i])):
            if sh1.cell_value(listMerge[i][lens][0],listMerge[i][lens][2]) == '':
                sh1_multi.append('none')
            else:
                sh1_multi.append(sh1.cell_value(listMerge[i][lens][0],listMerge[i][lens][2]))
        tuplesh1_multi = tuple(sh1_multi)
        print("sh1_multi=", sh1_multi)
        if i == 0:
            for j in range(len(sh1_multi)):
                dict_funSh1Index[tuplesh1_multi[j]]=listMerge[i][j]
            setMultiParam = set(list(dict_funSh1Index.keys()))
            #记录page页面含一个接口的情况,用集合概念
            setFunSingleSh1 = set_page - setMultiParam
            # print('setFunSingleSh1=', setFunSingleSh1)
            for m in range(len(setFunSingleSh1)):
                for lineIndex in range(5, rownum1):
                    if list(setFunSingleSh1)[m].lower() in (str(sh1.row_values(lineIndex))).lower():
                        tempLineIndex = lineIndex
                        break
                dict_funSh1SingleIndex[list(setFunSingleSh1)[m]] = [tempLineIndex, tempLineIndex + 1, 0, 1]
            dict_funSh1Index.update(dict_funSh1SingleIndex)
            print('重要信息1：dict_funSh1Index=', dict_funSh1Index)
        elif i == 1:#记录标签列的信息，不能用集合概念，出现none两次的情况
            for j in range(len(sh1_multi)):
                if tuplesh1_multi[j] != 'none':
                    dict_tab1Index[tuplesh1_multi[j]]=listMerge[i][j]
                else:pass

            for k in range(len(dict_tab1Index.keys())-1):
                for p in range(list(dict_tab1Index.values())[k][1],list(dict_tab1Index.values())[k+1][0]) :
                    temp_dict = {}
                    str = sh1.cell_value(list(dict_tab1Index.values())[k][1],1)
                    print('str = ',str)
                    if str != '':
                        temp_dict[str] = [list(dict_tab1Index.values())[k][1],list(dict_tab1Index.values())[k][1]+1,1,2]
                        dict_tab1Index.update(temp_dict)

            for L in range(merge_filter2[-1][1],allnows):
                str = sh1.cell_value(L, 1)
                print('str === ', str)
                temp_dict[str] = [L,L+1, 1, 2]
                dict_tab1Index.update(temp_dict)
            print('重要信息2：dict_tab1Index=', dict_tab1Index)

            dict_layouttab = {}
            for i in range(len(dict_funSh1Index.keys())):
                list_layouttab = []
                minPageIndex = list(dict_funSh1Index.values())[i][0]
                maxPageIndex = list(dict_funSh1Index.values())[i][1]
                for j in range(len(dict_tab1Index.keys())):
                    minTab1Index = list(dict_tab1Index.values())[j][0]
                    maxTab1Index = list(dict_tab1Index.values())[j][1]
                    if minTab1Index >= minPageIndex and maxTab1Index <= maxPageIndex:
                        #有value 得到key
                        element = list(dict_tab1Index.keys())[list(dict_tab1Index.values()).index(list(dict_tab1Index.values())[j])]
                        list_layouttab.append(element)
                dict_layouttab[list(dict_funSh1Index.keys())[i]] =  list_layouttab
            print('重要信息3：dict_layouttab = ',dict_layouttab)
        elif i == 2:pass
        '''
            for j in range(len(sh1_multi)):
                if tuplesh1_multi[j] != 'none':
                    dict_tab2Index[tuplesh1_multi[j]]=listMerge[i][j]
                else:pass
            print('dict_tab2Index=', dict_tab2Index)

        '''





