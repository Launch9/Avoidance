#include "stdafx.h"
#include <iostream>
#include "Shop.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Itemids.h"
#include "Light_MOTHER.h"
#include "Dia.h"
#include "GF.h"
#include "Font.h"
#include <memory>
#define base32 32
std::vector<Shop *> Shop::ShopObjects;

Shop::Shop(int ID, int x_pos, int y_pos, int DialougeNum, vector <int> items, TileMap &TM) {

	sprite *= All_Sprites[TM.getTextureID()][typeID][0][ID];
	sprite.setPosition(x_pos, y_pos);
	x = x_pos;
	y = y_pos;
	GF::CheckTile_OverLap(x, y);
	typeID = 2;
	shopv = items;
	SavedParameters = { x_pos, y_pos, DialougeNum };
	for (unsigned int i = 0; i < items.size(); i++) {
		SavedParameters.push_back(items[i]);
	}
	Dialougestring = Dia::getDia_string(DialougeNum);
	Diaspr = Dia::getDia_sprite(DialougeNum);
	vector<string> strv = Itemids::rvstring(items);
	Cobj.setstringlist(strv);
	Cobj.setfont(Font::Get_isocpeur());
	Cobj.setPosition(x + (base32 * 2), y);
	Cobj.setbuttonlayout(0);
	Light_MOTHER::SetColorAndLighting(color, x, y);
	sprite.setColor(color);
	sprite.setup();
	ShopObjects.push_back(this);
	ColTiles.push_back(this);
	
}
int Shop::riterv(int index) {
	return shopv[index];
}
ChoiceRTEXT& Shop::rchoiceobj() {
	return Cobj;
}
int Shop::getx() {
	return x;
}
int Shop::gety() {
	return y;
}
vector<int> Shop::getv() {
	return shopv;
}
ST Shop::gets() {
	return sprite;
}
sf::Sprite Shop::getDiasprite() {
	return Diaspr;
}
std::string Shop::getDiastring() {
	return Dialougestring;
}

bool Shop::CheckShoppingCollision(int Playerx, int Playery) {

	

	for (unsigned int i = 0; i < ShopObjects.size(); i++) {

		int xblock = ShopObjects[i]->getx();
		int yblock = ShopObjects[i]->gety();

		if ((Playerx == xblock) && (Playery == yblock)) {
			//This triggers the Dialouge box.
			if (Dia::getcachelength() == 0) {
				Dia(ShopObjects[i]->getDiasprite(), ShopObjects[i]->getDiastring(), false);
			}
			return true;


		}
		else {

			if (i == ShopObjects.size()) {
				return false;

			}


		}
	}
	

		
	return false;
}

void Shop::CommenceShop(int PlayerChannel, int buttonlayout) {
	for (unsigned int i = 0; i < ShopObjects.size(); i++) {
		if ((ShopObjects[i]->getx() == Player::PlayerObjects[PlayerChannel]->getx()) && (ShopObjects[i]->gety() == Player::PlayerObjects[PlayerChannel]->gety() - base32)) {
			//This is for asking a choice question.
			int dn = ShopObjects[i]->rchoiceobj().Choice();
			switch (dn) {
			case -1:
				break;
			case -5:
				//In the case the user selected something.
				Player::PlayerObjects[PlayerChannel]->addinventoryitem(ShopObjects[i]->riterv(ShopObjects[i]->rchoiceobj().getindex()));
				break;
			//This is the case if you exit out of the choice.
			case -6:
				Player::PlayerObjects[PlayerChannel]->setCLock(false);
				Player::PlayerObjects[PlayerChannel]->setShoppingtog(false);
				Dia::iterate_apress();
				//Restting the choice object so that it will have the effect when it appears again.
				ShopObjects[i]->rchoiceobj().reset();
			}
			break;
		}
	}
	

}



