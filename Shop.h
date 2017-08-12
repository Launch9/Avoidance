#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include "ChoiceRTEXT.h"
#include "Basic_Tile_MOTHER.h"
class Shop: public Basic_Tile_MOTHER {
	//This is used for storing the shop objects in.
	//This is nesscasary for checking player collision. Like if you want to shop here.
	static std::vector<Shop *> Shop::ShopObjects;
private:
	
	
	//This is the Dialouge stuff.
	string Dialougestring;
	sf::Sprite Diaspr;
	//This is the shops choice items.
	vector <int> shopv;
	//Choice object
	ChoiceRTEXT Cobj;
	sf::Sprite getDiasprite();
	std::string getDiastring();

public:
	//items is the vector full of item ids.
	//DialougeNumber is the ID of the dialouge that is suppost to pop up whilst shopping.
	Shop(int ID, int x_pos, int y_pos, int DialougeNum, vector <int> items, TileMap &TM);
	//These functions are used for getting certin variables from the shop objects.
	int getx();
	int gety();
	//This returns a certain index of the entirety of the shop's inventory.
	int riterv(int index);
	vector<int> getv();
	ST gets();
	//--

	//This collision detection is used when you want the shop dialouge to show up.
	//This is used when you want to check Collision for only shops!
	//This modifies player variables to meet the standards for "Shopping".
	//This will make the shop menu appear.
	static bool CheckShoppingCollision(int Playerx, int Playery);
	static void CommenceShop(int PlayerChannel, int buttonlayout);
	ChoiceRTEXT& rchoiceobj();
};

