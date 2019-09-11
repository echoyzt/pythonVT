import os,sys,re,xlrd,time
from xlutils.copy import copy
import collectExcelInfo
import PyQt5
#============================================================
dict_base_struct = {'xy_vect':[['SMEE_DOUBLE', 'x'], ['SMEE_DOUBLE', 'y']],
                    'xz_vect':[['SMEE_DOUBLE', 'x'], ['SMEE_DOUBLE','z']],
                    'yz_vect':[['SMEE_DOUBLE','y'], ['SMEE_DOUBLE','z']],
                    'xyz_vect':[['SMEE DOUBLE','x'], ['SMEE_DOUBLE','y'], ['SMEE_DOUBLE','z']],
                    'zrxry_vect':[['SMEE_DOUBLE','z'], ['SMEE_DOUBLE','rx'], ['SMEE_DOUBLE','ry']],
                    'rxry_vect':[['SMEE_DOUBLE','rx'], ['SMEE_DOUBLE','ry']],
                    'xyrz_vect':[['SMEE_DOUBLE','x'],['SMEE_DOUBLE','y'], ['SMEE_DOUBLE','rz']],
                    'xyrzzrxry_vect':[['SMEE_DOUBLE','x'], ['SMEE_DOUBLE','y'], ['SMEE_DOUBLE','rz'], ['SMEE_DOUBLE','z'], ['SMEE_DOUBLE','rx'], ['SMEE_DOUBLE','ry']],
                    'ADAE_TIME_VALUE':[['ADAE_LONG','tm_sec'], ['ADAE_LONG','tm_usec']]}
#===================================================================

headfile_list = []  # 记录本次所需的所有头文件。
dict_funs = {}  # 接口和接口的参数。
dict_struct = {}
dict_enum = {}
dict_macro = {}
dict_universal_struct = {}
temp_list_enum_struct = []
temp_list = []
m_recursion = []
dict_enumForUi = {}

re_comment="^(#\s*include)|^(\/\*)|^(\/)|^(\\n|\*)"
pattern1=re.compile(re_comment)

re_comment2="((\/\*|\/\/).*)"
pattern2=re.compile(re_comment2)

re_del="^(#ifndef|#define)\s*([A-Z]{2}4[A|T]_TC_H)"
pattern3=re.compile(re_del)

re_dot="[,|;]"
pattern4=re.compile(re_dot)

re_nullString="\S" #非空字符
patNullString=re.compile(re_nullString)

re_endEnum="^}.*_ENUM$"
patEndEnum=re.compile(re_endEnum)

re_endStruct="^}.*_STRUCT$"
patEndStruct=re.compile(re_endStruct)



# pre4A_if.h,pre4T_if.h
def preprocess_header_files(CCNAME,filepath,existXX4A,existXX4T):
    filePreHeader = open((os.sep).join([filepath, "3temp_preProcess"]), 'w')
    print("mainwindow.existXX4A=", existXX4A)
    print("mainwindow.existXX4T=", existXX4T)
    list4a4t=[]
    if existXX4A == True:
        list4a4t.append((os.sep).join([filepath+'\\'+'temp_HeaderFiles', CCNAME + "4A_if.h"]))
    if existXX4T==True:
        list4a4t.append((os.sep).join([filepath+'\\'+'temp_HeaderFiles', CCNAME + "4T_if.h"]))
    #print('list4a4t=',list4a4t)

    if len(list4a4t)>0:
        for headfilePath in list4a4t:
            file1 = open(headfilePath, 'r')
            file1_line_infos = file1.readlines()
            for line in file1_line_infos:
                if line != '\n':
                    if 'SMEE_EXPORT SMEE_INT32' in line:
                        line1=re.sub(' +',' ',line)
                        filePreHeader.write(line1)
                    else:filePreHeader.write(line)
            file1.close()
    filePreHeader.close()

# 以temp_prexx4A_if.h,temp_prexx4T_if.h为输入，
# 用于保存需要刷代码的接口,并放在4temp_interfaces.txt 。
# dict_funs，保存从界面而来的接口和参数信息。
def generate_requirefuns_tempfile( filepath,dict_pageToFuns,log):
    file = open((os.sep).join([filepath, "3temp_preProcess"]), 'r')
    funslist = []
    for index in range(len(dict_pageToFuns.values())):
        for funs in range(len(list(dict_pageToFuns.values())[index])):
            funslist.append(list(dict_pageToFuns.values())[index][funs])
    print("funlist=",funslist)
    for funname in funslist:
        temp_parameter_list = []
        ExcelFunInFile(file,funname,temp_parameter_list,log)
    log.write("\n界面所得接口信息字典：\n dict_funs =%s\n " % (dict_funs))  # 接口和接口参数字典。
    file.close()

