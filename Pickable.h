#ifndef PICKABLE_H
#define PICKABLE_H

#include "Rectangle.h"
#include "Detector.h"
#include "EntityType.h"
#include "Treasure.h"
#include "Type.h"

class Pickable : public Detector {

private:
	Treasure treasure;
	void init_sprites();
	void set_item_hero();

	bool pickable;

public:
	Pickable(Treasure& treasure, int x, int y);

	~Pickable();
	
	static MapEntity* parse(Game &game, const std::string& line);

	bool is_obstacle();
	EntityType get_entity_type();
	void hero_pick_item();

	void notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode);
	void notify_collision(MapEntity& entity_overlapping, Sprite& other_sprite, Sprite& this_sprite);
};


#endif