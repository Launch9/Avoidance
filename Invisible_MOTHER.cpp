#include "stdafx.h"
#include "Invisible_MOTHER.h"
#include "GF.h"
#include "Player.h"
#include "Font.h"
#include "AniT.h"
#include <vector>
#define PlayerChan 0
#define InformationSize 16
std::vector<Invisible_MOTHER*> Invisible_MOTHER::Col_InvisibleObjects;
std::vector<Invisible_MOTHER*> Invisible_MOTHER::NonCol_InvisibleObjects;
std::vector<std::vector<std::vector<std::vector<AniT>>>> Invisible_MOTHER::All_Sprites;
std::vector<int> Invisible_MOTHER::GetSavedParameters() {
	return SavedParameters;
}

std::string Invisible_MOTHER::GetSave() {
	std::string r = "&3&";
	for (unsigned int i = 0; i < Col_InvisibleObjects.size(); i++) {
		r.append(":");
		r.append(std::to_string(Col_InvisibleObjects[i]->typeID) + ",");
		for (unsigned int b = 0; b < Col_InvisibleObjects[i]->GetSavedParameters().size(); b++) {
			r.append(std::to_string(Col_InvisibleObjects[i]->GetSavedParameters()[b]) + ",");
		}
		r.append(":");
	}
	for (unsigned int i = 0; i < NonCol_InvisibleObjects.size(); i++) {
		r.append(":");
		r.append(std::to_string(NonCol_InvisibleObjects[i]->typeID) + ",");
		for (unsigned int b = 0; b < NonCol_InvisibleObjects[i]->GetSavedParameters().size(); b++) {
			r.append(std::to_string(NonCol_InvisibleObjects[i]->GetSavedParameters()[b]) + ",");
		}
		r.append(":");
	}
	return r;
}

Invisible_MOTHER::~Invisible_MOTHER() {

}

void Invisible_MOTHER::tick() {
	std::cout << "You did not overwrite the tick class while you were making the derived class to Invisible_MOTHER" << std::endl;
	throw("You did not overwrite the tick class while you were making the derived class to Invisible_MOTHER.");
}

void Invisible_MOTHER::All_Tick() {

	for (unsigned int i = 0; i < Col_InvisibleObjects.size(); i++) {
		Col_InvisibleObjects[i]->tick();
	}
	for (unsigned int i = 0; i < NonCol_InvisibleObjects.size(); i++) {
		NonCol_InvisibleObjects[i]->tick();
	}
}

//This function will return the player's x position.
int Invisible_MOTHER::getPlayer_x() {
	return Player::PlayerObjects[PlayerChan]->getx();
}
//This function will return the player's y position.
int Invisible_MOTHER::getPlayer_y() {
	return Player::PlayerObjects[PlayerChan]->gety();
}
//This function will return the player's vx position.
float Invisible_MOTHER::getPlayer_vx() {
	return Player::PlayerObjects[PlayerChan]->getvx();
}
//This function will return the player's vy position.
float Invisible_MOTHER::getPlayer_vy() {
	return Player::PlayerObjects[PlayerChan]->getvy();
}

bool Invisible_MOTHER::deletetile(int x, int y) {
	for (unsigned int i = 0; i < Col_InvisibleObjects.size(); i++) {
		if (Col_InvisibleObjects[i]->getx() == x && Col_InvisibleObjects[i]->gety() == y) {
			delete Col_InvisibleObjects[i];
			Col_InvisibleObjects.erase(Col_InvisibleObjects.begin() + i);
			return true;
		}
	}
	for (unsigned int i = 0; i < NonCol_InvisibleObjects.size(); i++) {
		if (NonCol_InvisibleObjects[i]->getx() == x && NonCol_InvisibleObjects[i]->gety() == y) {
			delete NonCol_InvisibleObjects[i];
			NonCol_InvisibleObjects.erase(NonCol_InvisibleObjects.begin() + i);
			return true;
		}
	}
	return false;
}

bool Invisible_MOTHER::checkCollision(int x_pos, int y_pos, bool isPlayer, bool isProjectile) {
	for (unsigned int i = 0; i < Col_InvisibleObjects.size(); i++) {
		if (Col_InvisibleObjects[i]->checkCollision_over(x_pos, y_pos, isPlayer, isProjectile) == true) {
			return true;
		}
	}
	for (unsigned int i = 0; i < NonCol_InvisibleObjects.size(); i++) {
		if (NonCol_InvisibleObjects[i]->checkCollision_over_empty(x_pos, y_pos, isPlayer, isProjectile) == true) {
			return true;
		}
	}
	return false;
}

void Invisible_MOTHER::if_landed_on() {
	
	
}

bool Invisible_MOTHER::checkCollision_over(int x_pos, int y_pos, bool isPlayer, bool isProjectile) {
	if (x == x_pos && y == y_pos) {
		return true;
	}
	else {
		return false;
	}
}

int Invisible_MOTHER::getx() {
	return x;
}

int Invisible_MOTHER::gety() {
	return y;
}

bool Invisible_MOTHER::checkSpecialCollision(int Playerid) {
	for (unsigned int i = 0; i < NonCol_InvisibleObjects.size(); i++) {
		if (NonCol_InvisibleObjects[i]->x == Player::PlayerObjects[Playerid]->getx() && NonCol_InvisibleObjects[i]->y == Player::PlayerObjects[Playerid]->gety()) {
			NonCol_InvisibleObjects[i]->if_landed_on();
			return true;
		}
	}
	return false;
}

