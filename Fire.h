#ifndef FIRE_H
#define FIRE_H

#include "Enemy.h"
#include "Type.h"
#include "EntityType.h"

class Fire : public Enemy {

private:
	Sprite* fire_sprite;
	Game& game;

public:
	Fire(const std::string& fire_name, int x, int y, Game& game);
	~Fire();

	EntityType get_entity_type();

	void notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode);

	void update();
};

#endif