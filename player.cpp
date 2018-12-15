#include "player.h"

Player::Player()
{
	this->x = 0;
	this->y = 0;
	this->vx = 0;
	this->vy = 0;
	dirx = 1;
	this->invicible = false;
	invAnim.frames.push_back(true);
	invAnim.frames.push_back(false);
    this->health = 100;
	this->currentWeapon = nullptr;
    sprite.load(":/files/assets/images/MTileset.png");

	Animation<QRect> stayAnim;
	stayAnim.frames.push_back(Game::Entities::Player::Blue::playerStand1);
	stayAnim.frames.push_back(Game::Entities::Player::Blue::playerStand2);
	stayAnim.frameTimeout = std::chrono::milliseconds(500);
	animations.animations["stay"] = stayAnim;

	Animation<QRect> attackAnim;
	attackAnim.frames.push_back(Game::Entities::Player::Blue::playerAttack);
	attackAnim.frameTimeout = std::chrono::milliseconds(500);
	animations.animations["attack"] = attackAnim;

	Animation<QRect> hitAnim;
	hitAnim.frames.push_back(Game::Entities::Player::Blue::playerHit);
	hitAnim.frameTimeout = std::chrono::milliseconds(500);
	animations.animations["hit"] = hitAnim;

	Animation<QRect> climbAnim;
	climbAnim.frames.push_back(Game::Entities::Player::Blue::playerClimb);
	climbAnim.frames.push_back(Game::Entities::Player::Blue::playerClimb2);
	climbAnim.frameTimeout = std::chrono::milliseconds(200);
	animations.animations["climb"] = climbAnim;

	Animation<QRect> jumpAnim;
	jumpAnim.frames.push_back(Game::Entities::Player::Blue::playerJump);
	jumpAnim.frameTimeout = std::chrono::milliseconds(500);
	animations.animations["jump"] = jumpAnim;

	Animation<QRect> walkAnim;
	walkAnim.frames.push_back(Game::Entities::Player::Blue::playerStand1);
	walkAnim.frames.push_back(Game::Entities::Player::Blue::playerWalk);
	walkAnim.frameTimeout = std::chrono::milliseconds(200);
	animations.animations["walk"] = walkAnim;
}

void Player::takeDamage(int amount)
{
    if (!invicible)
    {

		hitCooldown.start(std::chrono::milliseconds(1000));
		invAnim.frameTimeout = std::chrono::milliseconds(100);
		invAnim.start();
		invicibleCooldown.start(std::chrono::milliseconds(5000));
		health -= amount;
    }
}

void Player::setCurrentWeapon(Weapon &w)
{
	this->currentWeapon = &w;
}

void Player::useCurrentWeapon()
{
	this->currentWeapon->use();
	this->attackAnimCooldown.start(std::chrono::milliseconds(500));
}

int Player::getHealth()
{
	return health;
}


void Player::setRect(QRect rect)
{
    this->playerRect = rect;
}



void Player::draw(QPainter &painter, Camera offset)
{
	QPixmap toDraw;
	if (isAttacking)
	{
		animations.setCurrentAnimation("attack");
		animations.update();
	}
	else if (STATE == stay)
	{
		animations.setCurrentAnimation("stay");
		animations.update();
	}
	else if (STATE == hit)
	{
		animations.setCurrentAnimation("hit");
	}
	else if (STATE == climb)
	{
		animations.setCurrentAnimation("climb");
		if (climbVel != 0) animations.update();
	}
	else if (STATE == jump)
	{
		animations.setCurrentAnimation("jump");
		animations.update();
	}
	else if (STATE == walk)
	{
		animations.setCurrentAnimation("walk");
		animations.update();
	}


	toDraw = sprite.copy(animations.getCurrentFrame());


	if (dirx == 1)
	{
		toDraw = toDraw.transformed(QTransform().scale(Game::scaleFactor, Game::scaleFactor));
	}
	else
	{
		toDraw = toDraw.transformed(QTransform().scale(-Game::scaleFactor, Game::scaleFactor));
	}
	if (this->currentWeapon != nullptr && this->currentWeapon->isUsing())
	{
		this->currentWeapon->draw(painter, offset);
	}


	if (visible)
	{
		painter.drawPixmap((x-playerRect.x()+offset.getPosition().x())*Game::scaleFactor, (y-playerRect.y()+offset.getPosition().y())*Game::scaleFactor, toDraw);
	}
}

void Player::move(float x)
{
	vx = x;
    dirx = vx >= 0;
}

QPointF Player::getPosition()
{
    return QPointF(x, y);
}

void Player::setClimbVel(float cvel)
{
	this->climbVel = cvel;
	this->onLadder = true;
}


void Player::_jump()
{

	if (STATE == climb)
		onLadder = false;
	if (STATE == stay || STATE == walk)
	{
        vy -= 160;
	}

}

bool Player::collision(MapObject &obj)
{
	QRect r = obj.getRect();
	QPointF p = obj.getPosition();
	this->STATE = jump;
	if (
			p.x() + r.width() > this->x &&
			p.y() + r.height() > this->y &&
			this->x + this->playerRect.width() > p.x() &&
			this->y + this->playerRect.height() > p.y()
		)
	{

		return 1;
	}
	return 0;

}

bool Player::activated(MapObject &obj)
{
	if ((oldy + playerRect.height()) <= obj.getPosition().y())
		return true;
    return false;
}

