#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

#include <SDL.h>
#include <string>

class InputEvent {

public:
	enum KeyboardKey {
		KEY_NONE = 0,
		KEY_ESCAPE = 27,
		KEY_SPACE = 32,
		KEY_1 = 49,
		KEY_2 = 50,
		KEY_UP = 273,
        KEY_DOWN = 274,
        KEY_RIGHT = 275,
        KEY_LEFT = 276,
	};

public:
	static void init();

private:
	SDL_Event internal_event;
	InputEvent(const SDL_Event& event);

	static const KeyboardKey directional_keys[];

public:
	~InputEvent();
	static InputEvent* get_event();

	bool is_keyboard_event();
	bool is_window_closing();

	bool is_keyboard_key_pressed();
	bool is_keyboard_key_pressed(KeyboardKey key);
	bool is_keyboard_key_pressed(const KeyboardKey* key);
	bool is_keyboard_direction_key_pressed();
	bool is_keyboard_non_direction_key_pressed();

	bool is_keyboard_key_released();
	bool is_keyboard_key_released(KeyboardKey key);
	bool is_keyboard_key_released(const KeyboardKey* key);
	bool is_keyboard_direction_key_released();
	bool is_keyboard_non_direction_key_released();

	KeyboardKey get_keyboard_key();

};

#endif