#include "stdafx.h"
#include "Stair.h"
#include "Light_MOTHER.h"
#include "GUI.h"
#include <memory>
#include "Sound.h"
#include "P_Switch_MAIN.h"
#include "random2.h"
std::vector<Stair *> Stair::Objects;
Stair::Stair(int x_pos, int y_pos, int Floor, int Dungeon, int type, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	Dungeonv = Dungeon;
	Floorv = Floor;
	Type = type;
	GF::CheckTile_OverLap(x_pos, y_pos);
	typeID = 3;
	switch (type) {
	case 0:
		sprite *= All_Sprites[TM.getTextureID()][typeID][0][1];
		normal_sprite = All_Sprites[TM.getTextureID()][typeID][0][0];
		is_allowed = false;
		sprite.setPosition(x, y);
		break;
	case 1:
		sprite *= All_Sprites[TM.getTextureID()][typeID][0][1];
		normal_sprite = All_Sprites[TM.getTextureID()][typeID][0][0];
		is_allowed = false;
		sprite.setPosition(x, y);
		break;
	case 2:
		sprite *= All_Sprites[TM.getTextureID()][typeID][0][1];
		normal_sprite = All_Sprites[TM.getTextureID()][typeID][0][0];
		is_allowed = false;
		sprite.setPosition(x, y);
		break;
	case 3:
		sprite *= All_Sprites[TM.getTextureID()][typeID][0][1];
		normal_sprite = All_Sprites[TM.getTextureID()][typeID][0][0];
		is_allowed = false;
		sprite.setPosition(x, y);
		break;
	case 4:
		
		sprite *= All_Sprites[TM.getTextureID()][typeID][0][1];
		normal_sprite = All_Sprites[TM.getTextureID()][typeID][0][0];
		is_allowed = false;
		sprite.setPosition(x, y);
		break;
	case 5:
		sprite *= All_Sprites[TM.getTextureID()][typeID][0][1];
		normal_sprite = All_Sprites[TM.getTextureID()][typeID][0][0];
		is_allowed = false;
		sprite.setPosition(x, y);
		break;
	case 6:
		sprite *= All_Sprites[TM.getTextureID()][typeID][0][1];
		normal_sprite = All_Sprites[TM.getTextureID()][typeID][0][0];
		is_allowed = false;
		sprite.setPosition(x, y);
		break;
	}
	sprite.setup();
	Light_MOTHER::SetColorAndLighting(color, x, y);
	sprite.setColor(color);
	SavedParameters = { x_pos, y_pos, Floor, Dungeon, Type };
	Objects.push_back(this);
	NonColTiles.push_back(this);

}

Stair::~Stair() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (Objects[i] == this) {
			Objects.erase(Objects.begin() + i);
		}
	}
}

bool Stair::ifCollision(int PlayerChannel) {
	if (is_allowed == true) {
		if (x == Player::PlayerObjects[PlayerChannel]->getx() && y == Player::PlayerObjects[PlayerChannel]->gety()) {
			Player::PlayerObjects[0]->setDungeon(Dungeonv);
			Sound::Play(15, x, y, random2::randomrange(1, 3), 0, 0);
			switch (Type) {
			case 0:
				//This tells the world class to start moving to a different world once it has reached its tick function in the .cpp folder.
				World::setDungeon(Dungeonv);
				World::setFloor(Floorv);
				World::setAnimation(0);
				return true;
			case 1:
				World::setAnimation(1);
				return true;
			case 2:
				World::setAnimation(2);
				return true;
			
			case 4:
				Player::PlayerObjects[0]->getScoring().reset();
				Player::PlayerObjects[0]->getScoring().set_high_score(0);
				Player::PlayerObjects[0]->getScoring().setTimer(true);
				World::setDungeon(Dungeonv);
				World::setFloor(Floorv);
				World::setAnimation(0);
				
				return true;
			case 5:
				Player::PlayerObjects[0]->getScoring().reset();
				Player::PlayerObjects[0]->getScoring().set_high_score(1);
				Player::PlayerObjects[0]->getScoring().setTimer(true);
				World::setDungeon(Dungeonv);
				World::setFloor(Floorv);
				World::setAnimation(0);
				
				return true;

			case 6:
				Player::PlayerObjects[0]->getScoring().reset();
				Player::PlayerObjects[0]->getScoring().set_high_score(2);
				Player::PlayerObjects[0]->getScoring().setTimer(true);
				World::setDungeon(Dungeonv);
				World::setFloor(Floorv);
				World::setAnimation(0);
				
				return true;
			}

		}
	}
	
	
	return false;
}

void Stair::update() {
	if (P_Switch_MAIN::deathSwitch == true) {
		for (unsigned int i = 0; i < Objects.size(); i++) {
			Objects[i]->is_allowed = true;
			Objects[i]->sprite *= Objects[i]->normal_sprite;
		}
	}
}