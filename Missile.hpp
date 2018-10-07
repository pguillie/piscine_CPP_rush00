#ifndef MISSILE_H
#define MISSILE_H

#include "Entity.hpp"

class Missile : public Entity {

private:

	Missile();
	Missile(Missile const &);
	Missile & operator=(Missile const &);

public:

	Missile(coord pos, movement dir, int speed, std::string design);
	virtual ~Missile();
	
	void setColor(int color);
	void collide();

};

#endif
