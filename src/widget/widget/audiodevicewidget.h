#ifndef AUDIODEVICEWIDGET_H
#define AUDIODEVICEWIDGET_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT AudioDeviceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AudioDeviceWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // AUDIODEVICEWIDGET_H
