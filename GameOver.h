#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "Surface.h"
#include "Sprite.h"
#include "TargetMovement.h"
#include "GameControls.h"
#include "Game.h"

class Sprite;

class GameOver {

protected:
	enum State {
		WAIT_START,
		DYING,
		RED_SCREEN,
		BLACK_SCREEN,
		FAIRY,
		WAIT_END,
		RESUME,
		MENU
	};

private:
	Game& game;
	
	Surface game_over_surface;
	Sprite hero_dead;
	Sprite fade_away;
	Sprite fairy;
	TargetMovement* fairy_movement;

	int hero_dead_x;
	int hero_dead_y;
	int fairy_x;
	int fairy_y;

	State state;
	uint32_t next_state_date;
	uint32_t date_interval;

public:
	GameOver(Game& game, int hero_direction);
	~GameOver();

	bool is_state_finished();

	void update();
	void display(Surface& dst_surface);
};

#endif