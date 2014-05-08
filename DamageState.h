#ifndef DAMAGE_STATE_H
#endif  DAMAGE_STATE_H

#include "State.h"

class Hero::DamageState : public Hero::State {

private:
	const Rectangle dmg_source_xy;
	uint32_t end_damage_date;

public:
	DamageState(Hero& hero, const Rectangle& dmg_source_xy);
	~DamageState();

	void start(State* last_state);
	void stop(State* next_state);
	std::string get_state_name();
	void update();
};