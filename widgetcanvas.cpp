#include "widgetcanvas.h"

WidgetCanvas::WidgetCanvas(const QSizeF &size, QWidget *parent) : MouseUnitTouchWidget(parent), Canvas(size)
{
    this->setFixedSize(size.toSize());//木有警告

//    resize(size.toSize());//会有警告
}

void WidgetCanvas::updateCanvas()
{
    update();
}

void WidgetCanvas::setLineColor(const QColor &color)
{
    m_color = color;
}

void WidgetCanvas::setLineWidth(int width)
{
    m_lineWidth = width;
}

void WidgetCanvas::widgetDotPress(int id, const QPointF &pos, const QSizeF &size)
{
    if(m_lineInfos.contains(id)){
        Q_ASSERT_X(!m_lineInfos.contains(id), "CbDrawLayer: line begin", qPrintable(QString("%1 id is exist").arg(id)));
        return;
    }
    createPoint(id, pos, size);

    if(!m_lineInfos.value(id)->isErase){
        drawDot(m_lineInfos.value(id)->points.last(), m_lineInfos.value(id)->witdh, m_lineInfos.value(id)->color);
    }else{
        eraseDot(m_lineInfos.value(id)->points.last(), m_lineInfos.value(id)->witdh);
    }
}

void WidgetCanvas::widgetDotmove(int id, const QPointF &pos, const QSizeF &size)
{
    if(!m_lineInfos.contains(id)){
        Q_ASSERT_X(!m_lineInfos.contains(id), "CbDrawLayer: line move", qPrintable(QString("%1 id is not exist").arg(id)));
        return;
    }
    if(!m_lineInfos.value(id)->isErase){
        m_lineInfos.value(id)->isErase = isErasePixSize(size);
    }

    if(!m_lineInfos.value(id)->isErase){
        drawLine(pos, m_lineInfos.value(id)->points.last(), m_lineInfos.value(id)->witdh, m_lineInfos.value(id)->color);
    }else{
        eraseLine(pos, m_lineInfos.value(id)->points.last(), m_lineInfos.value(id)->witdh);
    }

    m_lineInfos.value(id)->points.append(pos);
}

void WidgetCanvas::widgetDotRelease(int id, const QPointF &pos, const QSizeF &size)
{
    if(!m_lineInfos.contains(id)){
        Q_ASSERT_X(!m_lineInfos.contains(id), "CbDrawLayer: line end", qPrintable(QString("%1 id is not exist").arg(id)));
        return;
    }
    if(!m_lineInfos.value(id)->isErase){
        m_lineInfos.value(id)->isErase = isErasePixSize(size);
    }
    if(!m_lineInfos.value(id)->isErase){
        drawLine(pos, m_lineInfos.value(id)->points.last(), m_lineInfos.value(id)->witdh, m_lineInfos.value(id)->color);
    }else{
        eraseLine(pos, m_lineInfos.value(id)->points.last(), m_lineInfos.value(id)->witdh);
    }

    freeLine(id);
}

bool WidgetCanvas::createPoint(int id, const QPointF &pos, const QSizeF &size)
{
    LineInfo *info = new LineInfo;
    info->color = m_color;
    info->id = id;
    info->isErase = m_bErase ? m_bErase : isErasePixSize(size);
    info->points.append(pos);
    info->witdh = m_lineWidth;
    m_lineInfos.insert(id, info);
    return true;
}

bool WidgetCanvas::freeLine(int id)
{
    LineInfo *info = m_lineInfos.value(id);
    m_lineInfos.remove(id);
    delete info;
    return true;
}


void WidgetCanvas::resizeEvent(QResizeEvent *ev)
{
    Canvas::reset(this->size());
    QWidget::resizeEvent(ev);
}

void WidgetCanvas::paintEvent(QPaintEvent *)
{
    if(m_backgroundImage.isNull()){
        return;
    }
    QPainter painter(this);
    painter.drawImage(0, 0, m_backgroundImage);
}

