#include "stdafx.h"
#include "Seal.h"
#include <iostream>
#include "P_Switch.h"
#include "P_Switch_MAIN.h"
#include "Seal.h"
#include "Sound.h"
#include "random2.h"
std::vector<Seal *> Seal::Seals;

Seal::Seal(int Type, int x_pos, int y_pos, int Direction, const std::vector<int> &Switches, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	typeID = 11;
	channels = Switches;
	sprite *= All_Sprites[TM.getTextureID()][typeID][0][type];
	dir = Direction;
	type = Type;
	sprite.setPosition(x, y);
	sprite.setTexture(0);
	sprite.setup();
	isSIMPLELIGHTING = false;
	SavedParameters = { x_pos, y_pos, type, dir };
	for (unsigned int i = 0; i < Switches.size(); i++) {
		SavedParameters.push_back(channels[i]);
	}
	Seals.push_back(this);
	ColTiles.push_back(this);

}

Seal::~Seal() {
		
	for (unsigned int i = 0; i < Seals.size(); i++) {
		if (Seals[i] == this) {
			Seals.erase(Seals.begin() + i);
			break;
		}
	}

}

void Seal::update() {
	int howManyTrue = 0;
	for (unsigned int i = 0; i < channels.size(); i++) {
		if (P_Switch_MAIN::Switches[channels[i]] == true) {
			howManyTrue++;
		}
	}
	if (howManyTrue == channels.size()) {
		open();
		
	}
	else {
		switch (type) {
		case 1:
			close();
			break;
		}
		
	}
	
}
void Seal::update_all() {
	for (unsigned int i = 0; i < Seals.size(); i++) {
		Seals[i]->update();
	}
}

void Seal::open() {
	if (isOpen == false) {
		Sound::Play(14, x, y, random2::randomrange(1, 5), 0, 0);
		switch (dir) {
		case 0:
			y -= 32;
			break;
		case 1:
			x += 32;
			break;
		case 2:
			y += 32;
			break;
		case 3:
			x -= 32;
		}
		isOpen = true;
		sprite.setPosition(x, y);
	}
}

void Seal::close() {
	if (isOpen == true) {
		switch (dir) {
		case 0:
			y += 32;
			break;
		case 1:
			x -= 32;
			break;
		case 2:
			y -= 32;
			break;
		case 3:
			x += 32;
			
		}
		sprite.setPosition(x, y);
		isOpen = false;
	}
}