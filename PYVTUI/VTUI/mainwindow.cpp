#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_tempdir = "";
    m_CCName = "";
    m_excelName ="";
    p = new QProcess(0);
    //headFilesList = [];
    btn_steps = new QButtonGroup;
    btn_steps->addButton(ui->prepare_qtb,PREPARE_WORK);
    btn_steps->addButton(ui->step1_qtb,STEP1_BUTTON);
    btn_steps->addButton(ui->step2_qtb,STEP2_BUTTON);
    btn_steps->addButton(ui->step3_qtb,STEP3_BUTTON);
    btn_steps->addButton(ui->step4_qtb,STEP4_BUTTON);
    btn_steps->addButton(ui->step5_qtb,STEP5_BUTTON);
    btn_steps->addButton(ui->step6_qtb,STEP6_BUTTON);
    btn_steps->addButton(ui->step7_qtb,STEP7_BUTTON);
    btn_steps->addButton(ui->step8_qtb,STEP8_BUTTON);

    btn_operators = new QButtonGroup;
    btn_operators->addButton(ui->check_requirement_qpb,check_requirement_BTN);
    btn_operators->addButton(ui->check_requirement_qpb2,check_requirement2_BTN);
    btn_operators->addButton(ui->createTempDir_qpb,createTempDir_BTN);
    btn_operators->addButton(ui->addOtherPage_qpb,addOtherPage_BTN);
    btn_operators->addButton(ui->displayfunsInfo_qpb,displayFunsInfo_BTN);
    btn_operators->addButton(ui->headFileProcess_qpb,headFileProcess_BTN);
    btn_operators->addButton(ui->addenum_qpb,addenum_qpb_BTN);

    ui->stackedWidget->setCurrentIndex(0);
    ui->tabWidget_xuqiu_qtw->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(0);
    ui->resultOutput_qte->setReadOnly(true);
    ui->resultOutput_qte2->setReadOnly(true);
    ui->requirement_rule_qte->setReadOnly(true);


    connect(
            btn_steps,
            SIGNAL(buttonClicked(int)),
            this,
            SLOT(ButtonClickedSlot(int)));
    connect(
            btn_operators,
            SIGNAL(buttonClicked(int)),
            this,
            SLOT(OperatorClickedSlot(int)));
    fileButtons = new QButtonGroup;
    fileButtons->addButton(ui->filebtn_1,0);
    fileButtons->addButton(ui->tempdir_qpb,1);
    connect(
            fileButtons,
            SIGNAL(buttonClicked(int)),
            this,
            SLOT(FileButtonClickedSlot(int)));

    connect(ui->importToTreeWidegt_qpb,
            SIGNAL(clicked(bool)),
            this,
            SLOT(addFunsToTreeWidget_slot()));

    connect(ui->deleteFromTreeWidegt_qpb,
            SIGNAL(clicked(bool)),
            this,
            SLOT(deleteFromTreeWidegt_slot()));

    InitializeTreeWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::ButtonClickedSlot(int button_id)
{
    switch(button_id)
    {
    case PREPARE_WORK:
       ui->stackedWidget->setCurrentIndex(0);
       break;
    case STEP1_BUTTON:
       ui->stackedWidget->setCurrentIndex(1);
       break;
    case STEP2_BUTTON:
       ui->stackedWidget->setCurrentIndex(2);
       break;
    case STEP3_BUTTON:
       ui->stackedWidget->setCurrentIndex(3);
       break;
    case STEP4_BUTTON:
       ui->stackedWidget->setCurrentIndex(4);

       break;
    case STEP5_BUTTON:
       ui->stackedWidget->setCurrentIndex(5);
       break;
    case STEP6_BUTTON:
       ui->stackedWidget->setCurrentIndex(6);
       break;
    case STEP7_BUTTON:
       ui->stackedWidget->setCurrentIndex(7);
       break;
    case STEP8_BUTTON:
       ui->stackedWidget->setCurrentIndex(8);
       break;

    }

}

