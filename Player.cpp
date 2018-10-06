#include "Player.hpp"

Player::Player(coord position) :
	Character(position, NONE, 100)
{
	name_ = "player";
}

Player::~Player() { /**/ }

std::string Player::getName() const { return name_; }

void Player::setName(std::string name) { name_ = name; }

Missile * Player::shoot(float timeLapse) const {
	return weapon_->shoot(timeLapse, position_, RIGHT);
}

void Player::collide() { /**/ }

int Player::move(float timeLapse, int x, int y) {
	//set direction
	int ret(Entity::move(timeLapse, x, y));
	direction_ = NONE;
	return ret;
}
