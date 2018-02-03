#ifndef TRAYAPPLICATION_H
#define TRAYAPPLICATION_H

#include <QObject>
#include <QSystemTrayIcon>

class TrayApplication : public QObject
{
    Q_OBJECT

public:

    explicit TrayApplication(const QString& name, const QIcon& icon, QObject *parent = nullptr);

public slots:

    void show();
    void hide();

    QIcon icon() const;
    void setIcon(const QIcon& icon);

protected:
    QSystemTrayIcon* tray;
};

#endif // TRAYAPPLICATION_H
