#pragma once
#include "Invisible_MOTHER.h"
class InvisibleWall : public Invisible_MOTHER
{
public:
	InvisibleWall(int x_pos, int y_pos);
	void tick();
};

