#ifndef GAME_H
#define GAME_H

#include "Equipment.h"
#include "GameOver.h"
#include "GameControls.h"
#include "Type.h"

class Game {

private:
	Equipment* equipment;
	Hero* hero;
	Map* map;
	GameControls* controls;
	Hud* hud;
	GameOver* game_over;

public:
	Game();
	~Game();

	void notify_input(InputEvent& event);

	//game controls
	void key_pressed(GameControls::GameKey key);
	void key_released(GameControls::GameKey key);

	//map
	void set_map();
	Map& get_map();

	GameControls& get_controls();
	Hero& get_hero();
	const Rectangle& get_hero_xy();
	void get_hero_dead();
	Equipment& get_equipment();

	void start_game_over();
	bool is_game_over();

	void update_game_over();

	void update();
	void display(Surface& dst_surface);
};

#endif