#pragma once
#include "Invisible_MOTHER.h"
#include "Basic_Tile_MOTHER.h"
#include "T_MOTHER.h"
#include "NPC_MOTHER.h"
class Room;
class Basic_Tile_MOTHER;
class NPC_MOTHER;
class Room : public Invisible_MOTHER
{
private:
	static std::vector<Room *> Room::Objects;
	std::vector<T_MOTHER *> Tiles; //These are the sprites that are contained in the room.
	std::vector<NPC_MOTHER *> NPCs; //These are the NPCs that are contained in the room.
	sf::Vector2i size; //first is equal to width_in_blocks. second is equal to height_in_blocks.
	int channel = 0; //How it should be refered to.
	int type = 0; //This is the type of room that it is.
	sf::RectangleShape bounding; //This tells you the area that you have selected.
	bool is_active = false; //This tells whether or not the room is active.
	//This activates the room.
	void activate();
	//This decativates the room.
	void deactivate();
	friend Room;
public:
	void tick();
	Room(int Type, int Channel, int x_pos, int y_pos, int width_in_blocks, int height_in_blocks);
	~Room();
	//This function loops through all the rooms that are in the world, and grabs pointers to all the sprites that are in the rooms.
	static void update();
	//This draws everything. This was overwritten from Invisible_MOTHER.
	void draw(sf::RenderWindow &win);
	//This function activates a given room.
	static void activate_room(unsigned int channel);
	//This function deactivates a given room.
	static void deactivate_room(unsigned int channel);
	
};

