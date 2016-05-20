#include "canvas.h"

Canvas::Canvas(const QSizeF &size)
{
    reset(size);
}

Canvas::~Canvas()
{
    if(m_painter){
        delete m_painter;
        m_painter = 0;
    }
}

void Canvas::setDrawColor(const QColor &color)
{
    m_penColor = color;
}

void Canvas::drawLine(const QPointF &p1, const QPointF &p2, int witdh, QColor color)
{
    m_bChange = true;
    if(!color.isValid())
        color = m_penColor;
    m_painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    paintLine(p1, p2, witdh, color);
}

void Canvas::drawDot(const QPointF &p, int witdh, QColor color)
{
    m_bChange = true;
    if(!color.isValid())
        color = m_penColor;
    m_painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    paintDot(p, witdh, color);
}

void Canvas::eraseLine(const QPointF &p1, const QPointF &p2, int witdh)
{
    m_painter->setCompositionMode(QPainter::CompositionMode_Clear);
    paintLine(p1, p2, witdh);
}

void Canvas::eraseDot(const QPointF &p, int witdh)
{
    m_painter->setCompositionMode(QPainter::CompositionMode_Clear);
    paintDot(p, witdh);
    m_erasePointF = p;
}

void Canvas::reset(const QSizeF &size, QImage image)
{
    m_size = size;
    if(m_painter){
        delete m_painter;
        m_painter = 0;
    }
    m_bChange = false;
    if(image.isNull()){
        m_backgroundImage = QImage(m_size.toSize(), QImage::Format_ARGB32_Premultiplied);
        m_backgroundImage.fill(Qt::transparent);
    }else{
        m_backgroundImage = image;
    }
    m_painter = new QPainter(&m_backgroundImage);
   // m_painter->setRenderHints(QPainter::Antialiasing);
    updateCanvas();
}

void Canvas::updateCanvas(){

}


void Canvas::drawErasePoint(QPainter *painter, const QPointF &point, int width)
{
//    painter->setRenderHints(QPainter::Antialiasing);
    QPen pen;
    pen.setColor(QColor(0,0,0));

    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setWidth(width + 1);
    painter->setPen(pen);
    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter->drawPoint(point);

    painter->setCompositionMode(QPainter::CompositionMode_Clear);
    pen.setWidth(width);
    painter->setPen(pen);
    painter->drawPoint(point);
}

void Canvas::paintLine(const QPointF &p1, const QPointF &p2, int witdh, QColor color)
{
    QBrush brush(color, Qt::SolidPattern);
    m_painter->setPen(QPen(brush, witdh, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    m_painter->drawLine(p1, p2);
    updateCanvas();
}

void Canvas::paintDot(const QPointF &p, int witdh, QColor color)
{
    QBrush brush(color/*, Qt::SolidPattern*/);
    m_painter->setPen(QPen(brush, witdh/*, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin*/));
    m_painter->drawPoint(p);
    updateCanvas();
}
