#include "stdafx.h"
#include "Itemids.h"
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "Font.h"
using namespace std;

vector<sf::Sprite> Itemids::itemsprites;
vector <string> Itemids::itemstrings;
vector<sf::Text> Itemids::itemtexts;
std::vector<std::string> Itemids::rvstring(std::vector<int> intlist) {
	vector <string> returnvector;
	
	for (unsigned int i = 0; i < intlist.size(); i++) {
		//Pushing back the string that the item id called for.
		returnvector.push_back(itemstrings[intlist[i]]);
	}
	return returnvector;
}
std::string Itemids::rstring(int itemid) {
	return(itemstrings[itemid]);
}
void Itemids::init(sf::Texture &tex) {
	int dcs = 10; //Default character size for text objects.
	//Making the list of items
	//1
	string str1("Scissors of running really fast.");
	sf::Sprite s1;
	s1.setTexture(tex);
	s1.setTextureRect(sf::IntRect(544, 544, 32, 32));
	sf::Text t1;
	t1.setString("This speeds you up to 2x speed.");
	t1.setColor(sf::Color::White);
	t1.setFont(Font::Get_isocpeur());
	t1.setCharacterSize(10);

	//2
	string str2("Blanket of mischeif");
	sf::Sprite s2;
	s2.setTexture(tex);
	s2.setTextureRect(sf::IntRect(544, 512, 32, 32));
	sf::Text t2;
	t2.setString("This will slow down all things except the timer.");
	t2.setColor(sf::Color::White);
	t2.setFont(Font::Get_isocpeur());
	t2.setCharacterSize(10);
	itemstrings = { str1, str2 };
	itemsprites = { s1, s2 };
	itemtexts = { t1,t2 };
}

//Returns a vector of sprites corresponding to each integer.
std::vector<sf::Sprite> Itemids::rvsprite(std::vector<int> intlist) {
	vector <sf::Sprite> returnvector;
	for (unsigned int i = 0; i < intlist.size(); i++) {
		//Pushing back the string that the item id called for.
		returnvector.push_back(itemsprites[intlist[i]]);
	}
	return returnvector;
}
sf::Sprite Itemids::rsprite(int itemid) {
	return itemsprites[itemid];
}

void Itemids::useitem(int itemid) {
	switch (itemid) {
	case 0:
		break;
	}
}

sf::Text Itemids::rinfo(int itemid) {
	return itemtexts[itemid];
}