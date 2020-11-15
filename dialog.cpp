#include "dialog.h"

Dialog::Dialog()
{
	tileset.load(":/files/assets/images/MTileset.png");
	y = 0;


	textCount = 0;
	lettersopened = 0;
	isEnd = false;
	typeInterval = std::chrono::milliseconds(100);
	endlInterval = std::chrono::milliseconds(300);
	speedMult = 1;
}

void Dialog::addNode(DialogIcons icon, QString text)
{
	texts.push_back(text);
	icons.push_back(icon);
}

void Dialog::speedUp()
{
	speedMult = 2;
}

void Dialog::continueDialog()
{
	if (lettersopened < texts[textCount].length())
	{
		return;
	}
	textCount++;
	if (textCount >= texts.size())
	{
		textCount = texts.size()-1;
		isEnd = true;

	}
	else {

		lettersopened = 0;
	}
}

void Dialog::initByHeight(int height)
{
	y = (height/Game::scaleFactor)-7*8;
}

void Dialog::start()
{
	textCount = 0;
	lettersopened = 0;
	isEnd = 0;
	letterTypeCoolDown.start(typeInterval);
}

void Dialog::start(std::chrono::milliseconds time)
{
	textCount = 0;
	lettersopened = 0;
	isEnd = 0;
	typeInterval = time;
	letterTypeCoolDown.start(time);
}

void Dialog::update()
{
	if (letterTypeCoolDown.isTimeout())
	{
		nextLetter();
		letterTypeCoolDown.start(typeInterval);
	}
	speedMult = 1;
}

void Dialog::draw(QPainter &painter, Camera offset)
{
	painter.setBrush(QBrush(QColor(0, 0, 0)));
	painter.drawRect(0, y*Game::scaleFactor, 4000, 1000);



	QPixmap toDraw = tileset.copy(Game::frameTop);
	for (int i = 0; i < 100; i++)
	{
		painter.drawPixmap(i*8*Game::scaleFactor, y*Game::scaleFactor,
						   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	}


	//don't ask what is this
	toDraw = tileset.copy(Game::frameTopLeft);
	painter.drawPixmap(0, (y+8)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	toDraw = tileset.copy(Game::frameTop);
	painter.drawPixmap(8*Game::scaleFactor, (y+8)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	painter.drawPixmap(16*Game::scaleFactor, (y+8)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	painter.drawPixmap(24*Game::scaleFactor, (y+8)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	painter.drawPixmap(32*Game::scaleFactor, (y+8)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	toDraw = tileset.copy(Game::frameTopRight);
	painter.drawPixmap(40*Game::scaleFactor, (y+8)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	toDraw = tileset.copy(Game::frameLeft);
	painter.drawPixmap(0*Game::scaleFactor, (y+16)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	painter.drawPixmap(0*Game::scaleFactor, (y+24)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	painter.drawPixmap(0*Game::scaleFactor, (y+32)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	painter.drawPixmap(0*Game::scaleFactor, (y+40)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	toDraw = tileset.copy(Game::frameRight);
	painter.drawPixmap(40*Game::scaleFactor, (y+16)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	painter.drawPixmap(40*Game::scaleFactor, (y+24)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	painter.drawPixmap(40*Game::scaleFactor, (y+32)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	painter.drawPixmap(40*Game::scaleFactor, (y+40)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	toDraw = tileset.copy(Game::frameBottom);
	painter.drawPixmap(8*Game::scaleFactor, (y+48)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	painter.drawPixmap(16*Game::scaleFactor, (y+48)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	painter.drawPixmap(24*Game::scaleFactor, (y+48)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	painter.drawPixmap(32*Game::scaleFactor, (y+48)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));


	toDraw = tileset.copy(Game::frameBottomLeft);
	painter.drawPixmap(0, (y+48)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));

	toDraw = tileset.copy(Game::frameBottomRight);
	painter.drawPixmap(40*Game::scaleFactor, (y+48)*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));

	if (icons[textCount] == NARRATOR_NORMAL)
	{

		toDraw = tileset.copy(Game::NarratorNormal);
		painter.drawPixmap(8*Game::scaleFactor, (y+16)*Game::scaleFactor,
						   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	}
	if (icons[textCount] == PLAYER_ANGRY)
	{

		toDraw = tileset.copy(Game::DioBrando);
		painter.drawPixmap(8*Game::scaleFactor, (y+16)*Game::scaleFactor,
						   toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor)));
	}


	QString currentText = texts[textCount];
	currentText = currentText.mid(0, lettersopened);

	FakeText::draw(48, y+8, currentText, painter);

}

void Dialog::nextLetter()
{
	lettersopened++;
	if (lettersopened >= texts[textCount].length())
	{
		lettersopened = texts[textCount].length();
		return;
	}
	if (texts[textCount][lettersopened] == '\n')
	{
		typeInterval = endlInterval;
	}
	else
	{
		typeInterval = std::chrono::milliseconds(100/speedMult);
	}
	QSound::play(":/files/assets/sounds/typing.wav");
}
