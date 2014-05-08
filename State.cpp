#include "Sprite.h"
#include "System.h"
#include "State.h"
#include "Hero.h"
#include "Game.h"
#include "Map.h"

Hero::State::State(Hero& hero) :
  map(&hero.get_map()),
  hero(hero),
  state_name("") {}

Hero::State::~State() {}

Map& Hero::State::get_map() {
	return *map;
}

MapEntities& Hero::State::get_entities() {
	return map->get_entities();
}

Game& Hero::State::get_game() {
	return map->get_game();
}

GameControls& Hero::State::get_controls() {
	return get_game().get_controls();
}

void Hero::State::start(State* last_state) {}

void Hero::State::stop(State* next_state) {}

void Hero::State::update() {}

void Hero::State::display_on_map() {
	const Rectangle& displayed_xy = hero.get_displayed_xy();
	int x = displayed_xy.get_x();
	int y = displayed_xy.get_y();

	Map& map = hero.get_map();
	map.display_sprite(hero.get_light_sprite(), x, y);
	map.display_sprite(hero.get_tunic_sprite(), x, y);
}

bool Hero::State::is_current_state() {
	return hero.state == this;
}

bool Hero::State::can_control_movement() {
	return false;
}

bool Hero::State::can_start_game_over() {
	return false;
}

void Hero::State::notify_position_changed() {}

void Hero::State::notify_movement_finished() {}

void Hero::State::notify_movement_changed() {}

void Hero::State::notify_obstacle_reached() {}

void Hero::State::notify_walking_speed_changed() {}

void Hero::State::notify_control_pressed(GameControls::GameKey control) {
	switch(control) {
		case GameControls::FIREBALL:
			//notify_action_control_pressed(GameControls::FIREBALL);
			hero.start_fireball();
			break;
		case GameControls::RIGHT:
			notify_direction_control_pressed(1);
			break;
		case GameControls::DOWN:
			notify_direction_control_pressed(4);
			break;
		case GameControls::LEFT:
			notify_direction_control_pressed(3);
			break;
		case GameControls::UP:
			notify_direction_control_pressed(2);
			break;
		default:
			break;
	}
}

void Hero::State::notify_control_released(GameControls::GameKey control) {
	switch(control) {
		case GameControls::RIGHT:
			notify_direction_control_released(1);
			break;
		case GameControls::DOWN:
			notify_direction_control_released(4);
			break;
		case GameControls::LEFT:
			notify_direction_control_released(3);
			break;
		case GameControls::UP:
			notify_direction_control_released(2);
			break;
		default:
			break;
	}
}

void Hero::State::notify_direction_control_pressed(int direction4) {

}

void Hero::State::notify_direction_control_released(int direction4) {

}

void Hero::State::notify_action_control_pressed(int action) {
}

int Hero::State::get_movement_direction8() {
	return -1;
}

bool Hero::State::is_hole_obstacle() {
	return false;
}

bool Hero::State::can_avoid_hole() {
	return false;
}

bool Hero::State::can_jump() {
	return false;
}