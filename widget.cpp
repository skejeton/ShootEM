#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);
	testmap.open(":/files/assets/map.txt");

    you.setRect(QRect(-3, 0, 10, 15));

    //you.setCurrentWeapon(testWeapon);

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

	//setup animation managers
	//blue
	teamBlue.animations["stay"].frames.push_back(Game::Entities::Player::Blue::playerStand1);
	teamBlue.animations["stay"].frames.push_back(Game::Entities::Player::Blue::playerStand2);
	teamBlue.animations["stay"].frameTimeout = std::chrono::milliseconds(500);

	teamBlue.animations["jump"].frames.push_back(Game::Entities::Player::Blue::playerJump);
	teamBlue.animations["jump"].frameTimeout = std::chrono::milliseconds(500);


	teamBlue.animations["walk"].frames.push_back(Game::Entities::Player::Blue::playerStand1);
	teamBlue.animations["walk"].frames.push_back(Game::Entities::Player::Blue::playerWalk);
	teamBlue.animations["walk"].frameTimeout = std::chrono::milliseconds(200);

	teamBlue.animations["climb"].frames.push_back(Game::Entities::Player::Blue::playerClimb);
	teamBlue.animations["climb"].frames.push_back(Game::Entities::Player::Blue::playerClimb2);
	teamBlue.animations["climb"].frameTimeout = std::chrono::milliseconds(200);

	teamBlue.animations["dash"].frames.push_back(Game::Entities::Player::Blue::playerDash);
	teamBlue.animations["dash"].frames.push_back(Game::Entities::Player::Blue::playerDash2);
	teamBlue.animations["dash"].frameTimeout = std::chrono::milliseconds(100);


	//red
	teamRed.animations["stay"].frames.push_back(Game::Entities::Player::Red::playerStand1);
	teamRed.animations["stay"].frames.push_back(Game::Entities::Player::Red::playerStand2);
	teamRed.animations["stay"].frameTimeout = std::chrono::milliseconds(500);

	teamRed.animations["jump"].frames.push_back(Game::Entities::Player::Red::playerJump);
	teamRed.animations["jump"].frameTimeout = std::chrono::milliseconds(500);


	teamRed.animations["walk"].frames.push_back(Game::Entities::Player::Red::playerStand1);
	teamRed.animations["walk"].frames.push_back(Game::Entities::Player::Red::playerWalk);
	teamRed.animations["walk"].frameTimeout = std::chrono::milliseconds(200);

	teamRed.animations["climb"].frames.push_back(Game::Entities::Player::Red::playerClimb);
	teamRed.animations["climb"].frames.push_back(Game::Entities::Player::Red::playerClimb2);
	teamRed.animations["climb"].frameTimeout = std::chrono::milliseconds(200);

	teamRed.animations["dash"].frames.push_back(Game::Entities::Player::Red::playerDash);
	teamRed.animations["dash"].frames.push_back(Game::Entities::Player::Red::playerDash2);
	teamRed.animations["dash"].frameTimeout = std::chrono::milliseconds(100);


	//gold
	goldMember.animations["stay"].frames.push_back(Game::Entities::Player::Gold::playerStand1);
	goldMember.animations["stay"].frames.push_back(Game::Entities::Player::Gold::playerStand2);
	goldMember.animations["stay"].frameTimeout = std::chrono::milliseconds(500);

	goldMember.animations["jump"].frames.push_back(Game::Entities::Player::Gold::playerJump);
	goldMember.animations["jump"].frameTimeout = std::chrono::milliseconds(500);


	goldMember.animations["walk"].frames.push_back(Game::Entities::Player::Gold::playerStand1);
	goldMember.animations["walk"].frames.push_back(Game::Entities::Player::Gold::playerWalk);
	goldMember.animations["walk"].frameTimeout = std::chrono::milliseconds(200);

	goldMember.animations["climb"].frames.push_back(Game::Entities::Player::Gold::playerClimb);
	goldMember.animations["climb"].frames.push_back(Game::Entities::Player::Gold::playerClimb2);
	goldMember.animations["climb"].frameTimeout = std::chrono::milliseconds(200);

	goldMember.animations["dash"].frames.push_back(Game::Entities::Player::Gold::playerDash);
	goldMember.animations["dash"].frames.push_back(Game::Entities::Player::Gold::playerDash2);
	goldMember.animations["dash"].frameTimeout = std::chrono::milliseconds(100);

	goldMember.animations["hit"].frames.push_back(Game::Entities::Player::Gold::playerHit);
	goldMember.animations["hit"].frameTimeout = std::chrono::milliseconds(10000);


	testDialog.addNode(NARRATOR_NORMAL,
					   "WELCOME TO THE GAME!\nI WILL BE YOUR GUIDE\nTILL THE END.\nPRESS F TO CONTINUE");
	testDialog.addNode(NARRATOR_NORMAL,
					   "USE WASD TO MOVE,\nAND USE SPACEBAR TO JUMP\nPRE..");
	testDialog.addNode(PLAYER_ANGRY,
					   "SHUT MOUTH");
	testDialog.start(std::chrono::milliseconds(100));
	you.setAnimManager(teamBlue);
	dashRReleased = false;
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
		you.vx += 60;

		if (!dashIntervalR.isTimeout() && dashRReleased)
		{
			you._dash(120);
			dashRReleased = false;
		}
		else
		{
			dashRReleased = false;
			dashIntervalR.start(std::chrono::milliseconds(150));
		}
	}
	else
	{
		if (!dashIntervalR.isTimeout())
		{
			dashRReleased = true;
		}

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
		you.vx += -60;
		if (!dashIntervalL.isTimeout() && dashLReleased)
		{
			you._dash(-120);
			dashLReleased = false;
		}
		else
		{
			dashLReleased = false;
			dashIntervalL.start(std::chrono::milliseconds(150));
		}
	}
	else
	{
		if (!dashIntervalL.isTimeout())
		{
			dashLReleased = true;
		}
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
	if (keys[Qt::Key_F])
	{
		testDialog.speedUp();
		testDialog.continueDialog();
	}
	if (!testDialog.isEnd)
	{
		testDialog.update();
	}
	this->testLivesHud.value = you.health;
	cam.setPosition((-you.x)+(this->width()/(Game::scaleFactor*2)), (-you.y)+(this->height()/(Game::scaleFactor*2)));
	if (cam.getPosition().x() < -testmap.getWidth()*16+this->width()/Game::scaleFactor)
	{
		cam.setPosition(-testmap.getWidth()*16+this->width()/Game::scaleFactor, cam.getPosition().y());
	}
	if (cam.getPosition().x() > 0)
	{
		cam.setPosition(0, cam.getPosition().y());
	}
	if (cam.getPosition().y() < -testmap.getHeight()*16+this->height()/Game::scaleFactor)
	{
		cam.setPosition(cam.getPosition().x(), -testmap.getHeight()*16+this->height()/Game::scaleFactor);
	}

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
	painter.setBrush(QBrush(QColor(0, 64, 88)));
	//no outline
	painter.setPen(QColor(0,0,0,0));
	//draw bg

	painter.drawRect(0, 0, this->width(), this->height());
	testBg.draw(painter, this->width(), cam);
	//bricksBg.draw(painter, this->width(), cam);
    testmap.draw(painter, cam);
    you.draw(painter, cam);
	testDialog.initByHeight(this->height());
	if (!testDialog.isEnd)
	{
		testDialog.draw(painter);
	}
	testLivesHud.draw(painter, cam);
	you.currentWeapon->draw(painter, cam);
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
