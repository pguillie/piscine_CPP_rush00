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
	Missile * missile_;

public:

	Weapon(Missile * missile);
	Weapon(int speed, Missile * missile);
	~Weapon();

	Missile * shoot(float timeLapse, coord position, movement direction);

};

#endif
