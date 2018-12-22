#ifndef PLAYER_H
#define PLAYER_H
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include <QMap>
#include <iostream>
#include <QSound>
#include <functional>
#include <QVector>
#include "allweapons.h"
#include "gamedata.h"
#include "map.h"
#include "entity.h"
#include "animation.h"
#include "animationmanager.h"
#include "cooldown.h"
#include "mapobject.h"
#include "camera.h"

class Player : public Entity
{
private:

    CoolDown hitCooldown;
	CoolDown invincibleCooldown;

    Weapon *currentWeapon;
	QMap<BlockTypes, std::function<bool(MapObject&, CDIR)>> collisionCases;
	QVector<BlockTypes> collisionPriority;
	Animation<bool> invAnim;
	AnimationManager<QRect> animMan;
	CoolDown attackAnimCooldown;
	CoolDown dashTimeout;
	bool invincible;
	int dirx;
	bool isAttacking;
    bool onLadder;
	bool climbing;
	bool dashing;
public:
	int climbVelY;
	int dashVel;
	float oldX;
	float oldY;


    Player();
	void getHit(int amount);
	void setAnimManager(AnimationManager<QRect> &m);
    void useCurrentWeapon();
	void setClimbVel(int y);
	void interruptDash();
    void setRect(QRect rect) override;
    void draw(QPainter& painter, Camera offset = Camera()) override;
	void respawn();
    QRectF getMergedRect();

	void _dash(int dashVel);
	void _jump();
    void collision(Map& gameMap, CDIR cDir) override;
	bool activated(MapObject& obj);

    void update(float deltaTime, Map& map) override;


    AnimationManager<QRect> animations;
	enum {stay, jump, climb, hit, walk, dash} STATE;

};

#endif // PLAYER_H
