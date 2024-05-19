#ifndef MYTABLEWIDGETITEM_H
#define MYTABLEWIDGETITEM_H

#include <QTableWidgetItem>
#include <packdef.h>
#include <QTimer>
#include <QLabel>
#include <QDir>
#include <QVBoxLayout>

class MainWindow;
class MyTableWidgetItem : public QTableWidgetItem
{
public:
    MyTableWidgetItem();
public slots:
    void slot_setInfo(FileInfo & info);

private:
    FileInfo m_info;
    friend class MainWindow;
};

#endif // MYTABLEWIDGETITEM_H
