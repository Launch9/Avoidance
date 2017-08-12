#include "stdafx.h"
#include "Editor.h"
#include "Cam.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Wall.h"
#include "Bg.h"
#include "Shop.h"
#include "Dia.h"
#include "GF.h"
#include "NPC_MOTHER.h"
#include "Laser.h"
#include "Light_MOTHER.h"
#include "World.h"
#include "Invisible_MOTHER.h"
#include "Foreground.h"
#include "InvisibleWall.h"
#include "AniBg.h"
#include "AniWall.h"
#define b32 32
#define Camnum 0
#define Playernum 0
bool Editor::ableToMove;
float Editor::ticks;
float Editor::WaitTick;
bool Editor::isActive;
int Editor::x;
int Editor::y;
sf::Sprite Editor::Cursor;
unsigned int Editor::Tileid;
unsigned int Editor::TileType;
std::vector<sf::Text> Editor::ActiveTexts;
std::string Editor::DefaultSWorld;
sf::Font Editor::MAINFONT;
void Editor::moveup() {
	if (isActive == true && ableToMove == true) {
		y -= b32;
		//Changing the y cordinate text.
		ActiveTexts[3].setString(GF::str(y/b32));
		Cam::scroll_chan(Camnum, 0, -b32);
		Cursor.setPosition(x, y);
		ableToMove = false;
		MoveTextPos(0, -b32);
	}
	
}
void Editor::moveright() {
	if (isActive == true && ableToMove == true) {
		x += b32;
		//Chaning the x cordinate text.
		ActiveTexts[2].setString(GF::str(x / b32));
		Cam::scroll_chan(Camnum, b32, 0);
		Cursor.setPosition(x, y);
		ableToMove = false;
		MoveTextPos(b32, 0);
	}
	
	
}
void Editor::movedown() {
	if (isActive == true && ableToMove == true) {
		y += b32;
		//Changing the y cordinate text.
		ActiveTexts[3].setString(GF::str(y/b32));
		Cam::scroll_chan(Camnum, 0, b32);
		Cursor.setPosition(x, y);
		ableToMove = false;
		MoveTextPos(0, b32);
	}
	
}
void Editor::moveleft() {
	if (isActive == true && ableToMove == true) {
		x -= b32;
		//Chaing the x cordinate text.
		ActiveTexts[2].setString(GF::str(x / b32));
		Cam::scroll_chan(Camnum, -b32, 0);
		Cursor.setPosition(x, y);
		ableToMove = false;
		MoveTextPos(-b32, 0);
	}
	
}
void Editor::SnapCam() {
	Cam::setxy_chan(Camnum, x, y, true);
}
void Editor::Start() {
	Player::PlayerObjects[Playernum]->setCLock(true);
	NPC_MOTHER::PauseAllNPC();
	SnapCam();
	isActive = true;
}
void Editor::Stop() {
	Player::PlayerObjects[Playernum]->setCLock(false);
	NPC_MOTHER::UnPauseAllNPC();
	Player::PlayerObjects[Playernum]->SnapCam();
	isActive = false;
}

bool Editor::GetStatus() {
	return isActive;
}

void Editor::init(sf::Texture &tex, sf::Font font) {
	ticks = 0;
	WaitTick = 0.1;
	x = 0;
	y = 0;
	Tileid = 0;
	TileType = 0;
	ableToMove = true;
	MAINFONT = font;
	DefaultSWorld = "R/World Files/Default.txt";
	//These are for the text that displays on the screen while in the editor mode.
	sf::Text BlockId;
	sf::Text BlockType;
	sf::Text xcordinate;
	sf::Text ycordinate;
	BlockId.setFont(MAINFONT);
	BlockType.setFont(MAINFONT);
	BlockId.setString(GF::str(Tileid));
	BlockType.setString(GF::str(TileType));
	BlockId.setPosition(x + 32, y);
	BlockType.setPosition(x + (32 * 2), y);
	xcordinate.setFont(MAINFONT);
	ycordinate.setFont(MAINFONT);
	xcordinate.setPosition(x - 64, y);
	ycordinate.setPosition(x - 32, y);
	ActiveTexts.push_back(BlockId);
	ActiveTexts.push_back(BlockType);
	ActiveTexts.push_back(xcordinate);
	ActiveTexts.push_back(ycordinate);
	//End
	Cursor.setTexture(tex);
	Cursor.setTextureRect(sf::IntRect(0, 0, 32, 32));
	Cursor.setPosition(x, y);
}

