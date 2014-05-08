#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

class Item {

private:
	std::string item_name;
	int maximum;
	int current_amount;
	int add_amount;

public:
	Item(std::string item_name, int maximum, int starting_amount, 
		int add_amount);
	~Item();

	int get_current_amount();
	void set_current_amount(int amount);
	int get_maximum() const;
	int get_up() const;

	void notify_item_used(const std::string& item_name);
};

#endif