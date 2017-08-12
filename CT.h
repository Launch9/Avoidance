#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp> 
#include "ST.h"
#include "T_MOTHER.h"
///These are allowed to be rotated.
///They are a little heavier than the latter, "ST.cpp".
///Only use these when you have to rotate the sprite.
///These are generally used for the NPCs.
class CT : public T_MOTHER
{

private:
	//This is the origin where everything is made relative to.
	sf::Vector2f origin;
	//These factors tell how scaled the sprite is.
	sf::Vector2f scale_factors;
	//This decides what transforms to apply to the sprite.
	//Rotation, scaling.
	sf::Transform transform;
	
	//This is the degree at which the sprite is rotated at.
	float rotation = 0;
	//This will set all the vertices to the cordinates relative to the x and y positions.
	void mapCords();
	//This will translate the transform object to the right location.
	void translate();
	
	//Checks to see if a degree has gone over it's limts.
	//It returns the new degree after going through it's if statements.
	float checkDegree(float degree);
public:
	//Default constructor
	CT();
	
	//This will set the position of the tile to be drawn.
	void setPosition(const sf::Vector2f &position);
	//This will set the position of the tile to be drawn.
	void setPosition(float x_pos, float y_pos);
	//This sets the rotation of the CT.
	void setRotation(float degree);
	//This rotates the CT.
	void rotate(float degree);
	//This sets the origin of the CT.
	void setOrigin(const sf::Vector2f &Origin);
	//This sets the origin of the CT.
	void setOrigin(float x_offset, float y_offset);
	//This moves the sprite.
	void move(float x_offset, float y_offset);
	//This moves the sprite.
	void move(const sf::Vector2f &offset);
	//This gets you the position of the sprite. (top left corner)
	const sf::Vector2f &getPosition();
	//This gets the rotation of the CT.
	float getRotation();
	//This sets the scale of the CT.
	void setScale(const sf::Vector2f &factors);
	//This sets the scale of the CT.
	void setScale(float x_factor, float y_factor);
	//This sets the scale of the CT.
	//This scales the CT.
	void scale(float x_factor, float y_factor);
	//This scales the CT.
	void scale(const sf::Vector2f &factors);
	//This will specify what part of the texture given to the ST is drawn.
	void setTextureRect(const sf::IntRect &rect);
	//This is the equal operater overload.
	void operator=(const CT &I);
	//This is the operator used for taking the texture rectangle but keeping the pointer in the To_BeDrawn array.
	//Use this operator for animating things with the AniST objects.
	//This is equivalent to: setTextureRect(I.getRect());
	void operator*=(AniT &I);

	


};

