#pragma once
#include "Invisible_MOTHER.h"
#include "TileMap.h"
//Item name: Elevator
//Date made 12/8/2016 2:26:08 AM
//Made by Josh

class Elevator : public Invisible_MOTHER
{
private:
	static std::vector<Elevator *> Elevator::Objects;
	//This tells if the elevator is up or down.
	bool is_up = false;
	//This is a sound that plays.
	//Once the sound is done, then it means you have reached your destination.
	sf::Sound sound;
	//This is for identification purposes within this class type.
	int type = 0;
	//This tells if it has created the tiles yet.
	bool has_created = false;
	//This is the switch that controls a door.
	int SD = 0;
	//This is the switch that controls the movement. Toggles up or down.
	int SM = 0;
	//This a pointer to the tilemap.
	TileMap *Tmap;
	//This creates the tiles at the top of the elevator.
	void create_tiles_up();
	//This deletes the tiles at the top of the elevator.
	void delete_tiles_up();
	//This creates the tiles at the bottom of the elevator.
	void create_tiles_down();
	//This deletes the tiles at the bottom of the elevator.
	void delete_tiles_down();
	//This moves the elevator up.
	void move_up();
	//This moves the elevator down.
	void move_down();
	//This toggles the position of the elevator.
	void toggle();
	//This is called to update the elevator object.
	void update();
	//Virtual functions {

	//This is called if the player lands on the tile.
	void if_landed_on();
	//This is called every frame.
	void tick();

	//}
	
public:
	/*insert constructor description here.*/
	Elevator(int Type, int x_pos, int y_pos, int Switch_for_door, int Switch_for_toggle, TileMap &TM);
	//Deconstructor
	~Elevator();
	//This updates all the elevator objects.
	static void update_all();
};

