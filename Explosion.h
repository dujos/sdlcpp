#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Detector.h"
#include "Type.h"
#include <list>

class Explosion : public Detector {

private:
	bool i;

public:
	Explosion(const std::string& name, const Rectangle& xy);
	~Explosion();

	EntityType get_entity_type();
	bool can_be_obstacle();

    void notify_collision(MapEntity &other_entity, CollisionMode collision_mode);
    void notify_collision_with_sensor(Sensor& sensor, CollisionMode collision_mode);
	void notify_sprite_frame_changed(Sprite& sprite, const std::string& animation, int frame);

	void update();
};

#endif