#include "cooldown.h"

void CoolDown::setTimeout(std::chrono::milliseconds timeout)
{
	this->timeout = timeout;
}

void CoolDown::interrupt()
{
	started = false;
}

void CoolDown::start()
{
	started = true;
	this->timer.start();
}

void CoolDown::start(std::chrono::milliseconds timeout)
{
	started = true;
    this->timeout = timeout;
    this->timer.start();
}

bool CoolDown::isTimeout()
{
	if (!started) return true;
    return this->timer.elapsed() >= static_cast<unsigned int>(this->timeout.count());
}

CoolDown::CoolDown()
{
	started = false;
}
