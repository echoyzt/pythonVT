import xml.dom.minidom
import os
def xmlToUi(CCNAME,filepath):
    # minidom 解析器打开 XML 文件。
    DOMTree = xml.dom.minidom.parse(filepath+'\\'+"11excelXmlForUi.xml")
    pageInfo = DOMTree.documentElement
    pageNames = pageInfo.getElementsByTagName("pageName")
    #print('pageNames =',pageNames)

    for pageName in pageNames:
        page = pageName.getAttribute("pageId")
        file_ui = open((os.sep).join([filepath, "Outcodefiles",CCNAME+ "VT" +page+ '.ui']), 'w')
        write_Qwidget(file_ui,CCNAME,page)
        firstTabs = pageName.getElementsByTagName("firstTab")

        file_ui.write('    <widget class="QStackedWidget" name="stackedWidget">\n')
        file_ui.write('     <property name="currentIndex">\n')
        file_ui.write('      <number>0</number>\n')
        file_ui.write('     </property>\n')
        for index,firstTab in enumerate(firstTabs):
            '''
            tempTab = firstTab.getAttribute("tableName")
            file_ui.write('    <widget class="QStackedWidget" name="stackedWidget">\n')
            file_ui.write('     <property name="currentIndex">\n')
            file_ui.write('      <number>0</number>\n')
            file_ui.write('     </property>\n')
            if tempTab == "none":
                file_ui.write('    <widget class="QStackedWidget" name="stackedWidget">\n')
                file_ui.write('     <property name="currentIndex">\n')
                file_ui.write('      <number>0</number>\n')
                file_ui.write('     </property>\n')
            else:
                file_ui.write('    <widget class="QTabWidget" name="tabWidget">\n')
                file_ui.write('     <property name="currentIndex">\n')
                file_ui.write('      <number>0</number>\n')
                file_ui.write('     </property>\n')
                write_FirstTab(file_ui, index, tempTab)
            '''
            funNames = firstTab.getElementsByTagName("funName")
            for index1,funName in enumerate(funNames):
                temp_fun = funName.getAttribute('funId')
                temp_funLabel = funName.getAttribute('funLabelId')
                write_Fun(file_ui, index1, temp_fun, temp_funLabel)

                paramLabels = funName.getElementsByTagName("paramLabel")
                temp_row = len(paramLabels)
                #print('paramLabels=', paramLabels)
                for index,paramLabel in enumerate(paramLabels):
                    labelId = paramLabel.getAttribute('paramLabelId')
                    objName = (paramLabel.getElementsByTagName('paramObjectName')[0].childNodes[0].data)
                    paramUnit = (paramLabel.getElementsByTagName('paramUnit')[0].childNodes[0].data)
                    paramAttr = (paramLabel.getElementsByTagName('paramAttr')[0].childNodes[0].data)
                    ParamPrecision = (paramLabel.getElementsByTagName('ParamPrecision')[0].childNodes[0].data)

                    if(paramLabel.getElementsByTagName('paramType')[0].hasAttribute('enumName')):
                        paramType = paramLabel.getElementsByTagName('paramType')[0].getAttribute('enumName')
                    else:
                        paramType = (paramLabel.getElementsByTagName('paramType')[0].childNodes[0].data)

                    for count in range(2):#每个参数分标签和参数显示位于第0,1列。
                        if count == 0:
                            write_Label(file_ui,index,count,objName,labelId,paramUnit)
                        if count == 1:
                            file_ui.write('        <item row="%d" column="%d">\n' % (index, count))
                            if paramAttr =='IN':
                                if paramType == 'SMEE_INT32':
                                    write_SpinBox(file_ui,objName)
                                if paramType == 'SMEE_DOUBLE':
                                    write_DoubleSpinBox(file_ui,objName)
                                if paramType == 'SMEE_BOOL':
                                    write_CheckBox(file_ui,objName)
                                if '_ENUM' in paramType:
                                    paramTypes = paramLabel.getElementsByTagName('paramType')
                                    for paramType in paramTypes:
                                        if paramType.hasChildNodes():
                                            write_ComboBox(file_ui,paramType,objName)
                                file_ui.write('        </item>\n')
                            else:
                                write_StatusLine(file_ui, objName)

                write_Perform(file_ui,temp_fun,temp_row)

        write_Tail(file_ui)

