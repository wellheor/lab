#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QGraphicsView>

class MyGraphicsView: public QGraphicsView
{
public:
    MyGraphicsView();
protected:
    void mousePressEvent(QMouseEvent *event);

};

#endif // MYGRAPHICSVIEW_H
