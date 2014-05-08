#include "Item.h"

Item::Item(std::string item_name, int maximum, 
	int starting_amount, int add_amount) :
  item_name(item_name),
  maximum(maximum),
  current_amount(starting_amount),
  add_amount(add_amount) {

}

Item::~Item() {}

int Item::get_current_amount() {
	return this->current_amount;
}

void Item::set_current_amount(int amount) {
	this->current_amount = amount;
}

int Item::get_maximum() const {
	return this->maximum;
}

int Item::get_up() const {
	return this->add_amount;
}

void Item::notify_item_used(const std::string& item_name) {
	std::cout << "fairy" << std::endl;
}