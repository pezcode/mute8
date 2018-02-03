#include "mute8.h"
#include <QApplication>

Mute8::Mute8() :
    TrayApplication(NAME, QIcon(":/icons/tray.png")),
    settingsWindow(new SettingsWindow()),
    trayMenu(new QMenu())
{
    // QStyle::standardIcon
    QAction* settingsAction = new QAction(tr("&Settings"), this);
    connect(settingsAction, &QAction::triggered, this, &Mute8::showSettings);

    QAction* quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, &QApplication::quit);

    trayMenu->addAction(settingsAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);

    this->tray->setContextMenu(trayMenu);

    this->settingsWindow->setWindowTitle(NAME);
    showSettings();
}

Mute8::~Mute8()
{
    this->tray->setContextMenu(NULL);
    delete this->trayMenu;
    delete this->settingsWindow;
}

void Mute8::showSettings()
{
    this->settingsWindow->show();
}
