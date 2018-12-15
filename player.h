#ifndef PLAYER_H
#define PLAYER_H
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include <iostream>
#include <QVector>
#include "allweapons.h"
#include "gamedata.h"
#include "map.h"
#include "animation.h"
#include "animationmanager.h"
#include "cooldown.h"
#include "mapobject.h"
#include "camera.h"

#define PLAYER_REDTEAM Game::Entities::Player::Red
#define PLAYER_BLUETEAM Game::Entities::Player::Blue

class Player
{
private:

	bool visible;
	int health;
    CoolDown hitCooldown;
    CoolDown invicibleCooldown;
    int maxHealth = 100;
	enum CDIR {X, Y};
	Weapon *currentWeapon;
	AnimationManager<QRect> animations;
	Animation<bool> invAnim;
	CoolDown attackAnimCooldown;
	QRect playerRect;
	QPixmap sprite;
    bool invicible;
	bool dirx;
	bool isAttacking;
	bool onLadder;
	float x, y;
	float oldx, oldy;
	float vx, vy;
	float climbVel;
public:
	Player();
    void takeDamage(int amount);
	void setCurrentWeapon(Weapon &w);
	void useCurrentWeapon();
	void getHit(Weapon &w);
	int getHealth();
	void setImageRect(QRect rect);
	void setRect(QRect rect);
	void draw(QPainter& painter, Camera offset = Camera());
	void move(float x);
	QPointF getPosition();
	void setClimbVel(float cvel);
	void _jump();
	bool collision(MapObject& obj);
	bool activated(MapObject& obj);

    void onSpikeCollision(MapObject& obj, CDIR dir);
	void onLadderCollision(MapObject& obj, CDIR dir);
	void onSolidCollision(MapObject& obj, CDIR dir);
	void update(float deltaTime, Map& map);
	//void update(float deltaTime, MapObject& obj);
	//void update(float deltaTime, QVector<MapObject>& objs);
	enum {stay, jump, climb, hit, walk} STATE;

};

#endif // PLAYER_H
