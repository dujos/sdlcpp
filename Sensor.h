#ifndef SENSOR_H
#define SENSOR_H

#include "Detector.h"

class Sensor : public Detector {

public:
	enum SensorType { VISIBLE, INVISIBLE };

private:
	SensorType type;
	bool active;
	bool solid;
	Sprite* sensor;

public:
	Sensor(const std::string& name, int x, int y, SensorType type);
	~Sensor();

	SensorType get_sensor_type();

	static MapEntity* Sensor::parse(Game& game, const std::string& line);

	EntityType get_entity_type();
	bool is_obstacle_for(MapEntity& other);

	bool is_active();
	void set_inactive();

	void start_sensor();
	void start_explosion();

	void notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode);
	
	void update();
};

#endif