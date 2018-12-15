#ifndef WEAPONPART_H
#define WEAPONPART_H
#include <QRect>
#include <QPixmap>
#include <QPainter>
#include "camera.h"
#include "gamedata.h"

class WeaponPart
{
private:
	QPixmap texture;
	QRect textureRect;

public:
	WeaponPart();
	QRectF position;
	float damage;
	void draw(QPainter& painter, Camera offset = Camera());
	void setTexture(QPixmap &t);
	bool checkCollision(QRectF &pcoords);
	void setTextureRect(QRect tr);
};

#endif // WEAPONPART_H
