#ifndef RANDOM_MOVEMENT_H
#define RANDOM_MOVEMENT_H

#include "Type.h"
#include "StraightMovement.h"
#include "Rectangle.h"

class RandomMovement : public StraightMovement {

private:
	int speed;
	int max_distance;

	Rectangle movement_bounds;
	uint32_t next_direction_change_date;

public:
	RandomMovement(int speed, int max_distance);
	~RandomMovement();

	void notify_obstacle_reached();
	void notify_moving_entity();

	void set_max_distance(int max_distance);
	void set_next_direction();
	void update();
};


#endif