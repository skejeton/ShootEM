#ifndef ENTITY_H
#define ENTITY_H
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include "gamedata.h"
#include "map.h"
#include "animation.h"
#include "cooldown.h"
#include "mapobject.h"
#include "camera.h"

class Entity
{
protected:
    bool visible;
    QRect collisionRect;
    QPixmap sprite;


public:

    float x, y;
    float vx, vy;
    int health;
    int maxHealth;
    Entity();
    virtual ~Entity();
    virtual void setRect(QRect rect) = 0;
    virtual void draw(QPainter& painter, Camera offset = Camera()) = 0;
    virtual void collision(Map& gameMap, CDIR cDir) = 0;
    virtual void update(float deltaTime, Map& map) = 0;
};

#endif // ENTITY_H
