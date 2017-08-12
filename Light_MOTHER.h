#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
///This class is meant to be inherited.
///You can make some really cool light patterns by inheriting this class.
///This class comes with a free bottle of wine.
///PLEASE TAKE IT AWAY FROM US!
class Light_MOTHER
{
private:
	
	
	
	static unsigned int Light_MOTHER::t;
	//All of the Light Objects as pointers.
	
	
protected:
	static std::vector<Light_MOTHER*> Light_MOTHER::LObjects;
	int typeID = 0;
	std::vector<int> SavedParameters;
	sf::Sprite s;
	int x;
	int y;
	int lightpow;
	int baselightpow;
	inline int getx();
	inline int gety();
	//This adds the given amount to the color element provided without looping. e.g. color.b,color.a,color.r,color.g
	//This will return true if it has added the entire number to the color_element.
	//This will return false if it has exceeded 255.
	//If provided 0 amount to add, it will return false.
	bool addColor(sf::Uint8 &color_element, int amount_to_add);
	//This subtracts the given amount to the color element provided without looping. e.g. color.b,color.a,color.r,color.g
	//This will return true if it has subtracted the entire number to the color_element.
	//This will return false if it has fallen below 0.
	//If provided 0 amount to add, it will return false.
	bool subtractColor(sf::Uint8 &color_element, int amount_to_subtract);
	//This adds/subtracts the given amount to the color element provied without looping. e.g. color.b,color.a,color.r,color.g
	//This will return true if it has subtracted/added the entire number to the color_element.
	//This will return false if it went beyond 0 or 255.
	//If provided 0 amount to add, it will return false.
	bool add_subtract_Color(sf::Uint8 &color_element, int amount);
	//This is the color of the light.
	sf::Color LColor;
	inline unsigned int getbaselightpower();
	inline sf::Sprite getsprite();
	inline int getlightpower();
	inline void setlightpower(int power);
	sf::Color getcolor();
	//This will return the adress of the vector!
	std::vector<int> &getSavedParametersA();
	inline int gettypeID();
	//This function will be call every few frames or so.
	virtual void tick();
public:
	bool r = false;
	bool g = false;
	bool b = false;
	//This will delete a tile at the given cordinates.
	//If a light source tile was found, it will return true; otherwise, it will return false.
	static bool deletetile(int x, int y);
	//Please initalize before usage.
	//Will get weird effects if not initalized before making objects!
	//ALL ADJESTING VARIABLES ARE MADE HERE!
	static void init();
	//Should be threaded for maximum efficiency.
	static void maintick();
	//This returns the lighting power of the tile as an integer.
	static int get_tile_lighting(int tilex, int tiley);
	//This modifys the tile's lighting to the right color and ocupancy.
	static void SetColorAndLighting(sf::Color &tilecolor, int tilex, int tiley);
	//This will reset all the lighting on all tiles!
	//CPU time heavy
	static void ResetLighting();
	//This will delete all the lighting tiles contained in this class.
	static void deleteAll();
	//This will return the string for saving the lighting tiles to a file.
	static std::string GetSave();
	
};

