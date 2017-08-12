#pragma once
#include <vector>
#include "Light_MOTHER.h"
///This makes a constant light source(One that does not flash or anything special).
///This is the most time efficient light source.
///This does not get erased unless told to.
class ConstLight: public Light_MOTHER 
{
public:
	ConstLight(int xp, int yp, int lightpower, bool red, bool blue, bool green);
	void tick();
};

