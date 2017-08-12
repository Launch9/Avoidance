#include "stdafx.h"
#include "Inventory.h"
#include "Itemids.h"
#include "Player.h"
#include "Cam.h"
std::vector<sf::Sprite> Inventory::cursors;

Inventory::Inventory(int x_pos, int y_pos, int CursorID, std::vector<int> Items)
{
	index = 0;
	items = Items;
	x = x_pos;
	y = y_pos;
	itemsprites = Itemids::rvsprite(Items);
	ci = CursorID;
	cursor = cursors[CursorID];
	update();
}

Inventory::Inventory() {
	index = 0;
}
void Inventory::init(sf::Texture &tex) {
	sf::Sprite s1;
	s1.setTexture(tex);
	s1.setTextureRect(sf::IntRect(224, 128, 32, 32));
	cursors = { s1 };
}

void Inventory::movedown() {
	
	index -= 1;
	if (index < 0) {
		index = 0;
	}
	updatecursor();
}

void Inventory::moveup() {
	if (itemsprites.size() != 0) {
		index += 1;
		if (index > items.size() - 1) {

			index = items.size() - 1;
		}
	}
	
	updatecursor();
}

void Inventory::useitem() {
	Itemids::useitem(items[index]);
}

void Inventory::setXY(int x_pos, int y_pos) {
	x = x_pos; y = y_pos;
	update();
}

void Inventory::updatecursor() {
	cursor.setPosition(x, y + (index * 32));
}

void Inventory::update() {
	if (index < 0) {
		index = 0;
	}
	else if (index > items.size() - 1) {
		index = items.size() - 1;
	}


	int r = 0;
	for (unsigned int i = 0; i < itemsprites.size(); i++) {
		itemsprites[i].setPosition(x,y + r);
		r += 32;
	}
	cursor.setPosition(x, y + (index * 32));
}

void Inventory::draw(sf::RenderWindow &win) {
	for (unsigned int i = 0; i < itemsprites.size(); i++) {
		Cam::drawGUI_chan(0, win, itemsprites[i]);
	}
	Cam::drawGUI_chan(0, win, cursor);
}

void Inventory::setitemlist(std::vector<int> itemlist) {
	items = itemlist;
	itemsprites = Itemids::rvsprite(itemlist);
	update();
}

Inventory &Inventory::operator=(const Inventory &I) {
	this->ci = I.ci;
	this->x = I.x;
	this->y = I.y;
	this->items = I.items;
	this->itemsprites = I.itemsprites;
	this->cursor = I.cursor;
	this->index = I.index;
	this->update();
	return *this;
}

int Inventory::get_xpos() {
	return x;
}

int Inventory::get_ypos() {
	return y;
}

void Inventory::move(int xoffset, int yoffset) {
	setXY(x + xoffset, y + yoffset);
}