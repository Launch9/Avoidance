#include "stdafx.h"
#include "Exit.h"
#include "Room.h"
#include "Player.h"
std::vector<Exit *> Exit::Exits;
Exit::Exit(int Type, int x_pos, int y_pos, int ID)
{
	x = x_pos;
	y = y_pos;
	type = Type;
	GF::CheckTile_OverLap(x_pos, y_pos);
	exitID = ID;
	typeID = 8;
	SavedParameters = { type, x_pos, y_pos, ID };
	setup(sf::Color::Cyan, x, y, "Exit\nType: " + GF::str(Type) + "\nID: " + GF::str(ID));
	Exits.push_back(this);
	NonCol_InvisibleObjects.push_back(this);
}

void Exit::tick() {

}

void Exit::teleport_to_exit(int ID) {
	for (unsigned int i = 0; i < Exits.size(); i++) {
		if (Exits[i]->exitID == ID) {
			Player::PlayerObjects[0]->setXY(Exits[i]->x, Exits[i]->y);
		}
	}
}

Exit::~Exit() {
	for (unsigned int i = 0; i < Exits.size(); i++) {
		if (Exits[i] == this) {
			Exits.erase(Exits.begin() + i);
			break;
		}
	}
}