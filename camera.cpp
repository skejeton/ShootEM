#include "camera.h"

Camera::Camera()
{
    this->x = 0;
    this->y = 0;

}

void Camera::move(float x, float y)
{
    this->x += x;
    this->y += y;
}

void Camera::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;

}

QPointF Camera::getPosition()
{
    return QPointF(x, y);
}
