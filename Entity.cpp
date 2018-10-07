#include "Entity.hpp"

Entity::Entity(coord position, movement direction, int speed, std::string design) :
	direction_(direction),
	delay_(1 / (float)speed),
	design_(design)
{
	position_.y = position.y;
	position_.x = position.x;
}

Entity::~Entity() {}

coord Entity::getPosition() const { return position_; }

float Entity::getDelay() const { return delay_; }

int Entity::getSpeed() const { return 1 / delay_; }

std::string Entity::getDesign() const { return design_; }

int Entity::move(float timeLapse, int y, int x) {
	paused_ -= timeLapse;
	if (paused_ <= 0) {
		switch (direction_) {
		case NONE:
			return 0;
		case UP:
			if (position_.y > 1)
				position_.y--;
			else
				return -1;
			break;
		case DOWN:
			if (position_.y < y - 1)
				position_.y++;
			else
				return -1;
			break;
		case RIGHT:
			if (position_.x < x - 2)
				position_.x += 2;
			else
				return -1;
			break;
		case LEFT:
			if (position_.x > 2)
				position_.x -= 2;
			else
				return -1;
			break;
		}
		paused_ = delay_;
		return 1;
	}
	return 0;
}
