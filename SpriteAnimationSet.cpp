#include "SpriteAnimation.h"
#include "SpriteAnimationSet.h"
#include "SpriteAnimationDirection.h"


#include <sstream>
#include <iostream>
#include <fstream>

// load animations of a sprite from a file
SpriteAnimationSet::SpriteAnimationSet(const std::string& id) {
	//open file.
	std::ifstream sprite_file;
	sprite_file.open(id.c_str());

	Rectangle* position = NULL;
	SpriteAnimationDirection** directions = NULL;

	std::string animation; std::string image; int nb_directions; uint32_t frame_delay;
	int loop_on_frame;
	int x, y, width, height, origin_x, origin_y, nb_frames, columns;

	// read each animation.
	const int rows = 1;
	while(!sprite_file.eof()) {
		// first line.
		sprite_file >> animation >> image >> nb_directions >> frame_delay >> loop_on_frame;
		directions = new SpriteAnimationDirection*[nb_directions];
		
		for(int i = 0; i < nb_directions; i++) {
			sprite_file >> x >> y >> width >> height >> origin_x >> origin_y >> nb_frames >> columns;

			max_size.set_width(std::max(max_size.get_width(), width));
			max_size.set_height(std::max(max_size.get_height(), height));

			position = new Rectangle[nb_frames];

			int j = 0;
			for(int r = 0; r < rows && j < nb_frames; r++) {
				for(int c = 0; c < columns && j < nb_frames; c++) {
					position[j].set_xy(x + c * width, y + r * height);
				    position[j].set_size(width, height);
					j++;
				}
			}
			directions[i] = new SpriteAnimationDirection(nb_frames, position, origin_x, origin_y);
		}

		animations[animation] = new SpriteAnimation(image, nb_directions, directions, frame_delay, loop_on_frame);

		if(animations.size() == 1) {
			default_animation = animation;
		}
	}
	sprite_file.close();
}

SpriteAnimationSet::~SpriteAnimationSet() {
	std::map<std::string, SpriteAnimation*>::iterator it;
	for(it = animations.begin(); it != animations.end(); it++) {
		delete it->second;
	}
	animations.clear();
}

const std::string& SpriteAnimationSet::get_default_animation() const {
	return this->default_animation;
}

SpriteAnimation* SpriteAnimationSet::get_current_animation(const std::string& animation_name) {
	if(animations.count(animation_name) > 0) {
		return animations[animation_name];
	}
	return animations[default_animation];
}

void SpriteAnimationSet::set_map(Map& map) {
	std::map<std::string, SpriteAnimation*>::iterator it;
	for(it = animations.begin(); it != animations.end(); it++) {
		it->second->set_map(map);
	}
}