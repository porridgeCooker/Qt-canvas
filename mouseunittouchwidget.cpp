#include "mouseunittouchwidget.h"
#include <QDebug>
MouseUnitTouchWidget::MouseUnitTouchWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_AcceptTouchEvents);
    m_activeMouseAbleTimer = new QTimer(this);
    m_activeMouseAbleTimer->setSingleShot(true);
    connect(m_activeMouseAbleTimer, SIGNAL(timeout()),
            this, SLOT(onMouseAble()));
}


bool MouseUnitTouchWidget::isErasePixSize(const QSizeF &size)
{
    Q_UNUSED(size)
    return false;
    /**
    QSizeF tmp = size*g0->mmPerPix;//获取到物理大小
    return isErasePhysicsSize(tmp);
    */
}

bool MouseUnitTouchWidget::isErasePhysicsSize(const QSizeF &size)
{
    if((size.width() >40 && size.height() > 10)
            ||(size.width() > 10 && size.height() > 40)){
        return true;
    }else{
        return false;
    }
}


void MouseUnitTouchWidget::mousePressEvent(QMouseEvent *event)
{
    if(m_bMouseAble && getMouseEventID(event) == 0){
        widgetDotPress(getMouseEventID(event), QPointF(event->pos()));
    }else{
        return;
    }
    QWidget::mousePressEvent(event);
}

void MouseUnitTouchWidget::mouseMoveEvent(QMouseEvent *event)
{
    /**
        移动事件event()->button() == Qt::NoButton;
        **/
    if(m_bMouseAble){
        widgetDotmove(0, QPointF(event->pos()));
    }else{
        return;
    }
    QWidget::mouseMoveEvent(event);
}

void MouseUnitTouchWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_bMouseAble && getMouseEventID(event) == 0){
        widgetDotRelease(getMouseEventID(event), QPointF(event->pos()));
    }else{
        return;
    }
    QWidget::mouseReleaseEvent(event);
}

bool MouseUnitTouchWidget::touchEvent(QTouchEvent *event ){
    bool rtn = true;
    QList<QTouchEvent::TouchPoint> touchPoints = event->touchPoints();
    m_activeMouseAbleTimer->start(500);
    foreach (const QTouchEvent::TouchPoint &touchPoint, touchPoints) {
        int id = touchPoint.id() + 2;  //0,1 reserve for mouse event
        switch (touchPoint.state()) {
        case Qt::TouchPointPressed:{
            widgetDotPress(id, touchPoint.pos(), touchPoint.rect().size());
        }
            break;
        case Qt::TouchPointMoved:{
            widgetDotmove(id, touchPoint.pos(), touchPoint.rect().size());
        }
            break;
        case Qt::TouchPointReleased:{
            widgetDotRelease(id, touchPoint.pos(), touchPoint.rect().size());
        }
            break;
        default:
            break;
        }
    }
    return rtn;
}

bool MouseUnitTouchWidget::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick:
        if(!m_bMouseAble){
            return false;
        }else{
            break;
        }
    case QEvent::Gesture:
        event->accept();
        break;
    case QEvent::TouchEnd:
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
        m_bMouseAble = false;
        if(touchEvent(static_cast<QTouchEvent*>(event))){
            event->accept();
            return true;
        }
    }
    return QWidget::event(event);
}

int MouseUnitTouchWidget::getMouseEventID(QMouseEvent *event)
{
    int id = -1;
    if(event->button() == Qt::LeftButton){
        id=0;
    }else if(event->button() == Qt::RightButton){
        id=1;
    }else{
        qDebug()<<event->button();
    }
    return id;
}