def dict_pageToFuns_fromExcel(funslist,filepath,log ):
    file = open((os.sep).join([filepath, "3temp_preProcess"]), 'r')
    for funname in funslist:
        temp_parameter_list = []
        ExcelFunInFile(file, funname, temp_parameter_list, log)
    log.write("\n界面所得接口信息字典：\n dict_funs =%s\n " % (dict_funs))  # 接口和接口参数字典。
    file.close()

def ExcelFunInFile(file,funname,temp_parameter_list,log):
    file.seek(0)
    line_info = file.readline()
    while True:
        if not line_info: break
        line_info1 = line_info.lstrip()  # 去掉左边空格。
        if line_info1.startswith('SMEE_EXPORT'):  # 找到以SMEE_EXPORT 开头。
            start_smee_export_line = line_info  # 用于保存SMEE_EXPORT 同一行参数。
            #m = re.search(r'^SMEE_EXPORT SMEE_INT32.*\($', line_info1)
            m = re.search(r'^SMEE_EXPORT', line_info1)
            if m:
                tline2 = (line_info1[line_info1.find('SMEE_EXPORT') + 11:line_info1.rfind('(')]).strip()
                tline3=(tline2[tline2.find('SMEE_INT32')+10:]).strip()

            if funname==tline3:
                print("funname=%s,tline3=%s\n" % (funname, tline3))
                log.write(line_info)  # 只将需要刷代码的接口写到文件中。
                #print("4a start SMEE_EXPORT = ",line_info)
                line_info = file.readline()
                if '(IN ' in start_smee_export_line or '(OUT ' in start_smee_export_line or '(INOUT ' in start_smee_export_line:
                    sub_smee_export_line = start_smee_export_line[start_smee_export_line.find('(') + 1:-2]
                    temp_sub = sub_smee_export_line.replace(' *', ' ')
                    list_funsValue = temp_sub.split(' ')
                    temp_parameter_list.append(list_funsValue)

                while "IN " in line_info or "OUT " in line_info or "INOUT " in line_info:
                    line_info_strip = line_info.strip()  # 去掉两边空格。
                    temp_sub = line_info_strip.replace(' *', ' ')
                    sub_line_info_lstrip = temp_sub[:-1]  # 去掉 ；\n
                    list_sub_line_info_lstrip = sub_line_info_lstrip.split(' ')
                    temp_parameter_list.append(list_sub_line_info_lstrip)
                    log.write(line_info)
                    line_info = file.readline()
                    if not (line_info): break
                dict_funs[funname] = temp_parameter_list  # 键值对
                file.seek(0)
                break

            else:  # 找到下一个 SMEE_EXPORT开头
                line_info = file.readline()
                line_info2 = line_info.lstrip()  # 去掉左边空格。
                while not (line_info2.startswith("SMEE_EXPORT")):  # 一直读到 SMEE_EXPORT 为止。
                    line_info = file.readline()
                    line_info2 = line_info.lstrip()  # 去掉左边空格。
                    if not (line_info): break

        else:  # 找到下一个 SMEE_EXPORT开头
            line_info = file.readline()
            line_info2 = line_info.lstrip()  # 去掉左边空格。
            while not (line_info2.startswith("SMEE_EXPORT")):  # 一直读到 SMEE_EXPORT 为止。
                line_info = file.readline()
                line_info2 = line_info.lstrip()  # 去掉左边空格。
                if not (line_info): break
    print("dict_funs = ", dict_funs) #???



