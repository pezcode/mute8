#ifndef MUTE8_H
#define MUTE8_H

#include "trayapplication.h"
#include "settingswindow.h"
#include <QMenu>

class Mute8 : public TrayApplication
{
public:

    Mute8();
    ~Mute8();

public slots:

    void showSettings();

private:

    SettingsWindow* settingsWindow;
    QMenu* trayMenu;
};

#endif // MUTE8_H
