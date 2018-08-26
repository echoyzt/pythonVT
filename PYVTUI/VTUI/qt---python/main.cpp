
#include "mainwindow.h"
#include <Python.h>
#include <QApplication>
#include <QDebug>
//#include <Python.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Py_SetPythonHome((wchar_t*)(L"C:\\Users\\Administrator\\AppData\\Local\\Programs\\Python\\Python36"));
    //进行初始化
    Py_Initialize();
    //如果初始化失败，返回
    if(!Py_IsInitialized())
    {
       qDebug()<<"python 初始化失败.";
       return a.exec();
    }
    //加载模块，模块名称为myModule，就是myModule.py文件
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    PyObject *pModule = PyImport_ImportModule("createdir");
    //如果加载失败，则返回
    if(!pModule)
    {
        qDebug()<<"load createdir failure. ";
        return a.exec();
    }
    //加载函数greatFunc
    PyObject * pFunc1 = PyObject_GetAttrString(pModule, "createdir1");
    //如果失败则返回
    if(!pFunc1)
    {
        qDebug()<<"call fun createdir failure.";
        return a.exec();
    }
    //调用函数
    PyObject_CallFunction(pFunc1, NULL);
    //退出
    Py_Finalize();
    MainWindow w;
    w.show();
    return a.exec();
}
