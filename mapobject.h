#ifndef MAPOBJECT_H
#define MAPOBJECT_H
#include <QPainter>
#include <QPointF>
#include <tuple>
#include <QPixmap>
#include "camera.h"
#include <fstream>
#include "gamedata.h"


class MapObject
{
public:
	MapObject();
	void setRect(QRect rect);
    void draw(QPainter &painter, Camera offset = Camera());
	QRect getRect();
    QRectF getMergedRect();
	void applyProps(MapProps props);
	void setType(BlockTypes type);
	BlockTypes getType();
	void setPosition(QPointF pos);
	QPointF getPosition();
private:
	float x, y;
	BlockTypes type;
	QRect rect;
	QPixmap tileset;
};

#endif // MAPOBJECT_H
