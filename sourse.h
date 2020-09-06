#ifndef SOURSE_H
#define SOURSE_H

#include <QDialog>

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
};

#endif // SOURSE_H
