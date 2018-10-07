#ifndef ENTITY_H
#define ENTITY_H

#include <string>

# define RED 1
# define GREEN 2

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
	std::string design_;
	int color_;

public:

	Entity(coord pos, movement dir, int speed, std::string design);
	virtual ~Entity();

	coord getPosition() const;
	float getDelay() const;
	int getSpeed() const;
	std::string getDesign() const;
	movement getDirection() const;
	int getColor() const;

	virtual void collide() = 0;
	virtual int move(float timeLapse, int y, int x);

};

#endif
