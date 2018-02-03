#include "trayapplication.h"
#include <QMessageBox>
#include <QApplication>

TrayApplication::TrayApplication(const QString& name, const QIcon& icon, QObject *parent) :
    QObject(parent),
    tray(new QSystemTrayIcon(icon, this))
{
    Q_ASSERT(!name.isEmpty());
    Q_ASSERT(!icon.isNull());

    if(!QSystemTrayIcon::isSystemTrayAvailable())
    {
        // TODO show settings window to let user choose a hotkey to open the settings window
        // stay in background
        QMessageBox::critical(NULL, name, "Tray icon not supported");
        QApplication::quit();
    }
    QApplication::setQuitOnLastWindowClosed(false);
    this->tray->setToolTip(name);
}

void TrayApplication::show()
{
    this->tray->show();
}

void TrayApplication::hide()
{
    this->tray->hide();
}

QIcon TrayApplication::icon() const
{
    return this->tray->icon();
}

void TrayApplication::setIcon(const QIcon& icon)
{
    Q_ASSERT(!icon.isNull());
    this->tray->setIcon(icon);
}
