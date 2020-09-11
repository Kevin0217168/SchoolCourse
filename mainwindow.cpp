#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 表格初始化
    tableInit();
    // 读取课程数据到表格
    readConfigToTable("CourseConfig.ini");

    // 绑定保存配置按钮事件
    connect(ui->saveBtn, SIGNAL(clicked()), this, SLOT(saveTable()));
    // 绑定今日课程事件
    connect(ui->viewBtn, SIGNAL(clicked()), this, SLOT(openCourseWindow()));
}

// 析构函数
MainWindow::~MainWindow()
{
    delete ui;
}

// 初始化表格
void MainWindow::tableInit(void){
    //设置行数为10
    ui->courseTable->setRowCount(12);
    //设置列数为10
    ui->courseTable->setColumnCount(5);

    //设置表格标题
    QStringList rowTitles;
    rowTitles << "周一" << "周二" << "周三" << "周四" << "周五";
    // 设置行标题
    ui->courseTable->setHorizontalHeaderLabels(rowTitles);

    QStringList colTitles;
    colTitles << "早读" << "1" << "2" << "3" << "4" << "5" << "中午" << "6" << "7" << "8" << "9" << "10";
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
    // 以只读模式打开配置文件
    QFile file(filename);
    if (!file.open(QFileDevice::ReadOnly | QIODevice::Text))
        // 打开失败，弹出提示框
        QMessageBox::critical(this, "崩溃！", "程序已无法运行！\n原因：读取课程配置失败\n文件名为：\""+filename+"\"");
        this->close();

    QTextStream out(&file);
    out.setCodec("UTF-8");

    for (int row = 0; row < 12; row++){
        for (int col = 0; col < 5; col++){
            QString str;
            //读取空格就会结束
            out >> str;
            if (str == "#"){
                addTableItem(row, col, "");
            }else{
                addTableItem(row, col, str);
            }
            ui->courseTable->item(row, col)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
}

////////////////////////////// SLOT /////////////////////////////////

// 保存表格配置
void MainWindow::saveTable(void){
    QFile file("CourseConfig.ini");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out.setCodec("UTF-8");
    for (int row = 0; row < 12; row++){
        for (int col = 0; col < 5; col++){
            // 取出字符串并写入文件
            if(ui->courseTable->item(row, col)->text() == ""){
                out << "#";
            }else{
                out << ui->courseTable->item(row, col)->text();
            }
            // 用空格分隔
            out << " ";
        }
        // 换行
        out << "\n";
    }
    file.close();
}

// 外部打开课程表
void MainWindow::openCourseWindow(){
    // 判断实例是否创建过
    if (CourseWindow == NULL){
        // 新创建一个实例
        CourseWindow = new Course;
        // 绑定当弹窗关闭的时候，弹出主窗口
        connect(CourseWindow, SIGNAL(closed()), this, SLOT(openMenu()));
        connect(this, SIGNAL(sendCourseList(QStringList, QString)),
                CourseWindow, SLOT(courseArrive(QStringList, QString)));
    }
    // 展示弹窗
    CourseWindow->show();
    // 主窗口隐藏
    this->hide();

    // 获取当前日期
    QDateTime current_date_time = QDateTime::currentDateTime();
    // 转换为‘周一’..的形式
    QString current_week = current_date_time.toString("ddd");
    // 判断要选取的列数
    int col;
    if (current_week == "周一"){
        col = 0;
    }else if (current_week == "周二"){
        col = 1;
    }else if (current_week == "周三"){
        col = 2;
    }else if (current_week == "周四"){
        col = 3;
    }else if (current_week == "周五"){
        col = 4;
    }else{
        col = 0;
    }
    // 读取课程名称
    QStringList courseList;
    for (int row = 0; row < 12; row++){
        courseList << ui->courseTable->item(row, col)->text();
    }
    // 给弹窗发送今日课程信息
    emit sendCourseList(courseList, current_week);

}

// 当弹窗关闭时打开主菜单
void MainWindow::openMenu(void){
    // 展示主菜单
    this->show();
    // 销毁今日课程窗口
    delete CourseWindow;
    // 指针置为NULL
    CourseWindow = NULL;
}

