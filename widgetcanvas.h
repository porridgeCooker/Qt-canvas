#ifndef WIDGETCANVAS_H
#define WIDGETCANVAS_H

#include <QWidget>
#include "canvas.h"
#include <QDebug>

#include "mouseunittouchwidget.h"
class WidgetCanvas : public MouseUnitTouchWidget, public Canvas
{
    Q_OBJECT
public:
    explicit WidgetCanvas(const QSizeF &size, QWidget *parent = 0);

    void setLineColor(const QColor &color);
    inline QColor lineColor(){return m_color;}
    void setLineWidth(int width);
    inline int lineWidth(){return m_lineWidth;}
    void setErase(bool berase){m_bErase = berase;}
    inline bool isErase(){return m_bErase;}
private:
    void widgetDotPress(int id, const QPointF &pos, const QSizeF &size = QSizeF());
    void widgetDotmove(int id, const QPointF &pos, const QSizeF &size = QSizeF());
    void widgetDotRelease(int id, const QPointF &pos, const QSizeF &size = QSizeF());
protected:
    void updateCanvas();
    void resizeEvent(QResizeEvent *ev);
    void paintEvent(QPaintEvent *);
signals:

private:
    QRectF m_boundingRect;
    struct LineInfo{
        int witdh;
        QColor color;
        int id;
        bool isErase;
        QVector<QPointF> points;
    };
    QMap<int, LineInfo*> m_lineInfos;
    QColor m_color = QColor(Qt::black);
    int m_lineWidth = 3;
    bool m_bErase = false;
private:
    bool createPoint(int id, const QPointF &pos, const QSizeF &size);
    bool freeLine(int id);
};

#endif // WIDGETCANVAS_H
