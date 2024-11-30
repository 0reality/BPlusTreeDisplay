#ifndef ARROWS_H
#define ARROWS_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QVector>
#include <QtMath>

class ArrowOverlay : public QWidget {
    Q_OBJECT
public:
    explicit ArrowOverlay(QWidget *parent = nullptr)
        : QWidget(parent), arrows() {
        setAttribute(Qt::WA_TransparentForMouseEvents); // 忽略鼠标事件
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        setAttribute(Qt::WA_TranslucentBackground);
    }

    void addArrow(const QPoint &start, const QPoint &end);

    bool removeArrow(int index);

    void clearArrows();

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        for (const auto &data : arrows) {
            if (!data.show) continue;

            qreal angle = atan2(data.end.y() - data.start.y(),
                                data.end.x() - data.start.x());
            qreal arrowSize = 20; // 箭头大小可以调整

            QPointF p1 = data.end - QPointF(sin(angle + M_PI / 3) * arrowSize,
                                            cos(angle + M_PI / 3) * arrowSize);
            QPointF p2 = data.end - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                            cos(angle + M_PI - M_PI / 3) * arrowSize);

            QPolygonF arrowHead;
            arrowHead << data.end << p1 << p2;

            painter.setPen(Qt::black);
            painter.setBrush(Qt::black);

            painter.drawLine(data.start, data.end);
            painter.drawPolygon(arrowHead);
        }
    }

private:
    struct ArrowData {
        QPoint start;
        QPoint end;
        bool show;
        ArrowData(const QPoint &s, const QPoint &e, bool sh) : start(s), end(e), show(sh) {}
    };

    QVector<ArrowData> arrows;
};


#endif // ARROWS_H
