#include "player.h"


Player::Player()
{
    sprite.load(":/files/assets/images/MTileset.png");

    //Defines player direction (flips the image)
	dirx = 1;

    //Defines either player can be attacked or not
	invincible = false;

    //Defines either player attacking or not, used for animation
    isAttacking = false;

    //Defines either player on ladder or not
    onLadder = false;

    vx = vy = 0;

    health = 100;
    maxHealth = 100;

	dashing = false;

	//Invicibility animation
	invAnim.frameTimeout = std::chrono::milliseconds(200);
	invAnim.frames.push_back(false);
	invAnim.frames.push_back(true);
	invAnim.start();

	collisionPriority.push_back(solid);
	collisionPriority.push_back(spike);
	collisionPriority.push_back(laddertop);
	collisionPriority.push_back(ladder);

    collisionCases[solid] = [&](MapObject &cObj, CDIR cDir)
    {

        if (vx > 0 && cDir == CDIR::X)
        {
            this->x = cObj.getPosition().x() - this->collisionRect.width();
			vx = 0;
			interruptDash();
        }
        else if (vx < 0 && cDir == CDIR::X)
        {
            this->x = cObj.getPosition().x() + cObj.getRect().width();
            vx = 0;
			interruptDash();
        }
		if (vy >= 0 && cDir == CDIR::Y)
        {
            this->y = cObj.getPosition().y() - this->collisionRect.height();
            vy = 0;
			STATE = stay;
        }
        else if (vy < 0 && cDir == CDIR::Y)
        {
            this->y = cObj.getPosition().y() + cObj.getRect().height();
            vy = 0;
        }
		return true;
    };
    collisionCases[null] = [&](MapObject &cObj, CDIR cDir)
    {
		return false;
    };
    collisionCases[ladder] = [&](MapObject &cObj, CDIR cDir)
	{
		onLadder = true;
		if (climbing)
		{
			STATE = climb;
			x = cObj.getPosition().x() + (cObj.getRect().width()-collisionRect.width())/2;
		}

		return false;
    };
    collisionCases[laddertop] = [&](MapObject &cObj, CDIR cDir)
	{
		onLadder = true;
		if (cDir == CDIR::Y && activated(cObj) && climbVelY <= 0)
		{
			this->y = cObj.getPosition().y() - this->collisionRect.height();
			vy = 0;
			STATE = stay;
		}
		if (climbing)
		{
			STATE = climb;
			x = cObj.getPosition().x() + (cObj.getRect().width()-collisionRect.width())/2;
		}
		return false;
    };
    collisionCases[spike] = [&](MapObject &cObj, CDIR cDir)
	{
		if (cDir == Y)
		{
			getHit(20);
		}
		if (vx > 0 && cDir == CDIR::X)
		{
			this->x = cObj.getPosition().x() - this->collisionRect.width();
			vx = 0;
		}
		else if (vx < 0 && cDir == CDIR::X)
		{
			this->x = cObj.getPosition().x() + cObj.getRect().width();
			vx = 0;
		}
		if (vy > 0 && cDir == CDIR::Y)
		{
			this->y = cObj.getPosition().y() - this->collisionRect.height();
			vy = 0;
			STATE = stay;
		}
		else if (vy < 0 && cDir == CDIR::Y)
		{
			this->y = cObj.getPosition().y() + cObj.getRect().height();
			vy = 0;
		}
		return true;
    };

}

void Player::getHit(int amount)
{
	if (invincible) return;

	QSound::play(":/files/assets/sounds/hit.wav");
	health -= amount;
	if (health <= 0)
	{
		respawn();
	}
	else
	{
		hitCooldown.start(std::chrono::milliseconds(2000));
		invincibleCooldown.start(std::chrono::milliseconds(3000));
	}
}

void Player::setAnimManager(AnimationManager<QRect> &m)
{
	this->animMan = m;
}

void Player::useCurrentWeapon()
{
	currentWeapon->use();
}

void Player::setClimbVel(int y)
{
	if (y != 0)
		climbing = true;
	climbVelY = y;
}

