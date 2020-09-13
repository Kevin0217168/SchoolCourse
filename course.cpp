#include "course.h"
#include "ui_course.h"

Course::Course(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Course)
{
    ui->setupUi(this);
    initPos();

    // 不在任务栏显示图标
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);
    // 读取今日课程配置
    readConifg();
    // 读取课程时间信息
    readTime();
    // 创建定时器
    QTimer *timer = new QTimer(this); //this 为parent类, 表示当前窗口

    connect(timer, SIGNAL(timeout()), this, SLOT(updateCourse())); // SLOT填入一个槽函数
    // 每1秒更新一次时间
    timer->start(1000);
}

void Course::initPos(){
    QFile file("CourseWindowConfig.ini");

    if (!file.open(QFileDevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out.setCodec("UTF-8");

    int X, Y, WIDTH, HEIGHT;
    // 第一行为窗口位置
    out >> X >> Y;
    // 第二行为窗口大小
    out >> WIDTH >> HEIGHT;

    // 设置窗口位置
    move(X, Y);
    // 设置窗口大小
    resize(WIDTH,HEIGHT);

    setWindowOpacity(0.7);

}

Course::~Course()
{
    delete ui;
}

void Course::readConifg(){
    QFile file("dilagConfig.ini");

    if (!file.open(QFileDevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out.setCodec("UTF-8");

    // 第一行为正文字体大小
    out >> COURSEFONTSIZE;
    // 第二行为标题字体大小
    out >> TITLEFONTSIZE;
}


void Course::closeEvent(QCloseEvent *event)
{
    QFile file("CourseWindowConfig.ini");

    if (!file.open(QFileDevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out.setCodec("UTF-8");

    out << x() << " " << y() << "\n";
    out << width() << " " << height() << "\n";

    file.close();

    emit closed();
}

// 接收课程信息
void Course::courseArrive(QStringList CourseList, QString week){
    ui->listWidget->setFont(QFont("微软雅黑", COURSEFONTSIZE));
    // 填充标题星期
    ui->week_l->setText(week);
    ui->week_l->setFont(QFont("微软雅黑", TITLEFONTSIZE));
    ui->nowTime->setFont(QFont("微软雅黑", TITLEFONTSIZE));
    // 循环填入今日课程
    for (int i = 0; i < 12; i++){
        ui->listWidget->insertItem(i, tr(CourseList.at(i).toUtf8().data()));
        ui->listWidget->item(i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }

}

void Course::readTime(){
//    courseTime = new QList<QList<int>>;
    QFile file("time.ini");
    if (!file.open(QFileDevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out.setCodec("UTF-8");

    for (int i = 0; i < 22; i++){
        QString str;
        out >> str;
        QStringList timeList = str.split(":");
        QList<int> l;
        l << timeList.at(0).toInt() << timeList.at(1).toInt();
        courseTime.append(l);
    }
}

//int hour = 7, minute = 0;
// 设置全局变量，保存上一次的课程
int lastclass = -1;
// 更新课程高亮
void Course::updateCourse(){
    // 获取时间对象
    QTime current_time = QTime::currentTime();
    int hour = current_time.hour();//当前的小时
    int minute = current_time.minute();//当前的分

//    minute += 1;
//    if (minute > 59){
//        hour+=1;
//        minute = 0;
//    }

    // 填充标题时间
    ui->nowTime->setText(QString::number(hour)+":"+QString::number(minute));
    // 设置上课标志位为未上课
    int onclass = 0;
    // 遍历每一行的课程时间
    for (int y = 0; y < courseTime.length(); y+=2){
        // 将课程开始时间转换为秒
        int onclasstime = courseTime.at(y).at(0)*60 + courseTime.at(y).at(1);
        // 将课程结束时间时间转换为秒
        int offclasstime = courseTime.at(y+1).at(0)*60 + courseTime.at(y+1).at(1);
        // 将现在时间转换为秒
        int nowtime = hour*60 + minute;
        // 判断当前时间要大于上课时间且小于下课时间即为正在上课
        if(nowtime > onclasstime && nowtime < offclasstime){
            // 将此格子高亮
            ui->listWidget->item(y/2)->setBackground(QColor(255, 127, 39));
            // 设置此节课的坐标保存
            lastclass = y/2;
            // 设置上课标志位为上课
            onclass = 1;
            // 跳出
            break;
        }
    }
    // 判断没有在上课，并且已经上过一节课
    if (onclass == 0 && lastclass != -1){
        // 将上一节课的高亮取消
        ui->listWidget->item(lastclass)->setBackground(QColor(255, 255, 255));
    }
}


