#ifndef LEAFSHIELDWEAPON_H
#define LEAFSHIELDWEAPON_H
#include "weapon.h"

class LeafShieldWeapon : public Weapon
{
private:
	float angle;
public:
	void draw(QPainter &painter, Camera offset = Camera());
	void update(float deltaTime);
	void use();
	bool checkCollision(QRectF &entityRect);
	void moveToPlayer(QRect playerRect);
	LeafShieldWeapon();
};

#endif // LEAFSHIELDWEAPON_H
