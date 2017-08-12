#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Basic_Tile_MOTHER.h"
class Bg: public Basic_Tile_MOTHER
{


	
public:
	Bg(int ID, int x_pos, int y_pos, TileMap &TM);
	//Directions, 0 = up, 1 = right, 2 = down, 3 = left.
	static void Addline(unsigned int ID, int x, int y, int direction, int distance, TileMap &TM);
	
	
};

