#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QtCore>

Scene::Scene()
{
    setBackgroundBrush(QBrush(QColor(255,255,255), QPixmap("bg.jpg")));
}
void Scene::makeMap(int map[])
{
    QBrush brush(QColor(255, 255, 255), QPixmap("mapGrass.jpg"));
    QBrush firstBaseBrush(QColor(255, 255, 255), QPixmap("firstPlayerBase.jpg"));
    QBrush secondBaseBrush(QColor(255, 255, 255), QPixmap("secondPlayerBase.jpg"));
    QBrush firstHeroBrush(QColor(255, 255, 255), QPixmap("firstHero.png"));
    QBrush secondHeroBrush(QColor(255, 255, 255), QPixmap("secondHero.png"));
    QBrush allowStepBrush(QColor(255, 255, 255), QPixmap("mapGrassAllow.jpg"));
    QPen pen(Qt::NoPen);
    for (int x = 0; x < 15; x++){
        for(int y = 0; y < 15; y++){
            if(map[x+15*y] == 1){
               // qDebug("1");
            QGraphicsItem * item =
                    addRect(QRectF(50*x,50*y,50,50), pen, brush);
            item->setData(0,"Map");
            }
            if(map[x+15*y] == 2){
                //qDebug("2");
            QGraphicsItem * item =
                    addRect(QRectF(50*x,50*y,50,50), pen, firstBaseBrush);
            item->setData(0,"firstPlayerBase");
            }
            if(map[x+15*y] == 3){
                //qDebug("3");
            QGraphicsItem * item =
                    addRect(QRectF(50*x,50*y,50,50), pen, secondBaseBrush);
            item->setData(0,"secondPlayerBase");
            }
            if(map[x+15*y] == 4){
                //qDebug("4");
            QGraphicsItem * item =
                    addRect(QRectF(50*x,50*y,50,50), pen, firstHeroBrush);
            item->setData(0,"secondHero");
            }
            if(map[x+15*y] == 5){
                //qDebug("5");
            QGraphicsItem * item =
                    addRect(QRectF(50*x,50*y,50,50), pen, secondHeroBrush);
            item->setData(0,"secondHero");
            }
            if(map[x+15*y] == 6){
                //qDebug("6");
            QGraphicsItem * item =
                    addRect(QRectF(50*x,50*y,50,50), pen, allowStepBrush);
            item->setData(0,"secondHero");
            }

        }
    }
}
