#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tableInit();
    readConfigToTable("sourseConfig.ini");

    connect(ui->saveBtn, SIGNAL(clicked()), this, SLOT(saveTable()));
}

// 析构函数
MainWindow::~MainWindow()
{
    delete ui;
}

// 初始化表格
void MainWindow::tableInit(void){
    //设置行数为10
    ui->courseTable->setRowCount(11);
    //设置列数为10
    ui->courseTable->setColumnCount(5);

    //设置表格标题
    QStringList rowTitles;
    rowTitles << "周一" << "周二" << "周三" << "周四" << "周五";
    // 设置行标题
    ui->courseTable->setHorizontalHeaderLabels(rowTitles);

    QStringList colTitles;
    rowTitles << "早读" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10";
    // 设置列标题
    ui->courseTable->setVerticalHeaderLabels(colTitles);

    //双击后可修改
    ui->courseTable->setEditTriggers(QAbstractItemView::DoubleClicked);
}

// 添加表格对象
void MainWindow::addTableItem(int x, int y, QString text,
            QColor color=QColor(0 ,0 ,0), QColor bgcolor=QColor(255 ,255 ,255)){

    //创建一个QTableWidgetItem对象
    QTableWidgetItem *aItem;
    aItem = new QTableWidgetItem(text);
    //设置字体
    aItem->setFont(QFont("微软雅黑"));
    //设置文字颜色
    aItem->setForeground(color);
    //设置背景颜色
    aItem->setBackground(bgcolor);
    //设置显示内容
    ui->courseTable->setItem(x, y, aItem);
}

// 读取课程表文件到表格中
void MainWindow::readConfigToTable(QString filename){
    QFile file(filename);
    if (!file.open(QFileDevice::ReadOnly))
        return;

    QTextStream(out);
    for (int row = 0; row < 5; row++){
        for (int col = 0; col < 10; col++){
            QString str;
            //读取空格就会结束
            out >> str;
            qDebug() << str;
            if (str == "#"){
                addTableItem(row, col, "");
            }else{
                addTableItem(row, col, str);
            }
        }
    }
}

////////////////////////////// SLOT /////////////////////////////////

// 保存表格配置
void MainWindow::saveTable(void){
    QFile file("sourseConfig.ini");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (int row = 0; row < 5; row++){
        for (int col = 0; col < 10; col++){
            // 取出字符串并写入文件
            if(ui->courseTable->item(row , col)==0){
                out << "#";
            }else{
                out << QString(ui->courseTable->item(row, col)->text());
            }
            // 用空格分隔
            out << " ";
        }
        // 换行
        out << "\n";
    }
    file.close();
}
