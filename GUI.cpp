#include "stdafx.h"
#include "GUI.h"
#include "Cam.h"
#include "GF.h"
#include "Player.h"
#include <vector>
#include "Itemids.h"
#include "Inventory.h"
#include "Gauntlets.h"
#include "Font.h"
#define InventoryDist 32 * 5
#define IS 2
#define GauntletDisplayLength 3
std::vector<bool> GUI::Animations;
std::vector<sf::Sprite> GUI::Sprites;
std::vector<sf::RectangleShape> GUI::Rectangles;
std::vector<sf::Text> GUI::Texts;
std::vector<sf::RectangleShape> GUI::Lives;
std::vector<sf::Sprite> GUI::InventorySprites;
std::vector<sf::Sprite> GUI::GSprites;
sf::RectangleShape GUI::Life_Square;
sf::Color GUI::DefaultPowerColor;
sf::Color GUI::NewPowerColor;
Inventory GUI::inventoryobject;
int GUI::inventorymaxlength;
sf::Font GUI::F;
void GUI::init(sf::Texture &tex, sf::Font font) {
	inventorymaxlength = 5;
	sf::Text t0;
	sf::Text t1;
	sf::Text t2;
	sf::Text t3;//World loadup text
	sf::Text t4;//Framerate display
	sf::Text t5;//Special fire toggle ready or not.
	sf::Text t6;//High score in dungeon
	F = font;
	t0.setFont(F);
	t0.setString("Floor " + GF::str(0));
	t0.setPosition(0, 0);
	t0.setCharacterSize(30);
	t1.setFont(F);
	t1.setString("Time remaining: NULL");
	t1.setPosition(Cam::getdisplaywidth() - 500, 0);
	t1.setCharacterSize(30);
	t2.setFont(F);
	t2.setString("Score: 0");
	t2.setPosition(0,30);
	t2.setCharacterSize(30);
	t4.setFont(F);
	t4.setString("");
	t4.setCharacterSize(12);
	t4.setPosition(0, 0);
	t5.setPosition(Cam::getdisplaywidth() - 200, 5);
	t5.setColor(sf::Color::Red);
	t5.setFont(Font::Get_isocpeur());
	t5.setCharacterSize(10);
	t6.setPosition(Cam::getdisplaywidth() / 6, 0);
	t6.setColor(sf::Color::Blue);
	t6.setFont(F);
	t6.setCharacterSize(30);
	t6.setString("High score: NULL");
	Inventory inven(-32, InventoryDist, 0, { 0,0,0 });
	inventoryobject = inven;
	DefaultPowerColor = sf::Color(0, 60, 0, 255);
	NewPowerColor = sf::Color(0, 255, 0, 255);

	sf::Sprite s1; //Continuation sprite of the inventory pop out. (Middle)
	s1.setTexture(tex);
	s1.setTextureRect(sf::IntRect(64, 64, 32, 32));
	for (unsigned int i = 0; i < 3; i++) {
		GSprites.push_back(sf::Sprite());
	}
	int d = 0;
	for (unsigned int i = 0; i < inventorymaxlength; i++) {
		sf::Sprite s;
		s = s1;
		s.setPosition(-32, InventoryDist + d);
		InventorySprites.push_back(s);
		d += 32;

	}
	sf::Sprite s2; // Bottom end of item list.
	s2.setTexture(tex);
	s2.setTextureRect(sf::IntRect(32, 64, 32, 32));
	s2.setPosition(-32, InventoryDist + (32 * inventorymaxlength));
	sf::Sprite s3; // Top end of item list.
	s3.setTexture(tex);
	s3.setTextureRect(sf::IntRect(64, 96, 32, 32));
	s3.setPosition(-32, InventoryDist - 32);
	
	//Rectangles-=-=-=-=-=-=-=-=-=-=-=-=-
	sf::RectangleShape r0; //Blue fuel bar
	r0.setPosition(Cam::getdisplaywidth() - 48, 5);
	r0.setFillColor(sf::Color::Blue);
	sf::RectangleShape rect; //This is the square that represents a life
	rect.setFillColor(sf::Color::Blue);
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(2);
	rect.setSize(sf::Vector2f(8, 8));
	rect.setPosition(Cam::getdisplaywidth() - 66, -12);
	sf::RectangleShape rect1; //This is the outline for the fuel bar.
	rect1.setFillColor(sf::Color::Transparent);
	sf::Color Colour;
	Colour.r = 50;
	Colour.g = 50;
	Colour.b = 50;
	Colour.a = 255;
	rect1.setOutlineColor(Colour);
	rect1.setPosition(Cam::getdisplaywidth() - 48, 5);
	rect1.setOutlineThickness(4);
	sf::RectangleShape rect2; //This is a green charge bar that tells you how much power you have.
	rect2.setFillColor(DefaultPowerColor);
	rect2.setPosition(Cam::getdisplaywidth() - 80, 5);
	sf::RectangleShape rect3; //This is the outline for the power bar.
	rect3.setFillColor(sf::Color::Transparent);
	rect3.setOutlineColor(Colour);
	rect3.setPosition(Cam::getdisplaywidth() - 80, 5);
	rect3.setOutlineThickness(4);
	Life_Square = rect;
	Sprites = { s2,s3 };
	Texts = { t0, t1, t2, t4, t5, t6 };
	Rectangles = { r0, rect1, rect2, rect3 };
	Animations = { false, false, false, false };
}
void GUI::Draw_All(sf::RenderWindow &win, int CameraChannel) {
	for (unsigned int i = 0; i < Sprites.size(); i++) {
		Cam::drawGUI_chan(CameraChannel, win, Sprites[i]);
	}
	for (unsigned int i = 0; i < InventorySprites.size(); i++) {
		Cam::drawGUI_chan(CameraChannel, win, InventorySprites[i]);
	}
	for (unsigned int i = 0; i < Texts.size(); i++) {
		Cam::drawGUI_chan(CameraChannel, win, Texts[i]);
	}
	for (unsigned int i = 0; i < GSprites.size(); i++) {
		Cam::drawGUI_chan(CameraChannel, win, GSprites[i]);
	}
	for (unsigned int i = 0; i < Rectangles.size(); i++) {
		Cam::drawGUI_chan(CameraChannel, win, Rectangles[i]);
	}
	for (unsigned int i = 0; i < Lives.size(); i++) {
		Cam::drawGUI_chan(CameraChannel, win, Lives[i]);
	}
	inventoryobject.draw(win);
}

