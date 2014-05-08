#ifndef DESTRUCTIBLE_H
#define DESTRUCTIBLE_H

#include "Detector.h"

class Destructible : public Detector {

public:
	enum DestructibleType {POT, BUSH, STONE_SMALL_WHITE, STONE_SMALL_BLACK};

private:	
	struct Properties {
		std::string name;
		std::string animation_set_id;
	};

	DestructibleType type;

	static const Properties properties[];
	static const std::string destructible_names[];

public:
	Destructible(const std::string& name, int x, int y, DestructibleType type);
	~Destructible();

	static MapEntity* parse(Game& game, const std::string& line);
	
	EntityType get_entity_type();

	const std::string& get_animation_set_id();

	bool is_obstacle_for(MapEntity& other);
	void notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode);

	void update();
};

#endif