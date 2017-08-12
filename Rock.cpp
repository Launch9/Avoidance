#include "stdafx.h"
#include "Rock.h"
#include "Player.h"
#include "Light_MOTHER.h"
#include "App.h"
#include "GUI.h"
#include "Sub_NPC_A.h"
#include "random2.h"
Rock::Rock(int Type, int x_pos, int y_pos, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	type = Type;
	typeID = 18;
	//Making particles settings.
	settings = ParticleSettings(x + 16, y + 16, 1, 20, 2, 1);
	switch (Type) {
	case 0:
		settings.color = sf::Color::Yellow;
		break;
	}
	sprite.setup();
	sprite.setPosition(x, y);
	sprite *= All_Sprites[TM.getTextureID()][typeID][Type][random2::randomrange(0,4)];
	GF::CheckTile_OverLap(x, y);
	Light_MOTHER::SetColorAndLighting(color, x, y);
	SavedParameters = { Type,x_pos,y_pos };
	//Putting the object that was just created into a static vector to be used later.
	ColTiles.push_back(this);
	
}


bool Rock::ifCollisionBefore(bool isPlayer) {
	if (isPlayer == true && Player::PlayerObjects[0]->is_DoingAnimation() == false) {
		if (Player::PlayerObjects[0]->getx() == x + 32 && Player::PlayerObjects[0]->gety() == y) {
			Sub_NPC_A::set_moved(Player::PlayerObjects[0]->getWalk_Speed(), 2, 1, 300 * GF::getDelta());
			Player::PlayerObjects[0]->doAnimation(3, false);
			Player::PlayerObjects[0]->addFuel(5);
			//App::control_cache.clear();
			ParticleSystem::create(settings);
			GUI::update();
		}
		else if (Player::PlayerObjects[0]->getx() == x - 32 && Player::PlayerObjects[0]->gety() == y) {
			Sub_NPC_A::set_moved(Player::PlayerObjects[0]->getWalk_Speed(), 2, 1, 300 * GF::getDelta());
			Player::PlayerObjects[0]->doAnimation(2, false);
			Player::PlayerObjects[0]->addFuel(5);
			//App::control_cache.clear();
			ParticleSystem::create(settings);
			GUI::update();
		}
		
	}
	return true;
}