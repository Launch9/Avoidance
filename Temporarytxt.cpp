#include "stdafx.h"
#include "Temporarytxt.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <vector>
#include "Player.h"
#include <future>
#include <string>
#include <vector>

using namespace std;

vector<Temporarytxt> Temporarytxt::TObjs;




Temporarytxt::Temporarytxt(string &str, int x, int y, int maxticks, const sf::Font &font, sf::Color c, int effectnum, int textsize, bool isStatic)
{
	
	xo = x;
	yo = y;
	effectnumpri = effectnum;
	mxticks = maxticks;
	ticks = 0;
	text = str;
	disptext.setFont(font);
	disptext.setString(str);
	//Making the color for the text.
	
	disptext.setPosition(sf::Vector2f(x, y));
	//Deciding what to do with the effectnumber.
	switch (effectnum) {
		case 1:
			c.a = 0;
			disptext.setPosition(sf::Vector2f(x, y-32));
		
			
	}
	IsStatic = isStatic;
	RBGColor = { c.r, c.g, c.b, c.a };
	disptext.setColor(c);
	disptext.setCharacterSize(textsize);
	//Putting this object into the static object lists.
	TObjs.push_back(*this);
}

bool Temporarytxt::tick() {
	switch (effectnumpri) {
	case 1:
		//Checking to see if it really needs to go any higher.
		if (effect1a < 255) {
			effect1a += 5;
		}
		else {
			effect1a = 255;
		}
		if (effect1h < 32) {
			effect1h++;
		}
		else {
			effect1h = 32;
		}
		//Making the colors.
		sf::Color c(RBGColor[0], RBGColor[1], RBGColor[2], effect1a);
		disptext.setColor(c);
		//This is to set the position.
		disptext.setPosition(sf::Vector2f(xo, yo - effect1h));
		
	}
	ticks += 1;
	if (ticks >= mxticks) {
		return true;
	}
	else {
		return false;
	}
}
void Temporarytxt::TTxT_tick() {
	if (TObjs.size() > 0) {
		for (unsigned int i = 0; i < TObjs.size(); i++) {
			bool t = TObjs[i].tick();
			if (t == true) {
				TObjs.erase(TObjs.begin() + i);
			}
		}

	}
	
}
void Temporarytxt::drawtext(sf::RenderWindow &win) {
	if (IsStatic == false) {
		win.draw(disptext);
	}
	else {
		Cam::drawGUI_chan(0, win, disptext);
	}
	

}

void Temporarytxt::drawalltext(sf::RenderWindow &win) {
	if (TObjs.size() > 0) {
		for (unsigned int i = 0; i < TObjs.size(); i++) {

			//Drawing the text.
			TObjs[i].drawtext(win);
			
			
		}

	}
	
}

void Temporarytxt::clearCache() {
	TObjs.clear();
}

bool Temporarytxt::getisStatic() {
	return IsStatic;
}