def write_Qwidget(file_ui,CCNAME,page):
    file_ui.write('<?xml version="1.0" encoding="UTF-8"?>\n')
    file_ui.write('<ui version="4.0">\n')
    file_ui.write(' <class>%sVT%s</class>\n'%(CCNAME, page))
    file_ui.write(' <widget class="QWidget" name="%sVT%s">\n'%(CCNAME, page))
    file_ui.write('  <property name="geometry">\n')
    file_ui.write('   <rect>\n')
    file_ui.write('    <x>0</x>\n')
    file_ui.write('    <y>0</y>\n')
    file_ui.write('    <width>750</width>\n')
    file_ui.write('    <height>550</height>\n')
    file_ui.write('   </rect>\n')
    file_ui.write('  </property>\n')
    file_ui.write('  <property name="windowTitle">\n')
    file_ui.write('   <string>Form</string>\n')
    file_ui.write('  </property>\n')
    file_ui.write('  <layout class="QGridLayout" name="gridLayout">\n')
    file_ui.write('   <item row="0" column="0">\n')

def write_FirstTab(file_ui,index,tempTab):
    file_ui.write('     <widget class="QWidget" name="tab_%d">\n'%(index))
    file_ui.write('      <attribute name="title">\n')
    file_ui.write('       <string>%s</string>\n'%(tempTab))
    file_ui.write('      </attribute>\n')
    file_ui.write('      <widget class="QStackedWidget" name="stackedWidget">\n')
    file_ui.write('       <property name="currentIndex">\n')
    file_ui.write('        <number>0</number>\n')
    file_ui.write('       </property>\n')

def write_Fun(file_ui,index,temp_fun,temp_funLabel):
    file_ui.write('     <widget class="QWidget" name="page_%d">\n'%(index))
    file_ui.write('      <widget class="QGroupBox" name="%s_qgb">\n'%(temp_fun))
    file_ui.write('       <property name="geometry">\n')
    file_ui.write('        <rect>\n')
    file_ui.write('         <x>20</x>\n')
    file_ui.write('         <y>20</y>\n')
    file_ui.write('         <width>400</width>\n')
    file_ui.write('         <height>500</height>\n')
    file_ui.write('        </rect>\n')
    file_ui.write('       </property>\n')
    file_ui.write('       <property name="title">\n')
    file_ui.write('        <string>%s</string>\n'%(temp_funLabel))
    file_ui.write('       </property>\n')
    file_ui.write('       <layout class="QGridLayout" name="gridLayout_%d">\n'%(index))

def write_Label(file_ui,index,count,objName,labelId,paramUnit):
    file_ui.write('        <item row="%d" column="%d">\n'%(index, count))
    file_ui.write('         <layout class="QHBoxLayout">\n')
    file_ui.write('          <item>\n')
    file_ui.write('           <widget class ="QLabel" name="%s_qlb" >\n'%(objName))
    file_ui.write('            <property name="text">\n')
    file_ui.write('             <string>%s</string>\n'%(labelId))
    file_ui.write('            </property>\n')
    file_ui.write('           </widget>\n')
    file_ui.write('          </item>\n')
    file_ui.write('          <item>\n')
    file_ui.write('           <spacer>\n')
    file_ui.write('            <property name = "orientation">\n')
    file_ui.write('             <enum>Qt::Horizontal</enum>\n')
    file_ui.write('            </property>\n')
    file_ui.write('            <property name = "sizeHint" stdset="0">\n')
    file_ui.write('             <size>\n')
    file_ui.write('              <width>40</width>\n')
    file_ui.write('              <height>20</height>\n')
    file_ui.write('             </size>\n')
    file_ui.write('            </property>\n')
    file_ui.write('           </spacer>\n')
    file_ui.write('          </item>\n')
    if paramUnit != 'none':
        file_ui.write('          <item>\n')
        file_ui.write('           <widget class="QLabel" name="%s_qlb_2">\n'%(objName))
        file_ui.write('            <property name="text">\n')
        file_ui.write('             <string>[%s]</string>\n'%(paramUnit))
        file_ui.write('            </property>\n')
        file_ui.write('           </widget>\n')
        file_ui.write('          </item>\n')
        file_ui.write('         </layout>\n')
        file_ui.write('        </item >\n')
    else:
        file_ui.write('         </layout>\n')
        file_ui.write('        </item >\n')

