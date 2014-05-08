#include "Chest.h"
#include "Sprite.h"
#include "Hero.h"
#include "Enemy.h"
#include "Treasure.h"

Chest::Chest(const std::string& name, int x, int y) :
  Detector(CollisionMode::COLLISION_RECTANGLE, name, x, y, 16, 16),
  open(false),
  opening_finished_date(0) {
	Sprite& sprite = create_sprite("chest.txt");
	std::string animation = is_open() ? "open" : "closed";
	sprite.set_current_animation(animation);
	set_bounding_box(sprite);
}

Chest::~Chest() {}

EntityType Chest::get_entity_type() {
	return EntityType::CHEST;
}

MapEntity* Chest::parse(Game& game, const std::string& line) {
	std::istringstream iss(line);
	
	int entity_type; int x; int y; std::string item_name;
	iss >> entity_type >> x >> y >> item_name;
	return new Chest(item_name, x, y);
}

bool Chest::is_open() {
	return open;
}

bool Chest::can_open() {
	return true;
}

void Chest::open_chest(bool open) {
	if(open != this->open) {
		open = this->open;
		if(open)
			get_sprite().set_current_animation("open");
		else
			get_sprite().set_current_animation("closed");
	}
}

bool Chest::is_obstacle_for(MapEntity& entity) {
	return true;
}

void Chest::notify_collision(MapEntity& entity_overlapping, CollisionMode collision_mode) {
	entity_overlapping.notify_collision_with_chest(*this);
}

void Chest::update() {
}