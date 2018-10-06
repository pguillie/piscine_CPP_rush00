#include "Character.hpp"

Character::Character(coord position, movement direction, int speed) :
	Entity(position, direction, speed) {}

Character::~Character() { /**/ }

void Character::setWeapon(Weapon * w) { weapon_ = w; }

Missile * Character::shoot(float timeLapse) const {
	return weapon_->shoot(timeLapse, position_, direction_);
}

void Character::collide() { /**/ }
