#ifndef TARGET_MOVEMENT_H
#define TARGET_MOVEMENT_H

#include "Type.h"
#include "StraightMovement.h"

class TargetMovement : public StraightMovement {

private:
	int target_x;
	int target_y;

	int sign_x;
	int sign_y;

	int moving_speed;

	uint32_t next_recompute_movement_date;
	static const uint32_t recompute_movement_delay;

	bool finished;
	void recompute_movement();

public:
	TargetMovement(int target_x, int target_y, int moving_speed);
	~TargetMovement();

	void set_target(int target_x, int target_y);
	void set_moving_speed(int moving_speed);

	bool is_finished();

	void update();

};

#endif