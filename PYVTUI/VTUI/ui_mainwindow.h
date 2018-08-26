/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_15;
    QGridLayout *gridLayout_9;
    QPushButton *step3_qtb;
    QPushButton *step7_qtb;
    QPushButton *step4_qtb;
    QPushButton *step1_qtb;
    QPushButton *step5_qtb;
    QPushButton *step6_qtb;
    QPushButton *prepare_qtb;
    QPushButton *step8_qtb;
    QPushButton *step2_qtb;
    QStackedWidget *stackedWidget;
    QWidget *page_9;
    QGridLayout *gridLayout_10;
    QLabel *label_2;
    QLineEdit *projectName_qle;
    QLabel *label_3;
    QLineEdit *componentName_qle;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_4;
    QPushButton *tempdir_qpb;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *createTempDir_qpb;
    QLineEdit *lineEdit_3;
    QPushButton *filebtn_1;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *xlsfileName_qle;
    QLineEdit *tempdir_qle;
    QWidget *page;
    QGridLayout *gridLayout_16;
    QTabWidget *tabWidget_xuqiu_qtw;
    QWidget *tab_1;
    QGridLayout *gridLayout_12;
    QPushButton *check_requirement_qpb;
    QSpacerItem *horizontalSpacer_3;
    QTextEdit *resultOutput_qte;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QTextEdit *requirement_rule_qte;
    QWidget *page_2;
    QGridLayout *gridLayout_13;
    QTabWidget *tabWidget;
    QWidget *tab_4;
    QGridLayout *gridLayout_11;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit_5;
    QTreeWidget *funs_treeWidget;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *addPageName_qle;
    QPushButton *addOtherPage_qpb;
    QSpacerItem *verticalSpacer_2;
    QToolButton *importToTreeWidegt_qpb;
    QToolButton *deleteFromTreeWidegt_qpb;
    QSpacerItem *verticalSpacer_4;
    QPushButton *check_requirement_qpb2;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_4;
    QListWidget *funs_qlw;
    QWidget *tab_5;
    QGridLayout *gridLayout_14;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_4;
    QTextEdit *resultOutput_qte2;
    QWidget *page_3;
    QGridLayout *gridLayout_4;
    QPushButton *headFileProcess_qpb;
    QPushButton *displayfunsInfo_qpb;
    QTableWidget *headfilespath_qtb;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *addenum_qpb;
    QSpacerItem *horizontalSpacer_9;
    QWidget *page_4;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_7;
    QTextEdit *textEdit_2;
    QWidget *page_5;
    QGridLayout *gridLayout_5;
    QComboBox *comboBox;
    QTextEdit *textEdit_3;
    QWidget *page_6;
    QGridLayout *gridLayout_6;
    QLineEdit *lineEdit_8;
    QTextEdit *textEdit_4;
    QWidget *page_7;
    QGridLayout *gridLayout_8;
    QLineEdit *lineEdit_9;
    QTextEdit *textEdit_5;
    QWidget *page_8;
    QGridLayout *gridLayout_7;
    QLineEdit *lineEdit_10;
    QTextEdit *textEdit_6;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(770, 393);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_15 = new QGridLayout(centralwidget);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        step3_qtb = new QPushButton(centralwidget);
        step3_qtb->setObjectName(QStringLiteral("step3_qtb"));
        step3_qtb->setCheckable(true);

        gridLayout_9->addWidget(step3_qtb, 3, 0, 1, 1);

        step7_qtb = new QPushButton(centralwidget);
        step7_qtb->setObjectName(QStringLiteral("step7_qtb"));
        step7_qtb->setCheckable(true);

        gridLayout_9->addWidget(step7_qtb, 7, 0, 1, 1);

        step4_qtb = new QPushButton(centralwidget);
        step4_qtb->setObjectName(QStringLiteral("step4_qtb"));
        step4_qtb->setCheckable(true);

        gridLayout_9->addWidget(step4_qtb, 4, 0, 1, 1);

        step1_qtb = new QPushButton(centralwidget);
        step1_qtb->setObjectName(QStringLiteral("step1_qtb"));
        step1_qtb->setCheckable(true);
        step1_qtb->setChecked(false);

        gridLayout_9->addWidget(step1_qtb, 1, 0, 1, 1);

        step5_qtb = new QPushButton(centralwidget);
        step5_qtb->setObjectName(QStringLiteral("step5_qtb"));
        step5_qtb->setCheckable(true);

        gridLayout_9->addWidget(step5_qtb, 5, 0, 1, 1);

        step6_qtb = new QPushButton(centralwidget);
        step6_qtb->setObjectName(QStringLiteral("step6_qtb"));
        step6_qtb->setCheckable(true);

        gridLayout_9->addWidget(step6_qtb, 6, 0, 1, 1);

        prepare_qtb = new QPushButton(centralwidget);
        prepare_qtb->setObjectName(QStringLiteral("prepare_qtb"));
        prepare_qtb->setCheckable(true);
        prepare_qtb->setChecked(true);

        gridLayout_9->addWidget(prepare_qtb, 0, 0, 1, 1);

        step8_qtb = new QPushButton(centralwidget);
        step8_qtb->setObjectName(QStringLiteral("step8_qtb"));
        step8_qtb->setCheckable(true);

        gridLayout_9->addWidget(step8_qtb, 8, 0, 1, 1);

        step2_qtb = new QPushButton(centralwidget);
        step2_qtb->setObjectName(QStringLiteral("step2_qtb"));
        step2_qtb->setCheckable(true);

        gridLayout_9->addWidget(step2_qtb, 2, 0, 1, 1);


        gridLayout_15->addLayout(gridLayout_9, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page_9 = new QWidget();
        page_9->setObjectName(QStringLiteral("page_9"));
        gridLayout_10 = new QGridLayout(page_9);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        label_2 = new QLabel(page_9);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_10->addWidget(label_2, 0, 0, 1, 1);

        projectName_qle = new QLineEdit(page_9);
        projectName_qle->setObjectName(QStringLiteral("projectName_qle"));

        gridLayout_10->addWidget(projectName_qle, 0, 1, 1, 1);

        label_3 = new QLabel(page_9);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_10->addWidget(label_3, 0, 2, 1, 1);

        componentName_qle = new QLineEdit(page_9);
        componentName_qle->setObjectName(QStringLiteral("componentName_qle"));

        gridLayout_10->addWidget(componentName_qle, 0, 3, 1, 2);

        label = new QLabel(page_9);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_10->addWidget(label, 1, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(151, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer, 1, 3, 1, 2);

        label_4 = new QLabel(page_9);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_10->addWidget(label_4, 2, 0, 1, 1);

        tempdir_qpb = new QPushButton(page_9);
        tempdir_qpb->setObjectName(QStringLiteral("tempdir_qpb"));
        tempdir_qpb->setMinimumSize(QSize(100, 0));
        tempdir_qpb->setMaximumSize(QSize(50, 16777215));

        gridLayout_10->addWidget(tempdir_qpb, 3, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(485, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_2, 4, 0, 1, 4);

        createTempDir_qpb = new QPushButton(page_9);
        createTempDir_qpb->setObjectName(QStringLiteral("createTempDir_qpb"));

        gridLayout_10->addWidget(createTempDir_qpb, 4, 4, 1, 1);

        lineEdit_3 = new QLineEdit(page_9);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setEnabled(false);

        gridLayout_10->addWidget(lineEdit_3, 5, 0, 1, 2);

        filebtn_1 = new QPushButton(page_9);
        filebtn_1->setObjectName(QStringLiteral("filebtn_1"));
        filebtn_1->setMinimumSize(QSize(50, 0));

        gridLayout_10->addWidget(filebtn_1, 6, 4, 1, 1);

        verticalSpacer_3 = new QSpacerItem(518, 171, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_3, 7, 0, 1, 5);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_6, 5, 2, 1, 3);

        xlsfileName_qle = new QLineEdit(page_9);
        xlsfileName_qle->setObjectName(QStringLiteral("xlsfileName_qle"));

        gridLayout_10->addWidget(xlsfileName_qle, 6, 0, 1, 4);

        tempdir_qle = new QLineEdit(page_9);
        tempdir_qle->setObjectName(QStringLiteral("tempdir_qle"));

        gridLayout_10->addWidget(tempdir_qle, 3, 0, 1, 4);

        stackedWidget->addWidget(page_9);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        gridLayout_16 = new QGridLayout(page);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        tabWidget_xuqiu_qtw = new QTabWidget(page);
        tabWidget_xuqiu_qtw->setObjectName(QStringLiteral("tabWidget_xuqiu_qtw"));
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        gridLayout_12 = new QGridLayout(tab_1);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        check_requirement_qpb = new QPushButton(tab_1);
        check_requirement_qpb->setObjectName(QStringLiteral("check_requirement_qpb"));
        check_requirement_qpb->setMinimumSize(QSize(130, 0));
        check_requirement_qpb->setMaximumSize(QSize(300, 16777215));

        gridLayout_12->addWidget(check_requirement_qpb, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(556, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        resultOutput_qte = new QTextEdit(tab_1);
        resultOutput_qte->setObjectName(QStringLiteral("resultOutput_qte"));

        gridLayout_12->addWidget(resultOutput_qte, 1, 0, 1, 2);

        tabWidget_xuqiu_qtw->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        requirement_rule_qte = new QTextEdit(tab_2);
        requirement_rule_qte->setObjectName(QStringLiteral("requirement_rule_qte"));

        gridLayout_2->addWidget(requirement_rule_qte, 0, 0, 1, 1);

        tabWidget_xuqiu_qtw->addTab(tab_2, QString());

        gridLayout_16->addWidget(tabWidget_xuqiu_qtw, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        gridLayout_13 = new QGridLayout(page_2);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        tabWidget = new QTabWidget(page_2);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_11 = new QGridLayout(tab_4);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lineEdit_5 = new QLineEdit(tab_4);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setEnabled(false);

        verticalLayout_2->addWidget(lineEdit_5);

        funs_treeWidget = new QTreeWidget(tab_4);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        funs_treeWidget->setHeaderItem(__qtreewidgetitem);
        funs_treeWidget->setObjectName(QStringLiteral("funs_treeWidget"));

        verticalLayout_2->addWidget(funs_treeWidget);


        gridLayout_3->addLayout(verticalLayout_2, 0, 2, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer_5);

        addPageName_qle = new QLineEdit(tab_4);
        addPageName_qle->setObjectName(QStringLiteral("addPageName_qle"));
        addPageName_qle->setMinimumSize(QSize(85, 0));

        verticalLayout_3->addWidget(addPageName_qle);

        addOtherPage_qpb = new QPushButton(tab_4);
        addOtherPage_qpb->setObjectName(QStringLiteral("addOtherPage_qpb"));

        verticalLayout_3->addWidget(addOtherPage_qpb);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        importToTreeWidegt_qpb = new QToolButton(tab_4);
        importToTreeWidegt_qpb->setObjectName(QStringLiteral("importToTreeWidegt_qpb"));
        importToTreeWidegt_qpb->setMinimumSize(QSize(85, 0));

        verticalLayout_3->addWidget(importToTreeWidegt_qpb);

        deleteFromTreeWidegt_qpb = new QToolButton(tab_4);
        deleteFromTreeWidegt_qpb->setObjectName(QStringLiteral("deleteFromTreeWidegt_qpb"));
        deleteFromTreeWidegt_qpb->setMinimumSize(QSize(85, 0));

        verticalLayout_3->addWidget(deleteFromTreeWidegt_qpb);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        check_requirement_qpb2 = new QPushButton(tab_4);
        check_requirement_qpb2->setObjectName(QStringLiteral("check_requirement_qpb2"));

        verticalLayout_3->addWidget(check_requirement_qpb2);


        gridLayout_3->addLayout(verticalLayout_3, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEdit_4 = new QLineEdit(tab_4);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setEnabled(false);

        verticalLayout->addWidget(lineEdit_4);

        funs_qlw = new QListWidget(tab_4);
        funs_qlw->setObjectName(QStringLiteral("funs_qlw"));

        verticalLayout->addWidget(funs_qlw);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_11->addLayout(gridLayout_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        gridLayout_14 = new QGridLayout(tab_5);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        lineEdit = new QLineEdit(tab_5);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(false);

        gridLayout_14->addWidget(lineEdit, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(381, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_14->addItem(horizontalSpacer_4, 0, 1, 1, 1);

        resultOutput_qte2 = new QTextEdit(tab_5);
        resultOutput_qte2->setObjectName(QStringLiteral("resultOutput_qte2"));

        gridLayout_14->addWidget(resultOutput_qte2, 1, 0, 1, 2);

        tabWidget->addTab(tab_5, QString());

        gridLayout_13->addWidget(tabWidget, 0, 0, 1, 1);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        gridLayout_4 = new QGridLayout(page_3);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        headFileProcess_qpb = new QPushButton(page_3);
        headFileProcess_qpb->setObjectName(QStringLiteral("headFileProcess_qpb"));

        gridLayout_4->addWidget(headFileProcess_qpb, 2, 2, 1, 1);

        displayfunsInfo_qpb = new QPushButton(page_3);
        displayfunsInfo_qpb->setObjectName(QStringLiteral("displayfunsInfo_qpb"));

        gridLayout_4->addWidget(displayfunsInfo_qpb, 0, 2, 1, 1);

        headfilespath_qtb = new QTableWidget(page_3);
        if (headfilespath_qtb->columnCount() < 2)
            headfilespath_qtb->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        headfilespath_qtb->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        headfilespath_qtb->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        headfilespath_qtb->setObjectName(QStringLiteral("headfilespath_qtb"));

        gridLayout_4->addWidget(headfilespath_qtb, 1, 0, 1, 3);

        verticalSpacer_5 = new QSpacerItem(548, 96, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_5, 4, 0, 1, 3);

        horizontalSpacer_8 = new QSpacerItem(501, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_8, 2, 0, 1, 2);

        horizontalSpacer_7 = new QSpacerItem(441, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_7, 0, 0, 1, 2);

        addenum_qpb = new QPushButton(page_3);
        addenum_qpb->setObjectName(QStringLiteral("addenum_qpb"));

        gridLayout_4->addWidget(addenum_qpb, 3, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_9, 3, 0, 1, 1);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        gridLayout = new QGridLayout(page_4);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit_7 = new QLineEdit(page_4);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setEnabled(false);

        gridLayout->addWidget(lineEdit_7, 0, 0, 1, 1);

        textEdit_2 = new QTextEdit(page_4);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));

        gridLayout->addWidget(textEdit_2, 1, 0, 1, 1);

        stackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        gridLayout_5 = new QGridLayout(page_5);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        comboBox = new QComboBox(page_5);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_5->addWidget(comboBox, 0, 0, 1, 1);

        textEdit_3 = new QTextEdit(page_5);
        textEdit_3->setObjectName(QStringLiteral("textEdit_3"));

        gridLayout_5->addWidget(textEdit_3, 1, 0, 1, 1);

        stackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QStringLiteral("page_6"));
        gridLayout_6 = new QGridLayout(page_6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        lineEdit_8 = new QLineEdit(page_6);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setEnabled(false);

        gridLayout_6->addWidget(lineEdit_8, 0, 0, 1, 1);

        textEdit_4 = new QTextEdit(page_6);
        textEdit_4->setObjectName(QStringLiteral("textEdit_4"));

        gridLayout_6->addWidget(textEdit_4, 1, 0, 1, 1);

        stackedWidget->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName(QStringLiteral("page_7"));
        gridLayout_8 = new QGridLayout(page_7);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        lineEdit_9 = new QLineEdit(page_7);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));

        gridLayout_8->addWidget(lineEdit_9, 0, 0, 1, 1);

        textEdit_5 = new QTextEdit(page_7);
        textEdit_5->setObjectName(QStringLiteral("textEdit_5"));

        gridLayout_8->addWidget(textEdit_5, 1, 0, 1, 1);

        stackedWidget->addWidget(page_7);
        page_8 = new QWidget();
        page_8->setObjectName(QStringLiteral("page_8"));
        gridLayout_7 = new QGridLayout(page_8);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        lineEdit_10 = new QLineEdit(page_8);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));
        lineEdit_10->setEnabled(false);

        gridLayout_7->addWidget(lineEdit_10, 0, 0, 1, 1);

        textEdit_6 = new QTextEdit(page_8);
        textEdit_6->setObjectName(QStringLiteral("textEdit_6"));

        gridLayout_7->addWidget(textEdit_6, 1, 0, 1, 1);

        stackedWidget->addWidget(page_8);

        gridLayout_15->addWidget(stackedWidget, 0, 1, 2, 1);

        verticalSpacer = new QSpacerItem(20, 106, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_15->addItem(verticalSpacer, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 770, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(3);
        tabWidget_xuqiu_qtw->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        step3_qtb->setText(QApplication::translate("MainWindow", "step3 \346\224\266\351\233\206\346\216\245\345\217\243\344\277\241\346\201\257", 0));
        step7_qtb->setText(QApplication::translate("MainWindow", "step7 \347\224\237\346\210\220\344\273\243\347\240\201\346\226\207\344\273\266", 0));
        step4_qtb->setText(QApplication::translate("MainWindow", "step4 \347\224\237\346\210\220\351\200\232\347\224\250\344\273\243\347\240\201\346\226\207\344\273\266", 0));
        step1_qtb->setText(QApplication::translate("MainWindow", "step1 \346\243\200\346\237\245\351\234\200\346\261\202\350\241\250\346\240\274\350\247\204\350\214\203", 0));
        step5_qtb->setText(QApplication::translate("MainWindow", "step5 \347\224\237\346\210\220xml\346\226\207\344\273\266", 0));
        step6_qtb->setText(QApplication::translate("MainWindow", "step6 \347\224\237\346\210\220\345\220\204\345\255\220\351\241\265\351\235\242\345\244\264\346\226\207\344\273\266", 0));
        prepare_qtb->setText(QApplication::translate("MainWindow", "\345\207\206\345\244\207\345\267\245\344\275\234", 0));
        step8_qtb->setText(QApplication::translate("MainWindow", "step8 \347\224\237\346\210\220\347\225\214\351\235\242\346\226\207\344\273\266", 0));
        step2_qtb->setText(QApplication::translate("MainWindow", "step2 \346\224\266\351\233\206\350\241\250\346\240\274\344\277\241\346\201\257", 0));
        label_2->setText(QApplication::translate("MainWindow", "\351\241\271\347\233\256\345\220\215\357\274\210eg:506\357\274\214301c\357\274\211\357\274\232", 0));
        label_3->setText(QApplication::translate("MainWindow", "\347\273\204\344\273\266\345\220\215(eg:AE,WS)\357\274\232", 0));
        label->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272\344\270\264\346\227\266\346\226\207\344\273\266\345\244\271\357\274\214\345\255\230\346\224\276\347\224\237\346\210\220\347\232\204\344\270\255\351\227\264\345\244\204\347\220\206\346\226\207\344\273\266(\346\226\207\344\273\266\345\244\271\346\240\274\345\274\217\357\274\232temp_\351\241\271\347\233\256\345\220\215+'VT'+\347\273\204\344\273\266\345\220\215)\357\274\232", 0));
        label_4->setText(QApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\345\210\233\345\273\272\346\226\207\344\273\266\345\244\271\347\232\204\344\275\215\347\275\256", 0));
        tempdir_qpb->setText(QApplication::translate("MainWindow", "No.1 \351\200\211\346\213\251", 0));
        createTempDir_qpb->setText(QApplication::translate("MainWindow", "No.2 \345\210\233\345\273\272\346\226\207\344\273\266\345\244\271", 0));
        lineEdit_3->setText(QApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\346\234\254\345\234\260\347\273\204\344\273\266\351\234\200\346\261\202\350\241\250\346\240\274,\350\207\252\345\212\250\346\213\267\350\264\235\345\210\260\344\270\264\346\227\266\346\226\207\344\273\266\345\244\271\344\270\213\357\274\232", 0));
        filebtn_1->setText(QApplication::translate("MainWindow", "No.3 \351\200\211\346\213\251", 0));
        check_requirement_qpb->setText(QApplication::translate("MainWindow", "\346\243\200\346\237\245\351\234\200\346\261\202\350\241\250\346\240\274\350\247\204\350\214\203", 0));
        resultOutput_qte->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        tabWidget_xuqiu_qtw->setTabText(tabWidget_xuqiu_qtw->indexOf(tab_1), QApplication::translate("MainWindow", "\351\234\200\346\261\202\350\241\250\346\240\274\346\243\200\346\237\245\347\273\223\346\236\234", 0));
        requirement_rule_qte->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">\345\205\263\344\272\216\345\215\225\344\275\215\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-style:italic; color:#0b0b0b;\">1\343\200\201</span><span style=\" color:#0b0b0b;\">\345\217\202\346\225\260\345\246\202\346\236\234\346\262\241\346\234\211\345\215\225\344\275\215\357\274\214\345\241\253\345\206\231none,\351\230\262\346\255\242\346\234\211\345\215\225\344\275\215\347\232\204\345"
                        "\217\202\346\225\260\346\274\217\345\241\253</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">2\343\200\201\346\234\211\345\215\225\344\275\215\357\274\214\345\210\244\346\226\255\346\230\257\345\220\246\346\230\257\345\233\275\351\231\205\345\215\225\344\275\215\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">\345\205\263\344\272\216\346\225\260\346\215\256\347\261\273\345\236\213\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">1\343\200\201\344\275\277\347\224\250SMEE\345\206\205\347\275\256\345\215\225\344\275\215\357\274\214SMEE_BOOL,SMEE_FLOAT,SMEE_DOUBLE,...</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-le"
                        "ft:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">\345\205\263\344\272\216\347\262\276\345\272\246\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">1\343\200\201\345\246\202\346\236\234\346\262\241\346\234\211\346\214\207\345\256\232\357\274\214\346\225\264\345\236\213\344\270\2720,\346\265\256\347\202\271\345\236\213\344\270\2726\357\274\214\345\205\266\344\273\226\350\241\245none.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">\345\205\263\344\272\216\346\255\245\351\225\277\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">1\343\200\201\350\276\223\345\205\245\345\217\202\346\225\260\357"
                        "\274\214\346\234\211\350\214\203\345\233\264\357\274\214\346\225\264\345\275\242\344\270\2721\357\274\214\345\205\266\344\273\226\346\240\271\346\215\256\347\262\276\345\272\246\347\241\256\345\256\232\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">\345\205\263\344\272\216\351\273\230\350\256\244\345\200\274\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">1\343\200\201\350\276\223\345\207\272\345\217\202\346\225\260\357\274\214\351\273\230\350\256\244\345\200\274\344\270\200\345\276\213\345\241\253none\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">2\343\200\201\350\276\223\345\205\245\345\217\202\346\225\260\357\274\214"
                        "\346\234\211\345\217\202\346\225\260\350\214\203\345\233\264\347\232\204\357\274\214\346\214\211\345\256\236\351\231\205\351\234\200\346\261\202\345\241\253\345\206\231\343\200\202\346\262\241\346\234\211\350\246\201\346\261\202\347\232\204\357\274\214\344\270\200\345\276\213none\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">3\343\200\201\351\273\230\350\256\244\345\200\274\345\234\250\345\217\202\346\225\260\350\214\203\345\233\264\345\214\272\351\227\264\345\206\205\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">\345\205\263\344\272\216\345\217\202\346\225\260\350\214\203\345\233\264\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" co"
                        "lor:#0b0b0b;\">1\343\200\201\345\217\252\346\234\211\350\276\223\345\205\245\345\217\202\346\225\260\346\211\215\346\234\211\350\214\203\345\233\264\357\274\214\346\262\241\346\234\211\350\214\203\345\233\264\350\241\245none\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">2\343\200\201\350\276\223\345\207\272\350\214\203\345\233\264\357\274\214\350\204\232\346\234\254\344\270\200\345\276\213\350\207\252\345\212\250\350\241\245none\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">\345\205\263\344\272\216\345\217\202\346\225\260\346\240\207\347\255\276\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">1\343\200\201\345\215\225"
                        "\350\257\215\351\246\226\345\255\227\346\257\215\345\244\247\345\206\231\357\274\214\347\251\272\346\240\274\351\232\224\345\274\200\357\274\214\344\270\223\346\234\211\345\220\215\350\257\215\346\214\211\345\256\236\351\231\205\345\241\253\345\206\231\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">\345\205\263\344\272\216\350\241\250\346\240\274\344\271\246\345\206\231\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">1\343\200\201\344\270\215\345\210\260\346\234\200\345\220\216\344\270\200\350\241\214\357\274\214\344\270\215\350\203\275\346\234\211\347\251\272\350\241\214</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#0b0b0b;\">2\343\200\201"
                        "\346\216\245\345\217\243\346\227\240\345\217\202\346\225\260\346\227\266\345\220\214\346\240\267\350\246\201\344\277\235\347\225\231\344\277\241\346\201\257\343\200\202</span></p></body></html>", 0));
        tabWidget_xuqiu_qtw->setTabText(tabWidget_xuqiu_qtw->indexOf(tab_2), QApplication::translate("MainWindow", "\351\234\200\346\261\202\350\241\250\346\240\274\350\247\204\350\214\203\347\272\246\345\256\232", 0));
        lineEdit_5->setText(QApplication::translate("MainWindow", "\346\216\245\345\217\243\345\234\250\347\225\214\351\235\242\345\270\203\345\261\200\344\277\241\346\201\257\345\246\202\344\270\213\357\274\232", 0));
        addOtherPage_qpb->setText(QApplication::translate("MainWindow", "Add Page", 0));
        importToTreeWidegt_qpb->setText(QApplication::translate("MainWindow", ">>>", 0));
        deleteFromTreeWidegt_qpb->setText(QApplication::translate("MainWindow", "<<<", 0));
        check_requirement_qpb2->setText(QApplication::translate("MainWindow", " \346\224\266\351\233\206\351\234\200\346\261\202\350\241\250\346\240\274\344\277\241\346\201\257", 0));
        lineEdit_4->setText(QApplication::translate("MainWindow", "\351\234\200\346\261\202\350\241\250\346\240\274\344\270\255\347\232\204\346\216\245\345\217\243\345\210\227\350\241\250\345\246\202\344\270\213\357\274\232", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "\346\216\245\345\217\243\345\270\203\345\261\200", 0));
        lineEdit->setText(QApplication::translate("MainWindow", "\351\234\200\346\261\202\350\241\250\346\240\274\344\277\241\346\201\257\346\230\276\347\244\272\357\274\232", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "\351\234\200\346\261\202\350\241\250\346\240\274\344\277\241\346\201\257", 0));
        headFileProcess_qpb->setText(QApplication::translate("MainWindow", "\345\244\264\346\226\207\344\273\266\351\242\204\345\244\204\347\220\206", 0));
        displayfunsInfo_qpb->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\345\244\264\346\226\207\344\273\266\345\210\227\350\241\250", 0));
        QTableWidgetItem *___qtablewidgetitem = headfilespath_qtb->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\346\211\200\351\234\200\345\244\264\346\226\207\344\273\266\345\210\227\350\241\250\357\274\232", 0));
        QTableWidgetItem *___qtablewidgetitem1 = headfilespath_qtb->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\345\244\264\346\226\207\344\273\266\346\234\254\345\234\260\350\267\257\345\276\204\357\274\232", 0));
        addenum_qpb->setText(QApplication::translate("MainWindow", "\350\241\245\345\205\205\346\236\232\344\270\276\345\210\260\351\234\200\346\261\202\350\241\250\346\240\274", 0));
        lineEdit_7->setText(QApplication::translate("MainWindow", "\351\200\232\347\224\250\344\273\243\347\240\201\346\226\207\344\273\266\345\210\227\350\241\250\357\274\232", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "excelFunsXml", 0)
         << QApplication::translate("MainWindow", "excelXmlForUi", 0)
        );
        lineEdit_8->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\345\244\264\346\226\207\344\273\266\345\210\227\350\241\250\357\274\232", 0));
        lineEdit_9->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\344\273\243\347\240\201\346\226\207\344\273\266\357\274\232", 0));
        lineEdit_10->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\347\225\214\351\235\242\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
