#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
class Dia
{
private:
	//This is a vector full of the sprites that come with the dialouge package!
	static std::vector<sf::Sprite> Dia::DiaSprites;
	//This is the sprite that the player sees depending on who is talking.
	sf::Sprite spr;
	//This is the text of the dialouge.
	sf::Text txt;
	//This is the default font for the text.
	static sf::Font Dia::f;
	//These are all the Objects that will be iterated throughtout the ticks.
	static std::vector <Dia> Dia::DiaObjects;
	//These are variables that tell where to put the sprites and text.
	static int Dia::screendivisionY;
	static int Dia::screendivisionX;
	static int Dia::txt_spr_div;
	//This is used for getting the sprite of a dialouge box.
	sf::Sprite getsprite();
	//This is for setting the sprite's x and y cordinates.
	void setspritexy(int x, int y);
	//This is for setting the text's x and y cordinates.
	void settextxy(int x, int y);
	//This is for getting the text.
	sf::Text gettext();
	//This is the boolean that is used when you want to change the dialouge.
	static bool bpress;
	//This is the boolean that is used when you want to change the dialouge with a second advanced bool.
	//This will not change dialouge objects that are advanced(apress).
	static bool Dia::apress;
	//This is to see if you need to use the bpress variable to iterate through this one or if it needs an apress variable.
	bool bpress_compatibility;
	//This is used to see if the bpress is compatibile. If not, then use the iterate_apress() function.
	bool get_bpress_compatibility();
public:
	//This will search through all the dialouge in the game.
	//Give this an ID and it will return the dialouge for that ID as an std::string.
	static std::string getDia_string(int ID);
	//This will search through all the dialouge in the game.
	//Give this an ID and it will return the sprite designated to that dialouge ID.
	static sf::Sprite getDia_sprite(int ID);
	//This gets the length of the total amount of dialouges in the vector.
	static int getcachelength();
	//Use this to iterate once through the dialouge cache.
	static void iterate();
	//This is for making all the sprites.
	static void init(sf::Texture &t, sf::Font font);
	//This is for moving all the dialouge text and sprite positions and setting everything up.
	static void tick();
	//This is for drawing all the dialouge text and sprites.
	static void draw(sf::RenderWindow &win);
	///-=-
	//This will not change dialouge objects that are advanced(apress).
	static void iterate_apress();
	//This will clear the dialouge cache.
	static void clear();
	//This is for making objects...
	Dia(sf::Sprite &sprite, const std::string &string, bool bpress_Compatibility = true);
	Dia(sf::Sprite &sprite, const std::vector<std::string> &string, bool bpress_Compatibility = true);
	
};

