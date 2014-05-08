#include "TargetMovement.h"
#include "System.h"
#include "Geometry.h"

const uint32_t TargetMovement::recompute_movement_delay = 150;

TargetMovement::TargetMovement(int target_x, int target_y, int moving_speed) :
  StraightMovement(),
  target_x(target_x),
  target_y(target_y),
  moving_speed(moving_speed),
  sign_x(0),
  sign_y(0),
  next_recompute_movement_date(System::now()),
  finished(false) {
  
}

TargetMovement::~TargetMovement() {

}

void TargetMovement::set_target(int target_x, int target_y) {
	this->target_x = target_x;
	this->target_y = target_y;
	recompute_movement();
	next_recompute_movement_date = System::now() + recompute_movement_delay;
}

void TargetMovement::set_moving_speed(int moving_speed) {
	this->moving_speed = moving_speed;
	recompute_movement();
}

void TargetMovement::recompute_movement() {
	if(get_x() != target_x || get_y() != target_y) {
		this->finished = false;

		double angle = Geometry::get_angle(get_x(),get_y(), target_x, target_y);
		int dx = target_x - get_x();
		int dy = target_y - get_y();

		sign_x = dx >= 0 ? 1 : -1;
		sign_y = dy >= 0 ? 1 : -1;

		if(std::fabs(angle - get_angle()) > 1E-6 || get_speed() < 1E-6) {
		    set_speed(moving_speed);
		    set_angle(angle);
		}
	}
}

bool TargetMovement::is_finished() {
	return finished;
}

void TargetMovement::update() {
	int dx = target_x - get_x();
	int dy = target_y - get_y();
	int now = System::now();

	if(now >= next_recompute_movement_date) {
		recompute_movement();
		next_recompute_movement_date += recompute_movement_delay;
	}

	if(dx*sign_x <= 0 && dy*sign_y <= 0) {
		set_xy(target_x, target_y);
		stop();
		finished = true;
	}
	StraightMovement::update();
}
