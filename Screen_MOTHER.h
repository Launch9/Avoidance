#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "ChoiceRTEXT.h"
#include "GF.h"
#include "Ani_MOTHER.h"
#include "Music.h"
#include "TileMap.h"
class Screen_MOTHER
{	
private:
	static bool Screen_MOTHER::is_ready; //This tells the class whether or not you are ready to start a temporary screen.
	//This is the index of screen that is waiting to be called.
	static int Screen_MOTHER::screen_index;
protected:
	
	Music song;
	//This vector holds all your animation objects that you would want to use on a screen.
	std::vector<Ani_MOTHER> AO;
	//This decides wether or not the screen should exit its main loop or not.
	bool Exit = false;
	//This distinguishs which screen is which.
	int typeID;
	//This is a vector full of screen objects that will be refered to later.
	static std::vector<Screen_MOTHER*> Screen_MOTHER::Screens;
	//This is the texture that the screen uses.
	sf::Texture tex;
	//This is a vector that holds all the sprites that your screen may contain.
	std::vector<sf::Sprite> Sprites;
	//This is a vector that holds all the text that your screen may contain.
	std::vector<sf::Text> Texts;
	//This is the main function for looping through the screen.
	virtual bool main(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event);
public:
	//This tells you if there is a temporary screen being used at the present time.
	static bool get_is_ready();
	static void init();
	//This will go to the screen index given.
	//This will return true if it has completed the function well.
	//This will return false if the player has closed the window.
	static void start(int Screen_index);
	//This will check to see if you are ready to start a screen.
	//This will return true, if it is using a screen.
	//If it is using a screen, then you should make sure that this function is called contantly.
	static bool check(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event);
	
};

