#include "map.h"

Map::Map()
{
	this->map = nullptr;
}

Map::~Map()
{
    for (int i = 0; i < width; i++)
    {
        delete[] this->map[i];
    }
    delete[] this->map;
}

void Map::draw(QPainter &p, Camera offset)
{

    for (int i = 0; i < this->width; i++)
    {
        for (int j = 0; j < this->height; j++)
        {
			if (map[i][j].getType() == BlockTypes::null ||
					map[i][j].getPosition().x()+offset.getPosition().x() < -map[i][j].getRect().width())
            {
                //qDebug()<< "null at" << i << " "<< j;
                continue;
            }
            this->map[i][j].draw(p, offset);
        }
    }
}

void Map::open(QString file)
{
    QFile in;

    in.setFileName(file);



    if (!in.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream stream(&in);



    stream >> this->width;
    stream >> this->height;

    if (this->map != nullptr)
    {
        delete this->map;
    }

    this->map = new MapObject*[width];
    for (int i = 0; i < width; i++)
    {
        this->map[i] = new MapObject[height];
    }

	for (int i = 0; i < this->height; i++)
    {
		for (int j = 0; j < this->width; j++)
        {
            int currentObject;
			stream >> currentObject;
			if (currentObject >= 0 && currentObject < Game::ids.size())
			{

				this->map[j][i].applyProps(Game::ids.at(currentObject));
				this->map[j][i].setPosition(QPointF(j*16, i*16));
				if (map[j][i].getType() == ladder)
				{
					if (map[j][i-1].getType() != ladder && map[j][i-1].getType() != laddertop)
					{
						map[j][i].setType(laddertop);
					}
				}
			}
			else
			{
				this->map[j][i].setType(BlockTypes::null);
			}


        }
        qDebug() << "next";
    }

}

int Map::getWidth()
{
	return width;
}

int Map::getHeight()
{
	return height;
}

MapObject Map::getObject(int x, int y)
{
	if (x >= 0 && y >= 0 && x < width && y < height)
	{
		return this->map[x][y];
	}
	return MapObject();
}
