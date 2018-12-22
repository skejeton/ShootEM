#include "particle.h"

void Particle::draw(QPainter painter, Camera offset)
{
}

void Particle::setTextureRect(QRect tRect)
{
	this->textureRect = tRect;
}

Particle::Particle()
{
	texture.load(":/files/assets/images/MTileset.png");
}
