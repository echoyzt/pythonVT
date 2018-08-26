import os
import smee_widgets
def xxvt_ui(CCNAME):#建立XXVT.ui
    str_ui_head = ''
    filename = CCNAME + "VT" + r".ui"
    pagename = CCNAME + "VT"
    file = open((os.sep).join(["./XXVT", filename]), 'w')
    #print('str_ui_head = ',str_ui_head)
    new_general_xml_ui = smee_widgets.ui_head(str_ui_head).replace('%s',pagename.__str__())
    file.write(new_general_xml_ui)
    file.write(r'   <item row="0" column="0">'+'\n')
    file.write(r'    <widget class="QStackedWidget" name="ECVT_StackWidget">'+'\n')
    file.write(r'     <property name="currentIndex">'+'\n')
    file.write(r'      <number>0</number>'+'\n')
    file.write(r'     </property>'+'\n')
    file.write(r'     <widget class="QWidget" name="page_2">'+'\n')
    file.write(r'      <layout class="QGridLayout"/>'+'\n')
    file.write(r'     </widget>'+'\n')
    file.write(r'    </widget>'+'\n')
    file.write(r'   </item>'+'\n')
    file.write(r'   <item row="1" column="0">'+'\n')
    file.write(r'    <widget class="SMEE::OutputWidget" name="ECVT_Output"/>'+'\n')
    file.write(r'   </item>'+'\n')
    file.write(r'  </layout>'+'\n')
    file.write(r' </widget>'+'\n')
    file.write(r' <customwidgets>'+'\n')
    file.write(r'  <customwidget>'+'\n')
    file.write(r'   <class>SMEE::OutputWidget</class>'+'\n')
    file.write(r'   <extends>QWidget</extends>'+'\n')
    file.write(r'   <header>OutputWidget.h</header>'+'\n')
    file.write(r'  </customwidget>'+'\n')
    file.write(r' </customwidgets>'+'\n')
    file.write(r' <resources/>'+'\n')
    file.write(r' <connections/>'+'\n')
    file.write(r'</ui>')
    file.close()

def xxvtCategory_ui(CCNAME,pagenames):
    str_ui_head = ''
    filename = CCNAME + "VTCategory" + r".ui"
    pagename = CCNAME + "VTCategory"
    file = open((os.sep).join(["./XXVT", filename]), 'w')
    new_general_xml_ui = smee_widgets.ui_head(str_ui_head).replace('%s', pagename.__str__())
    file.write(new_general_xml_ui)
    for i in range(len(pagenames)):
        file.write(r'   <item row = "%d" column = "0" >'%i + '\n')
        smee_widgets.ui_qpushbutton(file,pagenames[i])
    file.write(r'   <item row="%d" column="0">'%(len(pagenames)+1)+'\n')
    smee_widgets.ui_spaceVertical(file)
    file.write(r'   <item row="%d" column="0">'%(len(pagenames) + 2) + '\n')
    smee_widgets.ui_btnClose(file)
    file.write('''  </layout>
     </widget>
     <resources/>
     <connections/>
    </ui>
    ''')
    file.close()

'''
def widgets_ui_head(file):
    # XML头部
    file.write("<ui version=\"4.0\" >")
    file.write(" <class>"
    # com_vt_upper# category#"</class>")
    file.write(" <widget class=\"QWidget\" name=\""
    # com_vt_upper# category#"\" >")
    file.write("  <property name=\"geometry\" >")
    file.write("   <rect>")
    file.write("    <x>0</x>")
    file.write("    <y>0</y>")
    file.write("    <width>1000</width>")
    file.write("    <height>1300</height>")
    file.write("   </rect>")
    file.write("  </property>")
    file.write("  <property name=\"windowTitle\" >")
    file.write("   <string>Form</string>")
    file.write("  </property>")
    file.write("  <widget class=\"QTabWidget\" name=\"tabWidget\" >")
    file.write("   <property name=\"geometry\" >")
    file.write("    <rect>")
    file.write("     <x>20</x>")
    file.write("     <y>150</y>")
    file.write("     <width>950</width>")
    file.write("     <height>1150</height>")
    file.write("    </rect>")
    file.write("   </property>")
    file.write("   <property name=\"currentIndex\" >")
    file.write("    <number>0</number>")
    file.write("   </property>")
    '''
'''

def widgets_label():
def widgets_statusline():
def widgets_lineEdit():
def widgets_spinBox():
def widgets_doubleSpinBox():
def widgets_inputFile():
def widgets_comboBox():
def widgets_tableWidget():
'''

def widgets_ui_tail(file):
    file.write("  </widget>")
    # 尾部
    file.write(" </widget>")
    file.write(" <resources/>")
    file.write(" <connections/>")
    file.write("</ui>")

def widgets_widget(file,pagenames,index):
    file.write('''
 <class>Form</class>
<widget class="QWidget" name="Form">'''+'\n')
    file.write('''<property name="geometry">
   <rect>
    <width>927</width>
    <height>544</height>
   </rect>
  </property>
  <property name="windowTitle">
   <string>%s</string>
  </property>
 </widget>'''%(pagenames[index]))

def widgets_general(CCNAME,pagenames,):
    for index in range(len(pagenames)):
        filename = CCNAME+"VT"+pagenames[index]+".ui"
        file = open((os.sep).join(['./XXVT',filename]),'w')
        file.write('''<?xml version="1.0" encoding="UTF-8"?>''')

