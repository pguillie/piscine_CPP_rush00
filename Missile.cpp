#include "Missile.hpp"

Missile::Missile(coord position, movement direction, int speed, std::string design) :
	Entity(position, direction, speed, design) {}

Missile::~Missile() { /**/ }

void Missile::collide() { /**/ }
