#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "AniT.h"
///Use this class if you want to make invisible blocks that do different things.
///e.g. Sound blocks and Next World blocks.
///This class is meant to be inherited.
class Invisible_MOTHER
{
private:
	
	
protected:
	//These are all the sprites, in the entire game.
	//first index = type of texture you are using.
	//second index = type of sprite it is.(like for a wall?, or a background?).
	//third index = type of animation it is.
	//fourth index = type of AniT it is.
	static std::vector<std::vector<std::vector<std::vector<AniT>>>> Invisible_MOTHER::All_Sprites;
	//This is some text that will be drawn next to a invisible block to define what it is to the editor.
	sf::Text Information;
	//This is the rectangle that is drawn where the invisible objects are while in editor.
	sf::RectangleShape Rect;
	//This function should be overwritten so that it is called every tick.
	virtual void tick();
	int typeID = 0;
	int x = 0;
	int y = 0;
	static std::vector<Invisible_MOTHER*> Invisible_MOTHER::Col_InvisibleObjects;
	static std::vector<Invisible_MOTHER*> Invisible_MOTHER::NonCol_InvisibleObjects;
	//This function will return the object's x position.
	int getx();
	//This function will return the object's y position.
	int gety();
	//This function will return the player's x position.
	static int getPlayer_x();
	//This function will return the player's y position.
	static int getPlayer_y();
	//This function will return the player's vx position.
	static float getPlayer_vx();
	//This function will return the player's vy position.
	static float getPlayer_vy();
	//This is called when the player lands on the x and y cordiantes.
	virtual void if_landed_on();
	virtual bool checkCollision_over(int x_pos, int y_pos, bool isPlayer, bool isProjectile);
	//This checks the collision of the nonCol tiles.
	virtual bool checkCollision_over_empty(int x_pos, int y_pos, bool isPlayer, bool isProjectile);
	//This is called everytime the world is reset. (the player dies).
	virtual void WorldReset();
	//These are the parameters and variables that will be saved to the disk.
	std::vector<int> SavedParameters;
	std::vector<int> GetSavedParameters();
	//This function will set up the Information and Rectangle variables to default.
	void setup(sf::Color c, int x, int y, std::string Information_About_Block);
	//This function will draw a sprite to the screen only if the editor is active.
	virtual void draw(sf::RenderWindow &win);
	//Virtual deconstructor
	virtual ~Invisible_MOTHER();

public:
	static bool checkCollision(int x_pos, int y_pos, bool isPlayer, bool isProjectile); //This is checked in the Basic_Tile_MOTHER class.
	static bool checkSpecialCollision(int Playerid); //This is checked in the Basic_Tile_MOTHER class.
	//This function will make the sprites for all the objects.
	static void init(sf::Texture &tex);
	//This function returns a string full of information to be kept on the disk for use later.
	static std::string GetSave();
	//This function goes through all the objects this class contains and ticks them.
	static void All_Tick();
	//This function erases a soundblock at the given cordinates.
	static bool deletetile(int x, int y);
	//This function will draw all the sprites.
	static void All_Draw(sf::RenderWindow &win);
	//This function clears all the objects.
	static void clear_all();
	//This function tells all the NonCol objects that the player has died.
	static void tell_WorldReset_all();
};

