#include "MapEntity.h"
#include "Movement.h"
#include "System.h"
#include "Map.h"

int Movement::next_id = 0;

Movement::Movement() :
  id(next_id++),
  entity(NULL),
  xy(0, 0),
  last_move_date(0),
  suspended(false),
  when_suspended(0) {

}

Movement::~Movement() {

}

MapEntity* Movement::get_entity() {
	return entity;
}

void Movement::set_entity(MapEntity* entity) {
	this->entity = entity;
	if(entity == NULL) {
		xy.set_xy(0, 0);
	} else {
		this->xy.set_xy(entity->get_xy());
		entity->notify_movement_changed();
	}
	notify_moving_entity();
}

void Movement::set_x(int x) {
	set_xy(x, get_y());
}

void Movement::set_y(int y) {
	set_xy(get_x(), y);
}

void Movement::set_xy(const Rectangle& xy) {
    set_xy(xy.get_x(), xy.get_y());
}

void Movement::set_xy(int x, int y) {
	if(entity != NULL) {
		entity->set_xy(x, y);
		notify_position_changed();
	} else {
		this->xy.set_xy(x, y);
	}
	last_move_date = System::now();
	notify_moving_entity();
}

int Movement::get_x() {
	return (entity != NULL) ? entity->get_x() : xy.get_x();
}

int Movement::get_y() {
	return (entity != NULL) ? entity->get_y() : xy.get_y();
}

const Rectangle Movement::get_xy() {
	return (entity != NULL) ? entity->get_xy() : xy;
}

void Movement::translate_y(int dy) {
	translate_xy(0, dy);
}

void Movement::translate_x(int dx) {
	translate_xy(dx, 0);
}

void Movement::translate_xy(const Rectangle& dxy) {
	translate_xy(dxy.get_x(), dxy.get_y());
}

void Movement::translate_xy(int dx, int dy) {
	set_xy(get_x() + dx, get_y() + dy);
}

bool Movement::is_stopped() {
	return !is_started();
}

bool Movement::is_started() {
	return false;
}

bool Movement::is_finished() {
	return false;
}

bool Movement::test_collision_with_obstacles(const Rectangle& dxy) {
	return test_collision_with_obstacles(dxy.get_x(), dxy.get_y());
}

bool Movement::test_collision_with_obstacles(int dx, int dy) {
	if(entity == NULL) {
		return false;
	}
	Map& map = entity->get_map();
	// Place collision box where we want to check for collisions.
	Rectangle collision_box = entity->get_bounding_box();
	collision_box.move_xy(dx, dy);
	bool collision = map.test_collision_with_obstacles(collision_box, *entity);
	return collision;
}

bool Movement::test_collision_with_borders(int dx, int dy) {
	Map& map = entity->get_map();
	Rectangle collision_box = entity->get_bounding_box();
	collision_box.move_xy(dx, dy);
	return map.test_collision_with_border(collision_box);
}

void Movement::stop() {

}

bool Movement::is_suspended() {
	return suspended;
}

void Movement::set_suspended(bool suspended) {
	if(this->suspended != suspended) {
		this->suspended = suspended;
		uint32_t now = System::now();
		if(suspended) {
			when_suspended = now;
		}
	}
}

uint32_t Movement::get_when_suspended() {
	return when_suspended;
}

void Movement::notify_position_changed() {
	if(entity != NULL && !entity->is_removing()) {
		entity->notify_position_changed();
	}
}

void Movement::notify_obstacle_reached() {
	if(entity != NULL && !entity->is_removing()) {
		entity->notify_obstacle_reached();
	}
}

void Movement::notify_moving_entity() {}

void Movement::update() {

}

const Rectangle Movement::get_displayed_xy() {
	return get_xy();
}