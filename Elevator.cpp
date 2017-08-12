#include "stdafx.h"
#include "Elevator.h"
#include "GF.h"
#include "Sound.h"
#include "Wall.h"
#include "Bg.h"
#include "P_Switch_MAIN.h"
#include "TileMap.h"
#include "Teleporter.h"
#include "Stair.h"
#include "Editor.h"
#include "AniBg.h"
std::vector<Elevator *> Elevator::Objects;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=CONTROL PANEL-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define setupColor sf::Color::Red //This is the color that is used for the block that shows up when the editor is turned on.
#define information_text "Elevator" //This is the text that appears next to the block to show you information about the block.
#define TypeID 10 //This is the identification of what object it is in relation to others in the NPC_MOTHER class.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Elevator::Elevator(int Type, int x_pos, int y_pos, int Switch_for_door, int Switch_for_toggle, TileMap &TM)
{
	x = x_pos;
	y = y_pos;
	type = Type;
	SM = Switch_for_toggle;
	SD = Switch_for_door;
	GF::CheckTile_OverLap(x_pos, y_pos);
	typeID = TypeID;
	sound.setBuffer(Sound::GetSoundBuffer(57));
	Tmap = &TM;
	SavedParameters = { Type, x_pos, y_pos, Switch_for_door,Switch_for_toggle };
	setup(setupColor, x, y, information_text);

	NonCol_InvisibleObjects.push_back(this);
	Objects.push_back(this);
	//move_up();
}

Elevator::~Elevator() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (this == Objects[i]) {
			Objects.erase(Objects.begin() + i);
			break;
		}
	}
}

void Elevator::update() {
	
	if (P_Switch_MAIN::Switches[SM] == true) {
		//P_Switch_MAIN::Switches[SM] == false;
		if (sound.getStatus() == 0) {
			
			if (is_up == true) {
				move_down();
			}
			else {
				move_up();
			}
		}
	}
	
	
}

void Elevator::update_all() {
	for (unsigned int i = 0; i < Objects.size(); i++) {
		Objects[i]->update();
	}
}
//This moves the elevator up.
void Elevator::move_up() {
	sound.play();
	is_up = true;
	has_created = false;
	P_Switch_MAIN::Switches[SD] = false;
	delete_tiles_down();
	P_Switch_MAIN::update();
}
//This moves the elevator down.
void Elevator::move_down() {
	sound.play();
	is_up = false;
	has_created = false;
	P_Switch_MAIN::Switches[SD] = false;
	delete_tiles_up();
	P_Switch_MAIN::update();
}
void Elevator::create_tiles_up() {
	new Wall(27, 1 * 32, 5 * 32, *Tmap);
	new Wall(27, 2 * 32, 6 * 32, *Tmap);
	new Wall(27, 2 * 32, 7 * 32, *Tmap);
	new Wall(27, 2 * 32, 8 * 32, *Tmap);
	new Wall(27, 1 * 32, 9 * 32, *Tmap);
	new Wall(27, 0 * 32, 9 * 32, *Tmap);
	new Wall(27, -1 * 32, 9 * 32, *Tmap);
	new Wall(27, -2 * 32, 8 * 32, *Tmap);
	new Wall(27, -2 * 32, 7 * 32, *Tmap);
	new Wall(27, -2 * 32, 6 * 32, *Tmap);
	new Wall(27, -2 * 32, 5 * 32, *Tmap);
	new Bg(0, -1 * 32, 5 * 32, *Tmap);
	new Bg(0, 0 * 32, 5 * 32, *Tmap);
	new Bg(0, 0 * 32, 6 * 32, *Tmap);
	new Bg(0, 1 * 32, 6 * 32, *Tmap);
	new Bg(0, 1 * 32, 7 * 32, *Tmap);
	new Bg(0, 1 * 32, 8 * 32, *Tmap);
	new Bg(0, 0 * 32, 8 * 32, *Tmap);
	new Bg(0, -1 * 32, 8 * 32, *Tmap);
	new Bg(0, -1 * 32, 7 * 32, *Tmap);
	new Bg(0, -1 * 32, 6 * 32, *Tmap);
	new Bg(0, 0 * 32, 7 * 32, *Tmap);
	new Wall(25, 0 * 32, 6 * 32, *Tmap);
	new Stair(0, 7 * 32, 1, 3, 0, *Tmap);
}

void Elevator::delete_tiles_up() {
	Basic_Tile_MOTHER::deletetile(1 * 32, 5 * 32);
	Basic_Tile_MOTHER::deletetile(2 * 32, 6 * 32);
	Basic_Tile_MOTHER::deletetile(2 * 32, 7 * 32);
	Basic_Tile_MOTHER::deletetile(2 * 32, 8 * 32);
	Basic_Tile_MOTHER::deletetile(1 * 32, 9 * 32);
	Basic_Tile_MOTHER::deletetile(0 * 32, 9 * 32);
	Basic_Tile_MOTHER::deletetile(-1 * 32, 9 * 32);
	Basic_Tile_MOTHER::deletetile(-2 * 32, 8 * 32);
	Basic_Tile_MOTHER::deletetile(-2 * 32, 7 * 32);
	Basic_Tile_MOTHER::deletetile(-2 * 32, 6 * 32);
	Basic_Tile_MOTHER::deletetile(-1 * 32, 5 * 32);
	Basic_Tile_MOTHER::deletetile(0 * 32, 5 * 32);
	Basic_Tile_MOTHER::deletetile(0 * 32, 6 * 32);
	Basic_Tile_MOTHER::deletetile(1 * 32, 6 * 32);
	Basic_Tile_MOTHER::deletetile(1 * 32, 7 * 32);
	Basic_Tile_MOTHER::deletetile(1 * 32, 8 * 32);
	Basic_Tile_MOTHER::deletetile(0 * 32, 8 * 32);
	Basic_Tile_MOTHER::deletetile(-1 * 32, 8 * 32);
	Basic_Tile_MOTHER::deletetile(-1 * 32, 7 * 32);
	Basic_Tile_MOTHER::deletetile(-1 * 32, 6 * 32);
	Basic_Tile_MOTHER::deletetile(0 * 32, 7 * 32);
	Basic_Tile_MOTHER::deletetile(0 * 32, 7 * 32);
	Basic_Tile_MOTHER::deletetile(0 * 32, 6 * 32);
	Basic_Tile_MOTHER::deletetile(0, 7 * 32);
	Basic_Tile_MOTHER::deletetile(-2 * 32, 5 * 32);
}

