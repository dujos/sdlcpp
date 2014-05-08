#ifndef TREASURE_H
#define TREASURE_H

#include "EntityType.h"
#include "Type.h"
#include "Item.h"

#include <string>

class Treasure {

public:
	enum Treasures {RUPEE_GREEN, RUPEE_BLUE, RUPEE_RED, LIFE};
	static const std::string treasure_names[];

private:
	Game* game;
	std::string item_name;
	
	Sprite* sprite;

public:
	Treasure(Game& game, std::string item_name);
	~Treasure();

	Item& get_equipment_item() const ;
	const std::string& get_item_name() const;
	
	void hero_take_treasure() const;

	void display(Surface& dst_surface, int x, int y);

};

#endif


