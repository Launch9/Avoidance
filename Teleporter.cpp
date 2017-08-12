#include "stdafx.h"
#include "Teleporter.h"
#include "GF.h"
#include "Sound.h"
#include "random2.h"
Teleporter::Teleporter(int type, int x_pos, int y_pos, int Dungeon, int Floor, int ExitID)
{
	typeID = 4;
	Type = type;
	dungeon = Dungeon;
	floor = Floor;
	exitID = ExitID;
	x = x_pos;
	y = y_pos;
	setup(sf::Color::Green, x, y, "Teleporter\nDungeon: " + GF::str(Dungeon) + "\nFloor: " + GF::str(Floor) + "\nExitID: " + GF::str(ExitID) + "\nType: " + GF::str(type));
	SavedParameters = { type, x_pos, y_pos, Dungeon, Floor, ExitID };
	NonCol_InvisibleObjects.push_back(this);
}

void Teleporter::tick() {

}

void Teleporter::if_landed_on() {
		Player::PlayerObjects[0]->setDungeon(dungeon);
		Sound::Play(16, 0, 0, random2::randomrange(1,5), 0, 0);
		switch (Type) {
		case 0:
			//This tells the world class to start moving to a different world once it has reached its tick function in the .cpp folder.
			World::setDungeon(dungeon);
			World::setFloor(floor);
			World::setExitID(exitID);
			World::setAnimation(2);
			break;
		case 1:
			World::setDungeon(dungeon);
			World::setFloor(floor);
			World::setExitID(exitID);
			World::setAnimation(3);
			break;
		case 2:
			World::setDungeon(dungeon);
			World::setFloor(floor);
			World::setExitID(exitID);
			World::setAnimation(4);
			break;
		case 3:
			World::setDungeon(dungeon);
			World::setFloor(floor);
			World::setExitID(exitID);
			World::setAnimation(5);
			break;
		case 4:
			
			World::setDungeon(dungeon);
			World::setFloor(floor);
			World::setExitID(exitID);	
			Player::PlayerObjects[0]->setStep(1);
			World::setAnimation(7);
			break;
		case 5:
			World::setDungeon(dungeon);
			World::setFloor(floor);
			World::setExitID(exitID);
			
			Player::PlayerObjects[0]->setStep(2);
			//Player::PlayerObjects[0]->getScoring().reset();
			World::setAnimation(8);
			break;
		case 6:
			World::setDungeon(dungeon);
			World::setFloor(floor);
			World::setExitID(exitID);
			
			Player::PlayerObjects[0]->setStep(3);
			//Player::PlayerObjects[0]->getScoring().reset();
			World::setAnimation(9);
			break;
		case 7:
			World::setDungeon(dungeon);
			World::setFloor(floor);
			World::setExitID(exitID);
			Player::PlayerObjects[0]->setStoryID(1);
			World::setAnimation(4);
			break;
			
		
			
		}

	
}