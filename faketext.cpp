#include "faketext.h"

QRect FakeText::getLetter(QChar letter)
{
	if (letter == 'A')
	{
		return QRect(152, 96, 8, 8);
	}
	if (letter == 'B')
	{
		return QRect(160, 96, 8, 8);
	}
	if (letter == 'C')
	{
		return QRect(168, 96, 8, 8);
	}
	if (letter == 'D')
	{
		return QRect(176, 96, 8, 8);
	}
	if (letter == 'E')
	{
		return QRect(184, 96, 8, 8);
	}
	if (letter == 'F')
	{
		return QRect(192, 96, 8, 8);
	}
	if (letter == 'G')
	{
		return QRect(200, 96, 8, 8);
	}
	if (letter == 'H')
	{
		return QRect(208, 96, 8, 8);
	}
	if (letter == 'I')
	{
		return QRect(216, 96, 8, 8);
	}
	if (letter == 'J')
	{
		return QRect(224, 96, 8, 8);
	}
	if (letter == 'K')
	{
		return QRect(232, 96, 8, 8);
	}
	if (letter == 'L')
	{
		return QRect(240, 96, 8, 8);
	}
	if (letter == 'M')
	{
		return QRect(248, 96, 8, 8);
	}
	if (letter == 'N')
	{
		return QRect(256, 96, 8, 8);
	}
	if (letter == 'O')
	{
		return QRect(264, 96, 8, 8);
	}
	if (letter == 'P')
	{
		return QRect(272, 96, 8, 8);
	}
	if (letter == 'Q')
	{
		return QRect(280, 96, 8, 8);
	}
	if (letter == 'R')
	{
		return QRect(288, 96, 8, 8);
	}
	if (letter == 'S')
	{
		return QRect(296, 96, 8, 8);
	}
	if (letter == 'T')
	{
		return QRect(304, 96, 8, 8);
	}
	if (letter == 'U')
	{
		return QRect(312, 96, 8, 8);
	}
	if (letter == 'V')
	{
		return QRect(320, 96, 8, 8);
	}
	if (letter == 'W')
	{
		return QRect(328, 96, 8, 8);
	}
	if (letter == 'X')
	{
		return QRect(336, 96, 8, 8);
	}
	if (letter == 'Y')
	{
		return QRect(344, 96, 8, 8);
	}
	if (letter == 'Z')
	{
		return QRect(352, 96, 8, 8);
	}
	if (letter == ' ')
	{
		return QRect(0, 0, 1, 1);
	}
	if (letter == '1')
	{
		return QRect(152, 104, 8, 8);
	}
	if (letter == '2')
	{
		return QRect(160, 104, 8, 8);
	}
	if (letter == '3')
	{
		return QRect(168, 104, 8, 8);
	}
	if (letter == '4')
	{
		return QRect(176, 104, 8, 8);
	}
	if (letter == '5')
	{
		return QRect(184, 104, 8, 8);
	}
	if (letter == '6')
	{
		return QRect(192, 104, 8, 8);
	}
	if (letter == '7')
	{
		return QRect(200, 104, 8, 8);
	}
	if (letter == '8')
	{
		return QRect(208, 104, 8, 8);
	}
	if (letter == '9')
	{
		return QRect(216, 104, 8, 8);
	}
	if (letter == '0')
	{
		return QRect(224, 104, 8, 8);
	}
	if (letter == '.')
	{
		return QRect(232, 104, 8, 8);
	}
	if (letter == '!')
	{
		return QRect(240, 104, 8, 8);
	}
	if (letter == '?')
	{
		return QRect(248, 104, 8, 8);
	}
	if (letter == ',')
	{
		return QRect(256, 104, 8, 8);
	}

	return QRect(360, 96, 0, 0);
}

void FakeText::draw(int x, int y, QString text, QPainter &painter, Camera offset)
{
	int endls = 0;
	int charcnt = 0;
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == '\n')
		{
			charcnt = 0;
			endls++;
			continue;
		}


		QPixmap toDraw;
		toDraw.load(":/files/assets/images/MTileset.png");
		toDraw = toDraw.copy(getLetter(text[i]));
		painter.drawPixmap((x+(charcnt*8))*Game::scaleFactor, (y+(endls*8))*Game::scaleFactor, toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));

		charcnt ++;
	}
}

FakeText::FakeText()
{

}

