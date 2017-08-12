#include "stdafx.h"
#include "ConstLight.h"
#include <iostream>

ConstLight::ConstLight(int xp, int yp, int lightpower, bool red, bool blue, bool green)
{
	x = xp;
	y = yp;
	r = red;
	b = blue;
	g = green;
	lightpow = lightpower;
	baselightpow = lightpower;
	SavedParameters = { lightpower, r, b, g};
	typeID = 0;
	LObjects.push_back(this);
}

void ConstLight::tick() {
	
}