def write_StatusLine(file_ui,objName):
    file_ui.write('         <widget class="SMEE::StatusLine" name="%s_qle">\n'%(objName))
    file_ui.write('          <property name="minimumSize">\n')
    file_ui.write('           <size>\n')
    file_ui.write('            <width>180</width>\n')
    file_ui.write('            <height>25</height>\n')
    file_ui.write('           </size>\n')
    file_ui.write('          </property>\n')
    file_ui.write('          <property name="maximumSize">\n')
    file_ui.write('           <size>\n')
    file_ui.write('            <width>180</width>\n')
    file_ui.write('            <height>25</height>\n')
    file_ui.write('           </size>\n')
    file_ui.write('          </property>\n')
    file_ui.write('          <property name="alignment">\n')
    file_ui.write('           <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>\n')
    file_ui.write('          </property>\n')
    file_ui.write('         </widget>\n')
    file_ui.write('        </item>\n')

def write_Perform(file_ui,temp_fun,index):
    file_ui.write('		<item row="%d" column="0" colspan="2">\n'%(index))
    file_ui.write('         <spacer name="verticalSpacer">\n')
    file_ui.write('          <property name="orientation">\n')
    file_ui.write('           <enum>Qt::Vertical</enum>\n')
    file_ui.write('          </property>\n')
    file_ui.write('          <property name="sizeHint" stdset="0">\n')
    file_ui.write('           <size>\n')
    file_ui.write('            <width>20</width>\n')
    file_ui.write('            <height>40</height>\n')
    file_ui.write('           </size>\n')
    file_ui.write('          </property>\n')
    file_ui.write('         </spacer>\n')
    file_ui.write('        </item>\n')
    file_ui.write('        <item row="%d" column="0" colspan="2">\n'%(index+1))
    file_ui.write('         <layout class="QGridLayout">\n')
    file_ui.write('          <item row="0" column="0">\n')
    file_ui.write('           <spacer>\n')
    file_ui.write('            <property name="orientation">\n')
    file_ui.write('             <enum>Qt::Horizontal</enum>\n')
    file_ui.write('            </property>\n')
    file_ui.write('            <property name="sizeHint" stdset="0">\n')
    file_ui.write('             <size>\n')
    file_ui.write('              <width>40</width>\n')
    file_ui.write('              <height>20</height>\n')
    file_ui.write('             </size>\n')
    file_ui.write('            </property>\n')
    file_ui.write('           </spacer>\n')
    file_ui.write('          </item>\n')
    file_ui.write('          <item row="0" column="1">\n')
    file_ui.write('           <widget class="SMEE::PerformButton" name="%s_qpb">\n'%(temp_fun))
    file_ui.write('            <property name="text">\n')
    file_ui.write('             <string>Perform</string>\n')
    file_ui.write('            </property>\n')
    file_ui.write('           </widget>\n')
    file_ui.write('          </item>\n')
    file_ui.write('         </layout>\n')
    file_ui.write('        </item>\n')
    file_ui.write('       </layout>\n')
    file_ui.write('      </widget>\n')
    file_ui.write('     </widget>\n')

def write_ComboBox(file_ui,paramType,objName):
    enumMembers = paramType.getElementsByTagName('enumMember')
    #print('enumMembers = ',enumMembers)
    file_ui.write('         <widget class="SMEE::ComboBox" name="%s_qcb">\n' % (objName))
    file_ui.write('          <property name="layoutDirection">\n')
    file_ui.write('           <enum>Qt::LeftToRight</enum>\n')
    file_ui.write('          </property>\n')
    file_ui.write('          <property name="text" stdset="0">\n')
    file_ui.write('           <string>ComboBox</string>\n')
    file_ui.write('          </property>\n')
    for index,enumMember in enumerate(enumMembers):
        enumdisplay = (paramType.getElementsByTagName('enumMember')[index].childNodes[0].data)
        file_ui.write('          <item>\n')
        file_ui.write('           <property name="text">\n')
        file_ui.write('            <string>%s</string>\n' % (enumdisplay))
        file_ui.write('           </property>\n')
        file_ui.write('          </item>\n')
    file_ui.write('         </widget>\n')

def write_CheckBox(file_ui,objName):
    file_ui.write('           <widget class="SMEE::CheckBox" name="%s_qckb">\n' % (objName))
    file_ui.write('            <property name="minimumSize">\n')
    file_ui.write('             <size>\n')
    file_ui.write('              <width>180</width>\n')
    file_ui.write('              <height>25</height>\n')
    file_ui.write('             </size>\n')
    file_ui.write('            </property>\n')
    file_ui.write('            <property name="maximumSize">\n')
    file_ui.write('             <size>\n')
    file_ui.write('              <width>180</width>\n')
    file_ui.write('              <height>25</height>\n')
    file_ui.write('             </size>\n')
    file_ui.write('            </property>\n')
    file_ui.write('            <property name="text">\n')
    file_ui.write('             <string/>\n')
    file_ui.write('            </property>\n')
    file_ui.write('           </widget>\n')