void MainWindow::addFunsToTreeWidget_slot()
{
    QList<QListWidgetItem*> list = ui->funs_qlw->selectedItems();//listWidget.item(row).text()
    if (list.count()<=0)
    {
        QMessageBox::warning(this,
            "Add Function to TreeWidget",
            QString("Selected Interface(s) From Left first."));
                 return;
    }

    else
    {
        QTreeWidgetItem* parent = ui->funs_treeWidget->currentItem()->parent();//判断当前项目是否有父节点
        if(parent)
        {
            QMessageBox::warning(this,
                "Add Function to TreeWidget",
                QString("Selected Item Is Not Top Level Drop."));
                     return;

         }

        else
        {
            QString interfaceName;
            //qDebug()<<"list.length()="<<list.length();
            for(int i = 0; i <list.length();i++)
            {
               int rowNum = ui->funs_qlw->row(list[i]);
               interfaceName = ui->funs_qlw->item(rowNum)->text();
               //qDebug()<<"interfaceName="<<interfaceName;
               QTreeWidgetItem* newItem = new QTreeWidgetItem(ui->funs_treeWidget->currentItem());//for 里面新建。
               newItem->setText(0,interfaceName);
               ui->funs_qlw->takeItem(rowNum);//removeItemWidget(QListWidgetItem *item)
            }
        }
    }
}

