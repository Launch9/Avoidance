#include "stdafx.h"
#include "Cloud_Spawner.h"
#include "Cloud.h"

Cloud_Spawner::Cloud_Spawner(int type, int x_pos, int y_pos, int x_end, int max_ticks, int speed)
{
	x = x_pos;
	y = y_pos;
	end_x = x_end;
	C_speed = speed;
	mt = max_ticks;
	typeID = 1;
	SavedParameters = { type, x, y, x_end, max_ticks, speed };
	if (speed < 0) {
		direction = false;
		setup(sf::Color::Blue, x, y, "Cloud Spawner\n Direction: left\n mt: " + GF::str(max_ticks) + "s" + GF::str(speed));
	}
	else {
		direction = true;
		setup(sf::Color::Blue, x, y, "Cloud Spawner\n Direction: right\n mt: " + GF::str(max_ticks) + "s" + GF::str(speed));
	}
	NonCol_InvisibleObjects.push_back(this);
}

void Cloud_Spawner::tick() {
	ticks += GF::getDelta();
	if (ticks >= mt) {
		ticks = 0;
		new Cloud(x, y, end_x, C_speed, 0);
	}
}


