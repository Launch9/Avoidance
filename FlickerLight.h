#pragma once
#include <vector>
#include "Light_MOTHER.h"
class FlickerLight: public Light_MOTHER
{
public:
	FlickerLight(int xp, int yp, int lightpower, bool red, bool blue, bool green);
	void tick();
};

