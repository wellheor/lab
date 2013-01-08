#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
public:
    Scene();
    void makeMap(int map[]);
};

#endif // SCENE_H
