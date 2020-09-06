#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QColor>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QCloseEvent>
#include <QDateTime>
#include "sourse.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Sourse *sourseWindow = NULL;

    Ui::MainWindow *ui;
    void tableInit(void);
    void addTableItem(int, int, QString, QColor, QColor);
    void readConfigToTable(QString);

private slots:
    void saveTable(void);
    void openSourseWindow(void);
    void openMenu(void);

signals:
    void sendSourseList(QStringList, QString);

};
#endif // MAINWINDOW_H