void Editor::draw(sf::RenderWindow &win) {
	if (isActive == true) {
		Invisible_MOTHER::All_Draw(win);

		//This draws all the text linked to this editor class to the screen.
		DrawText(win);
		win.draw(Cursor);
	}
	
}
void Editor::tick() {
	
	if (isActive == true) {
		if (ableToMove == false) {
			
				ticks += GF::getDelta();

				if (ticks >= WaitTick) {
					ticks = 0;
					ableToMove = true;
				}
			
				
			
		}
		
		
	}
	
}

void Editor::SetWaitTick(int amount) {
	ticks = 0;
	WaitTick = amount;
}

void Editor::placetile(TileMap &TM) {
	switch (TileType) {
		
	case 0:
		if (Tileid == -1) {
			new InvisibleWall(x, y);
			break;
		}
		if (Tileid >= 0 && Tileid < Basic_Tile_MOTHER::All_Sprites[TM.getTextureID()][0][0].size()) {
			//In the case that it is a wall.
			new Wall(Tileid, x, y, TM);
		}
		else {
			std::cout << "Error: No such Tileid: Editor.cpp, placetile(): Wall" << std::endl;
		}
		
		break;
		
	case 1:
		if (Tileid >= 0 && Tileid < Basic_Tile_MOTHER::All_Sprites[TM.getTextureID()][1][0].size()) {
			//In the case that it is a background.
			new Bg(Tileid, x, y, TM);
		}
		else {
			std::cout << "Error: No such Tileid: Editor.cpp, placetile(): Background" << std::endl;
		}
		
		break;
	case 2:
		if (Tileid >= 0 && Tileid < Basic_Tile_MOTHER::All_Sprites[TM.getTextureID()][7][0].size()) {
			//In the case that it is a foreground.
			new Foreground(Tileid, x, y, TM);
		}
		else {
			std::cout << "Error: No such Tileid: Editor.cpp, placetile(): Foreground" << std::endl;
		}
		
		break;
	case 3:
		if (Tileid >= 0 && Tileid < Basic_Tile_MOTHER::All_Sprites[TM.getTextureID()][4].size()) {
			new AniBg(Tileid, x, y, TM);
		}
		else {
			std::cout << "Error: No such Tileid: Editor.cpp placetile(): AniBg" << std::endl;
		}
		break;
	case 4:
		if (Tileid >= 0 && Tileid < Basic_Tile_MOTHER::All_Sprites[TM.getTextureID()][19].size()) {
			new AniWall(Tileid, x, y, TM);
		}
		else {
			std::cout << "Error: No such Tileid: Editor.cpp placetile(): AniWall" << std::endl;
		}
		break;
	}
	
}
void Editor::deletetile() {
	GF::DeleteTile_OverLap(x, y);
	//If already found something to delete in the Basic_Tile_MOTHER class, then, don't bother with the NPC_MOTHER class.
	if (NPC_MOTHER::deleteNPC(x, y) == false) {
		if (Invisible_MOTHER::deletetile(x, y) == false) {
			if (Basic_Tile_MOTHER::deletetile(x, y) == false) {
				if (Light_MOTHER::deletetile(x, y) == false) {

				}
				//This happens if you do delete a lighting tile.
				//It will need to reset all the lighting on the floor.
				else {
					Light_MOTHER::ResetLighting();
				}
			}
		}
		

	}
	
}

void Editor::Tileid_UP(unsigned int amount) {
	Tileid += amount;
	ActiveTexts[0].setString(GF::str(Tileid));
}
void Editor::Tileid_DOWN(unsigned int amount) {
	Tileid -= amount;
	ActiveTexts[0].setString(GF::str(Tileid));
}
void Editor::Tiletype_UP(unsigned int amount) {
	TileType += amount;
	ActiveTexts[1].setString(GF::str(TileType));
}
void Editor::Tiletype_DOWN(unsigned int amount) {
	TileType -= amount;
	ActiveTexts[1].setString(GF::str(TileType));
}

void Editor::MoveTextPos(int x_offset, int y_offset) {
	for (unsigned int i = 0; i < ActiveTexts.size(); i++) {
		ActiveTexts[i].move(x_offset, y_offset);
	}
}
void Editor::DrawText(sf::RenderWindow &win) {
	for (unsigned int i = 0; i < ActiveTexts.size(); i++) {
		win.draw(ActiveTexts[i]);
	}
}

void Editor::PauseNPCs() {
	NPC_MOTHER::PauseAllNPC();
}

void Editor::UnPauseNPCs() {
	NPC_MOTHER::UnPauseAllNPC();
}

int Editor::getx() {
	return x;
}
int Editor::gety() {
	return y;
}

void Editor::SaveDWorld(TileMap &TM) {
	World::SaveWorld(DefaultSWorld, TM);
}

void Editor::SetDWorld(std::string WorldFile) {
	DefaultSWorld = WorldFile;
}