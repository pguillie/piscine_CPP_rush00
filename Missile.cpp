#include "Missile.hpp"

Missile::Missile(coord position, movement direction, int speed) :
	Entity(position, direction, speed) {}

Missile::~Missile() { /**/ }

void Missile::collide() { /**/ }
