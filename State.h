#ifndef HERO_STATE_H
#define HERO_STATE_H

#include "Hero.h"
#include "GameControls.h"

class Hero::State {

protected:
	Hero& hero;
	Map* map;
	
	MapEntities& get_entities();
	Game& get_game();
	Map& get_map();
	GameControls& get_controls();

	std::string state_name;

public:
	State(Hero& hero);
	virtual ~State();

	virtual void start(State* last_state);
	virtual void stop(State* next_state);

	virtual void update();
	virtual void display_on_map();

	virtual std::string get_state_name()=0;

	bool is_current_state();

	// Movement.
	virtual bool can_control_movement();
	bool can_start_game_over();
	virtual void notify_position_changed();
	virtual void notify_movement_finished();
	virtual void notify_movement_changed();
	virtual void notify_obstacle_reached();
	virtual void notify_walking_speed_changed();
	virtual void notify_control_pressed(GameControls::GameKey control);
	virtual void notify_control_released(GameControls::GameKey control);
	virtual void notify_direction_control_pressed(int direction4);
	virtual void notify_direction_control_released(int direction4);
	virtual void notify_action_control_pressed(int action);
	virtual int get_movement_direction8();
	
	// Obstacles and collisions.
	virtual bool is_hole_obstacle();
	virtual bool can_avoid_hole();
	virtual bool can_jump();
};

#endif