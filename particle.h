#ifndef PARTICLE_H
#define PARTICLE_H
#include <QPainter>
#include <QRect>
#include "camera.h"

class Particle
{
private:
	QRect textureRect;
	QPixmap texture;
public:
	virtual void draw(QPainter painter, Camera offset = Camera());
	void setTextureRect(QRect tRect);
	virtual ~Particle() = 0;
	Particle();
};

#endif // PARTICLE_H
