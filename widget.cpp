#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);
    testmap.open(":/files/assets/map.txt");

	you.setRect(QRect(3, 0, 10, 15));

	you.setCurrentWeapon(testWeapon);

    testLivesHud.max = 100;

	frameUpdate.setInterval(1000/Game::framerate);
	frameUpdate.start();
	frameInterval.start();
	bricksBg.setRect(Game::Tiles::Backgrounds::bgBrick);
	bricksBg.setPosition(0, 360);
	bricksBg.setColorAfter(QColor(0,0,0,255));
	bricksBg.repeatX = true;
	bricksBg.repeatY = true;
	testBg.setRect(Game::Tiles::Backgrounds::bgMountain);
	testBg.setPosition(0, 80);
	testBg.setColorAfter(QColor(0,0,0,255));
	connect(&frameUpdate, SIGNAL(timeout()), this, SLOT(update()));
}

Widget::~Widget()
{
	delete ui;
}

void Widget::update()
{
	float deltaTime = frameInterval.restart()/1000.f;

	if (keys[Qt::Key_D])
	{
        you.move(60);
	}
    if (keys[Qt::Key_O])
    {
        testLivesHud.value++;
    }
    if (keys[Qt::Key_L])
    {
        testLivesHud.value--;
    }
    if (keys[Qt::Key_A])
	{
        you.move(-60);
	}
	if (keys[Qt::Key_W] && !keys[Qt::Key_Space])
	{
        you.setClimbVel(-60);
	}
	if (keys[Qt::Key_S] && !keys[Qt::Key_Space])
	{
		you.setClimbVel(60);
	}
	if (keys[Qt::Key_Space])
	{
		you._jump();
	}

    this->testLivesHud.value = you.getHealth();
	cam.setPosition((-you.getPosition().x())+(this->width()/(Game::scaleFactor*2)), (-you.getPosition().y())+(this->height()/(Game::scaleFactor*2)));
	you.update(deltaTime, testmap);

	this->repaint();
}

void Widget::mousePressEvent(QMouseEvent *e)
{
	you.useCurrentWeapon();
}


void Widget::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	//background color
	painter.setBrush(QBrush(QColor(136, 255, 234)));
	//no outline
	painter.setPen(QColor(0,0,0,0));
	//draw bg

	painter.drawRect(0, 0, this->width(), this->height());
	testBg.draw(painter, this->width(), cam);
	//bricksBg.draw(painter, this->width(), cam);
    testmap.draw(painter, cam);
    you.draw(painter, cam);

    testLivesHud.draw(painter, cam);

}

void Widget::keyPressEvent(QKeyEvent *e)
{

	keys[e->key()] = true;
	QWidget::keyPressEvent(e);
}

void Widget::keyReleaseEvent(QKeyEvent *e)
{
	keys[e->key()] = false;
	QWidget::keyReleaseEvent(e);
}
