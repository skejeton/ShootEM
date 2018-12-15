#include "weaponpart.h"

WeaponPart::WeaponPart()
{

}

void WeaponPart::draw(QPainter &painter, Camera offset)
{
	QPixmap renderer = this->texture.copy(this->textureRect);
	renderer = renderer.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor));
	painter.drawPixmap((position.x()+offset.getPosition().x())*Game::scaleFactor,
					   (position.y()+offset.getPosition().y())*Game::scaleFactor, renderer);
}

void WeaponPart::setTexture(QPixmap &t)
{
	this->texture = t;
}

bool WeaponPart::checkCollision(QRectF &pcoords)
{
	if (pcoords.intersects(this->position))
	{
		return true;
	}
	return true;
}

void WeaponPart::setTextureRect(QRect tr)
{
	this->textureRect = tr;
}


