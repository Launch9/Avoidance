#pragma once
#include "T_MOTHER.h"
#include "AniT.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp> 
#include "ST.h"
class RT : public T_MOTHER
{
	
private:
	//This contains the size of the sprite.
	sf::Vector2f tile_size;
	//This will set all the vertices to the cordinates relative to the x and y positions.
	void mapCords();
public:
	//Default constructor
	RT();
	//Deconstructor
	~RT();
	//This will set the size of the rect that contains the texture of the sprite.
	void setSize(const sf::Vector2f &size);
	//This will set the size of the rect that contains the texture of the sprite.
	void setSize(float width, float height);
	//This will set the position of the tile to be drawn.
	void setPosition(const sf::Vector2f &Position);
	//This will set the position of the tile to be drawn.
	void setPosition(const sf::Vector2i &Position);
	//This will set the position of the tile to be drawn.
	void setPosition(float x_pos, float y_pos);
	//This will specify what part of the texture given to the ST is drawn.
	void setTextureRect(const sf::IntRect &rect);
	//This is the equal operater overload.
	void operator=(const RT &I);
	//This is the operator used for taking the texture rectangle but keeping the pointer in the To_BeDrawn array.
	//Use this operator for animating things with the AniST objects.
	//This is equivalent to: setTextureRect(I.getRect());
	void operator*=(AniT &I);
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	//This returns the cordinates of the sprite.
	const sf::Vector2f &getPosition();
};

