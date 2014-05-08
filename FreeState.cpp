#include "FreeState.h"
#include "Hero.h"
#include "PlayerMovementState.h"
#include "System.h"
#include "Game.h"

Hero::FreeState::FreeState(Hero& hero) :
	PlayerMovementState(hero) {
	state_name = "FreeState";
}

Hero::FreeState::~FreeState() {}

void Hero::FreeState::start(State* previous_state) {
	hero.set_animation_light();
	PlayerMovementState::start(previous_state);
}

void Hero::FreeState::stop(State* next_state) {
	PlayerMovementState::stop(next_state);
}

void Hero::FreeState::update() {
	PlayerMovementState::update();
}

bool Hero::FreeState::is_free() {
	return true;
}

bool Hero::FreeState::can_jump() {
	return true;
}

std::string Hero::FreeState::get_state_name() {
	return state_name;
}
