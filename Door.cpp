#include "stdafx.h"
#include "Door.h"
#include "Light_MOTHER.h"
#include <iostream>
#include "Player.h"
#include "Sound.h"
#include <memory>
Door::Door(int x_pos, int y_pos, int exit_X, int exit_Y, int Extra, int direction, int type, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	
	Type = type;
	Direction = direction;
	typeID = 6;
	switch (type) {
	case 0:
		sprite *= All_Sprites[TM.getTextureID()][typeID][0][0];
		sprite.setPosition(x, y);
		break;
		
	}
	switch (direction) {
	case 0:
		//sprite.setRotation(-90);
		y -= 32;
		break;
	case 3:
		//sprite.setRotation(-180);
		//y -= 32;x -= 32;
		sprite.setPosition(x + 32, y + 32);
		break;
	case 2:
		//sprite.setRotation(-270);
		x -= 32;
		break;
	}
	E = Extra;
	Exit_Y = exit_Y;
	Exit_X = exit_X;
	
	GF::CheckTile_OverLap(x, y);
	Light_MOTHER::SetColorAndLighting(color, x, y);
	sprite.setColor(color);
	SavedParameters = { x_pos, y_pos, exit_X, exit_Y, Extra, direction, Type };
	ColTiles.push_back(this);
}


bool Door::ifCollisionBefore(bool isPlayer) {
	
	isChecking = true;
	if (isOpen == true) {
		return false;
	}
	else {
		Sound::Play(10);
		//sprite.rotate(-90);
		isOpen = true;
		return true;
	}


}

bool Door::elseCollisionBefore(int PlayerChannel) {
	if (isOpen == true && isChecking == true) {
		
		int d = Player::PlayerObjects[PlayerChannel]->getdirection();
		int px = Player::PlayerObjects[PlayerChannel]->getvx();
		int py = Player::PlayerObjects[PlayerChannel]->getvy();

		switch (Direction) {
		case 0:
			
			//Walking toward the door entrance.
			if (d == 0) {
				if ((py == y)) {
					World::setLCords(Exit_X, Exit_Y);
					World::setAnimation(2);
					World::setFloor(Player::PlayerObjects[PlayerChannel]->getFloor());
					World::setDungeon(Player::PlayerObjects[PlayerChannel]->getDungeon());
					World::setExtra(E);
					
					isChecking = false;
				}
				
			}
			
			break;
		case 1:
			//Walking toward the door entrance.
			if (d == 1) {
				if ((px == x)) {
					World::setLCords(Exit_X, Exit_Y);
					World::setAnimation(2);
					World::setFloor(Player::PlayerObjects[PlayerChannel]->getFloor());
					World::setDungeon(Player::PlayerObjects[PlayerChannel]->getDungeon());
					World::setExtra(E);
					
					isChecking = false;
				}

			}
			
			break;

		case 2:
			//Walking toward the door entrance.
			if (d == 2) {
				if ((px == x)) {
					World::setLCords(Exit_X, Exit_Y);
					World::setAnimation(2);
					World::setFloor(Player::PlayerObjects[PlayerChannel]->getFloor());
					World::setDungeon(Player::PlayerObjects[PlayerChannel]->getDungeon());
					World::setExtra(E);
					
					isChecking = false;
				}

			}
			
			break;
		case 3:
			//Walking toward the door entrance.
			if (d == 3) {
				if ((px == x)) {
					World::setLCords(Exit_X, Exit_Y);
					World::setAnimation(2);
					World::setFloor(Player::PlayerObjects[PlayerChannel]->getFloor());
					World::setDungeon(Player::PlayerObjects[PlayerChannel]->getDungeon());
					World::setExtra(E);
					
					isChecking = false;
				}

			}
			
			break;
		}



		return false;
	}
	
}