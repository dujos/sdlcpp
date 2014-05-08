#include "StraightMovement.h"
#include "MapEntity.h"
#include "Geometry.h"
#include "Globals.h"
#include "System.h"

#include <cmath>

StraightMovement::StraightMovement() :
  Movement(),
  angle(0),
  speed_x(0),
  speed_y(0),
  move_x(0),
  move_y(0),
  next_move_date_x(System::now()),
  next_move_date_y(System::now()),
  finished(false) {

}

StraightMovement::StraightMovement(double angle, double speed) :
  Movement(),
  move_y(0),
  move_x(0),
  next_move_date_x(System::now()),
  next_move_date_y(System::now()),
  finished(false) {
	set_speed(speed);
	set_angle(Geometry::degrees_to_radians(angle));
	//set_angle(angle);
}

StraightMovement::~StraightMovement() {

}

void StraightMovement::set_suspended(bool suspended) {
	Movement::set_suspended(suspended);
	if(!suspended) {
		if(get_when_suspended() != 0) {
			uint32_t difference = System::now() - get_when_suspended();
			// Sets next move date.
			next_move_date_x += difference;
			next_move_date_y += difference;
		}
	}
}

void StraightMovement::set_speed_x(double speed_xx) {
	if(std::fabs(speed_xx) <= 1E-6) {
		speed_xx = 0;
	}
	this->speed_x = speed_xx;
	uint32_t now = System::now();

	// compute delay_x, move_x, next_move_date_x.
	if(speed_x > 0) {
		this->delay_x = (uint32_t) (1000 / this->speed_x);
		move_x = 1;
		set_next_move_date_x(now + delay_x);
	} else if(speed_x < 0) {
		this->delay_x = (uint32_t) (-1000 / this->speed_x);
		move_x = -1;
		set_next_move_date_x(now + delay_x);
	} else {
		move_x = 0;
	}

	this->angle = Geometry::get_angle(0.f, 0.f, speed_x * 100, speed_y * 100);
	start_xy.set_xy(get_xy());
	this->finished = false;

	if(get_entity() != NULL) {
		get_entity()->notify_movement_changed();
	}
}

void StraightMovement::set_speed_y(double speed_yy) {
	if(std::fabs(speed_yy) <= 1E-6) {
		speed_yy = 0;
	}
	this->speed_y = speed_yy;
	uint32_t now = System::now();

	// compute delay_x, move_x, next_move_date_x.
	if(speed_y > 0) {
		this->delay_y = (uint32_t) (1000 / this->speed_y);
		move_y = 1;
		set_next_move_date_y(now + delay_y);
	} else if(speed_y < 0) {
		this->delay_y = (uint32_t) (-1000 / this->speed_y);
		move_y = -1;
		set_next_move_date_y(now + delay_y);
	} else {
		move_y = 0;
	}

	this->angle = Geometry::get_angle(0.f, 0.f, speed_x * 100, speed_y * 100);
	start_xy.set_xy(get_xy());
	this->finished = false;

	if(get_entity() != NULL) {
		get_entity()->notify_movement_changed();
	}
}

void StraightMovement::set_next_move_date_x(uint32_t next_move_date_x) {
	if(is_suspended()) {
		uint32_t delay = next_move_date_x - System::now();
		this->next_move_date_x = get_when_suspended() + delay;
	} else {
		this->next_move_date_x = next_move_date_x;
	}
}

void StraightMovement::set_next_move_date_y(uint32_t next_move_date_y) {
	if(is_suspended()) {
		uint32_t delay = next_move_date_y - System::now();
		this->next_move_date_y = get_when_suspended() + delay;
	} else {
		this->next_move_date_y = next_move_date_y;
	}
}

void StraightMovement::set_speed(double speed) {
	if(speed_y == 0 && speed_x == 0) {
		speed_x = 1;
	}

	//compute the new speed vector.
	double old_angle = this->angle;
	set_speed_x(speed * std::cos(old_angle));
	set_speed_y(-speed * std::sin(old_angle));
	this->angle = old_angle;

	if(get_entity() != NULL) {
		get_entity()->notify_movement_changed();
	}
}

