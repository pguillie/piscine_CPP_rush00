#include "Entity.hpp"

Entity::Entity(coord position, int speed, movement direction, float currentTime) :
	speed_(1 / (float)speed),
	direction_(direction),
	lastMoveTime_(currentTime)
{
	position_.x = position.x;
	position_.y = position.y;
}

Entity::~Entity() {}

coord Entity::getPosition() const { return this->position_; }

void Entity::move(float currentTime, int x, int y) {
	if (currentTime - lastMoveTime_ >= speed_) {
		switch (direction_) {
		case UP:
			if (position_.y > 0)
				position_.y--;
		case DOWN:
			if (position_.y < y)
				position_.y++;
		case RIGHT:
			if (position_.x < x)
				position_.x++;
		case LEFT:
			if (position_.x > 0)
				position_.x--;
		}
	}
}
