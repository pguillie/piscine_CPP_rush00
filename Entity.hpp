#ifndef ENTITY_H
#define ENTITY_H

#include <string>

enum movement { NONE, UP, DOWN, RIGHT, LEFT };

typedef struct coordonnees {
	int x;
	int y;
} coord;

class Entity {

private:

	Entity();
	Entity(Entity const &);
	Entity & operator=(Entity const &);

protected:

	coord position_;
	movement direction_;
	float delay_;
	float paused_;

public:

	Entity(coord pos, movement dir, int speed);
	virtual ~Entity();

	coord getPosition() const;
	float getDelay() const;
	int getSpeed() const;

	virtual void collide() = 0;
	virtual int move(float timeLapse, int x, int y);

};

#endif
