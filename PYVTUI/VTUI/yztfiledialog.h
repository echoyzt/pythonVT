#ifndef YZTFILEDIALOG_H
#define YZTFILEDIALOG_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QButtonGroup>
#include <QMessageBox>
namespace Ui {
class yztFileDialog;
}

class yztFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit yztFileDialog(QWidget *parent = 0);
    ~yztFileDialog();
    QString m_tempdir;
    void openFileDialog(bool xx4a,bool xx4t,QString tempdir);
    QButtonGroup* fileButtons;
public slots:
   void slot_copyHeaderFileToTempDir();
   void FileButtonClickedSlot(int);

private:
    Ui::yztFileDialog *ui;
};

#endif // YZTFILEDIALOG_H
