#ifndef FIREBALL_H
#define FIREBALL_H

#include "MapEntity.h"
#include "Type.h"

class Fireball : public MapEntity {

private:
	Hero& hero;
	int speed;
	bool stop_now;
	int disapear_date;
	bool collision;

private:
	int get_angle(int direction4);

public:
	Fireball(Hero& hero, int speed);
	~Fireball();

	EntityType get_entity_type();

	//state
	void update();
	void stop();

	//collisions
	bool has_reached_border();
	void notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode);
	void notify_collision_with_destructible(Destructible& destructible);
	void notify_collision_with_enemy(Enemy& enemy, Sprite& enemy_sprite, Sprite& this_sprite);
    void notify_collision_with_enemy(Enemy& enemy);
};

#endif