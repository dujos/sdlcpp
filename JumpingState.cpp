#include "JumpingState.h"
#include "FreeState.h"
#include "Game.h"
#include "Hero.h"
#include "MapEntities.h"
#include "Map.h"
#include "StraightMovement.h"
#include "System.h"
#include "TargetMovement.h"

Hero::JumpingState::JumpingState(Hero& hero) :
	State(hero),
	end_jumping_date(0) {
	state_name = "JumpingState";
	//this->movement = new TargetMovement(220, 220, 120);
	this->movement = new StraightMovement(90, 120);
}

Hero::JumpingState::~JumpingState() {}

void Hero::JumpingState::start(State* previous_state) {
	State::start(previous_state);
	
	//hero.set_direction(1);
	hero.get_sprite().set_current_direction(1);
	hero.set_animation_direction(0);
	
	hero.set_animation_jumping();
	hero.set_movement(this->movement);
	end_jumping_date = System::now() + 580;
}

void Hero::JumpingState::stop(State* next_state) {
	State::stop(next_state);
	hero.clear_movement();
	end_jumping_date = 0;
}

void Hero::JumpingState::update() {
	State::update();
	uint32_t now = System::now();
	if(movement->is_finished() || now >= end_jumping_date) {
		end_jumping_date = 0;
		hero.set_state(new FreeState(hero));
	}
}

std::string Hero::JumpingState::get_state_name() {
	return state_name;
}