#include "mute8.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mute8 mute8;
    mute8.show();

    return a.exec();
}