void Invisible_MOTHER::draw(sf::RenderWindow &win) {
	
	win.draw(Rect);
	win.draw(Information);
	
}

void Invisible_MOTHER::All_Draw(sf::RenderWindow &win) {
	for (unsigned int i = 0; i < Col_InvisibleObjects.size(); i++) {
		Col_InvisibleObjects[i]->draw(win);
	}
	for (unsigned int i = 0; i < NonCol_InvisibleObjects.size(); i++) {
		NonCol_InvisibleObjects[i]->draw(win);
	}
}

void Invisible_MOTHER::setup(sf::Color c, int x, int y, std::string Information_About_Block) {
	Rect.setPosition(x, y);
	Rect.setFillColor(c);
	Rect.setSize(sf::Vector2f(32, 32));
	Information.setFont(Font::Get_isocpeur());
	Information.setPosition(x, y);
	Information.setColor(sf::Color::White);
	Information.setString(Information_About_Block);
	Information.setCharacterSize(InformationSize);
	
}

void Invisible_MOTHER::clear_all() {
	for (unsigned int i = 0; i < NonCol_InvisibleObjects.size(); i++) {
		delete NonCol_InvisibleObjects[i];
	}
	for (unsigned int i = 0; i < Col_InvisibleObjects.size(); i++) {
		delete Col_InvisibleObjects[i];
	}
	NonCol_InvisibleObjects.clear();
	Col_InvisibleObjects.clear();
}

void Invisible_MOTHER::init(sf::Texture &tex) {
	for (unsigned int i = 0; i < 8; i++) {
		All_Sprites.push_back({});
		for (unsigned int b = 0; b < 100; b++) {
			All_Sprites[i].push_back({});
		}
	}

	//For lobby2
	//Weather sprites
	//Rain:

	AniT R1(sf::IntRect(0, 96, 32, 32));
	AniT R2(sf::IntRect(0, 96 + 32, 32, 32));
	AniT R3(sf::IntRect(0, 96 + (32 * 2), 32, 32));
	AniT R4(sf::IntRect(0, 96 + (32 * 3), 32, 32));
	AniT R5(sf::IntRect(0, 96 + (32 * 4), 32, 32));

	All_Sprites[3][9] = { {R1,R2,R3,R4,R5} };
	//For dungeon 2
	//P_Fog sprites
	AniT PF1(sf::IntRect(470, 320, 32, 32));
	AniT PF2(sf::IntRect(470, 320 + (32 * 1), 32, 32));
	AniT PF3(sf::IntRect(470, 320 + (32 * 2), 32, 32));
	AniT PF4(sf::IntRect(470, 320 + (32 * 3), 32, 32));
	AniT PF5(sf::IntRect(470, 320 + (32 * 4), 32, 32));

	All_Sprites[4][13] = { {PF1,PF2,PF3,PF4,PF5} };
	//For lobby3
	//Weather sprites
	//Snow:

	AniT S1(sf::IntRect(0, 96, 32, 32));
	AniT S2(sf::IntRect(0, 96 + 32, 32, 32));
	AniT S3(sf::IntRect(0, 96 + (32 * 2), 32, 32));
	AniT S4(sf::IntRect(0, 96 + (32 * 3), 32, 32));
	AniT S5(sf::IntRect(0, 96 + (32 * 4), 32, 32));

	All_Sprites[5][9] = { { S1,S2,S3,S4,S5 } };
	//For dungeon 3
	//Weather sprites
	//Snow:

	AniT HS1(sf::IntRect(288, 672, 32, 32));
	AniT HS2(sf::IntRect(288, 672 + 32, 32, 32));
	AniT HS3(sf::IntRect(288, 672 + (32 * 2), 32, 32));
	AniT HS4(sf::IntRect(288, 672 + (32 * 3), 32, 32));
	AniT HS5(sf::IntRect(288, 672 + (32 * 4), 32, 32));

	All_Sprites[6][9] = { { HS1,HS2,HS3,HS4,HS5 } };

	//For lobby4
	//Weather sprites
	//Ash?:

	AniT J1(sf::IntRect(0, 96, 32, 32));
	AniT J2(sf::IntRect(0, 96 + 32, 32, 32));
	AniT J3(sf::IntRect(0, 96 + (32 * 2), 32, 32));
	AniT J4(sf::IntRect(0, 96 + (32 * 3), 32, 32));
	AniT J5(sf::IntRect(0, 96 + (32 * 4), 32, 32));

	All_Sprites[7][9] = { { J2,J3,J4,J5 } };
}

bool Invisible_MOTHER::checkCollision_over_empty(int x_pos, int y_pos, bool isPlayer, bool isProjectile) {
	return false;
}

void Invisible_MOTHER::WorldReset() {
	
}

void Invisible_MOTHER::tell_WorldReset_all() {
	
	
	for (unsigned int i = 0; i < NonCol_InvisibleObjects.size(); i++) {
		NonCol_InvisibleObjects[i]->WorldReset();
		
	}
	for (unsigned int i = 0; i < Col_InvisibleObjects.size(); i++) {
		Col_InvisibleObjects[i]->WorldReset();
		
	}
	//throw("error");
}