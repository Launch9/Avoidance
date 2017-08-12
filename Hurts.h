#pragma once
#include "Invisible_MOTHER.h"
class Hurts : public Invisible_MOTHER
{
private:
	//This is the type of thing that hurts you. (lava, spikes, spider?)
	int type = 0;
	bool checkCollision_over_empty(int x_pos, int y_pos, bool isPlayer, bool isProjectile);
public:
	Hurts(int Type, int x_pos, int y_pos);
	void tick();
	void if_landed_on();
};

