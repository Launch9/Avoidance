#include "stdafx.h"
#include "InvisibleWall.h"
#include "Invisible_MOTHER.h"
#include "GF.h"
#include <iostream>

InvisibleWall::InvisibleWall(int x_pos, int y_pos)
{
	x = x_pos;
	y = y_pos;
	GF::CheckTile_OverLap(x_pos, y_pos);
	typeID = 3;
	SavedParameters = { x_pos, y_pos };
	sf::Color c;
	c.b = 30;
	c.g = 30;
	c.r = 30;
	c.a = 255;
	setup(c, x, y, "Wall");
	
	Col_InvisibleObjects.push_back(this);
	
}

void InvisibleWall::tick() {

}


