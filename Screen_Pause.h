#pragma once
#include "Screen_MOTHER.h"
#include "Choice.h"
#include <functional>
#include "MusicPlayer.h"
class Screen_Pause : public Screen_MOTHER
{
private:
	//This stores the boolean telling if the score timer was on or off when the player paused the game.
	bool was_timer_on = false;
	//This tells you if this is the first entrance loop or not.
	bool is_first = true;
	//These are the lambda functions that are called when a choice has been made.
	std::vector<std::function<void(sf::RenderWindow &win)>> Lambdas;
	//This is the image of what was on the screen before you paused.
	sf::Texture preRender_Tex;
	//This is the sprite that is drawn to show what happened before the game was paused.
	sf::RectangleShape preRender;
	//This is used to access the MusicPlayer.
	MusicPlayer mp;
	//This is the vector of text objects that are displayed in the check object.
	std::vector<sf::Text> options;
	//This is what text that is displayed when called.
	sf::Text text;
	//This is the text that comprises the controls.
	sf::Text controls;
	//This shades everything to make it look nice.
	sf::RectangleShape shader;
	//This is the object that allows a choice to be made once paused.
	Choice C;
	//This renders everything in the menu.
	void render(sf::RenderWindow &win);
	//This makes all the lambda functions to be used in the choice object.
	void make_lambda_functions();
public:
	//Default constructor
	Screen_Pause();
	//This is called over and over to make sure that the screen is doing what it should be doing.
	bool main(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event);
	

};