int StraightMovement::get_current_direction8() {
	int direction = (Geometry::radians_to_degrees(angle) + 360) / 45;
	return direction % 8;
}

double StraightMovement::get_speed() {
	return std::sqrt(speed_x * speed_x + speed_y * speed_y);
}

void StraightMovement::set_angle(double angle) {
	double speed = get_speed();
	set_speed_x(speed * std::cos(angle));
	set_speed_y(-speed * std::sin(angle));
	this->angle = angle;

	if(get_entity() != NULL) {
		get_entity()->notify_movement_changed();
	}
}

double StraightMovement::get_angle() {
	return this->angle;
}

void StraightMovement::set_finished() {
	stop();
	this->finished = true;
}

bool StraightMovement::is_finished() {
	return finished;
}

void StraightMovement::stop() {
	double old_angle = this->angle;
	set_speed_x(0);
	set_speed_y(0);
	this->move_x = 0;
	this->move_y = 0;
	this->angle = old_angle;

	if(get_entity() != NULL) {
		get_entity()->notify_movement_finished();
	}
}

void StraightMovement::notify_moving_entity() {
	Movement::notify_moving_entity();
	xy.set_xy(get_xy());
}

void StraightMovement::set_entity(MapEntity* entity) {
	Movement::set_entity(entity);
	start_xy.set_xy(get_xy());
}

void StraightMovement::update_x() {
	uint32_t next_move_time_x;
	if(move_x != 0) {	// entity wants to move in x direction.
		next_move_time_x = delay_x;
		if(!test_collision_with_obstacles(move_x, 0) && !test_collision_with_borders(move_x, 0)) {
			translate_x(move_x);	// no collision in x direction 
			if(move_y != 0 && test_collision_with_obstacles(0, move_y)) {
				// if there is also a y move and this move is stopped by an obstacles.
				next_move_time_x = (int) (1000 / get_speed());
				update_y();
			}
		}
	} else {	//entity does not want to move in x direction so we stop the movement.
	    stop();
	}
	next_move_date_x += next_move_time_x;
}

void StraightMovement::update_y() {
	uint32_t next_move_time_y = delay_y;
	if(move_y != 0) { //entity wants to move in y direction.
		next_move_time_y = delay_y;
		if(!test_collision_with_obstacles(0, move_y) && !test_collision_with_borders(0, move_y)) {
			translate_y(move_y);  //make the move on y
			if(move_x != 0 && test_collision_with_obstacles(move_x, 0)) {
				// if there is also a y move and this move is stopped by an obstacles.
				next_move_time_y = (int) (1000 / get_speed());
				update_x();
			}
		}
	} else {
		stop();
	}
	next_move_date_y += next_move_time_y;
}

void StraightMovement::update() {
	Movement::update();
	
	if(!is_suspended()) {
		uint32_t now = System::now();
		bool current_move_y = move_y != 0 && now >= next_move_date_y;
		bool current_move_x = move_x != 0 && now >= next_move_date_x;

		while(current_move_x || current_move_y) {
			// save current coordinates.
			Rectangle old_xy(get_x(), get_y());

			if(current_move_x) {	// time to move in x direction.
				if(current_move_y) {	// time to move in y direction.
					if(next_move_date_x <= next_move_date_y) {	//	we first move in x direction.
						update_x();
						if(now >= next_move_date_y) {
							update_y();
						}
					} else {
						update_y();								// we first move in y direciton.
						if(now >= next_move_date_x) {
							update_x();
						}
					}
				} else {	// we only move in x direction.
					update_x();
				}
			} else {	// we only move in y direction.
				update_y();
			}

			if(get_entity() != NULL && !finished) {
				// movement is successful old coordinates have changed.
				bool success = (get_x() != old_xy.get_x() || get_y() != old_xy.get_y()
					&& (move_x != 0 || move_y != 0));

				// no movement notify obstacle.
				if(!success) {
					notify_obstacle_reached();
					set_finished();
				}
			}

			// check if we continue wit movement.
			now = System::now();
			current_move_x = move_x != 0 && now >= next_move_date_x;
			current_move_y = move_y != 0 && now >= next_move_date_y;
		}
	}
}