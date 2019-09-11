import time
import os

year = time.strftime('%Y', time.localtime(time.time()))
year_mouth_day = time.strftime('%Y-%m-%d', time.localtime(time.time()))
def codefileUniversal(CCNAME,author,pagenames,curpath):
    isExist=os.path.exists(curpath+"/Outcodefiles")
    if isExist:
        file1 = open((os.sep).join([curpath,"Outcodefiles", "VT_if.h"]), 'w')
        file2 = open( (os.sep).join([curpath,"Outcodefiles","VT_if.cpp"]) ,'w')
        file3 = open((os.sep).join([curpath,"Outcodefiles","VT.h"]), 'w')
        file4 = open( (os.sep).join([curpath,"Outcodefiles","VT.cpp"]) ,'w')
    else:
        os.mkdir(curpath+"/Outcodefiles")
        file1 = open((os.sep).join([curpath, "Outcodefiles", "VT_if.h"]), 'w')
        file2 = open((os.sep).join([curpath, "Outcodefiles", "VT_if.cpp"]), 'w')
        file3 = open((os.sep).join([curpath, "Outcodefiles", "VT.h"]), 'w')
        file4 = open((os.sep).join([curpath, "Outcodefiles", "VT.cpp"]), 'w')
    file1.write('''
    #ifndef _VT_IF_H_
    #define _VT_IF_H_
    #include "smee.h"
    #include "Widget.h"
    SMEE_EXPORT SMEE::Widget * %sVT_create_widget();
    #endif
    ''' %(CCNAME))
    file2.write('''
    #include "VT.h"
    #include "VT_if.h"
    SMEE::Widget * %sVT_create_widget()
    {
	    return new VT(0);
    }
    ''' %(CCNAME))


    file3.write('''
#ifndef _VT_H_
#define _VT_H_
#include <QButtonGroup>
#include "smee.h"
#include "Widget.h"
#include "ui_VT.h"
#include "ui_%sVTCategory.h"
#include "PerformFunctionThread.h"
#include <TR4A_tc.h>
    '''%(CCNAME))

    for index in range(len(pagenames)):
        file3.write("# include \"VT%s.h\"+\n"%(CCNAME))
    file3.write('''
typedef enum
{
    FUN_MIN_PAGE = 0, 
''')
    for index in range(len(pagenames)):
        file3.write("%s_PAGE,+\n"%(pagenames[index].upper()))
    file3.write('''
    FUNC_PAGE_MAX
}FUNC_PAGE_ENUM;
//线程执行函数参数打包结构体
typedef struct
{
    QObject * executor;
    int pageIndex;
    int funcCode;
}PERFORM_FUNC_PARAM_STRUCT;
class VT;
class VTCategory;
class PerformFunctionThread;
class VT : public SMEE::Widget, public  Ui::VT
{
    Q_OBJECT
public:
    VT(QWidget *parent = 0);
    ~VT();
    QWidget * getSideWidget( void ); //连接导航页面,供外部使用
    static void execute(void * param);
    private slots:
        // 侧栏页面选择函数
        void switchFuncPageSlot(int pageIndex);
        //关闭所有页面
        void closeWindowSlot();
        void outputLogSlot(int flag,const QString title,const QString text);
        void peformFuncSlot(int funcCode);
        void disableLogoutButtonSlot();//线程开始禁用logout按钮
        void enableLogoutButtonSlot();//线程结束启用logout按钮
private:
    QHash<int, QWidget*> m_FunctionPageHash;
    VTCategory * m_pCategory;
    VTGeneral  *m_VTGeneral;
    SMEE::PerformFunctionThread * m_Thread_p;
signals:
    void errorLogSignal(const QString systemName, const QString description, const int exceptionCode);
    /* - true	线程开始,OIMA界面logout进入锁定状态
    * - false	线程结束,OIMA界面logout解除锁定状态
    */
    void lockLogout (bool flags);
};
//VT侧栏界面类
class VTCategory : public QWidget, public Ui::VTCategory
{
    Q_OBJECT
public:
    VTCategory(QWidget * parent = 0);
    ~VTCategory();
private:
    QButtonGroup * m_ButtonGroup_p ; //侧栏按钮组对象指针
signals:
    void closeWindowSignal();
    void buttonClicked(int index);
private slots:
    void disableCloseButtonSlot();//线程开始禁用close按钮
    void enableCloseButtonSlot();//线程结束启用close按钮
};
#endif
''')

    file4.write('''
    /**************************************************************************
    * Copyright (C) %s, 上海微电子装备有限公司
    * All rights reserved.
    * 产品号 : SS B500/10M
    * 所属组件 : %s
    * 模块名称 : %sVT
    * 文件名称 : %sVT.cpp
    * 概要描述 : %sVT源文件
    * 历史记录 :
    * 版本    日期         作者        内容
    * 1.0     %s            %s
    **************************************************************************/
    '''%(year,CCNAME,CCNAME,CCNAME,CCNAME,year_mouth_day,author))
    file4.write('''
    #include \"VT.h\"
    //构造主界面
    VT::VT(QWidget *parent):Widget(parent)
    {
        setupUi(this);
        m_Thread_p = new SMEE::PerformFunctionThread(this);
        m_FunctionPageHash.clear();
        m_pCategory = new VTCategory(this);//创建一个导航栏对象,用于返回到VT主页面。主页面负责导航栏的打开和关闭
        switchFuncPageSlot(GENERAL_PAGE);
        connecst (m_pCategory, SIGNAL (closeWindowSignal()), this, SLOT (closeWindowSlot()));
        connect (m_pCategory, SIGNAL (buttonClicked(int)), this, SLOT (switchFuncPageSlot(int)));
    }
    VT::~VT(){}
    QWidget * VT::getSideWidget( void ) 
    { 
        return m_pVTCategory; 
    }
    void VT::peformFuncSlot(int funcCode)
    {
        bool result = true;
        if(NULL != m_Thread_p)
        {
            PERFORM_FUNC_PARAM_STRUCT *param;
            param = new PERFORM_FUNC_PARAM_STRUCT;
            param->executor = VT_StackWidget->currentWidget();
            param->pageIndex = m_FunctionPageHash.key(VT_StackWidget->currentWidget());
            param->funcCode = funcCode;
            result = m_Thread_p->performFunctionStart(VT::execute, param);
            if(!result)
            {
                delete param;
            }
        }
    }
    void VT::execute(void *param)
    {
       
        PERFORM_FUNC_PARAM_STRUCT *param_p;
        param_p = (PERFORM_FUNC_PARAM_STRUCT *)param;
        switch(param_p->pageIndex)
        {
    ''')
    for index in range(len(pagenames)):
        file4.write('''
            case %s_PAGE:
            VT%s *%sPage;
            %sPage = qobject_cast<VT%s *>(param_p->executor);
            if(NULL != %sPage)
            {
                %sPage->performFunction(param_p->funcCode);
            }
            break;
            ''' % (pagenames[index].upper(),pagenames[index],pagenames[index].lower(),
                     pagenames[index].lower(),pagenames[index],pagenames[index].lower(),pagenames[index].lower()))
    file4.write('''
    default:
        break;
    }
    delete param_p;
}   ''')
    file4.write('''
    //槽函数
    void VT::switchFuncPageSlot(int pageIndex)
    {
        if(pageIndex >= FUNC_PAGE_MIN && pageIndex <= FUNC_PAGE_MAX)
        {
            if(!m_FunctionPageHash.contains(pageIndex))
            {
                switch(pageIndex)
                {
    ''')
    for index in range(len(pagenames)):
        file4.write('''
         case %s_PAGE:
                    m_FunctionPageHash[pageIndex] = new VT%s;
                    break;
        '''%(pagenames[index].upper(),pagenames[index].title()))
    file4.write('''
        default:
                    break;
                }
                if(NULL != m_FunctionPageHash[pageIndex])
                {
                    connect(m_FunctionPageHash[pageIndex], SIGNAL(send_log(int,const QString,const QString)),
                        this, SLOT(outputLogSlot(int,const QString,const QString)));
                    connect(m_FunctionPageHash[pageIndex], SIGNAL(performFuncSignal(int)), this, SLOT(peformFuncSlot(int)));
                    connect(m_Thread_p, SIGNAL(doFuncStartedSignal()), m_FunctionPageHash[pageIndex], SLOT(disablePerformButtonSlot()));
                    connect(m_Thread_p, SIGNAL(doFuncFinishedSignal()), m_FunctionPageHash[pageIndex], SLOT(enablePerformButtonSlot()));
                    //接口返回之前，禁止用户执行close操作
                    connect(m_Thread_p, SIGNAL(doFuncStartedSignal()), m_%sVTCategory, SLOT(disableCloseButtonSlot()));
                    connect(m_Thread_p, SIGNAL(doFuncFinishedSignal()), m_%sVTCategory, SLOT(enableCloseButtonSlot()));
                    //接口返回之前，禁止用户执行logout操作
                    connect(m_Thread_p, SIGNAL(doFuncStartedSignal()), this, SLOT(disableLogoutButtonSlot()));
                    connect(m_Thread_p, SIGNAL(doFuncFinishedSignal()), this, SLOT(enableLogoutButtonSlot()));
                    VT_StackWidget->insertWidget(pageIndex,m_FunctionPageHash[pageIndex]);
                }
                else
                {
                    SMEE::MessageBox::warning(this, 
                        QString(\"Switch Page\"), 
                        QString(\"%sVT create function page(%s) failed!\").arg(pageIndex));
                    return;
                }
            }
            VT_StackWidget->setCurrentWidget(m_FunctionPageHash[pageIndex]);
        }
    }
    void VT::closeWindowSlot()
    {
        SMEE::MessageBox::StandardButton button;
        button = SMEE::MessageBox::question(this,
            QString(\"Question\"),
            QString(\"Are you sure to exit?\"),
            SMEE::MessageBox::Ok|SMEE::MessageBox::Cancel);
        if(button == SMEE::MessageBox::Ok)
        {
            m_FunctionPageHash.clear();
            close();
        }
    }
    //接受信息的槽
    void VT::outputLogSlot(int flag,const QString title,const QString text)
    {
        if (flag == OK)
        {
            VT_Output->normal(title,text);
        }else
        {
            emit errorLogSignal(QObject::tr(\"VT%s\", \"VT%s\"), text, flag);
            VT_Output->error(title,text);
        }
    }
    //线程开始禁用OIMA中的logout按钮
    void VT::disableLogoutButtonSlot()
    {
        emit lockLogout(true);
    }
    //线程结束启用OIMA中的logout按钮
    void VT::enableLogoutButtonSlot()
    {
        emit lockLogout(false);
    }
    //导航界面构造
    VTCategory::VTCategory(QWidget *parent)
    :QWidget(parent)
    {
        setupUi(this);
        m_ButtonGroup_p = new QButtonGroup(this);//创建按钮组
    ''' )
    for index in range(len(pagenames)):
        file4.write("m_ButtonGroup_p->addButton(btn_%s,%s_PAGE);"%(pagenames[index].lower(),pagenames[index].upper()))
    file4.write('''
        m_ButtonGroup_p->setExclusive(true);
        btn_general->setChecked(true);
        ////绑接界面切换 信号和槽函数。
        connect(m_ButtonGroup_p,SIGNAL(buttonClicked(int)),this,SIGNAL(buttonClicked(int)));	
        connect (btn_close, SIGNAL (clicked()), this, SIGNAL (closeWindowSignal()));
    }
    VTCategory::VTCategory()
    {
        if(m_ButtonGroup_p != NULL)
        {
            delete m_ButtonGroup_p;
            m_ButtonGroup_p = NULL;
        }
    }
    //线程开始禁用close按钮
    void VTCategory::disableCloseButtonSlot()
    {
        btn_close->setEnabled(false);
    }
    //线程结束启用close按钮
    void VTCategory::enableCloseButtonSlot()
    {
        btn_close->setEnabled(true);
    }
    ''')

    file1.close()
    file2.close()
    file3.close()
    file4.close()



