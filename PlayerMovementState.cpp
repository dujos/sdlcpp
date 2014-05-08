#include "PlayerMovementState.h"
#include "PlayerMovement.h"

Hero::PlayerMovementState::PlayerMovementState(Hero& hero) :
  State(hero) {
  state_name = "PlayerMovementState";
}

Hero::PlayerMovementState::~PlayerMovementState() {

}

PlayerMovement* Hero::PlayerMovementState::get_player_movement() {
	return (PlayerMovement*)hero.get_movement();
}

void Hero::PlayerMovementState::start(State* last_state) {
	hero.set_movement(new PlayerMovement(hero.get_walking_speed()));
	if(is_current_state()) {
		get_player_movement()->compute_movement();
		int direction8 = get_movement_direction8();
		if(direction8 != -1) {
			hero.set_animation_walking();
		} else {
			hero.set_animation_stopped();
		}
	}
}

void Hero::PlayerMovementState::stop(State* next_state) {
	hero.clear_movement();
	hero.set_animation_stopped();
}

std::string Hero::PlayerMovementState::get_state_name() {
	return this->state_name;
}

bool Hero::PlayerMovementState::can_control_movement() {
	return true;
}

void Hero::PlayerMovementState::notify_walking_speed_changed() {
	if(get_player_movement() != NULL) {
		get_player_movement()->set_moving_speed(hero.get_walking_speed());
	}
}

int Hero::PlayerMovementState::get_movement_direction8() {
	return get_player_movement()->get_current_direction8();
}

void Hero::PlayerMovementState::notify_movement_changed() {
	bool walking = get_movement_direction8() != -1;
	if(walking) {
		hero.set_animation_walking();
	} else {
		hero.set_animation_stopped();
	}
}

bool Hero::PlayerMovementState::can_take_jumper() {
	return false;
}