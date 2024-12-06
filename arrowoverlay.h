#ifndef ARROWOVERLAY_H
#define ARROWOVERLAY_H

#include <QWidget>
#include <QVector>
#include <QPointF>
#include <QPainter>

class Arrow {
public:
    QPointF start;
    QPointF end;
    QColor color;
    int thickness;

    Arrow(const QPointF &start, const QPointF &end, const QColor &color = Qt::black, int thickness = 2)
        : start(start), end(end), color(color), thickness(thickness) {}
};

class ArrowOverlay : public QWidget {
    Q_OBJECT
public:
    explicit ArrowOverlay(QWidget *parent = nullptr);
    ~ArrowOverlay();

    void addArrow(const QPointF &start, const QPointF &end, const QColor &color = Qt::black, int thickness = 2);
    void clearArrows();
    void showArrows();
    void hideArrows();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<Arrow> arrows;
    bool isVisible = true;
};

#endif // ARROWOVERLAY_H
