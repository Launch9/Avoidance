#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Basic_Tile_MOTHER.h"
#include <vector>
///General Functions
namespace GF
{
	
	//This is the clock for the beginning of the program. Or since the last time called, clock_reset.
	extern sf::Clock c;
	//This is the standard framerate for the window.
	extern int standardFramerate;
	
	extern float delta; //time this round - time last round
	extern float ttr; //time this round
	extern float tlr; //time last round
	extern bool isPaused; //Is app paused?
	extern sf::Time tss; //time since start
	extern std::vector<sf::Font> Fonts;
	extern sf::Sprite OverlapSprite;
	extern std::vector<std::vector<int>> Overlapcords;
	
	void init(sf::Texture &tex, int framerate);
	
	//This checks to see if one block is on top of another.
	//This is mainly used so that my OCD doens't break down whilst placing blocks everywhere.
	bool CheckTile_OverLap(int x, int y);
	//This will loop through all the OverLap sprite tiles.
	//It will delete the one at the given x and y cordinates.
	void DeleteTile_OverLap(int x, int y);
	//This will tell the computer the game is paused.
	void setPause(const bool &TF);
	//This will tell you if the game is paused or not.
	bool getPause();
	//This is used for many functions. please use this function in the main loop.
	void tick();
	//This sets the seed for the random function.
	void setSeed(float new_seed);
	//This is used to draw things.
	void draw(sf::RenderWindow &win);
	//This is for converting an integer to a string.
	std::string str(float conversionint);
	//This will convert a string to a float.
	float StringtoFloat(std::string string);
	//This will convert the given string into an integer and return it.
	int StringtoInt(std::string string);
	//This will convert the given string into an unsigned int and return it.
	unsigned int StringtoUnint(std::string string);
	//This takes in a vector and finds the highest value of the vector.
	int MaxValue(std::vector<int> Vector);
	//This takes in a vector and fidns the lowest value of the vector.
	int MinValue(std::vector<int> Vector);
	//This returns the distance the two cordinates are.(IN BLOCKS)
	int Distance(int x1, int x2, int y1, int y2);
	//This gets the standard Framerate.
	int getFramerate();

	//This gets converts degrees to radians.
	float radians(float degree);
	//This sets the delta float variable.
	void setDelta(float Delta);
	//This sets the "time this round" float variable.
	void setTTR(float Timethisround);
	//This sets the "time last round" float variable.
	void setTLR(float Timelastround);
	//This sets the "time since start" sf::Time variable.
	void setTSS(sf::Time TimeSinceStart);
	//This gets the delta float variable.
	float getDelta();
	//This gets the "time this round" float variable.
	float getTTR();
	//This gets the "time last round" float variable.
	float getTLR();
	//This returns true if all the variables in a boolean vector are false.
	 bool is_all_false(const std::vector<bool> &Vector);
	//This returns true if all the variables in a boolean vector are true.
	 bool is_all_true(const std::vector<bool> &Vector);
	//This gets the "time since start" float variable.
	 sf::Time getTSS();
	//This rounds the float given to the highest 32
	 int round32(float num);
	//This tells if the index of the vector given is a legal move.
	//returns true if index exists.
	//returns false if index does not exist.
	 bool does_exist(int index, int size_of_vector);
	//This gets the average between two numbers.
	 float average(float num1, float num2);
	//This gets the distance between two points in pixels.
	 float getDistance_Pixels(const sf::Vector2f &position1, const sf::Vector2f &position2);
};

