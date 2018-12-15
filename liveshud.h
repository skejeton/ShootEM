#ifndef LIVESHUD_H
#define LIVESHUD_H
#include <QPainter>
#include "gamedata.h"
#include "camera.h"

class LivesHud
{
private:
    QPixmap mainTileset;
public:
    float value;
    float max;
    void draw(QPainter& painter, Camera offset = Camera());
    LivesHud();
};

#endif // LIVESHUD_H
