#include "main_window.h"
#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    controller ctl;
    ctl.init_game(":/mapres/map/map1.txt");
    return a.exec();
}
