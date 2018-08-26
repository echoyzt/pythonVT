
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::codecForName("UTF-8");
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("GB18030"));
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    MainWindow w;
    w.show();
    return a.exec();
}
