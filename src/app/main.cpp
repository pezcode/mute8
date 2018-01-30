#include "mute8.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    if(translator.load(QLocale(), "mute8", "_", "translations", ".qm"))
    {
        a.installTranslator(&translator);
    }
    Mute8 mute8;
    mute8.show();
    return a.exec();
}
