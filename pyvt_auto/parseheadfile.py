import os
import sys
import re
import checkExcel

from xml.dom.minidom import Document  # ?
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
# pre4A_if.h,pre4T_if.h
def preprocess_header_files(CCNAME,filepath):
    if checkExcel.bool_XX4A == True:
        file1 = open((os.sep).join([filepath, "headFiles", CCNAME + "4A_if.h"]), 'r')
        os.chdir(r'XXVT')
        #print('os.chdir=',os.chdir)
        filePreHeader_4A = open((os.sep).join([filepath, "XXVT", "pre" + CCNAME + "4A_if.h"]), 'w')
        file1_line_infos = file1.readlines()
        #print('file1_line_infos=====',file1_line_infos)
        for line in file1_line_infos:
            if line != '\n':
                if 'SMEE_EXPORT SMEE_INT32' in line:
                    filePreHeader_4A.write(line.replace('(', ' ('))  # 为后面排除req，wait接口
                else:filePreHeader_4A.write(line)
            else:pass
        file1.close()
        filePreHeader_4A.close()

    if checkExcel.bool_XX4T == True:
        file2 = open((os.sep).join([filepath, "headFiles", CCNAME + "4T_if.h"]), 'r')

        filePreHeader_4T = open((os.sep).join([filepath, "XXVT","pre" + CCNAME + "4T_if.h"]), 'w')
        file2_line_info = file2.readlines()
        for line in file2_line_info:
            if line != '\n':
                filePreHeader_4T.write(line)
            else:pass
        file2.close()
        filePreHeader_4T.close()

