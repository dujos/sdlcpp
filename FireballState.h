#ifndef FIREBALL_STATE_H
#define FIREBALL_STATE_H

#include "State.h"

class Hero::FireballState : public Hero::State {

public:
	FireballState(Hero& hero);
	~FireballState();

	void start(State* previous_state);
	std::string get_state_name();
	void update();
};

#endif