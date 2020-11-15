#ifndef DIALOG_H
#define DIALOG_H

#include <QPainter>
#include <QSound>
#include <QString>
#include <QVector>
#include "camera.h"
#include "gamedata.h"
#include "cooldown.h"
#include "faketext.h"

class Dialog
{
private:
	QPixmap tileset;
	int y;
	QVector<QString> texts;
	std::chrono::milliseconds endlInterval;
	std::chrono::milliseconds typeInterval;
	QVector<DialogIcons> icons;
	int textCount;
	int lettersopened;

	int speedMult;
public:
	Dialog();
	bool isEnd;
	CoolDown letterTypeCoolDown;

	void addNode(DialogIcons icon, QString text);
	void speedUp();
	void continueDialog();
	void initByHeight(int height);
	void start();
	void start(std::chrono::milliseconds time);
	void update();
	void draw(QPainter &painter, Camera offset = Camera());
	void nextLetter();
};

#endif // DIALOG_H
