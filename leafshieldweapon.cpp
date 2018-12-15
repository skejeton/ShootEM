#include "leafshieldweapon.h"

void LeafShieldWeapon::draw(QPainter &painter, Camera offset)
{
	for (int i = 0; i < parts.size(); i++)
	{
		parts[i].draw(painter, offset);
	}
}

void LeafShieldWeapon::update(float deltaTime)
{
	angle += M_PI/3*deltaTime;
}

void LeafShieldWeapon::use()
{
	if (_isUsing) return;
	angle = 0;
	this->texture.load(":/files/assets/images/MTileset.png");
	for (int i = 0; i < 4; i++)
	{
		WeaponPart wp;
		wp.damage = 40;
		wp.setTexture(this->texture);
		wp.setTextureRect(Game::Weapons::Magic::leafShieldLeaf);
		wp.position.setWidth(8);
		wp.position.setHeight(8);
		this->parts.push_back(wp);
	}
	this->_isUsing = true;
}

bool LeafShieldWeapon::checkCollision(QRectF &entityRect)
{
	for (int i = 0; i < parts.size(); i++)
	{
		if (parts[i].checkCollision(entityRect)) return true;
	}
	return false;
}

void LeafShieldWeapon::moveToPlayer(QRect playerRect)
{
	QVector<QPointF> points {QPointF(-20, 0), QPointF(20, 0), QPointF(0, 20), QPointF(0, -20)};
	QPointF playerCenter = QPointF(playerRect.x()+(playerRect.width()/4), playerRect.y()+(playerRect.height()/4));


	this->texture.load(":/files/assets/images/MTileset.png");
	for (int i = 0; i < 4; i++)
	{
		float pointx = points[i].x() + playerCenter.x();
		float pointy = points[i].y() + playerCenter.y();

		points[i].setX(cos(angle)*(pointx-playerCenter.x()) -
				sin(angle) * (pointy-playerCenter.y()) + playerCenter.x());
		points[i].setY(sin(angle)*(pointx-playerCenter.x()) +
				cos(angle) * (pointy-playerCenter.y()) + playerCenter.y());


		parts[i].position.setX(points[i].x());
		parts[i].position.setY(points[i].y());
	}
}

LeafShieldWeapon::LeafShieldWeapon()
{
	this->_isUsing = false;
}
