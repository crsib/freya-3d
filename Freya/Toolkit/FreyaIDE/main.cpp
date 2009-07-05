#include <QtGui>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Freya 3D team");
    a.setApplicationName("FreyaIDE");
    a.setApplicationVersion("pre-commit");
    MainWindow w;
    w.show();
    return a.exec();
}
