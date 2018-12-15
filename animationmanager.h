#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H
#include <QMap>
#include "animation.h"
#include <QString>

template <class T>
class AnimationManager
{
	QString currentAnimation;
public:
	AnimationManager();
	Animation<T> getCurrentAnimation();
	T getCurrentFrame();
	void setCurrentAnimation(QString anim);
	void update();


	QMap<QString, Animation<T>> animations;
};

#include "animationmanager.tpp"

#endif // ANIMATIONMANAGER_H
