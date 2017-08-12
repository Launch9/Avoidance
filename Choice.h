#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
class Choice : public sf::Drawable
{
private:
	static sf::Sprite Choice::globalSprite;
	//Relative x position
	float x = 0;
	//Relative y position
	float y = 0;
	//This is the sprite that tells you where the index is at.
	sf::Sprite Cursor;
	//These are the choices that you can make.
	std::vector<sf::Text> TextVector;
	//This is the index of where the cursor is currently at.
	int index = 0;
	//This moves the index up the amount given.
	void moveindexup(const unsigned int &amount);
	//This moves the index down the amount given.
	void moveindexdown(const int &amount);
	//This maps the cursor's location to the index number.
	void mapCCords();
	//This maps all the text objects relative to the x and y cordinates.
	void mapTCords();
	//This will set the scale and map the cursor.
	void mapSCCords();
public:
	//Default constructor
	Choice();
	//This checks to see what is happening in the choice object.
	//This should be called constantly in order to get constant updates from it.
	//Return MAP-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//Will return -5 if a selection has been made.
	//Will return -6 if a backwards selection has been made.
	//Will return the index if nothing happens.
	//INFORMATION-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	//The index 0 is equal to the bottom most text displayed in the choice object.
	//It moves up from there.
	int check();
	//This sets the position of the choice object.
	void setPosition(float x_pos, float y_pos);
	//This sets up the kind of text displayed in the choice object.
	void setText(const std::vector<sf::Text> &txt, bool should_reset_index = true);
	//This gets the index the cursor is at.
	int getIndex();
	//This sets the color of the cursor.
	//By default the cursor is black.
	void setColorCursor(const sf::Color &new_color);
	//This sets the color of all the text objects.
	void setColor(const sf::Color &Color_to_be_changed_to);
	//This draws the choice object.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//This will initiate anything that needs to be made.
	static void init(sf::Texture &tilemap_tex);
};

