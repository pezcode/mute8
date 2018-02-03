#ifndef MUTE8_H
#define MUTE8_H

#include "trayapplication.h"
#include "settingswindow.h"
#include <QMenu>

class Mute8 : public TrayApplication
{
    Q_OBJECT

public:

    static constexpr char NAME[] = "Mute8";
    static constexpr char ORGANIZATION[] = "pezcode";
    static constexpr char VERSION[] = "1.0.0";

    Mute8();
    ~Mute8();

public slots:

    void showSettings();

private:

    SettingsWindow* settingsWindow;
    QMenu* trayMenu;
};

#endif // MUTE8_H
