#ifndef PLAYER_H
#define PLAYER_H

#include "Character.hpp"

class Player : public Character {

private:

	Player();
	Player(Player const &);
	Player & operator=(Player const &);

	std::string name_;

public:

	Player(coord position);
	virtual ~Player();

	std::string getName() const;
	void setName(std::string name);

	void setDirection(movement dir);

	virtual Missile * shoot(float timeLapse) const;
	void collide();
	int move(float timeLapse, int x, int y);

};

#endif
