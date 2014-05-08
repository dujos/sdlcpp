#ifndef RUPEE_COUNTER_H
#define RUPEE_COUNTER_H

#include "HudElement.h"
#include "Type.h"

class RupeeHud : public HudElement {

private:
	Surface* image_rupee;
	Counter* counter;
	int counter_value_displayed;

public:
	RupeeHud(Game& game, int x, int y, int width, int height);
	~RupeeHud();

	bool is_visible();
	void rebuild();
	void update();
};

#endif