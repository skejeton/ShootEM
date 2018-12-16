#include "liveshud.h"

void LivesHud::draw(QPainter &painter, Camera offset)
{
    float height = 8;
    float tempValue = value;
    if (value > max)
    {
        tempValue = max;
    }

    float precent = tempValue / max;
    float barsAmount = precent*height*4;

    for (int i = 0; i < height; i++)
    {
		if (i == 0)
		{
			painter.drawPixmap(8*Game::scaleFactor, 0, this->mainTileset.copy(Game::HudCapTop).transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
		}
		if (i == height-1)
		{
			painter.drawPixmap(8*Game::scaleFactor, (((height+1)*8))*Game::scaleFactor, this->mainTileset.copy(Game::HudCapBot).transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
		}
        if ((barsAmount - 4) >= 0)
        {
            barsAmount -= 4;
			painter.drawPixmap(8*Game::scaleFactor, (((height-i)*8))*Game::scaleFactor, this->mainTileset.copy(Game::Hud4).transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
		}
        else if ((barsAmount - 3) >= 0)
        {
            barsAmount -= 3;
            painter.drawPixmap(8*Game::scaleFactor, (((height-i)*8))*Game::scaleFactor, this->mainTileset.copy(Game::Hud3).transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
        }
        else if ((barsAmount - 2) >= 0)
        {
            barsAmount -= 2;
            painter.drawPixmap(8*Game::scaleFactor, (((height-i)*8))*Game::scaleFactor, this->mainTileset.copy(Game::Hud2).transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
        }
        else if ((barsAmount - 1) >= 0)
        {
            barsAmount -= 1;
            painter.drawPixmap(8*Game::scaleFactor, (((height-i)*8))*Game::scaleFactor, this->mainTileset.copy(Game::Hud1).transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
        }
        else
        {
            painter.drawPixmap(8*Game::scaleFactor, (((height-i)*8))*Game::scaleFactor, this->mainTileset.copy(Game::Hud0).transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
        }
    }
}

LivesHud::LivesHud()
{
    this->mainTileset.load(":/files/assets/images/MTileset.png");
}
