#ifndef CAMERA_H
#define CAMERA_H
#include <QPointF>


class Camera
{
private:
    float x, y;
public:
    Camera();
    void move(float x, float y);
    void setPosition(float x, float y);
    QPointF getPosition();
};

#endif // CAMERA_H
