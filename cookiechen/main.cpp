#include <QApplication>
#include "mainwindow.h"
#include "class_handler.h"
#include "class_log.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Log log("../test.log");
    Handler handler(&log);
    MainWindow w(&handler);
    w.show();
    return a.exec();
}
