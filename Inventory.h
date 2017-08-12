#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
class Inventory
{
private:
	//x cordinate in which everything is relative to.
	int x = 0;
	//y cordinate in which everything is relative to.
	int y = 0;
	//This will set the cursor's position to the right position.
	void updatecursor();
	//This will set all the positions of all sprites to the correct location.
	void update();
	//This holds all the cursor sprites that are not being used at the moment.
	static std::vector<sf::Sprite> Inventory::cursors;
	//This holds all the item ids.
	std::vector<int> items;
	//This holds all the item sprites.
	std::vector<sf::Sprite> itemsprites;
	//This is the cursor sprite that you are using.
	sf::Sprite cursor;
	//This is the index at which the cursor is at.
	int index = 0;
	//This is the cursorID.
	int ci = 0;
public:

	//This initalizes everything.
	static void init(sf::Texture &tex);
	//This makes an object with variables set to your liking.
	Inventory(int x_pos, int y_pos, int CursorID, std::vector<int> Items);
	Inventory();
	Inventory &operator=(const Inventory &I);
	//This moves the cursor down an index(32 pixels).
	void movedown();
	//This moves the cursor up an index(32 pixels).
	void moveup();
	//This will use the item at the current index.
	void useitem();
	//This will set the x and y position of the entire inventory object.
	void setXY(int x_pos, int y_pos);
	//Gets the x position.
	int get_xpos();
	//Gets the y position.
	int get_ypos();
	//This just moves the x/y position.
	void move(int xoffset, int yoffset);
	//This will change the list of items the inventory object is holding at the moment.
	void setitemlist(std::vector<int> itemlist);
	//This will draw all things within this class that are drawable.
	void draw(sf::RenderWindow &win);
};