//Sprite functions
void GUI::rotateSprite(const int &index, const float &rotation_offset) {
	Sprites[index].rotate(rotation_offset);
}
void GUI::moveSprite(const int &index, const int &x_offset, const int &y_offset) {
	Sprites[index].move(sf::Vector2f(x_offset, y_offset));
}
void GUI::setSpritePosition(const int &index, const int &x, const int &y) {
	Sprites[index].setPosition(x, y);
}
void GUI::setSpriteRotation(const int &index, const float &degree) {
	Sprites[index].setRotation(degree);
}
float GUI::getSpriteRotation(const int &index) {
	return Sprites[index].getRotation();
}
int GUI::getSpritePosition_x(const int &index) {
	return Sprites[index].getPosition().x;
}
int GUI::getSpritePosition_y(const int &index) {
	return Sprites[index].getPosition().y;
}

//Sprite functions
void GUI::rotateRect(const int &index, const float &rotation_offset) {
	Rectangles[index].rotate(rotation_offset);
}
void GUI::moveRect(const int &index, const int &x_offset, const int &y_offset) {
	Rectangles[index].move(sf::Vector2f(x_offset, y_offset));
}
void GUI::setRectPosition(const int &index, const int &x, const int &y) {
	Rectangles[index].setPosition(x, y);
}
void GUI::setRectRotation(const int &index, const float &degree) {
	Rectangles[index].setRotation(degree);
}
float GUI::getRectRotation(const int &index) {
	return Rectangles[index].getRotation();
}
int GUI::getRectPosition_x(const int &index) {
	return Rectangles[index].getPosition().x;
}
int GUI::getRectPosition_y(const int &index) {
	return Rectangles[index].getPosition().y;
}

