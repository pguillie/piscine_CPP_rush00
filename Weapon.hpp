#ifndef WEAPON_H
#define WEAPON_H

#include "Missile.hpp"
#include <ctime>

class Weapon {

private:
	Weapon();
	Weapon(Weapon const &);
	Weapon & operator=(Weapon const &);
	int fireRate_;
	int missileSpeed_;
	std::clock_t lastShot_;
	int color_;

public:

	Weapon(int speed);
	Weapon(int speed, int missileSpeed);
	~Weapon();

	void setColor(int color);

	Missile *shoot(float timeLapse, coord position, movement direction);

};

#endif
