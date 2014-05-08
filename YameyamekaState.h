#ifndef YAMEYAMEKA_STATE_H
#define YAMEYAMEKA_STATE_H

#include "State.h"

class Hero::YameyamekaState : public Hero::State {

public:
	YameyamekaState(Hero& hero);
	~YameyamekaState();

	void start(State* previous_state);
	void update();
	std::string get_state_name();
};

#endif