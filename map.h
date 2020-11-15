#ifndef MAP_H
#define MAP_H
#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include "dialog.h"
#include "mapobject.h"
#include "camera.h"
#include "gamedata.h"


class Map
{
public:
	Map();
	~Map();
    void draw(QPainter& p, Camera offset = Camera());
    void open(QString file);
	int getWidth();
	int getHeight();
	MapObject getObject(int x, int y);



private:
    int width;
    int height;
	Dialog startDialog;
	MapObject** map;
};

#endif // MAP_H