//Text functions
void GUI::rotateText(const int &index, const float &rotation_offset) {
	Texts[index].rotate(rotation_offset);
}
void GUI::moveText(const int &index, const int &x_offset, const int &y_offset) {
	Texts[index].move(x_offset, y_offset);
}
void GUI::setTextPosition(const int &index, const int &x, const int &y) {
	Texts[index].setPosition(x, y);
}
void GUI::setTextRotation(const int &index, const float &degree) {
	Texts[index].setRotation(degree);
}
float GUI::getTextRotation(const int &index) {
	return Texts[index].getRotation();
}
int GUI::getTextPosition_x(const int &index) {
	return Texts[index].getPosition().x;
}
int GUI::getTextPosition_y(const int &index) {
	return Texts[index].getPosition().y;
}
const sf::Font &GUI::getTextFont(const int &index) {
	const sf::Font *t = Texts[index].getFont();
	
	return *t;
}
int GUI::getTextSize(const int &index) {
	return Texts[index].getCharacterSize();
}
void GUI::toggle_ani(int index) {
	if (Animations[index] == true) {
		
		Animations[index] = false;
	}
	else {
	
		Animations[index] = true;
	}
	
}
void GUI::anitick() {

	//This is the inventory opening animation.
	if (Animations[0] == true) {
		
		for (unsigned int i = 0; i < InventorySprites.size(); i++) {
			InventorySprites[i].move(IS, 0);
		}
		
		Sprites[0].move(IS, 0);
		Sprites[1].move(IS, 0);
		inventoryobject.move(IS, 0);
		if (InventorySprites[0].getPosition().x >= 0) {
			
			for (unsigned int i = 0; i < InventorySprites.size(); i++) {
				InventorySprites[i].setPosition(0, InventorySprites[i].getPosition().y);
			}
			
			Sprites[0].setPosition(0,Sprites[0].getPosition().y);
			Sprites[1].setPosition(0,Sprites[1].getPosition().y);
		
			inventoryobject.setXY(0, inventoryobject.get_ypos());
			Animations[0] = false;
		}
		
	}
	if (Animations[1] == true) {
		for (unsigned int i = 0; i < InventorySprites.size(); i++) {
			InventorySprites[i].move(-IS, 0);
		}
		Sprites[0].move(-IS, 0);
		Sprites[1].move(-IS, 0);
		inventoryobject.move(-IS, 0);
		if (InventorySprites[0].getPosition().x <= -32) {
			for (unsigned int i = 0; i < InventorySprites.size(); i++) {
				InventorySprites[i].setPosition(-32, InventorySprites[i].getPosition().y);
			}
			Sprites[0].setPosition(-32, Sprites[0].getPosition().y);
			Sprites[1].setPosition(-32, Sprites[1].getPosition().y);
			inventoryobject.setXY(-32, inventoryobject.get_ypos());
			Animations[1] = false;
		}
	}
	
}

void GUI::update() {
	
	if (Lives.size() != Player::PlayerObjects[0]->getLives()) {
		
		Lives.clear();
		
		sf::RectangleShape r = Life_Square;
		
		for (unsigned int i = 0; i < Player::PlayerObjects[0]->getLives(); i++) {
			r.move(0, 17);
			Lives.push_back(r);
		}
		
	}
	
	if (Player::PlayerObjects[0]->is_powershot_ready() == true) {
		Texts[4].setString("PowerShot is Active");
	}
	else {
		Texts[4].setString("PowerShot is Inactive");
	}

	if (Player::PlayerObjects[0]->getPower() >= Player::PlayerObjects[0]->get_maxPower()) {
		Rectangles[2].setFillColor(NewPowerColor);
	}
	else {
		Rectangles[2].setFillColor(DefaultPowerColor);
	}
	Rectangles[0].setSize(sf::Vector2f(5,Player::PlayerObjects[0]->getFuel()));
	Rectangles[1].setSize(sf::Vector2f(5, Player::PlayerObjects[0]->get_maxFuel()));
	Rectangles[2].setSize(sf::Vector2f(5, Player::PlayerObjects[0]->getPower()));
	Rectangles[3].setSize(sf::Vector2f(5, Player::PlayerObjects[0]->get_maxPower()));
	std::vector<int> inventory = Player::PlayerObjects[0]->getinventory();
	std::vector<sf::Sprite> Items = Itemids::rvsprite(inventory);
	
	int r = 0;
	for (unsigned int i = 0; i < Items.size(); i++) {
		Items[i].setPosition(-32, InventoryDist + r);
		r += 32;
	}
	GSprites = {};
	//Setting up the GSprites(Gauntlet Sprites).
	int failed = 0;
	for (unsigned int i = 0; i < Player::PlayerObjects[0]->getDisplayGauntlets().size(); i++) {
		if (Player::PlayerObjects[0]->getDisplayGauntlets()[i] != -1) {
			GSprites.push_back(Gauntlets::GetIcon(Player::PlayerObjects[0]->getDisplayGauntlets()[i]));
			GSprites[i - failed].setPosition(Cam::getdisplaywidth() - 32, i * 32);
		}
		else {
			failed++;
		}
		
	}
	inventoryobject.setitemlist(inventory);
	
	Texts[0].setString("Floor " + GF::str(Player::PlayerObjects[0]->getFloor()));
	Texts[1].setString("Time: " + GF::str(Player::PlayerObjects[0]->getScoring().getTime()));
	Texts[2].setString("Score: " + GF::str(Player::PlayerObjects[0]->getScoring().getScore()));
	Texts[5].setString("High score: " + GF::str(Player::PlayerObjects[0]->getScoring().get_high_score()));
	//Texts[3].setString("Framerate: " + GF::str(GF::getFPS()));
}

void GUI::Iup() {
	inventoryobject.moveup();
}
void GUI::Idown() {
	inventoryobject.movedown();
}