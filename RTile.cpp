#include "stdafx.h"
#include "RTile.h"
#include "Light_MOTHER.h"
#include "Player.h"
#include "GUI.h"
#include "Sound.h"
#include "random2.h"

RTile::RTile(const int &type, const int &x_pos, const int &y_pos, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	GF::CheckTile_OverLap(x_pos, y_pos);
	typeID = 12;
	Type = type;
	sprite.setPosition(x, y);
	switch (type) {
	case 0:
		spr = All_Sprites[TM.getTextureID()][typeID];
		amount = 20;
		break;
	
	}
	Sprites = spr[0];
	sprite.setup();
	Light_MOTHER::SetColorAndLighting(color, x, y);
	sprite.setColor(color);
	sprite *= Sprites[0];
	SavedParameters = { x_pos, y_pos, type };
	NonColAniTiles.push_back(this);

}

bool RTile::ifCollision(int PlayerChannel) {
	
	if (x == Player::PlayerObjects[PlayerChannel]->getx() && y == Player::PlayerObjects[PlayerChannel]->gety()) {
		if (hasBeenLandedOn == false) {
			Sound::Play(17, x, y, random2::randomrange(1, 5), 0, 0);
			Player::PlayerObjects[PlayerChannel]->addFuel(amount);
			GUI::update();
			hasBeenLandedOn = true;
			switch (Type) {
			case 0:
				Sprites = spr[1];
				sprite *= Sprites[0];
				break;
			}
			return true;
		}
		
	}
	return false;
}

