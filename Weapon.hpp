#ifndef WEAPON_H
#define WEAPON_H

#include "Missile.hpp"

class Weapon {

private:

	Weapon();
	Weapon(Weapon const &);
	Weapon & operator=(Weapon const &);

	float delay_;
	float paused_;
	int missileSpeed_;

public:

	Weapon(int speed);
	Weapon(int speed, int missileSpeed);
	~Weapon();

	Missile * shoot(float timeLapse, coord position, movement direction);

};

#endif
