#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Inventory.h"
#include "World.h"
class World;
class GUI
{
private:
	static sf::RectangleShape GUI::Life_Square; //This is the rectangle that is put into the Lives vector when needed.
	//This is the font used during drawing of the GUI.
	static sf::Font GUI::F;
	static sf::Color GUI::DefaultPowerColor;
	static sf::Color GUI::NewPowerColor;
	static std::vector<bool> GUI::Animations;
	static std::vector<sf::Sprite> GUI::Sprites;
	static std::vector<sf::RectangleShape> GUI::Rectangles;
	static std::vector<sf::RectangleShape> GUI::Lives;
	static std::vector<sf::Text> GUI::Texts;
	static std::vector<sf::Sprite> GUI::InventorySprites;
	static std::vector<sf::Sprite> GUI::GSprites;
	static int GUI::inventorymaxlength;
	static Inventory GUI::inventoryobject;
public:
	friend World;
	static void init(sf::Texture &tex, sf::Font font);
	//Sprite functions
	static void Draw_All(sf::RenderWindow &win, int CameraChannel);
	static void rotateSprite(const int &index, const float &rotation_offset);
	static void moveSprite(const int &index, const int &x_offset, const int &y_offset);
	static void setSpritePosition(const int &index, const int &x, const int &y);
	static void setSpriteRotation(const int &index, const float &degree);
	static float getSpriteRotation(const int &index);
	static int getSpritePosition_x(const int &index);
	static int getSpritePosition_y(const int &index);
	//Rectangle functions
	static void rotateRect(const int &index, const float &rotation_offset);
	static void moveRect(const int &index, const int &x_offset, const int &y_offset);
	static void setRectPosition(const int &index, const int &x, const int &y);
	static void setRectRotation(const int &index, const float &degree);
	static float getRectRotation(const int &index);
	static int getRectPosition_x(const int &index);
	static int getRectPosition_y(const int &index);
	//Text functions
	static void rotateText(const int &index, const float &rotation_offset);
	static void moveText(const int &index, const int &x_offset, const int &y_offset);
	static void setTextPosition(const int &index, const int &x, const int &y);
	static void setTextRotation(const int &index, const float &degree);
	static float getTextRotation(const int &index);
	static int getTextPosition_x(const int &index);
	static int getTextPosition_y(const int &index);
	static const sf::Font &getTextFont(const int &index);
	static int getTextSize(const int &index);

	//This function updates all the text in the GUI.
	static void update();
	//This toggles an animation that you want to happen.
	static void toggle_ani(int index);
	//This will be for all the animations that you might want to happen.
	static void anitick();
	//This moves the inventory index up.
	static void Iup();
	//This moves the inventory index down.
	static void Idown();
	
};

