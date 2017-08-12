#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "TileMap.h"
///This function is meant to be inherited by the debug class.
///This function allows the user to move around the world and place blocks and such.
class Editor
{
private:
	//This is the font used for making objects that need a font to go with them.
	//MAIN FONT
	static sf::Font Editor::MAINFONT;
	//This holds all the text objects that need to be displayed during the active part of the editor.
	static std::vector<sf::Text> Editor::ActiveTexts;
	//This determines what blockID is used during the placement of blocks.
	static unsigned int Tileid;
	//This determines what type of block is used during the placement of blocks.
	static unsigned int TileType;
	//This is determines wether or not you are a able to move the cursor.
	static bool ableToMove;
	//This is the main amount of ticks the class is keeping track of.
	static float ticks;
	//This is how many ticks it takes before you can use another moving function.
	static float WaitTick;
	//These are the cordinates where the cursor is going to be when moving around.
	static int x;
	static int y;
	//This will loop through all the texts and draw them.
	static void DrawText(sf::RenderWindow &win);
	//This can be used to tell if the editor is on or off.
	static bool isActive;
	//This is the sprite that is at the center of the screen.
	//This is where blocks are placed during editor hours.
	static sf::Sprite Editor::Cursor;
	//This holds the default saving world.
	static std::string Editor::DefaultSWorld;
public:
	//This returns the x cordinate of the cursor.
	static int getx();
	//This returns the y cordinate of the cursor.
	static int gety();
	//This function initaites the sprites and such.
	//Call this before you use this class.
	static void init(sf::Texture &tex, sf::Font font);
	static void moveup();
	static void moveright();
	static void movedown();
	static void moveleft();
	//This will place a tile at the x and y cordinates of the cursor.
	static void placetile(TileMap &TM);
	//This will delete the tile at the given x and y cordinates.
	static void deletetile();
	//This will snap the cam toward the editor's cursor.
	static void SnapCam();
	//This function switchs to the editor class during gameplay.
	static void Start();
	//This function switchs back to the player, and turns off the editor.
	static void Stop();
	//This function returns the isActive boolean. This is used to tell what controls to use.
	static bool GetStatus();
	//This will change variables and such.
	static void tick();
	//This will draw things.
	static void draw(sf::RenderWindow &win);
	//This will change the amount of ticks that need to pass before you can move again.
	static void SetWaitTick(int amount);
	//This makes the Tileid variable move up the given amount.
	static void Tileid_UP(unsigned int amount);
	//This makes the Tileid variable move down the given amount.
	static void Tileid_DOWN(unsigned int amount);
	//This makes the type of tile variable move up the given amount.
	static void Tiletype_UP(unsigned int amount);
	//This makes the type of tile variable move down the given amount.
	static void Tiletype_DOWN(unsigned int amount);
	//This will move all the text on the screen joined with the editor class to a given offset.
	static void MoveTextPos(int x_offset, int y_offset);
	
	//This will start the NPCs moving again.
	static void PauseNPCs();
	//This will stop the NPCs.
	static void UnPauseNPCs();
	//This saves the world to a default file.
	static void SaveDWorld(TileMap &TM);
	//This sets the default save world.
	static void SetDWorld(std::string WorldFile);
};

