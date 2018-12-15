#include "animationmanager.h"

template <class T>
AnimationManager<T>::AnimationManager()
{

}

template<class T>
Animation<T> AnimationManager<T>::getCurrentAnimation()
{
	return animations[currentAnimation];
}

template<class T>
T AnimationManager<T>::getCurrentFrame()
{
	return animations[currentAnimation].getCurrentFrame();
}

template<class T>
void AnimationManager<T>::setCurrentAnimation(QString anim)
{
	if (anim == currentAnimation) return;
	currentAnimation = anim;
	animations[currentAnimation].start();
}

template<class T>
void AnimationManager<T>::update()
{
	animations[currentAnimation].requestFrame();
}
