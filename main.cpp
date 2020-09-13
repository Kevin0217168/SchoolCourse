#include "mainwindow.h"
#include <QApplication>
#include <QtSingleApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QtSingleApplication app(argc, argv);
    if (app.isRunning())
    {
        QMessageBox::information(NULL, "课程表",
                                 "您已有一个程序在运行 ...",
                         QMessageBox::Ok);
        app.sendMessage("raise_window_noop");
        return EXIT_SUCCESS;
    }

    MainWindow w;
//    w.show();

    return app.exec();
}