# 以prexx4A_if.h,prexx4T_if.h为输入，
# 用于保存需要刷代码的接口,并放在temp_interfaces.txt 。
# dict_funs，保存接口和参数信息。
def generate_requirefuns_tempfile(CCNAME, filepath,log):
    file3 = open((os.sep).join([filepath,"XXVT", "temp_interfaces.txt"]), 'w')
    for i in range(len(checkExcel.funs_list_sh1)):
        temp_parameter_list = []
        if CCNAME + '4A' == checkExcel.funs_list_sh1[i][0:4]:  # CC4A接口
            file1 = open((os.sep).join([filepath,"XXVT", "pre" + CCNAME + "4A_if.h"]), 'r')
            file1.seek(0)
            line_info = file1.readline()
            # print("4a line_info = ",line_info)
            while True:
                if not line_info: break
                line_info1 = line_info.lstrip()  # 去掉左边空格。
                if line_info1.startswith('SMEE_EXPORT'):  # 找到以SMEE_EXPORT 开头。
                    start_smee_export_line = line_info  # 用于保存SMEE_EXPORT 同一行参数。

                    line_info_list = line_info1.split(' ')  # 防止有req，wait 接口干扰。
                    #print("4a line_info_list = ",line_info_list)
                    if checkExcel.funs_list_sh1_tuple[i] in line_info_list:
                        file3.write(line_info)  # 只将需要刷代码的接口写到文件中。
                        #print("4a start SMEE_EXPORT = ",line_info)
                        line_info = file1.readline()
                        if '(IN ' in start_smee_export_line or '(OUT ' in start_smee_export_line or '(INOUT ' in start_smee_export_line:
                            sub_start_smee_export_line = start_smee_export_line[start_smee_export_line.find('(') + 1:-2]
                            temp_sub = sub_start_smee_export_line.replace(' *', ' ')
                            list_funsValue = temp_sub.split(' ')
                            temp_parameter_list.append(list_funsValue)

                        while "IN " in line_info or "OUT " in line_info or "INOUT " in line_info:
                            line_info_strip = line_info.strip()  # 去掉两边空格。
                            temp_sub = line_info_strip.replace(' *', ' ')
                            sub_line_info_lstrip = temp_sub[:-1]  # 去掉 ；\n
                            list_sub_line_info_lstrip = sub_line_info_lstrip.split(' ')
                            # print("4a IN,OUT,INOUT line_info = ",line_info)
                            temp_parameter_list.append(list_sub_line_info_lstrip)
                            file3.write(line_info)
                            line_info = file1.readline()
                            if not (line_info): break
                        dict_funs[checkExcel.funs_list_sh1_tuple[i]] = temp_parameter_list  # 键值对
                        # print("4a dict_funs = ",dict_funs)
                        file1.seek(0)
                        break
                    else:  # 找到下一个 SMEE_EXPORT开头
                        line_info = file1.readline()
                        line_info2 = line_info.lstrip()  # 去掉左边空格。
                        while not (line_info2.startswith("SMEE_EXPORT")):  # 一直读到 SMEE_EXPORT 为止。
                            line_info = file1.readline()
                            line_info2 = line_info.lstrip()  # 去掉左边空格。
                            # print("line 218,line_info = ",line_info)
                            if not (line_info): break

                else:  # 找到下一个 SMEE_EXPORT开头
                    line_info = file1.readline()
                    line_info2 = line_info.lstrip()  # 去掉左边空格。
                    while not (line_info2.startswith("SMEE_EXPORT")):  # 一直读到 SMEE_EXPORT 为止。
                        line_info = file1.readline()
                        line_info2 = line_info.lstrip()  # 去掉左边空格。
                        # print("line 218,line_info = ",line_info)
                        if not (line_info): break
        elif CCNAME + '4T' == checkExcel.funs_list_sh1[i][0:4]:  # CC4T接口
            file2 = open((os.sep).join([filepath,"XXVT", "pre" + CCNAME + "4T_if.h"]), 'r')
            file2.seek(0)
            line_info = file2.readline()
            # print("line_info 4t = ", line_info)
            while True:
                if not line_info: break
                line_info1 = line_info.lstrip()  # 去掉左边空格。
                if line_info1.startswith('SMEE_EXPORT'):
                    start_smee_export_line = line_info  # 用于保存SMEE_EXPORT 同一行参数。
                    line_info_list = line_info1.split(' ')  # 防止有req，wait 接口干扰。
                    if checkExcel.funs_list_sh1_tuple[i] in line_info_list:
                        # print("line info =", line_info)
                        file3.write(line_info)  # 只将需要刷代码的接口写到文件中。
                        # print("4t start SMEE_EXPORT = ", line_info)
                        line_info = file2.readline()
                        if '(IN ' in start_smee_export_line or '(OUT ' in start_smee_export_line or '(INOUT ' in start_smee_export_line:
                            sub_start_smee_export_line = start_smee_export_line[start_smee_export_line.find('(') + 1:-2]
                            list_funsValue = sub_start_smee_export_line.split(' ')
                            temp_parameter_list.append(list_funsValue)
                        while "IN " in line_info or "OUT " in line_info or "INOUT " in line_info:
                            line_info_strip = line_info.strip()
                            temp_sub = line_info_strip.replace(' *', ' ')
                            sub_line_info_lstrip = temp_sub[:-1]
                            list_sub_line_info_lstrip = sub_line_info_lstrip.split(' ')
                            # print("4t IN,OUT,INOUT line_info = ",line_info)
                            temp_parameter_list.append(list_sub_line_info_lstrip)
                            file3.write(line_info)
                            line_info = file2.readline()
                            if not (line_info): break
                        dict_funs[checkExcel.funs_list_sh1_tuple[i]] = temp_parameter_list  # 键值对
                        # print("4t dict_funs = ",dict_funs)
                        file2.seek(0)
                        write_to_file = True
                        break
                    else:
                        line_info = file2.readline()
                        line_info2 = line_info.lstrip()  # 去掉左边空格。
                        while not (line_info2.startswith("SMEE_EXPORT")):
                            line_info = file2.readline()
                            line_info2 = line_info.lstrip()  # 去掉左边空格。
                            if not (line_info): break
                else:
                    line_info = file2.readline()
                    line_info2 = line_info.lstrip()  # 去掉左边空格。
                    while not (line_info2.startswith("SMEE_EXPORT")):
                        line_info = file2.readline()
                        line_info2 = line_info.lstrip()  # 去掉左边空格。
                        if not (line_info): break
        else:
            print("the function is not start with %s4A or %s4T. ", CCNAME, CCNAME)
            break
    log.write("dict_funs =%s\n "%(dict_funs)) # 接口和接口参数字典。
    if checkExcel.bool_XX4A == True:
        file1.close()
        #os.remove((os.sep).join(["./XXVT", "pre" + CCNAME + "4A_if.h"]))
    if checkExcel.bool_XX4T == True:
        file2.close()
        #os.remove((os.sep).join(["./XXVT", "pre" + CCNAME + "4T_if.h"]))
    file3.close()