# 分别新建三个字典 dict_struct,dict_enum，dict_macro。
# 生成temp_record_struct_enum_macro.txt
def collect_struct_enum(filepath, headfile_list,ExcelPath):
    file1 = open(ExcelPath+"\\5temp_StructEnumMacro.txt", 'w')
    #headfilepath = os.path.join(filepath, 'temp_HeaderFiles')
    sublines = []
    dict_macro = []
    for files in headfile_list:
        m = re.search(r'_if.h$', files)
        if m:continue  # if头文件跳过
        else:  # (解析tc头文件)
            if "smee_type.h" == files:continue
            file = open((os.sep).join([filepath, files]), 'r')
            file1.write('头文件名称为：' + files + '\n')
            lines = file.readlines()
            for line in lines:
                subline = line.strip()
                if pattern1.match(subline):pass
                elif pattern3.match(subline):pass
                else:
                    if pattern2.search(subline):
                        subline2 = subline[:subline.index(pattern2.search(subline).group())]
                        if pattern4.search(subline2):
                            subline3=subline2[:subline2.index(pattern4.search(subline2).group())]
                            file1.write(subline3+'\n')
                        else:file1.write(subline2+'\n')
                    else:
                        if not patNullString.findall(subline):pass
                        else:
                            if pattern4.search(subline):
                                subline3 = subline[:subline.index(pattern4.search(subline).group())]
                                file1.write(subline3 + '\n')
                            else:
                                file1.write(subline+'\n')
    parse_temp_record_struct_enum(file1,ExcelPath)
#5temp_StructEnumMacro.txt为输入，
#生成6temp_record_macro.txt，7temp_dict_enum_struct.txt
def parse_temp_record_struct_enum(file1,ExcelPath):
    file1.close()#之前是写模式
    file1 = open(ExcelPath+"\\5temp_StructEnumMacro.txt", 'r')
    file2 = open(ExcelPath+"\\6temp_record_macro.txt", 'w')
    file3 = open(ExcelPath+"\\7temp_dict_enum_struct.txt", 'w')
    file1.seek(0)
    for i in file1.readlines():
        temp = i.rstrip('\n')
        temp_list_enum_struct.append(temp)
    #print('temp_list_enum_struct = ',temp_list_enum_struct)
    file1.close()

    num_of_typedef_enum = temp_list_enum_struct.count('typedef enum')
    print("num_of_typedef_enum=", num_of_typedef_enum)
    # 取得枚举结构体的成员字典
    while temp_list_enum_struct.count('typedef enum') != 0:
        temp_list_enum = []
        index_typedef_enum = temp_list_enum_struct.index('typedef enum')
        #enum_MIN = temp_list_enum_struct[index_typedef_enum + 2]
        indexMin=index_typedef_enum + 2
        for index in range(indexMin,len(temp_list_enum_struct)):
            if patEndEnum.search(temp_list_enum_struct[index]):
                indexMax=index-1
                break
        for i in range(indexMin, indexMax + 1):
            temp_list_enum.append(temp_list_enum_struct[i])
        subenum_start = temp_list_enum_struct[indexMax + 1].find('}')
        subenum = temp_list_enum_struct[indexMax + 1][subenum_start + 1:]
        subenum2 = subenum.strip()
        dict_enum[subenum2] = temp_list_enum
        #print("dict_enum[%s] = %s" % (subenum2, dict_enum[subenum2]))  # 必須在此处打印
        file3.write("dict_enum[%s] = %s" % (subenum2, dict_enum[subenum2]) + '\n')
        del temp_list_enum_struct[index_typedef_enum:indexMax + 2]
    # print("dict_enum = ",dict_enum)
    # 取得 struct结构体的成员字典
    while temp_list_enum_struct.count('typedef struct') != 0:
        index_struct_end=0
        temp_list_struct = []
        #for struct_member in temp_list_enum_struct:
        index_typedef_struct = temp_list_enum_struct.index('typedef struct')
        indexStructFirst = index_typedef_struct + 2
        for inode in range(indexStructFirst, len(temp_list_enum_struct)):
            if patEndStruct.search(temp_list_enum_struct[inode]):
                index_struct_end = inode - 1
                break
        #print("indexStructFirst=%s, index_struct_end=%s"%(indexStructFirst, index_struct_end))
        for index in range(indexStructFirst, index_struct_end + 1):
            temp_list_struct.append(temp_list_enum_struct[index].split())

        substruct_start = temp_list_enum_struct[index_struct_end + 1].find('}')
        substruct = temp_list_enum_struct[index_struct_end + 1][substruct_start + 1:]
        substruct2 = substruct.strip()
        dict_struct[substruct2] = temp_list_struct
        file3.write(("dict_struct[%s] = %s" % (substruct2, dict_struct[substruct2]) + '\n'))
        #print("dict_struct[%s] = %s" % (substruct2, dict_struct[substruct2]))  # 必須在此处打印

        del temp_list_enum_struct[index_typedef_struct:index_struct_end+2 ]
    for basekey in dict_base_struct.keys():
        dict_struct[basekey]=dict_base_struct[basekey]
        file3.write(("dict_struct[%s] = %s" % (basekey, dict_base_struct[basekey]) + '\n'))
    #print("temp_list_enum_struct = ", temp_list_enum_struct)
    #枚举和结构体之后的即宏
    for i in temp_list_enum_struct:
        file2.write(i + '\n')
    file2.close()
    file3.close()


