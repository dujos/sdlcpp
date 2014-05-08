#ifndef CHEST_H
#define CHEST_H

#include "Detector.h"

class Chest : public Detector {

private:
	//Treasure treasure;
	bool open;
	uint32_t opening_finished_date;

public:
	Chest(const std::string& name, int x, int y);
	~Chest();

	static MapEntity* parse(Game &game, const std::string& line);

	EntityType get_entity_type();

	bool is_open();
	bool can_open();
	void open_chest(bool open);
	
	bool is_obstacle_for(MapEntity& entity);
	void notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode);

	void update();

};

#endif