#ifndef WEAPON_H
#define WEAPON_H
#include <QPainter>
#include <QVector>
#include <cmath>
#include "camera.h"
#include "weaponpart.h"
#include "gamedata.h"

class Weapon
{
public:
	float manaCost;
	float damageMult;
	virtual void draw(QPainter &painter, Camera offset = Camera()) = 0;
	virtual void update(float deltaTime) = 0;
	virtual bool checkCollision(QRectF &entityRect) = 0;
	virtual void use();
	virtual void moveToPlayer(QRect playerRect) = 0;
	virtual bool isUsing();
	Weapon();
protected:
	bool _isUsing;
	QPixmap texture;
	QVector<WeaponPart> parts;
};

#endif // WEAPON_H
