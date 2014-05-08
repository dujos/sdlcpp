#include "PlayerMovementState.h"
#include "FireballState.h"
#include "MapEntities.h"
#include "FreeState.h"
#include "Fireball.h"
#include "Hero.h"

Hero::FireballState::FireballState(Hero& hero) :
  State(hero) {
	state_name = "HadoukenState";
}

Hero::FireballState::~FireballState() {}

void Hero::FireballState::start(State* previous_state) {
	State::start(previous_state);
	hero.set_animation_hadouken();
}

void Hero::FireballState::update() {
	State::update();
	if(hero.is_animation_finished()) {
		hero.get_entities().add_entity(new Fireball(hero, 160));
		hero.set_state(new FreeState(hero));
	}
}

std::string Hero::FireballState::get_state_name() {
	return this->state_name;
}