void MainWindow::deleteFromTreeWidegt_slot()
{
    QTreeWidgetItem* parent = ui->funs_treeWidget->currentItem()->parent();
    int index;
    if(parent) //parent !=null
    {
        index = parent->indexOfChild(ui->funs_treeWidget->currentItem());
        qDebug()<<"----index="<<index;
        QString funName = parent->takeChild(index)->text(0);
        delete parent->takeChild(index);
        int rowlistwidget = ui->funs_qlw->count(); //得到子项总数
        ui->funs_qlw->insertItem(rowlistwidget+1,funName);

    }
    else//父节点上
    {

        index=ui->funs_treeWidget->indexOfTopLevelItem(ui->funs_treeWidget->currentItem());
        qDebug()<<"index----="<<index;
        delete ui->funs_treeWidget->takeTopLevelItem(index);
    }
}
void MainWindow::OperatorClickedSlot(int button_id)
{
    //QProcess* p = new QProcess(0);
    QString strTemp = "";
    bool result = false;
    switch(button_id)
    {
    case check_requirement_BTN:
    {
        Py_Initialize();
        if(!Py_IsInitialized())
        {
            QMessageBox::warning(this,"call python","call python Initialze failed.");

        }
        PyRun_SimpleString("import sys");
        QString setSysPath = QString("sys.path.append('%1')").arg(QCoreApplication::applicationDirPath());
        PyRun_SimpleString(setSysPath.toStdString().c_str());
        PyObject* pModule = PyImport_ImportModule("excelCheck_debug");
        if(!pModule)
        {
            QMessageBox::warning(this,"call python","cat not open module excelCheck_debug\n");
        }
        PyObject* pFuns = PyObject_GetAttrString(pModule,"oldwsExcelInformation");
        if(!pFuns)
        {
            QMessageBox::warning(this,"call python","Get funs oldwsExcelInformation failed.\n");
        }
        PyObject_CallFunction(pFuns,NULL);
        Py_Finalize();

        /*
            p->start("cmd", QStringList()<<"/c"<<"python"<<"excelCheck_debug.py"<<m_CCName<<m_tempdir<<m_excelName<<"NO1");
            result = p->waitForStarted();
            printf("p->waitForStarted() result=%s\n",result?"true":"false");
            if (true == result)
            {
               result = p->waitForFinished();
               if (true==result)
               {
                    strTemp=QString((p->readAll()).toStdString().c_str());
                    qDebug()<<"excelCheck_debug CMD RESULT="<<strTemp;
               }
            }
            testMassage = new QMessageBox();
            testMassage->setModal(false);
            testMassage->setText(QString("excelCheck_debug.py %1.\n").arg(result?"Success":"Failed"));
            testMassage->show();*/
            displayResult(button_id);
            displayFunsToUi();

    }
    break;
    case check_requirement2_BTN:
    {
        bool result = false;
        result = readPageInfo();
        if (result == true)
        {
            p->start("cmd", QStringList()<<"/c"<<"python"<<"manage.py"<<m_CCName<<m_tempdir<<m_excelName<<"NO2");
            result = p->waitForStarted();
            if (true == result)
            {
               result = p->waitForFinished();
               if (true==result)
               {
                    strTemp=QString((p->readAll()).toStdString().c_str());
                    qDebug()<<"collectExcelInfo CMD RESULT="<<strTemp;
               }
            }

            testMassage = new QMessageBox();
            testMassage->setModal(false);
            testMassage->setText(QString("collectExcelInfo.py %1.\n%2").arg(result?"Success":"Failed").arg(strTemp));
            testMassage->show();
            displayResult(button_id);

        }

    }
    break;
    case createTempDir_BTN:
    {
        createTempDir(ui->projectName_qle->text(),ui->componentName_qle->text());
    }
        break;
    case addOtherPage_BTN:
        if (ui->addPageName_qle->text()==NULL)
        {
            QMessageBox::warning(this,"Add Page To Right","页面名称不能为空。");
        }
        else
        {
            QTreeWidgetItem* newItem = new QTreeWidgetItem(ui->funs_treeWidget);
            newItem ->setText(0,ui->addPageName_qle->text());
        }
        break;
    case displayFunsInfo_BTN:
         qDebug()<<"m_headFilesList = "<<m_headFilesList;
         displayHeaderFilesPathToUi();
        break;
    case addenum_qpb_BTN:
        p->start("cmd", QStringList()<<"/c"<<"start"<<m_tempdir+'/'+m_excelName);
        result = p->waitForStarted();
        if (true == result)
        {
           result = p->waitForFinished();
           if (true==result)
           {
                strTemp=QString((p->readAll()).toStdString().c_str());
                qDebug()<<"open excel CMD RESULT="<<strTemp;
           }
        }
        testMassage = new QMessageBox();
        testMassage->setModal(false);
        testMassage->setText(QString("start excel %1.\n").arg(result?"Success":"Failed"));
        testMassage->show();
        break;
    case headFileProcess_BTN:
    {
        p->start("cmd", QStringList()<<"/c"<<"python"<<"manage.py"<<m_CCName<<m_tempdir<<m_excelName<<"NO3");
        result = p->waitForStarted();
        if (true == result)
        {
           result = p->waitForFinished();
           if (true==result)
           {
                strTemp=QString((p->readAll()).toStdString().c_str());
                qDebug()<<"parseheadfile CMD RESULT="<<strTemp;

                testMassage = new QMessageBox();
                testMassage->setModal(false);
                testMassage->setText(QString("parseheadfile.py %1.\n%2\n").arg(result?"Success":"Failed").arg(strTemp));
                testMassage->show();
           }
        }   
    }
        break;
    default:
        break;
    }
}
void MainWindow::FileButtonClickedSlot(int button_id)
{
    QString fileName;
    QString dirstr;
    QString xlsFileName;
    bool result = false;
    QDir* dir = new QDir(dirstr);
    switch(button_id)
    {
    case 0:
    {
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                          QDir::currentPath(),
                                                          tr("*.*"));
        if (!fileName.isEmpty() )
            {
              ui->xlsfileName_qle->setText(fileName);
            }

        QString xlsFileNamePath = ui->xlsfileName_qle->text();
        qDebug()<<"xlsFileNamePath="<<ui->xlsfileName_qle->text();
        int indexNum=xlsFileNamePath.lastIndexOf('/');
        QString subXlsFilePath=xlsFileNamePath.mid(0,indexNum);
        QString excelName= xlsFileNamePath.right(xlsFileNamePath.length()-indexNum-1);
        m_excelName = excelName;
        //printf("excelName=%s\n",excelName.toStdString().c_str());
        printf("subXlsFilePath=%s\n",subXlsFilePath.toStdString().c_str());
        if(m_tempdir != subXlsFilePath)
        {
            //将需求表格拷贝到temp_xxx目录
            QStringList strlist = xlsFileNamePath.split("/");
            xlsFileName = strlist.at(strlist.size()-1);
            QFile xlsFile(m_tempdir+"/"+xlsFileName);
            if (!xlsFile.exists())
            {
               result = QFile::copy(xlsFileNamePath,m_tempdir+"/"+xlsFileName);
               if(!result)
               {
                  QMessageBox::critical(this,"Error","xls file copy failed!\n");
               }
               else
               {
                   QMessageBox::warning(this,"success","xls file copy success!\n");
               }
            }
            else
            {
                // 存在需求表格,先删在拷
                result = xlsFile.remove(m_tempdir+"/"+xlsFileName);
                if (result)
                {
                    QMessageBox::warning(this,"success","Tempdir xls file remove success!\n");
                    result = QFile::copy(xlsFileNamePath,m_tempdir+"/"+xlsFileName);
                    if(!result)
                    {
                       QMessageBox::critical(this,"Error","xlsfile exist,xls file copy failed!\n");
                    }
                    else
                    {
                         QMessageBox::warning(this,"success"," xls file copy to tempdir success!\n");
                    }
                }
                else
                {
                    QMessageBox::critical(this,"Error","xls file remove failed!\n");
                }
            }
        }
    }
       break;

    case 1:
        dirstr = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                         QDir::currentPath(),
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
        //QDir* dir = new QDir(dirstr);
        if (dir->exists() )
            {
              ui->tempdir_qle->setText(dirstr);
            }

        if(NULL == ui->projectName_qle->text() || NULL == ui->componentName_qle->text())
        {
            QMessageBox::critical(this,"Error","Please select Project and Component First!!!\n");

        }

        break;
    default:
        break;
    }
}
void MainWindow::createTempDir(QString projectName,QString componentName)
{
    QDir* temp = new QDir();
    m_tempdir = ui->tempdir_qle->text()+"/temp_"+projectName+"VT"+componentName;
    m_CCName = ui->componentName_qle->text();

    printf("m_tempdir=%s\n",m_tempdir.toStdString().c_str());
    bool exist = temp->exists(m_tempdir);
    printf("m_tempdir exist = %s\n",exist?"True":"False");
    if (exist)
    {
        //bool result = temp->rmdir(ui->tempdir_qle->text()+"/temp_"+projectName+"VT"+componentName);//不能递归删除目录
        //printf("result =%s\n",result?"True":"False");
        QMessageBox::warning(this,"创建文件夹","文件夹temp_"+projectName+"VT"+componentName+"已经存在。");
    }
    //qDebug()<<"path="<<ui->tempdir_qle->text()+"/temp_"+projectName+"VT"+componentName;
    else
    {
        bool ok = temp->mkdir(m_tempdir);
        if (ok)
        {
            QMessageBox::warning(this,"创建文件夹","文件夹temp_"+projectName+"VT"+componentName+"创建成功");
        }
        else
        {
            QMessageBox::warning(this,"创建文件夹","文件夹temp_"+projectName+"VT"+componentName+"创建失败！");
        }
   }
}
void MainWindow::displayResult(int button_id)
{
    QString displayString;
    QTextCodec* codec=QTextCodec::codecForName("GB2312");
    switch(button_id)
    {

        case check_requirement_BTN:
        {
            QFile file(m_tempdir+"/check_result.txt");
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qDebug()<<"Can't open the file!"<<endl;
            }
            ui->resultOutput_qte->clear();


           //QTextCodec* codec=QTextCodec::codecForName("GB2312");
           QByteArray line = file.readAll();
           QString str = codec->toUnicode(line);
           ui->resultOutput_qte->append(str);
           file.close();
        }
        break;
        case check_requirement2_BTN:
        {
            //QTextCodec* codec=QTextCodec::codecForName("GB2312");
            QFile file2(m_tempdir+"/check_result2.txt");
            if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qDebug()<<"Can't open the file2!"<<endl;
            }
            while(!file2.atEnd())
            {
                QByteArray line = file2.readLine();
                QString str=codec->toUnicode(line);
                displayString.append(str);
            }

           ui->resultOutput_qte2->clear();
           ui->resultOutput_qte2->setPlainText(displayString);
        }
           break;
        default:
            break;
    }

}

