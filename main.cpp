#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setDesktopSettingsAware(false);
    QFont font("fira code");
    // font.setPointSize(14);
    QApplication::setFont(font);

    QApplication a(argc, argv);
    MainWindow   w;
    w.show();
    return a.exec();
}