# 判断headFiles 目录头文件收集是否齐全。
def check_headfile_all(filepath,headfile):
    headfile_path = (os.sep).join([filepath,"headFiles", headfile])
    if os.path.exists(headfile_path):
        if not headfile in headfile_list:  # 防止头文件重复读取。xx4a_if.h,xx4t.if.h可能都包含相同的头文件。
            headfile_list.append(headfile)
            file = open((os.sep).join([filepath, "headFiles", headfile]), 'r')
            file.seek(0)
            line_info = file.readline()
            while True:
                if not line_info: break
                m = re.match(r'^#include\s["|<].*.h["|>]$', line_info)
                if m:
                    #print("line_info = %s" % (line_info))
                    # print('#include_line_info=',line_info)
                    # print("line_info[9]=",line_info[9])
                    # print("line_info[-2]=",line_info[-2])
                    if 2 == line_info.count('"'):
                        sublineinfo = line_info[line_info.find('"') + 1:line_info.rfind('"')]
                        #print("sublineinfo = %s" % (sublineinfo))
                        check_headfile_all(filepath,sublineinfo)
                    if '<' == line_info[9] and '>' == line_info[-2]:  # 此处约定俗成
                        sublineinfo = line_info[10:-2]
                        #print("sublineinfo = %s" % (sublineinfo))
                        check_headfile_all(filepath,sublineinfo)
                line_info = file.readline()
                if line_info.startswith('SMEE_EXPORT') or line_info.startswith('#typedef'):
                    break  # 表示读取头文件包含文件部分结束。
            file.close()
        else:pass
            #print("headfile %s is already in list headfile_list" % (headfile))
    else:
        print("路径 %s 不存在。\n" % (headfile))
    return headfile_list





# 分别新建三个字典 dict_struct,dict_enum，dict_macro。收集所有文件的结构体和枚举,宏定义。
# 生成temp_record_struct_enum_macro.txt
def collect_struct_enum(filepath, headfile_list):
    file1 = open("struct_enum_macro.txt", 'w')

    headfilepath = os.path.join(filepath, 'headFiles')
    sublines = []
    dict_macro = []
    for files in headfile_list:
        m = re.search(r'_if.h$', files)
        if m:continue  # if头文件跳过
        else:  # (解析tc头文件)
            file = open((os.sep).join([headfilepath, files]), 'r')
            # print("file = ",file)
            file1.write('头文件名称为：' + files + '\n')
            lines = file.readlines()
            for line in lines:
                subline1 = line.strip()
                if subline1.startswith("//") \
                        or '\n' == subline1 \
                        or '#endif' in subline1 \
                        or '#include' in subline1 \
                        or '' == subline1:
                    pass
                elif subline1.startswith('/*'):  # (/*...*/)
                    index = lines.index(line)
                    temp_index = index
                    while not lines[index].endswith('*/\n'):
                        index = index + 1
                    # print("lines[%d] = %s"%(index,lines[index]))
                    del lines[temp_index:index]
                else:
                    subl = ""
                    location = 0
                    if re.search(r'/*.*\*/$', subline1):
                        location = subline1.find('/*')
                        subl = subline1[:location]
                        if re.search(r'[,|;|_MAX$]', subl):
                            if ',' in subl:  # 枚举成员以，结束
                                location = subl.find(',')
                                file1.write(subl[:location] + '\n')
                            elif re.search(r'_MAX$', subl):
                                location = subl.find('_MAX')
                                file1.write(subl[:location + 4] + '\n')
                            elif ';' in subl:  # 结构体成员以；结束
                                location = subl.find(';')
                                file1.write(subl[:location] + '\n')
                            else:
                                pass
                    elif re.search(r'//.*', subline1):
                        location = subline1.find('//')
                        subl = subline1[:location]
                        if re.search(r'[,|;]|_MAX$', subl):
                            if ',' in subl:
                                location = subl.find(',')
                                file1.write(subl[:location] + '\n')
                            elif re.search(r'_MAX$', subl):
                                location = subl.find('_MAX')
                                file1.write(subl[:location + 4] + '\n')
                            elif ';' in subl:  # 结构体成员以；结束
                                location = subl.find(';')
                                file1.write(subl[:location] + '\n')
                            else:
                                pass
                        else:
                            file1.write(subl + '\n')
                    elif re.search(r',$', subline1):  # 无注释的情况
                        location = subline1.find(',')
                        file1.write(subline1[:location] + '\n')
                    elif re.search(r';$', subline1):
                        location = subline1.find(';')
                        file1.write(subline1[:location] + '\n')
                    else:
                        file1.write(subline1 + '\n')
            file.close()
    parse_temp_record_struct_enum(file1)
    print("step .收集信息，利用dict_funs字典生成xml格式文件")
    genaral_xml(dict_struct, dict_enum)