void MainWindow::displayFunsToUi()
{
    ui->funs_qlw->clear();
    QFile file(m_tempdir+"/temp_funslist.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd())
    {
        int i = 0;
        QByteArray line = file.readLine();
        QString funName(line);
        //qDebug()<<funName;
        QString subFunName = funName.mid(0,funName.length()-1);// 去掉换行符
        ui->funs_qlw->insertItem(i,subFunName);
        ui->funs_qlw->setSelectionMode(QAbstractItemView::MultiSelection); //设置选择模式

    }
    //ui->funs_qlw->sortItems(QT::DescendingOrder);


}

void MainWindow::displayHeaderFilesPathToUi()
{
    QStringList subFunNameList;
    ui->headfilespath_qtb->resizeColumnsToContents();//根据内容自动调整给定列宽
    //ui->headfilespath_qtb-> //setColumnWidth(1,350);
    ui->headfilespath_qtb->clear();
    QFile file(m_tempdir+"/temp_headfilelist.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString headfileName(line);
        //qDebug()<<funName;
        subFunNameList << headfileName.mid(0,headfileName.length()-1);// 去掉换行符
    }
    qDebug()<<"subFunNameList.count()="<<subFunNameList.count();
    for (int i=0; i < subFunNameList.count(); i++)
    {
        QTableWidgetItem* item0 = new QTableWidgetItem(subFunNameList[i]);
        ui->headfilespath_qtb->setItem(i,0,item0);

        QTableWidgetItem* item1 = new QTableWidgetItem();
        ui->headfilespath_qtb->setItem(i,1,item1);

        QPushButton * button = new QPushButton("open");
        ui->headfilespath_qtb->setCellWidget(i,2,button);
    }
}
void MainWindow::InitializeTreeWidget()
{
    ui->funs_treeWidget->clear();
    ui->funs_treeWidget->setColumnCount(1);
    ui->funs_treeWidget->setHeaderLabel("Layout Infomation");
    QTreeWidgetItem *pageGeneral = new QTreeWidgetItem(ui->funs_treeWidget);
    pageGeneral->setText(0,"General");

    QTreeWidgetItem *pageApp = new QTreeWidgetItem(ui->funs_treeWidget);
    pageApp->setText(0,"Application");

    QTreeWidgetItem *pagePer = new QTreeWidgetItem(ui->funs_treeWidget);
    pagePer->setText(0,"Peripheral");

    QTreeWidgetItem *pageMaintenance = new QTreeWidgetItem(ui->funs_treeWidget);
    pageMaintenance->setText(0,"Maintenance");
}

bool MainWindow::readPageInfo()
{
    QHash <QString ,QString> hash_page_funs;
    QSet<QString> set;
    bool existXX4A = false;
    bool existXX4T = false;
    dlg = new yztFileDialog();
    QTreeWidgetItemIterator it(ui->funs_treeWidget);
    QFile file(m_tempdir+"/temp_funsToPage.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file temp_funsToPage.txt!"<<endl;
    }
         while (*it)
         {
             QString funs_list;
            //qDebug()<<"*it->item(0)="<<(*it)->text(0);
             if ((*it)->parent())
             {
                 qDebug()<<"row="<<(*it)->text(0);
             }
             else //父节点
             {
                 QString father = (*it)->text(0);
                  qDebug()<<"father="<<father;
                  int childNum = (*it)->childCount();
                  qDebug()<<"childNum="<<childNum;
                  for(int i = 0;i<childNum;i++)
                  {
                     it++;
                     funs_list.append((*it)->text(0)+',');
                     if ((*it)->text(0).mid(0,4)== m_CCName+"4A")//去字符串开头4个字符
                         existXX4A = true;
                     if ((*it)->text(0).mid(0,4)== m_CCName+"4T")
                         existXX4T = true;
                     qDebug()<<"p="<<(*it)->text(0);
                  }
                 hash_page_funs[father] = funs_list;

             }
             //int counts = ui->funs_treeWidget->topLevelItemCount();
             //qDebug()<<"counts="<<counts;
             it++;
         }
         QStringList tempfun;
         qDebug()<<"hash_page_funs length="<<hash_page_funs.values().length();
         tempfun<<hash_page_funs.values();
         set = QSet<QString>::fromList(tempfun);
         qDebug()<<"set="<<set;
         qDebug()<<"set.count()="<<set.count();
         if(set.count() == 1)
         {
             testMassage = new QMessageBox();
             testMassage->setModal(true);
             testMassage->setWindowTitle("接口布局信息");
             testMassage->setText("请先选择接口添加到右边的布局页面！");
             testMassage->show();
             //QMessageBox::warning(this,"接口布局信息","请先选择接口添加到右边的布局页面！");
             return false;

         }
         else
         {
             QTextStream out(&file);
             QHash<QString,QString>::iterator i;
             for(i = hash_page_funs.begin(); i!=hash_page_funs.end();++i)
             {
                 out <<i.key()+':'<<hash_page_funs[i.key()]+'\n';
             }

            dlg->setWindowTitle("拷贝xx4x头文件");
            qDebug()<<"---existXX4A="<<existXX4A;
            qDebug()<<"---existXX4T="<<existXX4T;
            dlg->openFileDialog(existXX4A,existXX4T,m_tempdir);
            dlg->exec();
            checkHeaderFiles(existXX4A,existXX4T);
            if(dlg !=NULL)
            {
                delete dlg;
                dlg = NULL;
            }
            return true;
         }
}

void MainWindow::collectHeadFiles(QString filepath,QString headfile)
{
    QRegExp rx;
    QString headfilename;
    rx.setPattern("^#include\\s*[:|<].*\\.h\\s*[:|>]");//#include <xx.h>
    rx.setCaseSensitivity(Qt::CaseInsensitive);
    QFile headfilepath(filepath+'/'+headfile);
    if (headfilepath.exists())
    {   if (!m_headFilesList.contains(headfile))
        {
            m_headFilesList<<headfile;
            if(headfilepath.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                while(!headfilepath.atEnd())
                {
                    QByteArray line = headfilepath.readLine();

                    if (QString(line).contains("SMEE_EXPORT",Qt::CaseSensitive) ||
                        QString(line).contains("typedef",Qt::CaseSensitive)){break;}

                    if (rx.isValid())
                    {

                        QString subline = QString(line).replace("\"",":");

                        if(-1!=rx.indexIn(subline))
                        {
                            qDebug()<<"line="<<QString(line);
                            QStringList matchstrlist;
                            matchstrlist = rx.capturedTexts();
                            qDebug()<<"matchstrlist="<<matchstrlist;
                            if (-1 != matchstrlist[0].indexOf(":"))//"xx.h"
                            {
                                headfilename = matchstrlist[0].mid(matchstrlist[0].indexOf(":")+1);
                                headfilename = headfilename.left(headfilename.indexOf(":"));
                                //qDebug()<<"headfilename="<<headfilename;
                            }
                            if (-1 != matchstrlist[0].indexOf("<"))//<xx.h>
                            {
                                headfilename = matchstrlist[0].mid(matchstrlist[0].indexOf("<")+1);
                                headfilename = headfilename.left(headfilename.indexOf(">"));
                                //qDebug()<<"headfilename="<<headfilename;
                            }

                            collectHeadFiles(m_tempdir+"/temp_HeaderFiles",headfilename);
                        }
                    }
                    else
                    {
                        QMessageBox::critical(this,"Error","regexp syntax error!\n");
                    }
                }
            }
            else
            {
                 QMessageBox::critical(this,"Error","Can't open the file ["+headfile+"]!\n");
            }
        }
    }
    else
    {
        QMessageBox::critical(this,"Error","["+headfile+"]"+"can not exist in"+"["+filepath+"]");
    }


}
void MainWindow::checkHeaderFiles(bool existXX4A,bool existXX4T)
{
    //QStringList headfileList = "" ;
    //bool result = false;
    if (existXX4A)
    {
        collectHeadFiles(m_tempdir+"/temp_HeaderFiles",m_CCName+"4A_if.h");

    }
    if (existXX4T)
    {
        collectHeadFiles(m_tempdir+"/temp_HeaderFiles",m_CCName+"4T_if.h");

    }

}

