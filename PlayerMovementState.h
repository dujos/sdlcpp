#ifndef PLAYER_MOVEMENT_STATE_H
#define PLAYER_MOVEMENT_STATE_H

#include "State.h"

class Hero::PlayerMovementState: public Hero::State {

public:
	PlayerMovementState(Hero& hero);
	virtual ~PlayerMovementState();
	PlayerMovement* get_player_movement();

	void start(State* last_state);
	void stop(State* next_state);

	std::string get_state_name();

	bool can_control_movement();
	void notify_walking_speed_changed();
	int get_movement_direction8();
	void notify_movement_changed();

	bool can_take_jumper();

};

#endif