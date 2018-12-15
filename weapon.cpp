#include "weapon.h"

Weapon::Weapon()
{

}

void Weapon::use()
{
	this->_isUsing = true;
}

bool Weapon::isUsing()
{
	return this->_isUsing;
}
