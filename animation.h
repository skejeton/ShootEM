#ifndef ANIMATION_H
#define ANIMATION_H
#include <QVector>
#include <chrono>
#include "cooldown.h"

template <class T>
class Animation
{
public:
	Animation();

	void start();
	void nextFrame();
	void requestFrame();
	T getCurrentFrame();

	std::chrono::milliseconds frameTimeout;

	CoolDown frameCooldown;
	typename QVector<T>::iterator currentFrame;
	QVector<T> frames;
};

#include "animation.tpp"

#endif // ANIMATION_H
