#ifndef COURSE_H
#define COURSE_H

#include <QMainWindow>

namespace Ui {
class Course;
}

class Course : public QMainWindow
{
    Q_OBJECT

public:
    explicit Course(QWidget *parent = nullptr);
    ~Course();

private:
    Ui::Course *ui;
};

#endif // COURSE_H
