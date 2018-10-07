#include <iostream>
#include "Enemy.hpp"
#include "Weapon.hpp"
#include <curses.h>

Enemy::Enemy(coord pos, movement dir, int speed, std::string design) :
	Character(pos, dir, speed, design),
	_attackSpeed(400),
	_timeUntilAttack(400)
{
	weapon_ = new Weapon(9000 + std::rand() % 5000, 50);
}

Enemy::~Enemy(void)
{
	delete weapon_;
}

Enemy &Enemy::operator=(Enemy const &rhs)
{
	(void)rhs;
	return *this;
}

Missile * Enemy::shoot(float timeLapse) const {
	coord missilePosition;
	missilePosition.y = position_.y + 2;
	missilePosition.x = position_.x + design_.length() / 2;
	return weapon_->shoot(timeLapse, missilePosition, DOWN);
}
