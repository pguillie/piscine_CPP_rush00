#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.hpp"
#include "Weapon.hpp"

class Character : public Entity {

private:

	Character();
	Character(Character const &);
	Character & operator=(Character const &);

protected:

	Weapon * weapon_;

public:

	Character(coord pos, movement dir, int speed);
	virtual ~Character();

	void setWeapon(Weapon * w);

	virtual Missile * shoot(float timeLapse) const;
	virtual void collide();

};

#endif
