import re,os
str='SMEE_EXPORT           SMEE_INT32   EC4A_get_state('
str1=re.sub(' +',' ',str)
print(str1)
re_comment="^(#\s*include)|^(\/\*)|^(\/)|^(\\n|\*)"
pattern1=re.compile(re_comment)

re_comment2="((\/\*|\/\/).*)"
pattern2=re.compile(re_comment2)



ExcelPath='G:\\all_exercises\\python_prjs\\pyvt_auto0630\\PYVTUI\\VTUI\\temp_506VTEC'
file1 = open(ExcelPath+"\\5temp_StructEnumMacro.txt", 'w')
file = open('G:\\all_exercises\\python_prjs\\pyvt_auto0630\\PYVTUI\\VTUI\\temp_506VTEC\\temp_HeaderFiles\\EC4A_tc.h', 'r')
lines = file.readlines()
for line in lines:
    subline=line.strip()
    m=pattern1.match(subline)
    if m:pass
    else:
        m2=pattern2.search(subline)
        if m2:
            subline2=subline[:subline.index(m2.group())]
            print(subline2)
        else:
            if "\n" ==subline:pass
            else:print(subline)
