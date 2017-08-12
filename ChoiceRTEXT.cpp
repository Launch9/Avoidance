#include "stdafx.h"
#include "ChoiceRTEXT.h"
#include <iostream>
#include <thread>
#include "Sound.h"
#include "Font.h"
#define base32 32
#define Fadespeed 4
bool ChoiceRTEXT::WK;
bool ChoiceRTEXT::SK;
bool ChoiceRTEXT::DK;
bool ChoiceRTEXT::AK;
bool ChoiceRTEXT::UPK;
bool ChoiceRTEXT::DOWNK;
bool ChoiceRTEXT::LEFTK;
bool ChoiceRTEXT::RIGHTK;
sf::Font ChoiceRTEXT::DefaultFont;


ChoiceRTEXT::ChoiceRTEXT() {
	f = DefaultFont;
	ExtraTextColor = {255, 255, 255, 0};
	TextColor = { 0,0,0,0 };
	sf::Text a;
	a.setString("-=Make your choice=-");
	a.setFont(f);
	sf::Text b;
	b.setString("->");
	b.setFont(f);
	dt = { a,b };
	Setuptxt();

}
ChoiceRTEXT::ChoiceRTEXT(int x_pos, int y_pos) {
	f = DefaultFont;
	ExtraTextColor = { 255, 255, 255, 0 };
	TextColor = { 0,0,0,0 };
	sf::Text a;
	a.setString("-=Make your choice=-");
	a.setFont(f);
	sf::Text b;
	b.setString("->");
	b.setFont(f);
	dt = { a,b };
	Setuptxt();
	 
}

ChoiceRTEXT::ChoiceRTEXT(int x_pos, int y_pos, sf::Font &font) {
	
	ExtraTextColor = { 255, 255, 255, 0 };
	TextColor = { 0,0,0,0 };
	f = font;
	sf::Text a;
	a.setString("-=Make your choice=-");
	a.setFont(f);
	sf::Text b;
	b.setString("->");
	b.setFont(f);
	dt = { a,b };
	Setuptxt();

}
void ChoiceRTEXT::Setuptxt() {
	dt[1].setFont(f);
	dt[0].setFont(f);
	dt[1].setString(arrow);
	dt[0].setString(toptext);
	dt[1].setColor(ExtraTextColor);
	dt[0].setColor(ExtraTextColor);
	dt[1].setCharacterSize(s);
	dt[0].setCharacterSize(s);
	dt[0].setPosition(x, y);
	dt[1].setPosition(x - base32, y + base32 + (base32 * index));
	for (unsigned int i = 0; i < vt.size(); i++) {
		vt[i].setCharacterSize(s);
		vt[i].setFont(f);
		vt[i].setPosition(x, y + (base32 * (i + 1)));
		vt[i].setColor(TextColor);
	}

}
void ChoiceRTEXT::UpdateText(sf::Text &txt) {
	txt.setColor(TextColor);
}

void ChoiceRTEXT::ExtraUpdateText(sf::Text &txt) {
	txt.setColor(ExtraTextColor);
}
void ChoiceRTEXT::UpdateAllText() {
	
	for (unsigned int i = 0; i < vt.size(); i++) {
		UpdateText(vt[i]);
	}
	ExtraUpdateText(dt[0]);
	ExtraUpdateText(dt[1]);
}

void ChoiceRTEXT::Checklimits() {
	if (index < 0) {
		index = 0;
	}
	else if (vt.size() == 0) {
		index = 0;
	}

	else if (index > vt.size() - 1) {
		index = vt.size() - 1;
	}
}
int ChoiceRTEXT::Choice() {
	
	
	
	if (ShouldFadeIn == true && Alpha < 255 - Fadespeed) {
		Alpha += Fadespeed;
	}
	else {
		Alpha = 255;
	}
	ExtraTextColor.a = Alpha;
	TextColor.a = Alpha;
	//Updating the alpha of the text.
	UpdateAllText();

	
	dt[1].setPosition(sf::Vector2f(x - base32, y + base32 + (base32 * index)));
	
	
	//Checking the button layout
	switch (buttonlayout) {
	//w,a,s,d
	case 0:
		//Checking the button presses.
		if (WK == 1) {
			index -= 1;
			/*Checking to see if you want it to make a tick sound
			 every time you want it to move up or down and index.*/
			if (ticksound == 1) {
				Sound::Play(0);
			}
			Checklimits();
			
		}
		else if (SK == 1) {
			index += 1;
			/*Checking to see if you want it to make a tick sound
			every time you want it to move up or down and index.*/
			if (ticksound == 1) {
				Sound::Play(0);
			}
			Checklimits();
		}
		else if (DK == 1) {

			return -5;
			
		}
		else if (AK == 1) {
			return -6;
			
		}
		else {
			return index;
		}
		break;


	//UP,DOWN,LEFT,RIGHT
	case 1:
		
		//Checking the button presses.
		if (UPK == 1) {
			index -= 1;
			/*Checking to see if you want it to make a tick sound
			every time you want it to move up or down and index.*/
			if (ticksound == 1) {
				Sound::Play(0);
			}
			Checklimits();
		}
		else if (DOWNK == 1) {
			index += 1;
			/*Checking to see if you want it to make a tick sound
			every time you want it to move up or down and index.*/
			if (ticksound == 1) {
				Sound::Play(0);
			}
			Checklimits();
		}
		else if (RIGHTK == 1) {
			return -5;
			
		}
		else if (LEFTK == 1) {
			return -6;
			
		}
		else {
			return index;
		}
	}
	
	

}

