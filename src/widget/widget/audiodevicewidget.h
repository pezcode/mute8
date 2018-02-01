#ifndef AUDIODEVICEWIDGET_H
#define AUDIODEVICEWIDGET_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>
#include <QLabel>
#include "levelmeter.h"

class QDESIGNER_WIDGET_EXPORT AudioDeviceWidget : public QWidget
{
    Q_OBJECT

public:

    explicit AudioDeviceWidget(QWidget *parent = nullptr);

public slots:

    void setDeviceName(const QString& name);
    void setAdapterName(const QString& name);
    void peakChanged(qreal peak);

private:

    LevelMeter* meterWidget;
    QLabel* deviceLabel;
    QLabel* adapterLabel;
};

#endif // AUDIODEVICEWIDGET_H
