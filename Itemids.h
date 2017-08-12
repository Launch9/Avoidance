#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
using namespace std;
class Itemids
{
private:

	static vector <string> Itemids::itemstrings;
	static vector<sf::Sprite> Itemids::itemsprites;
	static vector<sf::Text> Itemids::itemtexts;
public:
	static void useitem(int itemid);
	static void init(sf::Texture &tex);
	//Returns a vector of strings instead of a vector of integers.
	//This is used when trying to decode item ids.
	static std::vector<std::string> rvstring(std::vector<int> intlist);
	static std::string rstring(int itemid);
	//Returns a vector of sprites corresponding to each integer.
	static std::vector<sf::Sprite> rvsprite(std::vector<int> intlist);
	static sf::Sprite rsprite(int itemid);
	//This gets the item info in a text object.
	static sf::Text rinfo(int itemid);
};

