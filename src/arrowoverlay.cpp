#include "arrowoverlay.h"

ArrowOverlay::ArrowOverlay(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setStyleSheet("background-color:transparent;");
}

ArrowOverlay::~ArrowOverlay() {}

void ArrowOverlay::addArrow(const QPointF &start, const QPointF &end, const QColor &color, int thickness)
{
    arrows.append(Arrow(start, end, color, thickness));
    update(); // Request repaint to draw the new arrow
}

void ArrowOverlay::clearArrows()
{
    arrows.clear();
    update(); // Clear the display as well
}

void ArrowOverlay::showArrows()
{
    isVisible = true;
    update();
    show();
}

void ArrowOverlay::hideArrows()
{
    isVisible = false;
    update();
    hide();
}

void ArrowOverlay::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if (!isVisible) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (const auto &arrow : qAsConst(arrows)) {
        QPen pen(arrow.color, arrow.thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawLine(arrow.start, arrow.end);

        // Optionally, you can draw an arrow head here using painter.drawPolygon or similar
    }
}
