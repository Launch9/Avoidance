#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
/*This class draws gaint sprites in the background of all the objects in the level.*/
class BackSplash_MOTHER
{

protected:
	static BackSplash_MOTHER * BackSplash_MOTHER::Object;
	//This is the type of object that is it, relative to the BackSplash_MOTHER class.
	int typeID = 0;
	//This draws the object.
	//This has to be overwritten, otherwise, it does nothing.
	virtual void draw(sf::RenderWindow &win);
	//This draws the object in front of all the tiles.
	//This will do nothing if not overwritten.
	virtual void draw_FORE(sf::RenderWindow &win);
	//This ticks the object.
	virtual void tick();
	//These are all the sprites ever needed.
	static std::vector<std::vector<std::vector<sf::Sprite>>> BackSplash_MOTHER::All_sprites;
public:
	static void init(sf::Texture &tex);
	//This draws the backsplash object currently being used.
	static void draw_all(sf::RenderWindow &win);
	//This draws all the foregrounds in the backsplash object currently being used.
	static void draw_all_fore(sf::RenderWindow &win);
	//This ticks all the objects.
	static void tick_all();
	//This gets the type of the Object that is currently in use.
	//This is for saving the background to the world.
	static int getSave();
	//This clears the backsplash object and will return the background to complete black.
	static void clear();
	//This creates an object associated with this class by typeID.
	static void create(int type);

};

