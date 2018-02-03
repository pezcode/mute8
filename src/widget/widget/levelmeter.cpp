#include "levelmeter.h"

#include <QPainter>
#include <QTimer>
#include <QStylePainter>
#include <QStyleOptionFrame>
#include <QApplication>

const int RedrawInterval = 50; // ms
const qreal PeakDecayRate = 0.001;
const int PeakHoldLevelDuration = 2000; // ms

LevelMeter::LevelMeter(QWidget *parent)
    :   QWidget(parent)
    ,   m_rmsLevel(0.0)
    ,   m_peakLevel(0.0)
    ,   m_decayedPeakLevel(0.0)
    ,   m_peakDecayRate(PeakDecayRate)
    ,   m_peakHoldLevel(0.0)
    ,   m_redrawTimer(new QTimer(this))
    ,   m_rmsColor(Qt::red)
    ,   m_peakColor(255, 200, 200, 255)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    // TODO: DPI aware sizes?
    // so apps without Qt::AA_EnableHighDpiScaling still work
    // e.g. pick font point size so min height the size of a point 12 row of text
    // QWidget::logicalDpiX etc.

    // not really needed with sizehint
    setMinimumSize(QSize(10, 10));

    // DPI aware icons
    // Icon::addFile with @2x format, gives us Pixmaps with higher device DPI ratio

    connect(m_redrawTimer, &QTimer::timeout, this, &LevelMeter::redrawTimerExpired);
    m_redrawTimer->start(RedrawInterval);
}

QSize LevelMeter::sizeHint() const
{
    return QSize(15, 25);
}

void LevelMeter::reset()
{
    m_rmsLevel = 0.0;
    m_peakLevel = 0.0;
    update();
}

void LevelMeter::levelChanged(qreal rmsLevel, qreal peakLevel, int numSamples)
{
    // Smooth the RMS signal
    const qreal smooth = pow(qreal(0.9), static_cast<qreal>(numSamples) / 256); // TODO: remove this magic number
    m_rmsLevel = (m_rmsLevel * smooth) + (rmsLevel * (1.0 - smooth));

    if (peakLevel > m_decayedPeakLevel) {
        m_peakLevel = peakLevel;
        m_decayedPeakLevel = peakLevel;
        m_peakLevelChanged.start();
    }

    if (peakLevel > m_peakHoldLevel) {
        m_peakHoldLevel = peakLevel;
        m_peakHoldLevelChanged.start();
    }

    update();
}

void LevelMeter::redrawTimerExpired()
{
    // Decay the peak signal
    const int elapsedMs = m_peakLevelChanged.elapsed();
    const qreal decayAmount = m_peakDecayRate * elapsedMs;
    if (decayAmount < m_peakLevel)
        m_decayedPeakLevel = m_peakLevel - decayAmount;
    else
        m_decayedPeakLevel = 0.0;

    // Check whether to clear the peak hold level
    if (m_peakHoldLevelChanged.elapsed() > PeakHoldLevelDuration)
        m_peakHoldLevel = 0.0;

    update();
}

void LevelMeter::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStylePainter stylePainter(this);

    QStyleOptionFrame frameOptions;
    frameOptions.initFrom(this);
    stylePainter.drawPrimitive(QStyle::PE_Frame, frameOptions);

    /*
    // TODO shrink rect
    QStyleOptionProgressBar barOptions;
    barOptions.initFrom(this);
    barOptions.orientation = Qt::Vertical;
    barOptions.minimum = 0;
    barOptions.maximum = 100;
    barOptions.progress = static_cast<int>(m_peakLevel * 100.0);
    stylePainter.drawControl(QStyle::CE_ProgressBarContents, barOptions);
    */

    QPalette palette = QApplication::palette();
    QPalette::ColorGroup group = isEnabled() ? QPalette::Normal : QPalette::Disabled;
    QColor barColor = palette.color(group, QPalette::Highlight);

    QPainter painter(this);

    QStyle* style = QApplication::style();
    int margin = 2 * style->pixelMetric(QStyle::PM_DefaultFrameWidth);
    //int chunk = style->pixelMetric(QStyle::PM_ProgressBarChunkWidth);

    QRect bar = rect().marginsRemoved(QMargins(margin, margin, margin, margin));
    bar.setTop(bar.top() + (1.0 - m_peakLevel) * bar.height());
    painter.fillRect(bar, barColor);
}
