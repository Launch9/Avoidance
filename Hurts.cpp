#include "stdafx.h"
#include "Hurts.h"
#include "GF.h"
#include "Player.h"
#include "Sub_NPC_A.h"
Hurts::Hurts(int Type, int x_pos, int y_pos)
{
	x = x_pos;
	y = y_pos;
	type = Type;
	GF::CheckTile_OverLap(x_pos, y_pos);
	typeID = 5;
	SavedParameters = { Type, x_pos, y_pos };
	setup(sf::Color::Cyan, x, y, "Hurts");

	NonCol_InvisibleObjects.push_back(this);
}

void Hurts::tick() {

}

void Hurts::if_landed_on() {
	Player::PlayerObjects[0]->Die();
}

bool Hurts::checkCollision_over_empty(int x_pos, int y_pos, bool isPlayer, bool isProjectile) {
	if (isPlayer == false && isProjectile == false) {
		for (unsigned int i = 0; i < Sub_NPC_A::Object_Cache.size(); i++) {
			if (x_pos == x && y_pos == y) {
				return true;
			}
		}
	}
	else {
		return false;
	}
}