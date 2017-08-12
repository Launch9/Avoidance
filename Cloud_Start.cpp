#include "stdafx.h"
#include "Cloud_Start.h"
#include "GF.h"
#include "Cloud.h"
std::vector<Cloud_Start *> Cloud_Start::Clouds_st; //Starter
Cloud_Start::Cloud_Start(int type, int x_pos, int y_pos, int x_end, int speed)
{
	x = x_pos;
	y = y_pos;
	end_x = x_end;
	C_speed = speed;
	typeID = 2;
	SavedParameters = { type, x, y, x_end, speed };
	sf::Color c(20,20,255,255);
	if (speed < 0) {
		direction = false;
		setup(c, x, y, "Cloud Start\n Direction: left\ns: " + GF::str(speed));
	}
	else {
		direction = true;
		setup(c, x, y, "Cloud Start\n Direction: right\ns: " + GF::str(speed));
	}
	Clouds_st.push_back(this);
	NonCol_InvisibleObjects.push_back(this);
}

Cloud_Start::~Cloud_Start() {
	for (unsigned int i = 0; i < Clouds_st.size(); i++) {
		if (Clouds_st[i] == this) {
			Clouds_st.erase(Clouds_st.begin() + i);
			break;
		}
	}
}

void Cloud_Start::tick() {

}

void Cloud_Start::active() {
	new Cloud(x, y, end_x, C_speed, 0);
}

void Cloud_Start::activate_all() {
	for (unsigned int i = 0; i < Clouds_st.size(); i++) {
		Clouds_st[i]->active();
	}
}

