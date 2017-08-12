#include "stdafx.h"
#include "FlickerLight.h"
#include "GF.h"
#include <iostream>
#include "random2.h"
//Flickering Light difference
#define FLD 5
//Light decay
#define LDECAY 1

FlickerLight::FlickerLight(int xp, int yp, int lightpower, bool red, bool blue, bool green)
{
	x = xp;
	y = yp;
	r = red;
	b = blue;
	g = green;
	lightpow = lightpower;
	baselightpow = lightpower;
	SavedParameters = { lightpower, r, b, g };
	typeID = 1;
	LObjects.push_back(this);
}

void FlickerLight::tick() {
	
	//Setting the light power of the light to a random amount in the range of five difference of the base light power.
	if (baselightpow == lightpow) {
		lightpow = baselightpow + random2::randomrange(0, FLD);
	}
	else {
		lightpow -= LDECAY;
	}


}