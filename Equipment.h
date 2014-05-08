#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Globals.h"
#include "Game.h"
#include "Item.h"
#include "Type.h"

#include <string>
#include <map>

class Equipment {

private:
	Game& game;

	//items
	std::map<std::string, Item*> items;

public:
	Equipment(Game& game);
	~Equipment();

	Game* get_game();
	
	Item& get_item(const std::string& item_name);
	void add_item(const std::string& item_name);
	bool has_item(const std::string& item_name);

	int get_item_amount(const std::string& item_name);
	void set_item_amount(const std::string& item_name, int amount);
	void add_item_amount(const std::string& item_name, int amount);

	void notify_item_used(const std::string& item_name);

	void update();
};

#endif