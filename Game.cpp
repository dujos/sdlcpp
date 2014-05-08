#include "Game.h"
#include "Hero.h"
#include "Map.h"
#include "Surface.h"
#include "Hud.h"
#include "Enemy.h"
#include "Bubble.h"
#include "Fire.h"

Game::Game() :
  map(NULL),
  game_over(NULL) {
	controls = new GameControls(*this);
	equipment = new Equipment(*this);
	hero = new Hero();
	hud = new Hud(*this);
	set_map();
	hero->set_map(*map);
}

Game::~Game() {
	delete controls;
	delete map;
	delete hud;
	delete equipment;
}

void Game::notify_input(InputEvent& event) {
	controls->notify_input(event);
}

void Game::key_pressed(GameControls::GameKey key) {
	hero->notify_control_pressed(key);
}

void Game::key_released(GameControls::GameKey key) {
	hero->notify_control_released(key);
}

void Game::set_map() {
	if(map == NULL) {
		this->map = new Map(*this);
	}
}

Map& Game::get_map() {
	return *map;
}

GameControls& Game::get_controls() {
	return *controls;
}

Hero& Game::get_hero() {
	return *hero;
}

const Rectangle& Game::get_hero_xy() {
	return hero->get_xy();
}

Equipment& Game::get_equipment() {
	return *equipment;
}

void Game::start_game_over() {
	//if(game_over == NULL)
	//	game_over = new GameOver(*this, hero->get_animation_direction());
}

bool Game::is_game_over() {
	return game_over != NULL;
}

void Game::update_game_over() {
	if(!game_over->is_state_finished()) {
		game_over->update();
	} else {
		delete game_over;
		game_over = NULL;
	}
}

void Game::update() {
	map->update();
	hud->update();

	//if(is_game_over())
	//	update_game_over();
}

void Game::get_hero_dead() {
	hero->start_hero();
}

void Game::display(Surface& dst_surface) {
	map->get_visible_surface().display(dst_surface);
	map->display();
	hud->display(dst_surface);

	//if(is_game_over())
	//	game_over->display(dst_surface);
}

