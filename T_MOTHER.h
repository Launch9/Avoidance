#pragma once
#include "TileMap.h"
#define off 0.0075
///This class is mostly just a glue to hold together the ST and CT tiles.
///Keeping all types of basic drawing classes together so that I can refer to them as being one type.
class T_MOTHER
{
private:
	

protected:
	bool isSetup = false;
	//This is the position of the tile.
	sf::Vector2f position;
	//This is the color of the Tile.
	sf::Color color = sf::Color::White;
	//Type of texture to use.
	int type_of_texture = -1;
	//This tells if the sprite is active or not.
	bool isActive = true;
	//This will get the vertices of the tile.
	std::vector<sf::Vertex *> getVertices();
	friend class TileMap;
public:
	//This gets whether or not tile is active.
	//true = active, false = not active.
	bool get_is_Active();
	T_MOTHER();
	~T_MOTHER();
	//This will deactivate the sprite.
	//It will make it not visible, by changing the color's alpha to 0. It is still drawn!
	//Do not use this to speed things up.
	virtual void deactivate();
	//This will activate the sprite and make it visible and back to its original color again.
	//This is not the same as .setup!
	virtual void activate();
	
	//This will set the color of the Tile.
	void setColor(const sf::Color &new_color);
	//This will get the color of the Tile.
	const sf::Color &getColor();
	//type may equal these textures.
	//type = 0 : tiles : description = "It is composed of basic tiles such as the wall, or ground."
	//type = 1 : character : description = "Mainly used for npcs and characters."
	//type = 2 : tiles : description = "This is the same as 0 except for the fact that it is drawn over the player texture. Use this for foregrounds."
	//this should be called before you setup the sprite.
	virtual void setTexture(unsigned int type);
	//This will not work if you have not set up a texture.
	//This sets the object up for drawing.
	virtual void setup();
	//Member Objects---
	sf::VertexArray tile;
	sf::IntRect texrect;
};

