#include "PlayerMovement.h"
#include "GameControls.h"
#include "MapEntity.h"
#include "Geometry.h"
#include "Game.h"

#include <iostream>

PlayerMovement::PlayerMovement(int speed) :
  StraightMovement(),
  moving_speed(speed),
  current_direction8(-1) {
  
}

PlayerMovement::~PlayerMovement() {

}

void PlayerMovement::compute_movement() {
	if(current_direction8 == -1) {
		stop();
	} else {		
		set_angle(Geometry::degrees_to_radians(current_direction8 * 45));
		set_speed(moving_speed);
	}
	if(get_entity() != NULL) {
		get_entity()->notify_movement_changed();
	}
}

int PlayerMovement::get_current_direction8() {
	return current_direction8;
}

void PlayerMovement::set_moving_speed(int moving_speed) {
	this->moving_speed = moving_speed;
	compute_movement();
}

void PlayerMovement::update() {
	StraightMovement::update();
	if(get_entity() == NULL && !get_entity()->is_on_map()) {
		return;
	}	
	GameControls& controls = get_entity()->get_game().get_controls();
	int direction8 = controls.get_current_direction8();
	if(current_direction8 != direction8) {
		current_direction8 = direction8;
		compute_movement();
	}
}
