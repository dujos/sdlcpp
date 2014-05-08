#ifndef GAME_CONTROLS_H
#define GAME_CONTROLS_H

#include "Type.h"
#include "InputEvent.h"
#include <map>
#include <string>

class GameControls {

public:
	enum GameKey {NONE, RIGHT, UP, LEFT, DOWN, FIREBALL};

private:
	Game& game;
	bool keys_pressed[6];

	void game_key_pressed(GameKey key);
	void game_key_released(GameKey key);

	std::map<InputEvent::KeyboardKey, GameKey> keyboard_map;

	//keyboard mapping
	void key_pressed(InputEvent::KeyboardKey key_pressed);
	void key_released(InputEvent::KeyboardKey key_released);

    static const uint16_t direction_masks[4];
	static const int masks_to_directions8[16];

public:
	GameControls(Game& game);
	~GameControls();

	void notify_input(InputEvent &event);

	bool is_key_pressed(GameKey game_key);
	int get_current_direction8();
};

#endif