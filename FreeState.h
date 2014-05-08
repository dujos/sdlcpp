#ifndef FREE_STATE_H
#define FREE_STATE_H

#include "PlayerMovementState.h"

class Hero::FreeState : public Hero::PlayerMovementState {

public:
	FreeState(Hero& hero);
	~FreeState();

	void start(State* previous_state);
	void stop(State* next_state);
	void update();

	std::string get_state_name();
	bool is_free();
	bool can_jump();
};

#endif