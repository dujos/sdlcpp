#include "DamageState.h"
#include "FreeState.h"
#include "Game.h"
#include "Geometry.h"
#include "System.h"
#include "PlayerMovement.h"

Hero::DamageState::DamageState(Hero& hero, const Rectangle& dmg_source_xy) :
  State(hero),
  dmg_source_xy(dmg_source_xy),
  end_damage_date(0) {
	state_name = "DamageState";
}

Hero::DamageState::~DamageState() {}

void Hero::DamageState::start(State* previous_state) {
	State::start(previous_state);
	hero.clear_movement();
	hero.set_animation_damage();
	end_damage_date = System::now() + 20;
}

void Hero::DamageState::update() {
	State::update();
	uint32_t now = System::now();
	if(hero.is_animation_finished()) {
		hero.start_hero();
	}
}

std::string Hero::DamageState::get_state_name() {
	return state_name;
}

void Hero::DamageState::stop(State* next_state) {
	State::stop(next_state);
	hero.clear_movement();
}