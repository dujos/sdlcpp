#include "CircleMovement.h"
#include "MapEntity.h"
#include "Geometry.h"
#include "System.h"
#include "Map.h"


CircleMovement::CircleMovement() :
  Movement(),
  center_entity(NULL),
  current_angle(0),
  starting_angle(current_angle),
  angle_increment(1),
  next_angle_date(System::now()),
  next_angle_delay(20),
  current_radius(75),
  duration(1000),
  end_movement_date(0),
  max_rotations(10),
  current_rotation_count(0),
  loop_delay(0),
  restart_date(System::now()) {
    set_center(Rectangle(100, 100));
}

CircleMovement::CircleMovement(int x, int y) :
  Movement(),
  center_entity(NULL),
  current_angle(0),
  starting_angle(current_angle),
  angle_increment(1),
  next_angle_date(System::now()),
  next_angle_delay(30),
  current_radius(75),
  duration(1000),
  end_movement_date(0),
  max_rotations(10),
  current_rotation_count(0),
  loop_delay(0),
  restart_date(System::now()) {
    set_center(Rectangle(x, y));
}

CircleMovement::CircleMovement(int x, int y, int radius) :
  Movement(),
  center_entity(NULL),
  current_angle(0),
  starting_angle(current_angle),
  angle_increment(1),
  next_angle_date(System::now()),
  next_angle_delay(30),
  current_radius(radius),
  duration(1000),
  end_movement_date(0),
  max_rotations(10),
  current_rotation_count(0),
  loop_delay(0),
  restart_date(System::now()) {
    set_center(Rectangle(x, y));
}

CircleMovement::~CircleMovement() {

}

void CircleMovement::set_center(const Rectangle& center_point) {
	this->center_point = center_point;
	recompute_movement();
}

void CircleMovement::set_center(MapEntity& center_entity) {
	this->center_entity = &center_entity;
	this->center_point.set_xy(center_entity.get_center_point().get_x(),
		center_entity.get_center_point().get_y());
	recompute_movement();
}

void CircleMovement::set_radius(int radius) {
	this->current_radius = radius;
	recompute_movement();
}

void CircleMovement::set_angle_speed(int angle_speed) {
	this->next_angle_delay = 1000 / angle_speed;
	this->next_angle_date = System::now();
	recompute_movement();
}

void CircleMovement::set_starting_angle(double starting_angle) {
	this->starting_angle = Geometry::radians_to_degrees(starting_angle);
}

void CircleMovement::set_loop(uint32_t delay) {
	this->loop_delay = delay;
	if(loop_delay != 0 && is_stopped()) {
		this->restart_date = System::now() + delay;
	}
}

void CircleMovement::set_duration(uint32_t duration) {
	this->duration = duration;
	if(duration != 0 && is_started()) {
		this->end_movement_date = System::now() + duration;
	}
}

void CircleMovement::set_max_rotations(int max_rotations) {
	max_rotations = max_rotations;
	current_rotation_count = 0;
}

void CircleMovement::start() {
	current_angle = starting_angle;
	next_angle_date = System::now();
	current_rotation_count = 0;

	if(duration != 0) {
		end_movement_date = System::now() + duration;
	}
	recompute_movement();
}

void CircleMovement::stop() {
	set_radius(0);
	if(loop_delay != 0) {
		restart_date = System::now() + loop_delay;
	}
	recompute_movement();
}

bool CircleMovement::is_started() {
	return current_radius != 0;
}

bool CircleMovement::is_finished() {
	return is_stopped();
}

void CircleMovement::update() {
	Movement::update();

	bool update_needed = false;
	uint32_t now = System::now();

	if(is_started()) {
		while(now >= next_angle_date) {
		    current_angle += angle_increment;
		    current_angle = (360 + current_angle) % 360;
		    if(current_angle == starting_angle) {
			    current_rotation_count++;
			    if(current_rotation_count == max_rotations) {
				    stop();
			    }
		    }
			next_angle_date += next_angle_delay; 
		    update_needed = true;
		}
	}

	if(center_entity != NULL) {
		update_needed = true;
	}

	if(update_needed) {
		recompute_movement();
	}
}

void CircleMovement::recompute_movement() {
	Rectangle center = center_point;
	if(center_entity != NULL) {
		center.move_xy(center_entity->get_xy());
	}
	const Rectangle& xy = Geometry::get_xy(center, Geometry::degrees_to_radians(current_angle), current_radius);
	if(get_entity() != NULL) {
		if(!test_collision_with_obstacles(xy.get_x(), xy.get_y())) {
			set_xy(xy);
			notify_position_changed();
		} else {
            notify_obstacle_reached();
		}
	}
}
