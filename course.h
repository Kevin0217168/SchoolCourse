#ifndef COURSE_H
#define COURSE_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Course;
}

class Course : public QDialog
{
    Q_OBJECT

public:
    explicit Course(QWidget *parent = nullptr);
    ~Course();

private:
    Ui::Course *ui;
    QList<QList<int>> courseTime;
    int COURSEFONTSIZE = 20;
    int TITLEFONTSIZE = 20;
    void readConifg();

private slots:
    void closeEvent(QCloseEvent *event);
    void courseArrive(QStringList, QString);
    void updateCourse(void);
    void readTime();

signals:
    void closed(void);
};

#endif // Course_H
