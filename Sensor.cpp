#include "CollisionMode.h"
#include "Explosion.h"
#include "Game.h"
#include "Hero.h"
#include "Map.h"
#include "MapEntities.h"
#include "Sensor.h"
#include "Sprite.h"

Sensor::Sensor(const std::string& name, int x, int y, Sensor::SensorType type) :
  Detector(CollisionMode::COLLISION_RECTANGLE, name, x, y, 16, 16),
  type(type),
  active(false) {
	if(type == SensorType::VISIBLE) {
		sensor = &create_sprite("sensor.txt");
		sensor->set_current_animation("deactivate");
	} else {
		//sensor = &create_sprite("sensor.txt");
		//sensor->set_current_animation("deactivate");
	}
}

Sensor::~Sensor() {}

Sensor::SensorType Sensor::get_sensor_type() {
	return this->type;
}

MapEntity* Sensor::parse(Game& game, const std::string& line) {
	std::istringstream iss(line);

	int entity_type; int x; int y; std::string name; int type;
	iss >> entity_type >> x >> y >> name >> type;
	return new Sensor(name, x, y, (SensorType) type);
}

EntityType Sensor::get_entity_type() {
	return EntityType::SENSOR;
}

bool Sensor::is_obstacle_for(MapEntity& other) {
	return false;
}

bool Sensor::is_active() {
	return active;
}

void Sensor::set_inactive() {
	active = false;
}

void Sensor::start_explosion() {
	set_inactive();
	get_entities().add_entity(new Explosion("", get_center_point()));
}

void Sensor::start_sensor() {
	active = true;
}

void Sensor::notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode) {
	entity_overlapping.notify_collision_with_sensor(*this);
}

void Sensor::update() {
	Detector::update();
	check_collision_with_detectors();
	if(is_active())
		start_explosion();
}