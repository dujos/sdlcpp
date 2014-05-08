#include "GameControls.h"
#include "Game.h"
#include "Hero.h"

const uint16_t GameControls::direction_masks[4] = {
	0x0001,
	0x0002,
	0x0004,
	0x0008

};

const int GameControls::masks_to_directions8[16] = {
	-1,          //none, stop
	 0,          //right
	 2,          //up
	 1,          //right + up
	 4,          //left
	-1,          //left + right = stop
	 3,          //left + up
	-1,          //left + right + up = stop
	 6,          //down
	 7,          //down + right
	-1,          //down + right + up = stop
	-1,          //down + left + up = stop
	 5,          //down + left
	-1,          //down + left + right = stop
	-1,          //down + left + up = stop
	-1           //down + left + right + up = stop

};

GameControls::GameControls(Game& game) :
    game(game) {
	
	for(int i = 0; i < 7; i++)
		keys_pressed[i] = false;

	// TODO ESCAPE
	keyboard_map[InputEvent::KEY_NONE] = (GameKey) 0;
	keyboard_map[InputEvent::KEY_RIGHT] = (GameKey) 1;
	keyboard_map[InputEvent::KEY_UP] = (GameKey) 2;
	keyboard_map[InputEvent::KEY_LEFT] = (GameKey) 3;
	keyboard_map[InputEvent::KEY_DOWN] = (GameKey) 4;
	keyboard_map[InputEvent::KEY_1] = (GameKey) 5;
	keyboard_map[InputEvent::KEY_ESCAPE] = (GameKey) 6;
}

GameControls::~GameControls() {

}

void GameControls::notify_input(InputEvent &event) {
	if(event.is_keyboard_key_pressed())
		key_pressed(event.get_keyboard_key());
	else if(event.is_keyboard_key_released())
		key_released(event.get_keyboard_key());
}

void GameControls::key_pressed(InputEvent::KeyboardKey key_pressed) {
	GameKey key = keyboard_map[key_pressed];
	if(key != 0)
		game_key_pressed(key);
}

void GameControls::key_released(InputEvent::KeyboardKey key_released) {
	GameKey key = keyboard_map[key_released];
	if(key != 0) {
		game_key_released(key);
	}
}

void GameControls::game_key_pressed(GameKey key) {
	int index = key;
	if(keys_pressed[index])
		return;
	keys_pressed[index] = true;
	game.key_pressed(key);
}

void GameControls::game_key_released(GameKey key) {
	int index = key;
	if(!keys_pressed[index])
		return;
	keys_pressed[index] = false;
	game.key_released(key);
}

bool GameControls::is_key_pressed(GameKey game_key) {
	return keys_pressed[game_key];
}

int GameControls::get_current_direction8() {
	uint16_t direction_mask = 0x0000;
	if(is_key_pressed(RIGHT))
		direction_mask |= direction_masks[0];
	if(is_key_pressed(UP))
		direction_mask |= direction_masks[1];
	if(is_key_pressed(LEFT))
		direction_mask |= direction_masks[2];
	if(is_key_pressed(DOWN))
		direction_mask |= direction_masks[3];
	return masks_to_directions8[direction_mask];
}
