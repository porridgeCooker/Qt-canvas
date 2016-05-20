#include <QApplication>
#include "widgetcanvas.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WidgetCanvas canvas(QSizeF(600, 500));
    canvas.show();
    return a.exec();
}
