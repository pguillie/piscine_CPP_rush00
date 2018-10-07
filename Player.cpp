#include <ncurses.h>
#include "Player.hpp"

Player::Player(coord position, std::string design) :
	Character(position, NONE, 420, design)
{
	name_ = "player";
}

Player::~Player() { if (weapon_) delete weapon_; }

std::string Player::getName() const { return name_; }

void Player::setName(std::string name) { name_ = name; }

void Player::setDirection(movement direction) { direction_ = direction; }

Missile * Player::shoot(float timeLapse) const {
	coord missilePosition;
	missilePosition.y = position_.y - 1;
	missilePosition.x = position_.x + design_.length() / 2;
	return weapon_->shoot(timeLapse, missilePosition, UP);
}

void Player::collide() { /**/ }

int Player::move(float timeLapse, int y, int x) {
	int ret(Entity::move(timeLapse, y, x));
	direction_ = NONE;
	return ret;
}
