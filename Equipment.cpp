#include "Equipment.h"
#include "Game.h"
#include "Map.h"
#include "System.h"

#include <sstream>
#include <iostream>
#include <fstream>

//TODO
Equipment::Equipment(Game& game) :
  game(game) {
	
    const std::string& id = "items.txt";

	std::ifstream items_file;
    items_file.open(id.c_str());
    while(!items_file.eof()) {
		std::string item_name; int maximum; int starting_amount; int up;

		items_file >> item_name >> starting_amount >> maximum >> up; 

		Item* item = new Item(item_name, maximum, starting_amount, up);

		if(items[item_name] == NULL) {
		    items[item_name] = item;
		}
    }
	items_file.close();
}

Equipment::~Equipment() {
	std::map<std::string, Item*>::const_iterator iter;
	for(iter = items.begin(); iter != items.end(); iter++) {
		Item* item = iter->second;
		delete item;
	}
}

Game* Equipment::get_game() {
	return &game;
}

Item& Equipment::get_item(const std::string& item_name) {
	if(items[item_name] != NULL) {
	    Item* item = items[item_name];
	    return *item;
	}
}

void Equipment::add_item(const std::string& item_name) {
	Item& item = get_item(item_name);
	add_item_amount(item_name, item.get_up());
}

bool Equipment::has_item(const std::string& item_name) {
	return items.count(item_name) > 0;
}

int Equipment::get_item_amount(const std::string& item_name) {
	int counter_index = get_item(item_name).get_current_amount();
	return counter_index;
}

void Equipment::set_item_amount(const std::string& item_name, int amount) {
	amount = std::max(0, std::min(get_item(item_name).get_maximum(), amount));
	get_item(item_name).set_current_amount(amount);
}

void Equipment::add_item_amount(const std::string& item_name, int amount) {
	set_item_amount(item_name, get_item(item_name).get_current_amount() + amount);
}

void Equipment::notify_item_used(const std::string& item_name) {
	std::map<std::string, Item*>::iterator iter;
	for(iter = this->items.begin(); iter != items.end(); iter++) {
		iter->second->notify_item_used(item_name);
	}
}