#include "stdafx.h"
#include "Wall.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Light_MOTHER.h"
#include "Basic_Tile_MOTHER.h"
#include <memory>

#define base32 32
using namespace std;





//Make sure you check the equal operator overload function is working.

Wall::Wall(int ID, int x_pos, int y_pos, TileMap &TM) {

	
	typeID = 0;
	//Gettng the sprite out.
	
	sprite *= All_Sprites[TM.getTextureID()][typeID][0][ID];
	
	x = x_pos;
	y = y_pos;
	GF::CheckTile_OverLap(x, y);
	sprite.setTexture(0);
	sprite.setPosition(x,y);
	Light_MOTHER::SetColorAndLighting(color, x, y);
	sprite.setColor(color);
	
	sprite.setup();
	SavedParameters = { x_pos, y_pos, ID };
	
	//Putting the object that was just created into a static vector to be used later.
	ColTiles.push_back(this);
	
	
	

}

void Wall::Addline(unsigned int ID, int x, int y, int direction, int distance, TileMap &TM) {
	//Checking the direction that the line extends in.
	switch (direction) {
		//In the case the user wants it in the direction up.
	case 0:
		for (int i = 0; i <= distance; i++) {
			new Wall(ID, x, y + ((i*-1)*base32), TM);
		};
		break;
		//In the case the user wants it in the direction right.
	case 1:
		for (int i = 0; i <= distance; i++) {
			new Wall(ID, x + ((i)*base32), y, TM);
		};
		break;
		//In the case the user wants it in the direction down.
	case 2:
		for (int i = 0; i <= distance; i++) {
			new Wall(ID, x, y + ((i)*base32), TM);
		};
		break;
		//In the case the user wants it in the direction left.
	case 3:
		for (int i = 0; i <= distance; i++) {
			new Wall(ID, x + ((i*-1)*base32), y, TM);
		};
		break;
	}

	
}





