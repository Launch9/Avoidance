#pragma once
#include <string>
#include "PText.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp> 
////////////////////////////////
///This text class uses the PText class for its drawings.
///It has a clock to how long the text will last.
///If you change the text's string, it will reset the clock time.
////////////////////////////////
class TempText
{
private:
	//All text to be ticked through.
	static std::vector<TempText *> TempText::TT;
	//This is the text that is drawn.
	PText text;
	//This is the clock to tell how long it has been active.
	float time;
	//This is the type of way it dissapears.
	unsigned int type = 0;
	//This is a boolean used for fading effects.
	bool should_fade = false;
public:
	//This creates a temporary text that is able to be modified if kept.
	TempText(const float &x_pos, const float &y_pos, const std::string &string, int type_of_disapearence, const sf::Color &color = sf::Color::Red);
	//This creates a temporary text that is able to be modified if kept.
	TempText();
	//Deconstructor
	~TempText();
	//Ticking function.
	static void tick();
	//Function to delete the text.
	//This must be called to properly delete the text.
	void free();
	//Changes string.
	void setString(const std::string &string);
	//Sets position.
	void setPosition(const float &x_pos, const float &y_pos);
	//Sets position.
	void setPosition(const sf::Vector2f &position);
	//This sets the color of the text.
	void setColor(const sf::Color &color);
	//This sets the type of way it dissapears.
	void setType(int Type);
	//This function makes the text dissapear when you call it.
	void vanish();
	
};

