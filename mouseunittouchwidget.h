#ifndef MOUSEUNITTOUCHWIDGET_H
#define MOUSEUNITTOUCHWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QTouchEvent>
#include <QTimer>
class MouseUnitTouchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MouseUnitTouchWidget(QWidget *parent = 0);
    bool isErasePixSize(const QSizeF &size);
    bool isErasePhysicsSize(const QSizeF &size);
protected:
    virtual void widgetDotPress(int id, const QPointF &pos, const QSizeF &size = QSizeF()) = 0;
    virtual void widgetDotmove(int id, const QPointF &pos, const QSizeF &size = QSizeF()) = 0;
    virtual void widgetDotRelease(int id, const QPointF &pos, const QSizeF &size = QSizeF()) = 0;

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool touchEvent(QTouchEvent *event);
    bool event(QEvent *event);
    int getMouseEventID(QMouseEvent *event);
signals:

private:
   QTimer *m_activeMouseAbleTimer;
   bool m_bMouseAble = true;

public slots:
    void onMouseAble(){
        m_bMouseAble = true;
    }
};

#endif // MOUSEUNITTOUCHWIDGET_H
