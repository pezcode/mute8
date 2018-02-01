#include "audiodevicewidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

AudioDeviceWidget::AudioDeviceWidget(QWidget *parent) : QWidget(parent)
{
    this->meterWidget = new LevelMeter(this);

    this->deviceLabel = new QLabel(this);
    this->adapterLabel = new QLabel(this);

    QFont boldFont = this->deviceLabel->font();
    boldFont.setWeight(QFont::Medium);
    boldFont.setPointSize(boldFont.pointSize() + 1);
    this->deviceLabel->setFont(boldFont);

    this->adapterLabel->setDisabled(true);
    // QLabel seems to ignore color groups
    /*
    QPalette pal(this->adapterLabel->palette());
    pal.setCurrentColorGroup(QPalette::Disabled);
    this->adapterLabel->setPalette(pal);
    */

    QVBoxLayout* textLayout = new QVBoxLayout;
    textLayout->addWidget(deviceLabel);
    textLayout->addWidget(adapterLabel);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(meterWidget);
    layout->addLayout(textLayout);

    //layout->insertStretch(-1);
    this->setLayout(layout);

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
}

void AudioDeviceWidget::setDeviceName(const QString& name)
{
    this->deviceLabel->setText(name);
}

void AudioDeviceWidget::setAdapterName(const QString& name)
{
    this->adapterLabel->setText(name);
}

void AudioDeviceWidget::peakChanged(qreal peak)
{
    this->meterWidget->levelChanged(peak, peak, 100);
}