#temp_record_struct_enum.txt为输入，
#生成temp_record_macro.txt，dict_enum_struct.txt
def parse_temp_record_struct_enum(file1):
    file1.close()#之前是写模式
    file1 = open("struct_enum_macro.txt", 'r')
    file2 = open("temp_record_macro.txt", 'w')
    file3 = open("dict_enum_struct.txt", 'w')
    file1.seek(0)
    for i in file1.readlines():
        temp = i.rstrip('\n')
        temp_list_enum_struct.append(temp)
    # print('temp_list_enum_struct = ',temp_list_enum_struct)
    file1.close()
    num_of_typedef_enum = temp_list_enum_struct.count('typedef enum')
    print("num_of_typedef_enum", num_of_typedef_enum)
    # 取得枚举结构体的成员字典
    while temp_list_enum_struct.count('typedef enum') != 0:
        temp_list_enum = []
        index_typedef_enum = temp_list_enum_struct.index('typedef enum')
        enum_MIN = temp_list_enum_struct[index_typedef_enum + 2]
        if 'MIN = 0' in enum_MIN:
            enum_MAX = enum_MIN.replace('MIN = 0', 'MAX')
        elif 'MIN = -1' in enum_MIN:
            enum_MAX = enum_MIN.replace('MIN = -1', 'MAX')
        try:
            index_MAX = temp_list_enum_struct.index(enum_MAX)
        except:
            print("illigal enum：", enum_MIN)
        for i in range(index_typedef_enum + 2, index_MAX + 1):
            temp_list_enum.append(temp_list_enum_struct[i])
        subenum_start = temp_list_enum_struct[index_MAX + 1].find('}')
        subenum = temp_list_enum_struct[index_MAX + 1][subenum_start + 1:]
        subenum2 = subenum.strip()
        dict_enum[subenum2] = temp_list_enum

        #print("dict_enum[%s] = %s" % (subenum2, dict_enum[subenum2]))  # 必須在此处打印

        file3.write("dict_enum[%s] = %s" % (subenum2, dict_enum[subenum2]) + '\n')
        del temp_list_enum_struct[index_typedef_enum:index_MAX + 2]
    # print("dict_enum = ",dict_enum)
    # 取得 struct结构体的成员字典
    while temp_list_enum_struct.count('typedef struct') != 0:
        # time.sleep(1)
        num_of_typedef_struct = temp_list_enum_struct.count('typedef struct')
        # print("num_of_typedef_struct = ", num_of_typedef_struct)
        temp_list_struct = []
        # 此for 循环用于找到struct结构体首尾成员索引值。因为结构体不同于枚举，有_MIN,_MAX 判断
        for struct_member in temp_list_enum_struct:
            m = re.search(r'^}.*', struct_member)
            if 'typedef struct' in struct_member:
                index_struct_start = temp_list_enum_struct.index(struct_member)
            elif m:
                index_struct_end = temp_list_enum_struct.index(struct_member)
                for index in range(index_struct_start + 2, index_struct_end):
                    temp_list_struct.append(temp_list_enum_struct[index].split())

                substruct_start = temp_list_enum_struct[index_struct_end].find('}')
                substruct = temp_list_enum_struct[index_struct_end][substruct_start + 1:]
                substruct2 = substruct.strip()
                dict_struct[substruct2] = temp_list_struct
                #print("dict_struct[%s] = %s" % (substruct2, dict_struct[substruct2]))  # 必須在此处打印
                file3.write(("dict_struct[%s] = %s" % (substruct2, dict_struct[substruct2]) + '\n'))
                del temp_list_enum_struct[index_struct_start:index_struct_end + 1]
                break
                del temp_list_enum_struct[index_struct_start:index_base_struct + 1]
            else:
                pass
    # print("temp_list_enum_struct = ", temp_list_enum_struct)
    #枚举和结构体之后的即宏
    for i in temp_list_enum_struct:
        file2.write(i + '\n')
    file2.close()
    file3.close()