def write_DoubleSpinBox(file_ui,objName):
    file_ui.write('         <widget class="SMEE::DoubleSpinBox" name="%s_qdsb">\n' % (objName))
    file_ui.write('          <property name="minimumSize">\n')
    file_ui.write('           <size>\n')
    file_ui.write('            <width>180</width>\n')
    file_ui.write('            <height>25</height>\n')
    file_ui.write('           </size>\n')
    file_ui.write('          </property>\n')
    file_ui.write('          <property name="maximumSize">\n')
    file_ui.write('           <size>\n')
    file_ui.write('            <width>180</width>\n')
    file_ui.write('            <height>25</height>\n')
    file_ui.write('           </size>\n')
    file_ui.write('          </property>\n')
    file_ui.write('          <property name="text" stdset="0">\n')
    file_ui.write('           <string>0.000</string>\n')
    file_ui.write('          </property>\n')
    file_ui.write('         </widget>\n')

def write_SpinBox(file_ui,objName):
    file_ui.write('         <widget class="SMEE::SpinBox" name="%s_qsb">\n' % (objName))
    file_ui.write('          <property name="minimumSize">\n')
    file_ui.write('           <size>\n')
    file_ui.write('            <width>180</width>\n')
    file_ui.write('            <height>25</height>\n')
    file_ui.write('           </size>\n')
    file_ui.write('          </property>\n')
    file_ui.write('          <property name="maximumSize">\n')
    file_ui.write('           <size>\n')
    file_ui.write('            <width>180</width>\n')
    file_ui.write('            <height>25</height>\n')
    file_ui.write('           </size>\n')
    file_ui.write('          </property>\n')
    file_ui.write('          <property name="alignment">\n')
    file_ui.write('           <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>\n')
    file_ui.write('          </property>\n')
    file_ui.write('          <property name="text" stdset="0">\n')
    file_ui.write('           <string>2</string>\n')
    file_ui.write('          </property>\n')
    file_ui.write('          <property name="value">\n')
    file_ui.write('           <number>2</number>\n')
    file_ui.write('          </property>\n')
    file_ui.write('         </widget>\n')


def write_Tail(file_ui):
    file_ui.write('    </widget>\n')
    file_ui.write('   </item>\n')
    file_ui.write('  </layout>\n')
    file_ui.write(' </widget>\n')
    file_ui.write(' <customwidgets>\n')
    file_ui.write('  <customwidget>\n')
    file_ui.write('   <class>SMEE::Button</class>\n')
    file_ui.write('   <extends>QPushButton</extends>\n')
    file_ui.write('   <header>Button.h</header>\n')
    file_ui.write('  </customwidget>\n')
    file_ui.write('  <customwidget>\n')
    file_ui.write('   <class>SMEE::ComboBox</class>\n')
    file_ui.write('   <extends>QComboBox</extends>\n')
    file_ui.write('   <header>ComboBox.h</header>\n')
    file_ui.write('  </customwidget>\n')
    file_ui.write('  <customwidget>\n')
    file_ui.write('   <class>SMEE::LineEdit</class>\n')
    file_ui.write('   <extends>QLineEdit</extends>\n')
    file_ui.write('   <header>LineEdit.h</header>\n')
    file_ui.write('  </customwidget>\n')
    file_ui.write('  <customwidget>\n')
    file_ui.write('   <class>SMEE::PerformButton</class>\n')
    file_ui.write('   <extends>SMEE::Button</extends>\n')
    file_ui.write('   <header>PerformButton.h</header>\n')
    file_ui.write('  </customwidget>\n')
    file_ui.write('  <customwidget>\n')
    file_ui.write('   <class>SMEE::StatusLine</class>\n')
    file_ui.write('   <extends>SMEE::LineEdit</extends>\n')
    file_ui.write('   <header>StatusLine.h</header>\n')
    file_ui.write('  </customwidget>\n')
    file_ui.write(' </customwidgets>\n')
    file_ui.write(' <resources/>\n')
    file_ui.write(' <connections/>\n')
    file_ui.write('</ui>\n')