def pageCodeHeadFiles(CCNAME,
                      author,
                      pagenames,
                      b_xx4a,
                      b_xx4t,
                      dict_pages,
                      dict_funs,
                      curpath,
                      log):
    for i in range(len(pagenames)):
        head_file = open(((os.sep).join([curpath,"Outcodefiles",CCNAME+"VT"+pagenames[i]+".h"])) ,'w')
        head_file.write('''/***********************************************************
* Copyright (C) %s, 上海微电子装备有限公司
* All rights reserved.
* 产品号 : SS A600/20
* 所属组件 : %s
* 模块名称 : %sVT
* 文件名称 : %sVT.h
* 概要描述 :
* 历史记录 :
* 版本        日期                      作者          内容
*  ?          %s                         %s           创建
**************************************************/
#ifndef _%sVT_%s_H_
#define _%sVT_%s_H_
#include "SMEE_Gui.h"
#include <QThread>
#include "ui_%sVT%s.h"      
        '''%(year, CCNAME,CCNAME,CCNAME, year_mouth_day, author,CCNAME,pagenames[i].upper(),CCNAME,pagenames[i].upper(),CCNAME,pagenames[i]))

        if b_xx4a:
            head_file.write('''
#include "%s4A_if.h"'''% (CCNAME) +'\n')
            head_file.write(r'#include "%s4A_tc.h"'% (CCNAME)+'\n' )
        else:pass
        if b_xx4t:
            head_file.write("\n#include \"%s4T_if.h\""%(CCNAME)+'\n')
            head_file.write("#include \"%s4T_tc.h\""%(CCNAME) +'\n')
        else:pass
        head_file.write('''//*******输入输出参数联合体定义************************/
typedef union
{'''+'\n')
        log.write("len(dict_pages[%s]) = %d\n" %(pagenames[i],len(list(dict_pages[pagenames[i]]))))
        funsNameList = list(dict_pages[pagenames[i]])#各页面包含的接口列表。
        log.write("funsNameList=%s\n"%(funsNameList))
        for index_funs in range(len(funsNameList)): #各页面对应的接口的个数。
            head_file.write(''' struct
    {'''+'\n')
            fun_params_list = list(dict_funs[funsNameList[index_funs]])
            #print("fun_params_list=",fun_params_list)
            for  index_params in range(len(fun_params_list)):
                head_file.write("       %s %s;" %(fun_params_list[index_params][1],fun_params_list[index_params][2])+'\n')

            head_file.write("    }param_%s;"%(funsNameList[index_funs])+'\n')
        head_file.write('''}%sVT_%s_PARAM_UNION;
        '''%(CCNAME,pagenames[i].upper()))

        head_file.write('''
typedef enum
{
    %sVT_%s_FUNCTION_CODE_MIN = 0,'''%(CCNAME,pagenames[i].upper()))
        for enum_index in range(len(dict_pages[pagenames[i]])):
            head_file.write('''
    %s,'''%(funsNameList[enum_index].upper()))
        head_file.write('''\n    %sVT_%s_FUNCTION_CODE_MAX
}%sVT_%s_FUNCTION_CODE_ENUM; 
        '''%(CCNAME,pagenames[i].upper(),CCNAME,pagenames[i].upper()))
        head_file.write('''
class %sVT%s:public SMEE::Widget, private Ui::%sVT%s
{
Q_OBJECT
public:
    %sVT%s(QWidget * parent = 0);
    ~%sVT%s();
    void performFunction(int funcCode);
public slots:
    //禁止界面全部按钮
    void disablePerformButtonSlot();
    //使能所有按钮
    void enablePerformButtonSlot();
protected slots:
    //刷新界面数据
    void updateWindowData();
    //按钮对应的槽
    void performButtonClickedSlot(int button_id);
    private:
    //信息输出栏
    void m_log( int flag,const QString title ,const QString text);
    void outputStart( QString fun_name);
    void outputEnd( QString fun_name,int rtn);
    //执行接口函数
        '''%(CCNAME,pagenames[i],CCNAME,pagenames[i],CCNAME,pagenames[i],CCNAME,pagenames[i]))
        for funs_index in range(len(dict_pages[pagenames[i]])):
            head_file.write('''
    void m_exec_%s();'''%(funsNameList[funs_index]))
        head_file.write('''\nsignals:
    void send_log(int flag,const QString title,const QString text);
    void performFuncSignal(int funcCode);
private:
    %sVT_%s_FUNCTION_CODE_ENUM m_func;
    %sVT_%s_PARAM_UNION u_param;
    QButtonGroup  *SwichButtonG ; //侧栏按钮组对象指针 
};
#endif
        '''%(CCNAME,pagenames[i].upper(),CCNAME,pagenames[i].upper()))
        head_file.close()


