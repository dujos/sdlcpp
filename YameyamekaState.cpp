#include "PlayerMovementState.h"
#include "MapEntities.h"
#include "YameyamekaState.h"
#include "FreeState.h"
#include "Hero.h"

Hero::YameyamekaState::YameyamekaState(Hero& hero) :
	State(hero) {
	state_name="YameyamekaState";
}

Hero::YameyamekaState::~YameyamekaState() {}

void Hero::YameyamekaState::start(State* previous_state) {
	State::start(previous_state);
	hero.set_animation_yameyameka();
}

void Hero::YameyamekaState::update() {
	State::update();
	if(hero.is_animation_finished()) {
		hero.set_state(new FreeState(hero));
	}
}

std::string Hero::YameyamekaState::get_state_name() {
	return this->state_name;
}