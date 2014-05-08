#include "Geometry.h"
#include "RandomMovement.h"
#include "Random.h"
#include "System.h"

RandomMovement::RandomMovement(int speed, int max_distance) :
  StraightMovement(120, speed),
  speed(speed),
  max_distance(max_distance),
  next_direction_change_date(0) {
	set_next_direction();
}

RandomMovement::~RandomMovement() {}

void RandomMovement::notify_obstacle_reached() {
	StraightMovement::notify_obstacle_reached();
	set_next_direction();
}

void RandomMovement::notify_moving_entity() {
	StraightMovement::notify_moving_entity();
	set_max_distance(max_distance);
}

void RandomMovement::set_next_direction() {
	int direction = Random::get_rand(8);
	float angle = 0;
	if(direction == 0) {
		angle = 0;
	} else if(direction == 1) {
		angle = 45;
	} else if(direction == 2) {
		angle = 90;
	} else if(direction == 3) {
		angle = 135;
	} else if(direction == 4) {
		angle = 180;
	} else if(direction == 5) {
		angle = 225;
	} else if(direction == 6) {
		angle = 270;
	} else if(direction == 7) {
		angle = 315;
	}

	set_angle(Geometry::degrees_to_radians(angle));
	set_speed(speed);

	next_direction_change_date = System::now() + 4000;
}

void RandomMovement::set_max_distance(int max_distance) {
	this->movement_bounds.set_xy(get_xy());
	this->movement_bounds.move_xy(max_distance, max_distance);
	this->movement_bounds.set_size(max_distance*2, max_distance*2);
}

void RandomMovement::update() {
	StraightMovement::update();
	uint32_t now = System::now();
	if(now >= next_direction_change_date) {
		set_next_direction();
	}
}