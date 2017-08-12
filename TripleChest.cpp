#include "stdafx.h"
#include "TripleChest.h"
#include "Player.h"
#include "Sound.h"
#include "P_Switch_MAIN.h"
#include "random2.h"
#include "App.h"
TripleChest::TripleChest(int type, int x_pos, int y_pos, int contentID, int SwitchID, TileMap &TM)
{
	
	x = x_pos;
	y = y_pos;
	typeID = 17;
	switchID = SwitchID;
	content = contentID;
	sprite.setPosition(x, y);
	SavedParameters = { type, x_pos, y_pos, contentID, SwitchID };
	Sprites = All_Sprites[TM.getTextureID()][typeID][type];
	sprite.setTexture(0);
	sprite.setup();
	sprite *= Sprites[0];
	max_times = Sprites.size() - 1;
	switch (type) {
	case 0:
		for (unsigned int i = 0; i < Player::PlayerObjects[0]->get_Obtained_Gauntlets().size(); i++) {
			if (Player::PlayerObjects[0]->get_Obtained_Gauntlets()[i] == 0) { //The player already has a blue tornado gauntlet.
				is_open = true;
				sprite *= Sprites[2];
			}
		}
	}
	ColTiles.push_back(this);

}

bool TripleChest::ifCollisionBefore(bool isPlayer) {
	if (is_open == false) {
		App::control_cache.clear();
		howManyTimes++;
		sprite *= Sprites[howManyTimes];
		if (howManyTimes == max_times) {
			Sound::Play(21, x, y, random2::randomrange(1, 5), 0, 0);
			Player::PlayerObjects[0]->giveItem(content);
			is_open = true;
			if (switchID != -1) { //If not equal to -1 then it is allowed to activate the switch.
				P_Switch_MAIN::Switches[switchID] = true; //Making the switch that has been selected true.
			}
		}
	}
	return true;
}


