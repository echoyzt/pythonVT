/********************************************************************************
** Form generated from reading UI file 'yztfiledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YZTFILEDIALOG_H
#define UI_YZTFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_yztFileDialog
{
public:
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QLineEdit *xx4a_qle;
    QPushButton *xx4a_qpb;
    QLineEdit *xx4t_qle;
    QPushButton *xx4t_qpb;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QPushButton *copyToTempDir_qpb;

    void setupUi(QDialog *yztFileDialog)
    {
        if (yztFileDialog->objectName().isEmpty())
            yztFileDialog->setObjectName(QStringLiteral("yztFileDialog"));
        yztFileDialog->resize(400, 213);
        gridLayout = new QGridLayout(yztFileDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit = new QLineEdit(yztFileDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(false);

        gridLayout->addWidget(lineEdit, 0, 0, 1, 1);

        xx4a_qle = new QLineEdit(yztFileDialog);
        xx4a_qle->setObjectName(QStringLiteral("xx4a_qle"));

        gridLayout->addWidget(xx4a_qle, 1, 0, 1, 2);

        xx4a_qpb = new QPushButton(yztFileDialog);
        xx4a_qpb->setObjectName(QStringLiteral("xx4a_qpb"));

        gridLayout->addWidget(xx4a_qpb, 1, 2, 1, 1);

        xx4t_qle = new QLineEdit(yztFileDialog);
        xx4t_qle->setObjectName(QStringLiteral("xx4t_qle"));

        gridLayout->addWidget(xx4t_qle, 2, 0, 1, 2);

        xx4t_qpb = new QPushButton(yztFileDialog);
        xx4t_qpb->setObjectName(QStringLiteral("xx4t_qpb"));

        gridLayout->addWidget(xx4t_qpb, 2, 2, 1, 1);

        verticalSpacer = new QSpacerItem(338, 79, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(263, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 0, 1, 1);

        copyToTempDir_qpb = new QPushButton(yztFileDialog);
        copyToTempDir_qpb->setObjectName(QStringLiteral("copyToTempDir_qpb"));

        gridLayout->addWidget(copyToTempDir_qpb, 4, 2, 1, 1);


        retranslateUi(yztFileDialog);

        QMetaObject::connectSlotsByName(yztFileDialog);
    } // setupUi

    void retranslateUi(QDialog *yztFileDialog)
    {
        yztFileDialog->setWindowTitle(QApplication::translate("yztFileDialog", "Dialog", 0));
        lineEdit->setText(QApplication::translate("yztFileDialog", "\346\216\245\345\217\243\345\244\264\346\226\207\344\273\266\344\275\215\347\275\256\357\274\232", 0));
        xx4a_qpb->setText(QApplication::translate("yztFileDialog", "XX4A", 0));
        xx4t_qpb->setText(QApplication::translate("yztFileDialog", "XX4T", 0));
        copyToTempDir_qpb->setText(QApplication::translate("yztFileDialog", "\346\213\267\350\264\235\345\210\260\344\270\264\346\227\266\346\226\207\344\273\266\345\244\271", 0));
    } // retranslateUi

};

namespace Ui {
    class yztFileDialog: public Ui_yztFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YZTFILEDIALOG_H
