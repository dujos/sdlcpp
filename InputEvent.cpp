#include "InputEvent.h"
#include <iostream>

const InputEvent::KeyboardKey InputEvent::directional_keys[] = {
	KEY_RIGHT,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_NONE
};

void InputEvent::init() {
	SDL_EnableUNICODE(SDL_ENABLE);
	SDL_EnableKeyRepeat(0, 0);
}

InputEvent::InputEvent(const SDL_Event& event) :
  internal_event(event) {
}

InputEvent::~InputEvent() {}

InputEvent* InputEvent::get_event() {
	InputEvent* result = NULL;
	SDL_Event internal_event;
	if(SDL_PollEvent(&internal_event)) {
		result = new InputEvent(internal_event);
	}
	return result;
}

bool InputEvent::is_keyboard_event() {
	return internal_event.type == SDL_KEYDOWN
		|| internal_event.type == SDL_KEYUP;
}

bool InputEvent::is_window_closing() {
	return internal_event.type == SDL_QUIT;
}

bool InputEvent::is_keyboard_key_pressed() {
	return internal_event.type == SDL_KEYDOWN;
}

bool InputEvent::is_keyboard_key_pressed(KeyboardKey key) {
	return is_keyboard_key_pressed() 
		&& get_keyboard_key() == key;
}

bool InputEvent::is_keyboard_key_pressed(const KeyboardKey* keys) {
	while(*keys != KEY_NONE) {
		if(is_keyboard_key_pressed(*keys)) {
			return true;
		}
		keys++;
	}
	return false;
}

bool InputEvent::is_keyboard_direction_key_pressed() {
	return is_keyboard_key_pressed(directional_keys);
}

bool InputEvent::is_keyboard_non_direction_key_pressed() {
	return is_keyboard_key_pressed() 
		&& !is_keyboard_direction_key_pressed();
}

bool InputEvent::is_keyboard_key_released() {
	return internal_event.type == SDL_KEYUP;
}

bool InputEvent::is_keyboard_key_released(KeyboardKey key) {
	return is_keyboard_key_released() 
		&& get_keyboard_key() == key;
}

bool InputEvent::is_keyboard_key_released(const KeyboardKey* keys) {
		while(*keys != KEY_NONE) {
		if(is_keyboard_key_released(*keys)) {
			return true;
		}
		keys++;
	}
	return false;
}

bool InputEvent::is_keyboard_direction_key_released() {
	return is_keyboard_key_released(directional_keys);
}

bool InputEvent::is_keyboard_non_direction_key_released() {
	return is_keyboard_key_released() 
		&& !is_keyboard_direction_key_released();
}

InputEvent::KeyboardKey InputEvent::get_keyboard_key() {
	if(!is_keyboard_event()) {
		return KEY_NONE;
	}
	return KeyboardKey(internal_event.key.keysym.sym);
}