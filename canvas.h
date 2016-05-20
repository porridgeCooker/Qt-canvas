#ifndef CANVAS_H
#define CANVAS_H
#include <QObject>
#include <QGraphicsObject>
#include <QPainter>

/**
 * @brief The Canvas class
 * 建立这个类的目的是为了兼容QGraphics与QWidget的双缓冲截图方式，需要多继承，继承Canvas 与QGraphicsItem 或 QWidget实现两种模式
 *
 */
class Canvas
{
public:
    Canvas(const QSizeF &size);
    ~Canvas();

    void setDrawColor(const QColor &color);
    void drawLine(const QPointF &p1, const QPointF &p2, int witdh = 3, QColor color = QColor());
    void drawDot(const QPointF &p, int witdh = 3, QColor color = QColor());

    void eraseLine(const QPointF &p1, const QPointF &p2, int witdh);
    void eraseDot(const QPointF &p, int witdh);

    void reset(const QSizeF &size, QImage image = QImage());
    QImage backgroundImage()const{return m_backgroundImage;}
    bool isChange(){return m_bChange;}
protected:
    /**
     * @brief updateCanvas
     * 需要重载实现刷新
     */
    virtual void updateCanvas();
    QImage m_backgroundImage;
private:
    QSizeF m_size;
    QColor m_penColor;

    QPainter *m_painter = 0;
    QPointF m_erasePointF;
    bool m_bChange;
private:
    void drawErasePoint(QPainter *painter, const QPointF &point, int width);
    void paintLine(const QPointF &p1, const QPointF &p2, int witdh = 3, QColor color = QColor());
    void paintDot(const QPointF &p, int witdh = 3, QColor color = QColor());
};

#endif // CANVAS_H
