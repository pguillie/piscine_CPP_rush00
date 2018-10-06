#ifndef ENTITY_H
# define ENTITY_H

enum movement {	UP,	DOWN, RIGHT, LEFT };

typedef struct coordonnees {
	int x;
	int y;
} coord;

class Entity {

private:

	Entity();
	Entity(Entity const &);
	Entity & operator=(Entity const &);

	coord position_;
	float speed_; // ( 1 / speedFormUser )
	movement direction_;
	float lastMoveTime_;

public:

	Entity(coord position, int speed, movement direction, float currentTime);
	virtual ~Entity();

	coord getPosition() const;

	virtual void collide() = 0;
	void move(float currentTime, int x, int y);

};

#endif
