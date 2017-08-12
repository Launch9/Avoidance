#pragma once
#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include <vector>
///OLD CLASS
///NEEDS REBUILDING
///Note put on 2/11/2016

using namespace std;

class Temporarytxt
{
private:
	vector<int> RBGColor;
	int xo;
	int yo;
	unsigned int ticks;
	bool IsStatic = false;
	int mxticks;
	string text;
	sf::Text disptext;
	//Effect 1 variables
	int effectnumpri = 0;
	int effect1h = 0;
	unsigned int effect1a = 0;
	static vector<Temporarytxt> Temporarytxt::TObjs;
	inline void drawtext(sf::RenderWindow &win);
	//This is will return true if it wants you to delete the dialouge; Otherwise, it will return false, obviously.
	bool tick();
	bool getisStatic();
public:
	
	Temporarytxt(string &str, int x, int y, int maxticks, const sf::Font &font, sf::Color c, int effectnum = 0, int textsize = 24, bool isStatic = false);
	//This function clears all the temporary text on the screen.
	static void clearCache();
	static void TTxT_tick();

	static void Temporarytxt::drawalltext(sf::RenderWindow &win);
};

