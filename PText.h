#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp> 
///////////////////////////////////
///Preliminary text
///To be used for something greater.
///////////////////////////////////
class PText
{
private:
	//This is a vector full of pointers to the text objects within all the PText objects.
	static std::vector<PText *> PText::all_text;
	//This tells the object if it should be visible or not.
	bool isVisible = false;
	//This is the text that is drawn.
	sf::Text text;
	
public:
	//Quick constructor.
	PText(const sf::Text &text_to_be_drawn);
	//Default constructor.
	PText();
	//Deconstructor
	~PText();
	//This will set the position of the text.
	void setPosition(const float &x_pos, const float &y_pos);
	//This will set the position of the text.
	void setPosition(const sf::Vector2f &position);
	//This will set the string of the text.
	void setString(const std::string &str);
	//This will make the text equal to the given parameter.
	void setText(const sf::Text &txt);
	//This will make the text dissapear.
	//THIS WILL NOT DESTROY THE PTEXT OBJECT!
	void vanish();
	//This will make the text appear.
	void appear();
	//This sets the color of the text.
	void setColor(const sf::Color &color);
	//This gets the color of the text.
	const sf::Color &getColor();
	//This will properly delete(deallocate) the text.
	void free();
	//This tells you if the text is visible or not.
	//Will return true, if it is visible.
	//Will return false, if it is not visible.
	bool getIs_visible();
	//This will draw all the text associated with this class.
	static void drawAll(sf::RenderWindow &win);
};