void ChoiceRTEXT::draw(sf::RenderWindow &win) {
	win.draw(dt[0]);
	win.draw(dt[1]);
	//Looping through the size of the strlist to draw them all.
	for (unsigned int i = 0; i < vt.size(); i++) {

		win.draw(vt[i]);

	}
}
void ChoiceRTEXT::resetcontrolbools() {
	ChoiceRTEXT::WK = false;
	ChoiceRTEXT::AK = false;
	ChoiceRTEXT::SK = false;
	ChoiceRTEXT::DK = false;
	ChoiceRTEXT::UPK = false;
	ChoiceRTEXT::DOWNK = false;
	ChoiceRTEXT::LEFTK = false;
	ChoiceRTEXT::RIGHTK = false;
}

void ChoiceRTEXT::Printcontrols() {
	cout << "-----" << endl;
	cout << DK << endl;
	cout << AK << endl;
	cout << SK << endl;
	cout << WK << endl;
	cout << "ARROWKEYS" << endl;
	cout << UPK << endl;
	cout << DOWNK << endl;
	cout << RIGHTK << endl;
	cout << LEFTK << endl;
}

void ChoiceRTEXT::reset() {
	
	index = 0;
	Alpha = 0;
}

void ChoiceRTEXT::setstringlist(vector <string> slist) {

	vt = {};
	for (unsigned int i = 0; i < slist.size(); i++) {
		
		sf::Text txt;
		txt.setString(slist[i]);
		txt.setFont(f);
		txt.setCharacterSize(s);
		txt.setColor(TextColor);
		txt.setPosition(x, y + (base32 * (i + 1)));
		vt.push_back(txt);
	}
	
	



}
int ChoiceRTEXT::getindex() {
	return index;
}

void ChoiceRTEXT::setfont(sf::Font font) {
	
	f = font;
	for (unsigned int i = 0; i < dt.size(); i++) {
		dt[i].setFont(f);
	}
	for (unsigned int i = 0; i < vt.size(); i++) {
		vt[i].setFont(f);
	}
}


void ChoiceRTEXT::settextsize(int size) {
	s = size;
}
void ChoiceRTEXT::setsoundbool(bool TF) {
	ticksound = TF;
}

void ChoiceRTEXT::init(sf::Font Default_font) {
	DefaultFont = Default_font;
}

void ChoiceRTEXT::setPosition(int x_pos, int y_pos) {
	x = x_pos;
	y = y_pos;
	dt[1].setFont(f);
	dt[0].setFont(f);
	dt[0].setPosition(x, y);
	
	dt[1].setPosition(x - base32, y + base32 + (base32 * index));
	
	for (unsigned int i = 0; i < vt.size(); i++) {
		
		vt[i].setFont(f);
		int r = (32 * (i + 1));
		vt[i].setPosition(x, y + r);
		
		
	}
	
}

void ChoiceRTEXT::setTextSize(int Size) {
	s = Size;
	for (unsigned int i = 0; i < dt.size(); i++) {
		dt[i].setCharacterSize(s);
	}
	for (unsigned int i = 0; i < vt.size(); i++) {
		vt[i].setCharacterSize(s);
	}
}

void ChoiceRTEXT::setbuttonlayout(int layout) {
	buttonlayout = layout;
}

void ChoiceRTEXT::setshouldfadein(bool TF) {
	ShouldFadeIn = TF;
}

void ChoiceRTEXT::setTextColor(sf::Color color) {
	TextColor = color;
}
void ChoiceRTEXT::setExtraTextColor(sf::Color color) {
	ExtraTextColor = color;
}