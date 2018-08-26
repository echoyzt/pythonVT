#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "yztfiledialog.h"
#include <QMainWindow>
#include <QTableWidget>
#include <QButtonGroup>
#include <QStackedWidget>
#include <QFileDialog>
#include <QDir>
#include <QSet>
#include <QHash>
#include <QDebug>
#include <QProcess>
#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QtGui>
#include <stdlib.h>
#include <QTextStream>
#include <QRegExp>
#include <QTreeWidgetItemIterator>
#include <Python.h>
//#include <QObject>
typedef enum
{
    STEP_BUTTONS_MIN = -1,
    PREPARE_WORK,
    STEP1_BUTTON,
    STEP2_BUTTON,
    STEP3_BUTTON,
    STEP4_BUTTON,
    STEP5_BUTTON,
    STEP6_BUTTON,
    STEP7_BUTTON,
    STEP8_BUTTON,
    STEP_BUTTONS_MAX
}STEP_BUTTONS_ENUM;
typedef enum
{
    OPERATORS_BUTTON_MIN = -1,
    check_requirement_BTN,
    check_requirement2_BTN,
    createTempDir_BTN,
    addOtherPage_BTN,
    displayFunsInfo_BTN,
    headFileProcess_BTN,
    addenum_qpb_BTN,
    OPERATORS_BUTTON_MAX

}OPERATORS_BUTTON_ENUM;
namespace Ui {
class MainWindow;
}
class yztFileDialog;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createTempDir(QString projectName,QString componentName);
    QButtonGroup* btn_steps;
    QButtonGroup* btn_operators;
    QButtonGroup* fileButtons;
    QMessageBox *testMassage;
    yztFileDialog* dlg;
    QString m_tempdir;
    QString m_CCName;
    QString m_excelName;
    QStringList m_headFilesList;
    QProcess* p ;
    void callpython();
    void displayResult(int button_id);
    void displayFunsToUi();
    void displayHeaderFilesPathToUi();
    void InitializeTreeWidget();
    bool readPageInfo();
    void checkHeaderFiles(bool existXX4A,bool existXX4T);
    void collectHeadFiles(QString filepath,QString headfile);


signals:
public slots:
    void ButtonClickedSlot(int button_id);
    void OperatorClickedSlot(int button_id);
    void FileButtonClickedSlot(int button_id);
    void addFunsToTreeWidget_slot();
    void deleteFromTreeWidegt_slot();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
