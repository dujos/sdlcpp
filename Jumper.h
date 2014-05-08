#ifndef JUMPER_H
#define JUMPER_H

#include "Detector.h"
#include "Rectangle.h"
#include "EntityType.h"
#include "Type.h"

class Jumper : public Detector {

private:
	void init_sprites();

public:
	Jumper(const std::string& name, int x, int y, int direction);
	~Jumper();

	static MapEntity* parse(Game &game, const std::string& line);
	EntityType get_entity_type();
	void notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode);
};

#endif