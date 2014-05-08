#ifndef RED_KNIGHT_SOLDIER_H
#define RED_KNIGHT_SOLDIER_H

#include "Enemy.h"
#include "Game.h"

class RedKnightSoldier : public Enemy {

private:
	const int moving_speed;
	Sprite* soldier_sprite;
	Sprite* soldier_sword_sprite;
	Game& game;

public:
	RedKnightSoldier(const std::string& name, int x, int y, Game& game);
	~RedKnightSoldier();

	void set_animation(const std::string& animation);
	int get_animation_direction(); 

	void notify_movement_changed();
	void notify_obstacle_reached();
	void notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode);

	void update();
};

#endif