void Player::interruptDash()
{

	dashTimeout.interrupt();
}

void Player::setRect(QRect rect)
{
    this->collisionRect = rect;
}

void Player::draw(QPainter &painter, Camera offset)
{
    QPixmap toDraw;


	toDraw = sprite.copy(animMan.getCurrentFrame());

	if (visible == true)
		painter.drawPixmap((collisionRect.x()+x+offset.getPosition().x())*Game::scaleFactor, (collisionRect.y()+y+offset.getPosition().y())*Game::scaleFactor,
					   toDraw.transformed(QTransform().scale(Game::scaleFactor*dirx, Game::scaleFactor)));
}

void Player::respawn()
{
	QSound::play(":/files/assets/sounds/death.wav");
	//x = y = 0;
}

QRectF Player::getMergedRect()
{
    return QRectF(x, y,
				  collisionRect.width(), collisionRect.height());
}

void Player::_dash(int dashVel)
{
	if (STATE != climb && dashTimeout.isTimeout())
	{
		dashTimeout.start(std::chrono::milliseconds(500));
		this->dashVel = dashVel;
	}
}

void Player::_jump()
{
	climbing = false;
	interruptDash();
	if (STATE == stay || STATE == walk)
	{
		vy = -160;
	}
}

void Player::collision(Map &gameMap, CDIR cDir)
{
	STATE = jump;
	for (int k = 0; k < collisionPriority.size(); k++)
	{
		for (int i = 0; i < gameMap.getWidth(); i++)
		{
			for (int j = 0; j < gameMap.getHeight(); j++)
			{
				MapObject thisObject = gameMap.getObject(i, j);

				if (thisObject.getType() != collisionPriority[k])
				{
					continue;
				}

				if (thisObject.getMergedRect().intersects(getMergedRect()))
				{
					collisionCases[thisObject.getType()](thisObject, cDir);
				}
			}
		}
	}

}

bool Player::activated(MapObject &obj)
{
	return (this->oldY+collisionRect.height()) <= obj.getPosition().y();
}

void Player::update(float deltaTime, Map &map)
{
	if (vx != 0)
		dirx = Game::getSign(vx);
	oldX = x;
	oldY = y;
	//Defines either player overlaps ladder or not
	onLadder = false;

	if (!dashTimeout.isTimeout())
	{
		dashing = true;
		vx = dashVel;
	}
	else
	{
		dashing = false;
	}
	if (STATE != hit)
	{
		x += vx*deltaTime;
	}
    collision(map, CDIR::X);



	if (STATE == jump)
	{
		vy += Game::gravity;
	}


	if (onLadder && climbing)
	{
		vy = 0;
		y += climbVelY*deltaTime;

	}
	else
	{
		climbing = false;
	}
	if (dashing)
	{
		vy = 0;
	}
	y += vy*deltaTime;
    collision(map, CDIR::Y);


	if (!hitCooldown.isTimeout())
	{
		STATE = hit;
	}
	if (vx != 0 && STATE == stay)
	{
		STATE = walk;
	}

	if (dashing)
	{
		STATE = dash;
	}

	if (STATE == dash)
	{
		animMan.setCurrentAnimation("dash");
		animMan.update();
	}
	else if (STATE == stay)
	{
		animMan.setCurrentAnimation("stay");
		animMan.update();
	}
	else if (STATE == climb && climbVelY != 0)
	{
		animMan.setCurrentAnimation("climb");
		animMan.update();
	}
	else if (STATE == jump)
	{
		animMan.setCurrentAnimation("jump");
		animMan.update();
	}
	else if (STATE == walk)
	{
		animMan.setCurrentAnimation("walk");
		animMan.update();
	}
	else if (STATE == hit)
	{
		animMan.setCurrentAnimation("hit");
		animMan.update();
	}

	if (!invincibleCooldown.isTimeout())
	{
		invincible = true;
		visible = invAnim.getCurrentFrame();
		invAnim.requestFrame();
	}
	else
	{
		invincible = false;
		visible = true;
	}




	climbVelY = 0;


    vx = 0;
}
