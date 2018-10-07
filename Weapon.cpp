#include "Weapon.hpp"

Weapon::Weapon(int speed) :
	delay_(1 / (float)speed),
	paused_(0),
	missileSpeed_(speed)
{}

Weapon::Weapon(int speed, int missileSpeed) :
	delay_(1 / (float)speed),
	paused_(0)
{
	if (speed > missileSpeed)
		missileSpeed_ = speed;
}

Weapon::~Weapon() {}

Missile * Weapon::shoot(float timeLapse, coord position, movement direction) {
	paused_ -= timeLapse;
	if (paused_ <= 0) {
		Missile * m = new Missile(position, direction, missileSpeed_, "|");
		paused_ = delay_;
		return m;
	}
	return NULL;
}
