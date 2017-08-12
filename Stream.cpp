#include "stdafx.h"
#include "Stream.h"
#include <iostream>

Stream::Stream(int Type, bool is_flowing_left, float Speed, int x_pos, int y_pos, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	typeID = 16;
	type = Type;
	is_left = is_flowing_left;
	switch (Type) {
	case 0:
		isSIMPLELIGHTING = true;
		break;
	}
	speed = Speed / 2;
	SavedParameters = { Type, is_flowing_left, int(Speed), x_pos, y_pos };
	rect = All_Sprites[TM.getTextureID()][typeID][type][0].getRect();
	if (is_left == false) {
		texrect = sf::IntRect(rect.left, rect.top, 32, 32);
		sprite.setTextureRect(sf::IntRect(rect.left, rect.top, 32, 32));
	}
	else {
		texrect = sf::IntRect(rect.left + (rect.width - 32), rect.top + (rect.height - 32), 32, 32);
		sprite.setTextureRect(sf::IntRect(rect.left + (rect.width - 32), rect.top + (rect.height - 32), 32, 32));
	}
	sprite.setPosition(x, y);
	sprite.setup();
	NonColAniTiles.push_back(this);
}

void Stream::animate() {
	howFar += speed * GF::getDelta();
	
	if (is_left == true) {
		
		if (howFar >= rect.width - 32) {
			howFar -= rect.width - 32;
		}
		texrect.left = int(((rect.left + rect.width) - 32) - howFar);
		
	}
	else {
		
		if (howFar >= rect.width - 32) {
			howFar -= rect.width - 32;
		}
		texrect.left = int(rect.left + howFar);
	}
	sprite.setTextureRect(texrect);
}


