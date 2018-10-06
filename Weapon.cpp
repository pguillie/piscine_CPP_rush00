#include "Weapon.hpp"

Weapon::Weapon(Missile * missile) :
	delay_(0.1f),
	paused_(0),
	missile_(missile)
{
	if (delay_ > missile->getDelay())
		delay_ = missile->getDelay();
}

Weapon::Weapon(int speed, Missile * missile) :
	delay_(1 / (float)speed),
	paused_(0),
	missile_(missile)
{
	if (delay_ > missile->getDelay())
		delay_ = missile->getDelay();
}

Weapon::~Weapon() {}

Missile * Weapon::shoot(float timeLapse, coord position, movement direction) {
	paused_ -= timeLapse;
	if (paused_ <= 0) {
		Missile * m = new Missile(position, direction, missile_->getSpeed());
		paused_ = delay_;
		return m;
	}
	return NULL;
}