def enumWriteToExcel(worksheet,dict_enum,set_enumUi):
    #写入cell值ws.cell(row=4, column=2).value = 'test'
    list_enumUi = list(set_enumUi)
    list_enumUi.sort()
    count = 0
    for index in range(len(list_enumUi)):
        if list_enumUi[index] in list(dict_enum.keys()):
            worksheet.write(count, 0,list_enumUi[index])
            #print('(%d, 0)=%s'%(count,list_enumUi[index]))
            count = count + 1
            for index1,enumMember in enumerate(dict_enum[list_enumUi[index]]):
                worksheet.write(count, 1,dict_enum[list_enumUi[index]][index1])
                count = count + 1


def enumForUi(workbook,log):
    worksheet3 = workbook.sheet_by_index(3)
    rownum3 = worksheet3.nrows
    colnum3 = worksheet3.ncols
    #print('colnum3 = ',colnum3)#2
    if colnum3 > 2:
        for index in range (rownum3):
            if worksheet3.cell(index,2).value =="":pass

            else:
                dict_enumForUi[worksheet3.cell(index,1).value] = worksheet3.cell(index,2).value
    else:
        sys.exit(1)
        log.write('错误! 需求表格enum页为空！！！\n')
    log.write('\n枚举在界面的显示字符串：\n%s\n'%(dict_enumForUi))
    print('dict_enumForUi=',dict_enumForUi)






if __name__ == '__main__':
    '''
    CCName = sys.argv[1]
    ExcelPath = sys.argv[2]
    ExcelName = sys.argv[3]
    '''


    CCName = 'EC'
    ExcelPath = "G:\all_exercises\python_prjs\pyvt_auto0604\PYVTUI\VTUI\temp_506VTEC"
    ExcelName = "S314_SW_EDS_VTEC-V4.xls"

    #listheadfiles=[]
    log = open(ExcelPath + "/check_result.txt", 'a+')
    oldwb = xlrd.open_workbook(ExcelPath+'/'+ExcelName, formatting_info=True)  # excel 多单元格合并
    newwb = copy(oldwb)
    newws = newwb.get_sheet('enum')
    '''
    if os.path.exists(ExcelPath + "/temp_HeaderFiles"):
        print('collectExcelInfo.bool_XX4T=',collectExcelInfo.bool_XX4T)
        if collectExcelInfo.bool_XX4T:
            listheadfiles = check_headfile_all(ExcelPath + "/temp_HeaderFiles", CCName + '4T_if.h')

        if collectExcelInfo.bool_XX4A:
            listheadfiles = check_headfile_all(ExcelPath + "/temp_HeaderFiles", CCName + '4A_if.h')

        log.write('重要信息:完成此次刷代码需要的头文件：%s\n' % (set(listheadfiles) ))
    '''
    file = open(ExcelPath + "/temp_headfilelist.txt", 'w')
    #print("os.listdir= ",os.listdir(ExcelPath + "/temp_HeaderFiles"))
    for headfile in os.listdir(ExcelPath + "/temp_HeaderFiles"):
        if os.path.isfile(ExcelPath + "/temp_HeaderFiles/"+headfile):
            headfile_list.append(headfile)
            file.write(headfile+'\n')
    file.close()


    preprocess_header_files(CCName, ExcelPath + "/temp_HeaderFiles")
    generate_requirefuns_tempfile(CCName, ExcelPath, log)
    collect_struct_enum(ExcelPath + "/temp_HeaderFiles", headfile_list)
    log.write('step.将VT 界面接口需要的枚举提前写到excel 中。')

    set_enumUi = set(collectExcelInfo.list_enumUi)
    enumWriteToExcel(newws, dict_enum, set_enumUi)
    os.remove(ExcelPath+'/'+ExcelName)
    newwb.save(ExcelPath+'/'+ExcelName)