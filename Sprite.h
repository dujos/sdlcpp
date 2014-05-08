#ifndef SPRITE_H
#define SPRITE_H

#include "Displayable.h"
#include <map>
#include <string>

/**
 * Create a sprite with a specific set of animations.
 * A sprite is an instance of SpriteAnimationSet.
 * current animation, current direction and a current frame.
 */
class Sprite : public Displayable {

private:
	// animation set
	static std::map<std::string, SpriteAnimationSet*> all_animations_set;

	int current_frame;									/** current frame of the animation */
	int current_animation_direction;					/** current direction of the animation */
	bool frame_changed;									/** indicator frame has changed */

	bool finished;										/** true if animation has been stopped because last frame has been reached */

	uint32_t frame_delay;								/** delay between two frames */
	uint32_t next_frame_date;							/** date of the next frame */
	
	SpriteAnimation* current_animation;					/** current animation */
	std::string current_animation_name;					/** name of current animation */

	SpriteAnimationSet& current_animation_set;			/** animation set od this sprite */
	const std::string current_animation_set_id;			/** id of this sprite animation set */

    static SpriteAnimationSet& get_current_animation_set(const std::string& id);

public:
	static void quit();

	// creation and destruction.
	Sprite(const std::string& id);
	~Sprite();

	//animation
	void set_current_animation(const std::string& animation_name);
	std::string get_current_animation_name();
	void set_current_frame(int frame);
	int get_current_frame() const;
	void set_current_direction(int dir);
	int get_current_direction() const;
	int get_current_animation_direction(int key_direction);
	const Rectangle& get_size() const;
	const Rectangle& get_origin() const;
	int get_next_frame() const;
	
	bool is_animation_finished() const;

	void set_frame_delay(uint32_t frame_delay);
	uint32_t get_frame_delay() const;
	bool has_frame_changed();

	// map.
	void set_map(Map& map);

	// effects.
	//bool is_blinking() const;
	//void set_blinking(uint32_t blink_delay);

	void start_animation();
	void restart_animation();
	void stop_animation();

	// update and display.
	void update();
	void raw_display(Surface& dst_surface, const Rectangle& dst_position);
	void raw_display(Surface& dst_surface, int x, int y);
};


#endif