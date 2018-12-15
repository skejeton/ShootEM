#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "gamedata.h"
#include "camera.h"
#include <QPainter>
#include <QRect>
#include <cmath>


class Background
{
public:
	Background();
    void draw(QPainter &painter, int width, Camera offset = Camera());
	void setRect(QRect r);
	void setPosition(float x, float y);
	void setColorAfter(QColor colorAfter);
	bool repeatX;
	bool repeatY;
private:
	float x, y;
	QRect imageRect;
	QPixmap tileset;
	QColor colorAfter;
};

#endif // BACKGROUND_H
