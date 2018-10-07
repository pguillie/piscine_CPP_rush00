#include "Character.hpp"

Character::Character(coord position, movement direction, int speed, std::string design) :
	Entity(position, direction, speed, design)
{
	weapon_ = NULL;
}

Character::~Character() { /**/ }

void Character::setWeapon(Weapon * w) { weapon_ = w; }

Missile * Character::shoot(float timeLapse) const {
	if (weapon_)
		return weapon_->shoot(timeLapse, position_, direction_);
	return (NULL);
}

void Character::collide() { /**/ }
