#ifndef FAKETEXT_H
#define FAKETEXT_H
#include <QMap>
#include <QPainter>
#include "camera.h"
#include "gamedata.h"
#include <QRect>

class FakeText
{
public:
	static QRect getLetter(QChar letter);
	static void draw(int x, int y, QString text, QPainter &painter, Camera offset = Camera());
	FakeText();
};

#endif // FAKETEXT_H
