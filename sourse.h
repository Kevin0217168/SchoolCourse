#ifndef SOURSE_H
#define SOURSE_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Sourse;
}

class Sourse : public QDialog
{
    Q_OBJECT

public:
    explicit Sourse(QWidget *parent = nullptr);
    ~Sourse();

private:
    Ui::Sourse *ui;
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

#endif // SOURSE_H
