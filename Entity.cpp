#include "Entity.hpp"

Entity::Entity(coord position, movement direction, int speed) :
	direction_(direction),
	delay_(1 / (float)speed)
{
	position_.x = position.x;
	position_.y = position.y;
}

Entity::~Entity() {}

coord Entity::getPosition() const { return position_; }

float Entity::getDelay() const { return delay_; }

int Entity::getSpeed() const { return 1 / delay_; }

int Entity::move(float timeLapse, int x, int y) {
	paused_ -= timeLapse;
	if (paused_ <= 0) {
		switch (direction_) {
		case NONE:
		case UP:
			if (position_.y > 0)
				position_.y--;
			else
				return -1;
		case DOWN:
			if (position_.y < y)
				position_.y++;
			else
				return -1;
		case RIGHT:
			if (position_.x < x)
				position_.x++;
			else
				return -1;
		case LEFT:
			if (position_.x > 0)
				position_.x--;

			return -1;
		}
		paused_ = delay_;
		return 1;
	}
	return 0;
}
