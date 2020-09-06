#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QColor>
#include <QDebug>
#include <QFile>
#include <QString>


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
    Ui::MainWindow *ui;
    void tableInit(void);
    void addTableItem(int, int, QString, QColor, QColor);
    void readConfigToTable(QString);

private slots:
    void saveTable(void);

};
#endif // MAINWINDOW_H
