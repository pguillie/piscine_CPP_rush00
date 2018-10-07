#include "Weapon.hpp"

Weapon::Weapon(int fireRate) :
	fireRate_(fireRate),
	missileSpeed_(fireRate),
	lastShot_(0)
{
	color_ = 0;
}

Weapon::Weapon(int fireRate, int missileSpeed) :
	fireRate_(fireRate),
	missileSpeed_(missileSpeed)
{
	color_ = 0;
}

Weapon::~Weapon() {}

void Weapon::setColor(int color) { color_ = color; }

Missile * Weapon::shoot(float timeLapse, coord position, movement direction) {
	std::clock_t current = std::clock();

	(void)timeLapse;
	if (int(current - lastShot_) > fireRate_ * 10)
	{
		Missile * m = new Missile(position, direction, missileSpeed_, "'");
		m->setColor(color_);
		lastShot_ = current;
		return m;
	}
	return NULL;
}
