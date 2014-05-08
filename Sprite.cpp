#include "Sprite.h"
#include "SpriteAnimation.h"
#include "SpriteAnimationDirection.h"
#include "SpriteAnimationSet.h"
#include "Game.h"
#include "Map.h"
#include "Surface.h"
#include "System.h"

std::map<std::string, SpriteAnimationSet*> Sprite::all_animations_set;

void Sprite::quit() {
	std::map<std::string, SpriteAnimationSet*>::iterator it;
	for(it = all_animations_set.begin(); it != all_animations_set.end(); it++) {
		delete it->second;
	}
	all_animations_set.clear();
}

Sprite::Sprite(const std::string& id) :
  Displayable(),
  current_animation_set_id(id),
  current_animation_set(get_current_animation_set(id)),
  current_frame(-1),
  current_animation_direction(0),
  finished(false) {
  set_current_animation(current_animation_set.get_default_animation());
}

Sprite::~Sprite() {}

SpriteAnimationSet& Sprite::get_current_animation_set(const std::string& id) {
	if(all_animations_set.count(id) == 0) {
		all_animations_set[id] = new SpriteAnimationSet(id);
	}
	return *all_animations_set[id];
}

void Sprite::set_current_animation(const std::string& animation_name) {
	if(this->current_animation_name != animation_name) {
		SpriteAnimation* animation = current_animation_set.get_current_animation(animation_name);
		this->current_animation = animation;
		this->current_animation_name = animation_name;
		set_frame_delay(current_animation->get_frame_delay());
		set_current_frame(0);
	}
}

std::string Sprite::get_current_animation_name() {
	return this->current_animation_name;
}

void Sprite::set_current_frame(int frame) {
	finished = false;
	next_frame_date = System::now() + get_frame_delay();

	frame_changed = (current_frame != frame);
	this->current_frame = frame;
}

int Sprite::get_current_frame() const {
	return this->current_frame;
}

void Sprite::set_current_direction(int direction) {
	if(this->current_animation_direction != direction) {
		this->current_animation_direction = direction;
		set_current_frame(0);
	}
}

int Sprite::get_current_direction() const {
	return current_animation_direction;
}

int Sprite::get_current_animation_direction(int key_direction) {
	int result = -1;
	//no valid combination of directional keys: don't change the sprite's direction
    if(key_direction == -1) {
        result = -1;
    } else if(key_direction % 2 == 0) {
    //only one of the four main directions
        result = key_direction / 2;
	} else if(key_direction % 2 != 0) {
		if(key_direction == 3) {
			result = 1;
		} else if(key_direction == 1) {
			result = 1;
		} else if(key_direction == 7) {
			result = 3;
		} else if(key_direction == 5) {
			result = 3;
		}
	}
	return result;
}

const Rectangle& Sprite::get_size() const {
	const SpriteAnimation* animation = current_animation_set.get_current_animation(current_animation_name);
	return animation->get_direction(current_animation_direction)->get_size();
}

const Rectangle& Sprite::get_origin() const {
	const SpriteAnimation* animation = current_animation_set.get_current_animation(current_animation_name);
	return animation->get_direction(current_animation_direction)->get_origin();
}

int Sprite::get_next_frame() const {
	return current_animation->get_next_frame(current_animation_direction, current_frame);
}

bool Sprite::is_animation_finished() const {
	return finished;
}

void Sprite::set_frame_delay(uint32_t frame_delay) {
	this->frame_delay = frame_delay;
}

uint32_t Sprite::get_frame_delay() const {
	return frame_delay;
}

bool Sprite::has_frame_changed() {
	return frame_changed;
}

void Sprite::set_map(Map& map) {
	current_animation_set.set_map(map);
}

void Sprite::update() {
	int next_frame;
	uint32_t now = System::now();

	//only check for animation with multiple frames.
	while(!finished && now >= next_frame_date && get_frame_delay() > 0) {
		next_frame = get_next_frame();
	    if(next_frame == -1) {
			this->finished = true;
	    } else {
		    current_frame = next_frame;
			next_frame_date += get_frame_delay();
	    }
	}
}

void Sprite::raw_display(Surface& dst_surface, const Rectangle& dst_position) {
	if(!this->is_animation_finished() /*&& (blink_delay == 0 || blink_is_sprite_visible)*/) {
		current_animation->display(dst_surface, dst_position,
		current_animation_direction, current_frame);
	}
}

void Sprite::raw_display(Surface& dst_surface, int x, int y) {
	raw_display(dst_surface, Rectangle(x, y));
}

void Sprite::start_animation() {
	restart_animation();
}

void Sprite::restart_animation() {
	set_current_frame(0);
}

void Sprite::stop_animation() {
	finished = true;
}