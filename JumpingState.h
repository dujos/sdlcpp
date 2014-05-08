#ifndef JUMPING_STATE_H
#define JUMPING_STATE_H

#include "TargetMovement.h"

#include "State.h"

class StraightMovement;
//class TargetMovement;

class Hero::JumpingState : public Hero::State {

private:
	//TargetMovement* movement;
	StraightMovement* movement;
	std::string state_name;
	uint32_t end_jumping_date;

public:
	JumpingState(Hero& hero);
	~JumpingState();

	void start(State* previous_state);
	void stop(State* next_state);
	void update();

	std::string get_state_name();
};

#endif