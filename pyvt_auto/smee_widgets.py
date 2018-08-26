def ui_head(str_ui_head):
    str_ui_head = '''<?xml version="1.0" encoding="UTF-8"?>
    <ui version="4.0">
     <class>%s</class>
     <widget class="QWidget" name="%s">
      <property name="geometry">
       <rect>
        <x>0</x>
        <y>0</y>
        <width>644</width>
        <height>685</height>
       </rect>
      </property>
      <property name="windowTitle">
       <string>Form</string>
      </property>
      <layout class="QGridLayout">
        '''
    return str_ui_head

def ui_qpushbutton(*args):
        args[0].write(r'    <widget class="QPushButton" name="btn_%s">'%(args[1].lower())+'\n')
        args[0].write(r'     <property name="text">'+'\n')
        args[0].write(r'      <string>%s</string>'%(args[1].title())+'\n')
        args[0].write(r'     </property>'+'\n')
        args[0].write(r'     <property name="checkable">'+'\n')
        args[0].write(r'      <bool>true</bool>'+'\n')
        args[0].write(r'     </property>'+'\n')
        args[0].write(r'    </widget>'+'\n')
        args[0].write(r'   </item>'+'\n')

def ui_spaceVertical(file):
    file.write('''    <spacer>
     <property name="orientation">
      <enum>Qt::Vertical</enum>
     </property>
     <property name="sizeHint" stdset="0">
      <size>
       <width>88</width>
       <height>351</height>
      </size>
     </property>
    </spacer>
   </item> 
   ''')

def ui_btnClose(file):
    file.write('''    <widget class="QPushButton" name="btn_close">
     <property name="text">
      <string>Close</string>
     </property>
     <property name="checkable">
      <bool>false</bool>
     </property>
    </widget>
   </item>
    ''')


