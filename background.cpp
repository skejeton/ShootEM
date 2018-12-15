#include "background.h"

Background::Background()
{
	this->tileset.load(":/files/assets/images/MTileset.png");
	this->colorAfter = QColor(0,0,0,0);
	x = y = 0;
	repeatX = true;
	repeatY = false;
}

void Background::draw(QPainter& painter, int width, Camera offset)
{
	QPixmap renderer = this->tileset.copy(imageRect).transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor));


	if (repeatX && repeatY)
	{
		for (int i = -50; i < 50; i++)
		{
			float xresult = ((x+(offset.getPosition().x()*Game::scaleFactor)))+(i*imageRect.width())*Game::scaleFactor;
			if (xresult < -imageRect.width()*Game::scaleFactor &&
					xresult > width)
			{
				continue;
			}
			for (int j = 0; j < 25; j++)
			{

				painter.drawPixmap(((x+(offset.getPosition().x()*Game::scaleFactor)))+(i*imageRect.width())*Game::scaleFactor, (y+(offset.getPosition().y()*Game::scaleFactor))+(j*imageRect.height())*Game::scaleFactor, renderer);
			}
		}
	}
	else if (repeatX)
	{
		painter.setBrush(colorAfter);
		painter.drawRect((x)*Game::scaleFactor, (y+imageRect.height()+offset.getPosition().y()/10)*Game::scaleFactor, width, 3000);

		for (int i = -50; i < 50; i++)
		{
			float xresult = ((x+(offset.getPosition().x()*Game::scaleFactor)))+(i*imageRect.width())*Game::scaleFactor;
			if (xresult < -imageRect.width()*Game::scaleFactor &&
					xresult > width)
			{
				continue;
			}
			painter.drawPixmap(((x+offset.getPosition().x()/4)+(i*imageRect.width()))*Game::scaleFactor, (y+offset.getPosition().y()/10)*Game::scaleFactor, renderer);
		}

	}
	else if (repeatY)
	{
		for (int i = 0; i < 50; i++)
		{
			painter.drawPixmap(((x+offset.getPosition().x()))*Game::scaleFactor, (y+offset.getPosition().y())+(i*imageRect.height())*Game::scaleFactor, renderer);
		}
	}


}

void Background::setRect(QRect r)
{
	this->imageRect = r;
}

void Background::setPosition(float x, float y)
{
	this->y = y;
    this->x = x;
}

void Background::setColorAfter(QColor colorAfter)
{
	this->colorAfter = colorAfter;
}
