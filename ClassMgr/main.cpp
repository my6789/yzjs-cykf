#include "ClassMgr.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClassMgr w;
    w.show();
    return a.exec();
}
