#include "yztfiledialog.h"
#include "ui_yztfiledialog.h"

yztFileDialog::yztFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::yztFileDialog)
{
    ui->setupUi(this);
    m_tempdir = "";
    fileButtons = new QButtonGroup;
    fileButtons->addButton(ui->xx4a_qpb,0);
    fileButtons->addButton(ui->xx4t_qpb,1);
    connect(
            fileButtons,
            SIGNAL(buttonClicked(int)),
            this,
            SLOT(FileButtonClickedSlot(int)));

    connect(
            ui->copyToTempDir_qpb,
            SIGNAL(clicked(bool)),
            this,
            SLOT(slot_copyHeaderFileToTempDir()));


}
yztFileDialog::~yztFileDialog()
{
    delete ui;
}

void yztFileDialog::openFileDialog(bool xx4a,bool xx4t,QString tempdir)
{
   // qDebug()<<"yztFileDialog::openFileDialog";
    m_tempdir = tempdir;
    qDebug()<<"xx4a---="<<xx4a;
    qDebug()<<"xx4t---="<<xx4t;
    if(!xx4a)
    {
        ui->xx4a_qle->hide();
        ui->xx4a_qpb->hide();
        ui->xx4a_qle->setEnabled(false);
    }
    if(!xx4t)
    {
        ui->xx4t_qle->hide();
        ui->xx4t_qpb->hide();
        ui->xx4t_qle->setEnabled(false);
    }

}
void yztFileDialog::FileButtonClickedSlot(int buttonid)
{
    QString fileName="";
    switch(buttonid)
    {
        case 0:
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                          QDir::currentPath(),
                                                          tr("*4A_if.h"));
        if (!fileName.isEmpty() )
            {
              ui->xx4a_qle->setText(fileName);
            }
            break;
        case 1:
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                          QDir::currentPath(),
                                                          tr("*4T_if.h"));
        if (!fileName.isEmpty() )
            {
              ui->xx4t_qle->setText(fileName);
            }
            break;
    }
}
void yztFileDialog::slot_copyHeaderFileToTempDir()
{
   QString consttempdir = m_tempdir+"/temp_HeaderFiles";
   QDir* tempHeader = new QDir();
   bool exist = tempHeader->exists(consttempdir);
    if (exist)
    {

        if(ui->xx4a_qle->isEnabled() && ui->xx4a_qle->text().isEmpty())
        {
            QMessageBox::warning(this,"拷贝文件","XX4A头文件，路径名不能为空");
        }
        if(ui->xx4t_qle->isEnabled() && ui->xx4t_qle->text().isEmpty())
        {
            QMessageBox::warning(this,"拷贝文件","XX4T头文件，路径名不能为空");
        }
        if(ui->xx4a_qle->isEnabled() && !ui->xx4a_qle->text().isEmpty())
        {
            bool result = false;
            //将头文件拷贝到HeaderFiles目录
            QStringList strlist = ui->xx4a_qle->text().split("/");
            QString xx4aFileName = strlist.at(strlist.size()-1);
            QFile xx4aFile(consttempdir+"/"+xx4aFileName);
            if (!xx4aFile.exists())
            {
               result = QFile::copy(ui->xx4a_qle->text(),consttempdir+"/"+xx4aFileName);
               if(!result)
               {
                  QMessageBox::critical(this,"Error","xx4a file copy failed!\n");
               }
               else
               {
                   QMessageBox::warning(this,"success","xx4a file copy success!\n");
               }
            }
            else
            {
                // 存在xx4a,先删在拷
                result = xx4aFile.remove(consttempdir+"/"+xx4aFileName);
                if (result)
                {
                    QMessageBox::warning(this,"Success","xx4afile remove success!\n");
                    result = QFile::copy(ui->xx4a_qle->text(),consttempdir+"/"+xx4aFileName);
                    if(!result)
                    {
                       QMessageBox::critical(this,"Error","xx4afile exist,xls file copy failed!\n");
                    }
                    else
                    {
                       QMessageBox::warning(this,"Success","xx4afile  copy success!\n");
                    }
                }
                else
                {
                    QMessageBox::critical(this,"Error","xx4a file remove failed!\n");
                }
            }
        }
        if(ui->xx4t_qle->isEnabled() && !ui->xx4t_qle->text().isEmpty())
        {
            bool result = false;
            //将头文件拷贝到HeaderFiles目录
            QStringList strlist = ui->xx4t_qle->text().split("/");
            QString xx4tFileName = strlist.at(strlist.size()-1);
            QFile xx4tFile(consttempdir+"/"+xx4tFileName);
            if (!xx4tFile.exists())
            {
               result = QFile::copy(ui->xx4t_qle->text(),consttempdir+"/"+xx4tFileName);
               if(!result)
               {
                  QMessageBox::critical(this,"Error","xx4t file copy failed!\n");
               }
               else
               {
                   QMessageBox::warning(this,"success","xx4t file copy success!\n");
               }
            }
            else
            {
                // 存在xx4t,先删在拷
                result = xx4tFile.remove(consttempdir+"/"+xx4tFileName);
                if (result)
                {
                     QMessageBox::warning(this,"Success","xx4T file remove success!\n");
                    result = QFile::copy(ui->xx4t_qle->text(),consttempdir+"/"+xx4tFileName);
                    if(!result)
                    {
                       QMessageBox::critical(this,"Error","xx4tfile exist,xls file copy failed!\n");
                    }
                    else
                    {
                         QMessageBox::warning(this,"success","xx4t file  copy success!\n");
                    }
                }
                else
                {
                    QMessageBox::critical(this,"Error","xx4t file remove failed!\n");
                }
            }
        }
    }
    else
    {
        bool ok = tempHeader->mkdir(consttempdir);
        if (ok)
        {
            QMessageBox::warning(this,"创建文件夹","文件夹temp_HeaderFiles创建成功,请再执行一次拷贝操作");
        }
        else
        {
            QMessageBox::warning(this,"创建文件夹","文件夹HeaderFiles创建失败！");
        }
    }


}