# 注意解析结构体和枚举,头文件统一在headFiles目录下。
# 生成 XXVT/temp_funs.xml。
def genaral_xml(dict_struct, dict_enum):
    curPath = os.getcwd()
    fp = open((os.sep).join([curPath,'funsInfoToExcel.xml']), 'w')
    funs_key = list(dict_funs.keys())  # 获取所有的接口。
    doc = Document()  # 在内存中创建dom文档
    fun_info_root = doc.createElement('fun_info')  # 创建根节点fun_info
    doc.appendChild(fun_info_root)  # 根节点添加到dom树。
    for index in range(len(dict_funs)):#第一层循环，接口个数。

        nodeFunName = doc.createElement('fun_name')
        nodeFunName.setAttribute('name', funs_key[index])
        funs_value = dict_funs[funs_key[index]]  # 获取 funs_key[i]的值列表
        codeStr = 'u_param.param_' + funs_key[index]
        nodeParameter = doc.createElement('parameter')
        for params_num in range(len(funs_value)):  # 第二层循环，参数个数
            parameterlist = []
            parameterlist.append(codeStr)
            # 给节点attribute设置文本节点
            nodeAttribute = doc.createElement('attribute')
            nodeAttribute.appendChild(doc.createTextNode(funs_value[params_num][0]))
            del funs_value[params_num][0] #删除第一个元素，使其只有两个元素的列表，传给递归函数
            nodeParamsName = doc.createElement('param_name')
            nodeParamsName.appendChild(doc.createTextNode(funs_value[params_num][1]))
            nodeParamsName.setAttribute('type', funs_value[params_num][0])
            nodeParameter.appendChild(nodeAttribute)
            nodeParameter.appendChild(nodeParamsName)
            nodeMember = doc.createElement('members')

            listStructMember = []
            parseStructType(funs_value[params_num], listStructMember,parameterlist,nodeMember,nodeParameter,doc)


        # 将各叶子节点添加到父节点nodeParameter中
        nodeFunName.appendChild(nodeParameter)
        fun_info_root.appendChild(nodeFunName)
    doc.writexml(fp, indent="", addindent='\t', newl='\n')
    fp.close()

def parseStructType(funStruct,listStructMember,parameterlist,nodeMember,nodeParameter,doc):
    if funStruct[0] in dict_struct.keys():#説明是结构体。
        listStructMember.append(funStruct[1])
        for structValueNum in range(len(dict_struct[funStruct[0]])):
            if dict_struct[funStruct[0]][structValueNum][0] in dict_struct.keys():#説明是结构体。
                parseStructType(dict_struct[funStruct[0]][structValueNum],listStructMember,parameterlist,nodeMember,nodeParameter,doc)
            else:
                listStructMember.append(dict_struct[funStruct[0]][structValueNum][1])
                #print("---------------",listStructMember)
                parameterlist.append('.'.join(listStructMember))
                nodeMember.appendChild(doc.createTextNode('.'.join(parameterlist)))
                nodeParameter.appendChild(nodeMember)
                del listStructMember[-1]
                del parameterlist[-1]

        del listStructMember[-1]

    else:
        listStructMember.append(funStruct[1])
        #print("2---------------", listStructMember)
        parameterlist.append('.'.join(listStructMember))
        nodeMember.appendChild(doc.createTextNode('.'.join(parameterlist)))
        nodeParameter.appendChild(nodeMember)


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
    rownum3 = worksheet3.nrows;
    colnum3 = worksheet3.ncols;
    #print('colnum3 = ',colnum3)#2
    if colnum3 > 2:
        for index in range (rownum3):
            if worksheet3.cell(index,2).value =="":pass

            else:
                dict_enumForUi[worksheet3.cell(index,1).value] = worksheet3.cell(index,2).value

    else:
        sys.exit(1)
        log.write('错误! 需求表格enum页为空！！！\n')
    log.write('枚举在界面的显示字符串：\n%s\n'%(dict_enumForUi))
'''
dict_base_struct = {'xy_vect':['SMEE_DOUBLE x', 'SMEE_DOUBLE y'],
                    'xz_vect':['SMEE_DOUBLE x', 'SMEE_DOUBLE z'],
                    'yz_vect':['SMEE_DOUBLE y', 'SMEE_DOUBLE z'],
                    'xyz_vect':['SMEE DOUBLE x', 'SMEE_DOUBLE y', 'SMEE_DOUBLE z'],
                    'zrxry_vect':['SMEE_DOUBLE z', 'SMEE_DOUBLE rx', 'SMEE_DOUBLE ry'],
                    'rxry_vect':['SMEE_DOUBLE rx', 'SMEE_DOUBLE ry'],
                    'xyrz_vect':['SMEE_DOUBLE x', 'SMEE_DOUBLE y', 'SMEE_DOUBLE rz'],
                    'xyrzzrxry_vect':['SMEE_DOUBLE x', 'SMEE_DOUBLE y', 'SMEE_DOUBLE rz', 'SMEE_DOUBLE z', 'SMEE_DOUBLE rx', 'SMEE_DOUBLE ry'],
                    'ADAE_TIME_VALUE':['ADAE_LONG tm_sec', 'ADAE_LONG tm_usec']}
'''