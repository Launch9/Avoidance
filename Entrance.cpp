#include "stdafx.h"
#include "Entrance.h"
#include "GF.h"
#include "Room.h"
Entrance::Entrance(int Type, int x_pos, int y_pos, int RoomIDenter, int RoomIDexit)
{
	x = x_pos;
	y = y_pos;
	type = Type;
	GF::CheckTile_OverLap(x_pos, y_pos);
	roomIDenter = RoomIDenter;
	roomIDexit = RoomIDexit;
	typeID = 7;
	SavedParameters = { type, x_pos, y_pos, RoomIDenter, RoomIDexit };
	setup(sf::Color::Green, x, y, "Entrance\nType: " + GF::str(Type) + "\nRoomIDenter: " + GF::str(RoomIDenter) + "\nRoomIDexit: " + GF::str(RoomIDexit));

	NonCol_InvisibleObjects.push_back(this);
}

void Entrance::if_landed_on() {
	Room::activate_room(roomIDenter);
	Room::deactivate_room(roomIDexit);
}

void Entrance::tick() {

}
