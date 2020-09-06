#include "sourse.h"
#include "ui_sourse.h"

Sourse::Sourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sourse)
{
    ui->setupUi(this);
    readConifg();
    readTime();

    QTimer *timer = new QTimer(this); //this 为parent类, 表示当前窗口

    connect(timer, SIGNAL(timeout()), this, SLOT(updateCourse())); // SLOT填入一个槽函数
    // 每三十秒检查一次
    timer->start(1000);
}

Sourse::~Sourse()
{
    delete ui;
}

void Sourse::readConifg(){
    QFile file("dilagConfig.ini");

    if (!file.open(QFileDevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out.setCodec("UTF-8");

    out >> COURSEFONTSIZE;
    out >> TITLEFONTSIZE;

}


void Sourse::closeEvent(QCloseEvent *event)
{
    emit closed();
}

// 接收课程信息
void Sourse::courseArrive(QStringList sourseList, QString week){
    ui->listWidget->setFont(QFont("微软雅黑", COURSEFONTSIZE));
    ui->week_l->setText(week);
    ui->week_l->setFont(QFont("微软雅黑", TITLEFONTSIZE));
    ui->nowTime->setFont(QFont("微软雅黑", TITLEFONTSIZE));
    for (int i = 0; i < 12; i++){
        ui->listWidget->insertItem(i, tr(sourseList.at(i).toUtf8().data()));
        ui->listWidget->item(i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }

}

void Sourse::readTime(){
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
int lastclass = -1;
void Sourse::updateCourse(){
    QTime current_time = QTime::currentTime();
    int hour = current_time.hour();//当前的小时
    int minute = current_time.minute();//当前的分

//    minute += 1;
//    if (minute > 59){
//        hour+=1;
//        minute = 0;
//    }

    ui->nowTime->setText(QString::number(hour)+":"+QString::number(minute));
    int onclass = 0;
    for (int y = 0; y < courseTime.length(); y+=2){
        int onclasstime = courseTime.at(y).at(0)*60 + courseTime.at(y).at(1);
        int offclasstime = courseTime.at(y+1).at(0)*60 + courseTime.at(y+1).at(1);
        int nowtime = hour*60 + minute;
        if(nowtime > onclasstime && nowtime < offclasstime){
            ui->listWidget->item(y/2)->setBackground(QColor(255, 127, 39));
            lastclass = y/2;
            onclass = 1;
            break;
        }
    }
    if (onclass == 0 && lastclass != -1){
        ui->listWidget->item(lastclass)->setBackground(QColor(255, 255, 255));
    }
}


