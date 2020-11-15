#include "particle.h"

void Particle::update(float deltaTime)
{
	vx += ax;
	vy += ay;
	x += vx*deltaTime;
	y += vy*deltaTime;
}

void Particle::draw(QPainter &painter, Camera offset)
{
	QPixmap toDraw = this->texture.copy(this->textureRect);
	painter.drawPixmap((x+offset.getPosition().x())*Game::scaleFactor, (y+offset.getPosition().y())*Game::scaleFactor
					   , toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
}

void Particle::setTextureRect(QRect tRect)
{
	this->textureRect = tRect;
}

Particle::~Particle()
{

}

Particle::Particle()
{
	x = y = vx = vy = ax = ay = 0;
	texture.load(":/files/assets/images/MTileset.png");
}
