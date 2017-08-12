#include "stdafx.h"
#include "SaveStation.h"
#include "Light_MOTHER.h"
#include <iostream>
#include "Player.h"
#include "Sound.h"
#include "Font.h"
#include "Temporarytxt.h"
#include <memory>
SaveStation::SaveStation(int x_pos, int y_pos, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	
	GF::CheckTile_OverLap(x_pos, y_pos);
	typeID = 5;
	sprite.setPosition(x_pos, y_pos);
	sprite.setup();
	
	Sprites = All_Sprites[TM.getTextureID()][typeID][0];
	max_ticks = 0.5;
	Light_MOTHER::SetColorAndLighting(color, x, y);
	sprite.setColor(color);
	sprite *= Sprites[0];
	SavedParameters = { x_pos, y_pos };
	NonColAniTiles.push_back(this);

}


bool SaveStation::ifCollision(int PlayerChannel) {
	if (x == Player::PlayerObjects[PlayerChannel]->getx() && y == Player::PlayerObjects[PlayerChannel]->gety()) {
		std::string s = "Saved File";
		Temporarytxt(s, x, y, 100, Font::Get_isocpeur(), sf::Color::White, 1);
		World::SavePlayerFile();
		Sound::Play(9);
		return true;
	}
			
	return false;
}
