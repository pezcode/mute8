#include "mute8.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication::setApplicationName(Mute8::NAME);
    QApplication::setOrganizationName(Mute8::ORGANIZATION);
    QApplication::setApplicationVersion(Mute8::VERSION);

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

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