void Player::onSpikeCollision(MapObject &obj, Player::CDIR dir)
{
    QRect r = obj.getRect();
    QPointF p = obj.getPosition();
    if (vx > 0 && dir == CDIR::X)
    {
        this->x = p.x() - this->playerRect.width();
        vx = 0;
    }
    else if (vx < 0 && dir == CDIR::X)
    {
        this->x = p.x() + r.width();
        vx = 0;
    }
    if (vy > 0 && dir == CDIR::Y)
    {
        this->y = p.y() - this->playerRect.height();
        vy = 0;
    }
    else if (vy < 0 && dir == CDIR::Y)
    {
        this->y = p.y() + r.height();
        vy = 0;
    }
    STATE = stay;
}

void Player::onLadderCollision(MapObject &obj, CDIR dir)
{
	QRect r = obj.getRect();
	QPointF p = obj.getPosition();

    if (dir == CDIR::Y && activated(obj) && obj.getType() == laddertop && climbVel <= 0)
	{
		STATE = stay;
        onLadder = false;
		y = p.y()-playerRect.height();
		vy = 0;
	}

    if (onLadder)
    {
        x = p.x()+playerRect.x();
        STATE = climb;
        y = oldy;
        vy = 0;
    }
}

void Player::onSolidCollision(MapObject &obj, CDIR dir)
{
	QRect r = obj.getRect();
	QPointF p = obj.getPosition();
	if (vx > 0 && dir == CDIR::X)
	{
		this->x = p.x() - this->playerRect.width();
		vx = 0;
	}
	else if (vx < 0 && dir == CDIR::X)
	{
		this->x = p.x() + r.width();
		vx = 0;
	}
	if (vy > 0 && dir == CDIR::Y)
	{
		this->y = p.y() - this->playerRect.height();
		this->STATE = stay;
		if (vx != 0) STATE = walk;
		vy = 0;
	}
	else if (vy < 0 && dir == CDIR::Y)
	{
		this->y = p.y() + r.height();
		vy = 0;
	}

}

void Player::update(float deltaTime, Map &map)
{
	isAttacking = false;

    if (vy > 200) vy = 200;
	this->oldx = x;
	this->oldy = y;
	x += vx*deltaTime;
	bool checking = true;

	if (!invicibleCooldown.isTimeout())
    {
		invicible = true;
		invAnim.requestFrame();
		visible = invAnim.getCurrentFrame();
    }
	else
	{
		visible = true;
		invicible = false;
	}


	//check block collision in X
	for (int i = 0; i < map.getWidth() && checking; i++)
	{
		for (int j = 0; j < map.getHeight() && checking; j++)
		{
			MapObject obj(map.getObject(i, j));

			if (obj.getType() == BlockTypes::solid && collision(obj))
			{
				onSolidCollision(obj, CDIR::X);
				checking = false;
				break;
			}
			if (obj.getType() == BlockTypes::ladder && collision(obj))
			{
				onLadderCollision(obj, CDIR::X);
				checking = false;
				break;
			}
		}
	}
	checking = true;

	if (STATE == jump)
	{
		vy += Game::gravity;
	}

	y += vy*deltaTime;


	for (int i = 0; i < map.getWidth() && checking; i++)
	{
		for (int j = 0; j < map.getHeight() && checking; j++)
		{
			MapObject obj = map.getObject(i, j);

			//check block collision in Y
			if (obj.getType() == BlockTypes::solid && collision(obj))
			{
				onSolidCollision(obj, CDIR::Y);
				checking = false;
				break;
			}
            if (obj.getType() == BlockTypes::ladder || obj.getType() == BlockTypes::laddertop && collision(obj))
			{
				onLadderCollision(obj, CDIR::Y);
				if (onLadder && STATE == climb)
				{
					y += climbVel*deltaTime;
				}
				checking = false;
				break;
			}
            if (obj.getType() == BlockTypes::spike && collision(obj))
            {
                onSpikeCollision(obj, CDIR::Y);
				if (hitCooldown.isTimeout())
                {
					takeDamage(10);
                }
                checking = false;
                break;
            }
		}
	}

    if (!hitCooldown.isTimeout())
    {
       STATE = hit;
    }

	if (!attackAnimCooldown.isTimeout())
	{
		this->isAttacking = true;
	}


	// Check if player current weapon is using and not nullptr
	if (this->currentWeapon != nullptr && this->currentWeapon->isUsing())
	{
		this->currentWeapon->update(deltaTime);
		this->currentWeapon->moveToPlayer(QRect(this->x, this->y, this->playerRect.width(), this->playerRect.height()));
	}




	climbVel -= 3*Game::getSign(climbVel);
	vx -= 3*Game::getSign(vx);

}

//void Player::update(float deltaTime, MapObject &obj)
//{
//	x += vx*deltaTime;
//	collision(obj, 1);

//	if (STATE == jump)
//	{
//		vy += Game::gravity;
//	}

//	STATE = stay;
//	y += vy*deltaTime;
//	collision(obj, 0);
//	vx = 0;
//}

//void Player::update(float deltaTime, QVector<MapObject> &objs)
//{
//	x += vx*deltaTime;
//	for (int i = 0; i < objs.size(); i++)
//	{
//		if (collision(objs[i], 1))
//		{
//			break;
//		}
//	}


//	if (STATE == jump)
//	{
//		vy += Game::gravity;
//	}

//	STATE = stay;
//	y += vy*deltaTime;

//	for (int i = 0; i < objs.size(); i++)
//	{
//		if (collision(objs[i], 0))
//		{
//			break;
//		}
//	}

//	vx = 0;
//}