def pageTopCppCode(CCNAME,filepath,dict_pages,pages):
    str_class = CCNAME + 'VT' + pages
    cppfile = open(((os.sep).join([filepath, "Outcodefiles", CCNAME + "VT" + pages + ".cpp"])), 'w')

    cppfile.write('#include "%s.h"\n' % (str_class))
    cppfile.write('%s::%s(QWidget *parent)\n' % (str_class, str_class))
    cppfile.write('\t:SMEE::Widget(parent), m_func((%sVT_%s_FUNCTION_CODE_ENUM)(-1))\n{\n' % (CCNAME, pages.upper()))
    cppfile.write('\tsetupUi(this);\n')
    cppfile.write('\tSwichButtonG = new QButtonGroup;//创建按钮组\n')
    for funIndex in range(len(dict_pages[pages])):
        cppfile.write('\tSwichButtonG->addButton(%s_qpb,(int)%s);\n' % (
        list(dict_pages[pages])[funIndex], list(dict_pages[pages])[funIndex].upper()))
    cppfile.write('\tSwichButtonG->setExclusive(true);')
    cppfile.write('''
    connect(
    	SwichButtonG,
     	SIGNAL(buttonClicked(int)),
    	this,
    	SLOT(performButtonClickedSlot(int)));\n}\n''')


    cppfile.write('%s::~%s(){}' % (str_class, str_class))
    cppfile.write('''
void %s::disablePerformButtonSlot()
{
    int i;
    for (i=%sVT_%s_FUNCTION_CODE_MIN+1; i <%sVT_%s_FUNCTION_CODE_MAX; i++)
    {
        if (SwichButtonG->button(i))
        {
            SwichButtonG->button(i)->setEnabled(false);
        }
    }
}
void %s::enablePerformButtonSlot()
{
    int i;
    for (i=%sVT_%s_FUNCTION_CODE_MIN+1; i < %sVT_%s_FUNCTION_CODE_MAX; i++)
    {
        if (SwichButtonG->button(i))
        {
            SwichButtonG->button(i)->setEnabled(true);
        }
    }
    updateWindowData();
}
        ''' % (str_class, CCNAME, pages.upper(), CCNAME, pages.upper(),
               str_class, CCNAME, pages.upper(), CCNAME, pages.upper(),))
    cppfile.write('''
//****************传递信息********************************************************************************************
void %s::m_log(int flag,const QString title,const QString text)
{
    emit send_log(flag,title,text);
}
void %s::outputStart( QString fun_name)
{
    m_log(OK,QString("%sVT"),QString("%%1 start.").arg(fun_name));
}
    
void %s::outputEnd( QString fun_name,int rtn)
{
    if(rtn == OK)
    {
        m_log(OK,QString("%sVT"),QString("%%1 success.").arg(fun_name));
    }
    else
    {
        m_log(rtn,QString("%sVT"),QString("%%1 failed.  Error Code:0x%%2").arg(fun_name).arg(rtn, 0, 16));
    }
}  
''' % (str_class, str_class, CCNAME, str_class, CCNAME, CCNAME))
    cppfile.write('void %s::performFunction(int funcCode)\n{\n' % (str_class))
    cppfile.write('\tswitch(funcCode)\n\t{')
    for funIndex in range(len(dict_pages[pages])):
        cppfile.write('''
        case %s:
            m_exec_%s();
            break;
        ''' % (list(dict_pages[pages])[funIndex].upper(), list(dict_pages[pages])[funIndex]))
    cppfile.write('default:\n\t\t\tbreak;\n\t}\n}')
    cppfile.close()
    filepath = ((os.sep).join([filepath, "Outcodefiles", CCNAME + "VT" + pages + ".cpp"]))
    return filepath
