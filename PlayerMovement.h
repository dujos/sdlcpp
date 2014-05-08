#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include "StraightMovement.h"

class PlayerMovement: public StraightMovement {

protected:
	int moving_speed;
	int current_direction8;

public:
	PlayerMovement(int speed);
	virtual ~PlayerMovement();

	int get_current_direction8();
	void compute_movement();

	void set_moving_speed(int moving_speed);

	void update();

};

#endif