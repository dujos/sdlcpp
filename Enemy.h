#ifndef ENEMY_H
#define ENEMY_H

#include "Detector.h"
#include "Type.h"

class Enemy : public Detector {

public:
	enum EnemyType {
		BUBBLE,
		FIRE,
		RED_KNIGHT_SOLDIER
	};

protected:
	int life;
	bool damage_taken;

public:
	Enemy(const std::string& name, int x, int y);
	~Enemy();

	static MapEntity* parse(Game& game, const std::string& line);

	EntityType get_entity_type();

	void destroy_enemy();
	bool is_destroyed();
	bool is_dying_animation_finished();
	bool is_damage_taken();

	void damage_enemy();

	void notify_movement_finished();
	void notify_position_changed();
	void notify_movement_changed();
	void notify_obstacle_reached();

	bool is_obstacle_for(MapEntity& other);
	bool is_destructible_obstacle(Destructible& destructible);

	void notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode);
	void notify_collision(MapEntity& entity_overlapping, Sprite& other_overlapping, Sprite& this_overlapping);
	//void notify_collision_with_enemy(MapEntity& entity_overlapping, Sprite& other_sprite, Sprite& this_sprite);

	void update();
	void display_on_map();
};

#endif