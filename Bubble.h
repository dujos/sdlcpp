#ifndef BUBBLE_H
#define BUBBLE_H

#include "Enemy.h"
#include "Game.h"

class Bubble : public Enemy {

private:
	const int moving_speed;
	Sprite* bubble_sprite;
	Game& game;

public:
	Bubble(const std::string& name, int x, int y, Game& game);
	~Bubble();

	void notify_obstacle_reached();
	void notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode);
};

#endif