void Elevator::create_tiles_down(){
	new Wall(27, 1 * 32, 5 * 32, *Tmap);
	new Wall(27, 2 * 32, 6 * 32, *Tmap);
	new Wall(27, 2 * 32, 7 * 32, *Tmap);
	new Wall(27, 2 * 32, 8 * 32, *Tmap);
	new Wall(27, 1 * 32, 9 * 32, *Tmap);
	new Wall(27, 0 * 32, 9 * 32, *Tmap);
	new Wall(27, -1 * 32, 9 * 32, *Tmap);
	new Wall(27, -2 * 32, 8 * 32, *Tmap);
	new Wall(27, -2 * 32, 7 * 32, *Tmap);
	new Wall(27, -2 * 32, 6 * 32, *Tmap);
	new Wall(27, -2 * 32, 5 * 32, *Tmap);
	new Bg(4, -1 * 32, 5 * 32, *Tmap);
	new Bg(4, 0 * 32, 5 * 32, *Tmap);
	new Bg(4, 0 * 32, 6 * 32, *Tmap);
	new Bg(4, 1 * 32, 6 * 32, *Tmap);
	new Bg(4, 1 * 32, 7 * 32, *Tmap);
	new Bg(4, 1 * 32, 8 * 32, *Tmap);
	new Bg(4, 0 * 32, 8 * 32, *Tmap);
	new Bg(4, -1 * 32, 8 * 32, *Tmap);
	new Bg(4, -1 * 32, 7 * 32, *Tmap);
	new Bg(4, -1 * 32, 6 * 32, *Tmap);
	new AniBg(1, 0 * 32, 7 * 32, *Tmap);
	//new AniBg(25, 0 * 32, 6 * 32, *Tmap);
	new Teleporter(2, 0, 7 * 32, 5, 10, 1);
}

void Elevator::delete_tiles_down() {
	
	Basic_Tile_MOTHER::deletetile(1 * 32, 5 * 32);
	Basic_Tile_MOTHER::deletetile(2 * 32, 6 * 32);
	Basic_Tile_MOTHER::deletetile(2 * 32, 7 * 32);
	Basic_Tile_MOTHER::deletetile(2 * 32, 8 * 32);
	Basic_Tile_MOTHER::deletetile(1 * 32, 9 * 32);
	Basic_Tile_MOTHER::deletetile(0 * 32, 9 * 32);
	Basic_Tile_MOTHER::deletetile(-1 * 32, 9 * 32);
	Basic_Tile_MOTHER::deletetile(-2 * 32, 8 * 32);
	Basic_Tile_MOTHER::deletetile(-2 * 32, 7 * 32);
	Basic_Tile_MOTHER::deletetile(-2 * 32, 6 * 32);
	Basic_Tile_MOTHER::deletetile(-1 * 32, 5 * 32);
	Basic_Tile_MOTHER::deletetile(0 * 32, 5 * 32);
	Basic_Tile_MOTHER::deletetile(0 * 32, 6 * 32);
	Basic_Tile_MOTHER::deletetile(1 * 32, 6 * 32);
	Basic_Tile_MOTHER::deletetile(1 * 32, 7 * 32);
	Basic_Tile_MOTHER::deletetile(1 * 32, 8 * 32);
	Basic_Tile_MOTHER::deletetile(0 * 32, 8 * 32);
	Basic_Tile_MOTHER::deletetile(-1 * 32, 8 * 32);
	Basic_Tile_MOTHER::deletetile(-1 * 32, 7 * 32);
	Basic_Tile_MOTHER::deletetile(-1 * 32, 6 * 32);
	Basic_Tile_MOTHER::deletetile(0 * 32, 7 * 32);
	Basic_Tile_MOTHER::deletetile(0 * 32, 6 * 32);
	Basic_Tile_MOTHER::deletetile(0, 7 * 32);
	Basic_Tile_MOTHER::deletetile(-2 * 32, 5 * 32);
	
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-~MAIN TICK~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//This function is an overwritten virtual function, but this is a very important function
//So, this is placed seperate from the less important ones.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void Elevator::tick() {
	if (sound.getStatus() == 0 && has_created == false) {
		if (is_up == true) {
			create_tiles_up();
		}
		else {
			create_tiles_down();
		}
		P_Switch_MAIN::Switches[SM] = false;
		P_Switch_MAIN::Switches[SD] = true;
		has_created = true;
		//create_tiles_up();
		P_Switch_MAIN::update();
	}
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//-=-=-=-=-=-=-=-=-=-=-~VIRTUAL FUNCTIONS~-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//These are functions that overwrite the virtual functions in NPC_MOTHER.
//You may change these functions, but it is not necessary.
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//This is called if the player lands on the tile.
void Elevator::if_landed_on() {

}

