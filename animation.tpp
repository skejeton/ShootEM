#include "animation.h"

template<class T>
Animation<T>::Animation()
{
	currentFrame = frames.begin();
}

template<class T>
void Animation<T>::start()
{
	currentFrame = frames.begin();
	this->frameCooldown.start(frameTimeout);
}

template<class T>
void Animation<T>::nextFrame()
{
	++currentFrame;
	if (currentFrame == frames.end())
	{
		currentFrame = frames.begin();
		return;
	}
}

template<class T>
void Animation<T>::requestFrame()
{
	if (frameCooldown.isTimeout())
	{
		this->frameCooldown.start(frameTimeout);
		this->nextFrame();
	}
}

template<class T>
T Animation<T>::getCurrentFrame()
{
	return *currentFrame;
}
