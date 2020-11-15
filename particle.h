#ifndef PARTICLE_H
#define PARTICLE_H
#include <QPainter>
#include <QRect>
#include "gamedata.h"
#include "camera.h"

class Particle
{
private:
	QRect textureRect;
	QPixmap texture;
public:
	float x, y;
	float vx, vy;
	float ax, ay;

	virtual void update(float deltaTime);
	virtual void draw(QPainter &painter, Camera offset = Camera());
	void setTextureRect(QRect tRect);
	virtual ~Particle();
	Particle();
};

#endif // PARTICLE_H
