#ifndef SPRITE_ANIMATION_SET
#define SPRITE_ANIMATION_SET

#include "Rectangle.h"
#include "Type.h"

#include <string>
#include <map>

class SpriteAnimationSet {

private:
	std::map<std::string, SpriteAnimation*> animations;
	std::string default_animation;
	Rectangle max_size;

public:
	SpriteAnimationSet(const std::string& id);
	~SpriteAnimationSet();

	const std::string& get_default_animation() const;
	SpriteAnimation* get_current_animation(const std::string& animation_name);

	void set_map(Map& map);
};

#endif>