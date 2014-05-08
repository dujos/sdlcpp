#ifndef HERO_H
#define HERO_H

#include "Chest.h"
#include "GameControls.h"
#include "Ground.h"
#include "MapEntity.h"
#include "Rectangle.h"
#include <list>

class Hero : public MapEntity {

public:
	class State;
	class PlayerMovementState;
	class FreeState;
	class JumpingState;
	class FireballState;
	class YameyamekaState;
	class DamageState;

private:
	Sprite* tunic_sprite;
	Sprite* shadow_sprite;
	Sprite* light_sprite;
	std::list<State*> old_states;

	static const int normal_walking_speed;
	int walking_speed;

	// state
	State* state;
	void set_state(State* state);
	bool damaged;

	// ground.
	Ground ground;								/** Ground under the hero */
	Rectangle last_ground_coordinates;			/** Coordinates of the last hero position */
	Rectangle target_ground_coordinates;		/** Coordinates of the position where hero will move */
	uint32_t next_ground_date;					/** When something will happen with the ground */
	Rectangle hole_dxy;							/** Direction of movment when hero is attracted by a hole */

protected:
	void update_state();
	void update_movement();

public:
	Hero();
	~Hero();

	Sprite& get_tunic_sprite();
	Sprite& get_light_sprite();
	Sprite& get_shadow_sprite();

	EntityType get_entity_type();

	void notify_movement_changed();
	void notify_movement_finished();
	void notify_position_changed();
	void notify_obstacle_reached();
	void notify_control_pressed(GameControls::GameKey control);
	void notify_control_released(GameControls::GameKey control);

	bool is_animation_finished();

	//animation.
	void set_animation_direction(int direction);
	void set_animation_light();
	void set_animation_stopped();
	void set_animation_walking();
	void set_animation_falling();
	void set_animation_damage();
	void set_animation_jumping();
	void set_animation_hadouken();
	void set_animation_yameyameka();
	void set_animation_dying();

	//map.
	void set_map(Map& map);
	void check_game_over();

	//movement.
	void reset_movement();
	int get_walking_speed();
	void set_walking_speed(int walking_speed);
	int get_animation_direction();
	int get_movement_direction();

	//obstacles.
	bool is_obstacle_for(MapEntity& other);
	bool is_hole_obstacle();
	
	//collisions.
	void check_position();
	void notify_collision_with_sensor(Sensor& sensor);
	void notify_collision_with_jumper(Jumper& jumper);
	void notify_collision_with_fire(Fire& fire);
	void notify_collision_with_bubble(Bubble& bubble);
	void notify_collision_with_chest(Chest& chest);

	void start_jumping();
	void start_fireball();
	void start_yameyameka();
	void start_hero();

	//ground.
	Ground get_ground_tile();
	const Rectangle get_ground_point();
	void set_ground(Ground ground);

	//damage.
	void damage(MapEntity& source);
	void damage(const Rectangle& source_xy);
	bool is_damaged();
	void set_damaged(bool d);

	void update();
	void display_on_map();
};

#endif