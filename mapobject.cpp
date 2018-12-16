#include "mapobject.h"

MapObject::MapObject()
{
	x = y = 0;
	this->tileset.load(":/files/assets/images/MTileset.png");
	this->type = BlockTypes::null;
	this->rect = Game::Tiles::air;
	this->x = 0;
	this->y = 0;

}

void MapObject::setRect(QRect rect)
{
	this->rect = rect;
	this->tileset = this->tileset.copy(rect);
	this->tileset = this->tileset.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor));
}

void MapObject::draw(QPainter &painter, Camera offset)
{
    painter.drawPixmap((x+offset.getPosition().x())*Game::scaleFactor, (y+offset.getPosition().y())*Game::scaleFactor, tileset);
}

QRect MapObject::getRect()
{
    return this->rect;
}

QRectF MapObject::getMergedRect()
{
    return QRectF(x, y,
                 rect.width(), rect.height());
}

void MapObject::applyProps(MapProps props)
{
	this->setRect(std::get<0>(props));
	this->x = std::get<1>(props).x();
	this->y = std::get<1>(props).y();
	this->type = std::get<2>(props);
}

void MapObject::setType(BlockTypes type)
{
	this->type = type;
}

BlockTypes MapObject::getType()
{
	return this->type;
}

void MapObject::setPosition(QPointF pos)
{
	this->x = pos.x();
	this->y = pos.y();
}

QPointF MapObject::getPosition()
{
	return QPointF(x, y);
}
