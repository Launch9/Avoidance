#pragma once
#include "stdafx.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <ostream>
using namespace std;

class ChoiceRTEXT
{
private:
	
	static sf::Font ChoiceRTEXT::DefaultFont;
	sf::Font f;
	bool ShouldFadeIn = true;
	bool ticksound = true;
	//This is the alpha of any of the colors in this class.
	int Alpha = 0;
	//This holds all the default text, such as the arrow and the "Make your selection text".
	std::vector<sf::Text> dt;
	//This is the color to be used on the text.
	sf::Color TextColor;
	//This is the color used for everything except the given strings.
	sf::Color ExtraTextColor;
	//This is the text size.
	int s = 27;
	//This is a vector full of sf::Text objects.
	std::vector<sf::Text> vt;
	//These are strings to be used during the process of making a choice in game.
	string toptext = "-=Make your choice=-";
	string arrow = "->";
	
	//This is the buttonlayout.
	//Default is w,a,s,d
	int buttonlayout = 0;
	//This is the index.
	int index = 0;
	//These are the cordinates of the text.
	int x = 0;
	int y = 0;
	
	//This is used for fading in the text.
	void UpdateText(sf::Text &txt);
	void UpdateAllText();
	inline void Setuptxt();
	//This function checks to see if you have gone over the boundaries.
	void Checklimits();
	//This updates the text with the extra color included in the private section of this class.
	void ExtraUpdateText(sf::Text &txt);
	
public:
	static bool ChoiceRTEXT::WK;
	static bool ChoiceRTEXT::SK;
	static bool ChoiceRTEXT::DK;
	static bool ChoiceRTEXT::AK;
	static bool ChoiceRTEXT::UPK;
	static bool ChoiceRTEXT::DOWNK;
	static bool ChoiceRTEXT::LEFTK;
	static bool ChoiceRTEXT::RIGHTK;
	ChoiceRTEXT();
	//By default the soundbool is true.
	ChoiceRTEXT(int x_pos, int y_pos);
	//This constructor allows you to put the font in right away.
	ChoiceRTEXT(int x_pos, int y_pos, sf::Font &font);

	
	//Button layouts are:
	//0 is for w,a,s,d
	//1 is for Up,Down,Left,Right
	int Choice();
	int white[3] = { 255,255,255 };
	int black[3] = { 0,0,0 };
	int blue[3] = { 0,0,255 };
	int red[3] = { 255,0,0 };
	void setPosition(int x_pos, int y_pos);
	void setTextSize(int Size);

	void setTextColor(sf::Color color);
	void setExtraTextColor(sf::Color color);
	//This returns the index of the ChoiceRTEXT object.
	int getindex();
	void reset();
	//Sets the boolean to wether or not the text should fade in or out.
	void setshouldfadein(bool TF);
	//Sets the boolean to determine wether or not moving the index up or down makes noise.
	void setsoundbool(bool TF);
	//0 is for w,a,s,d
	//1 is for Up,Down,Left,Right
	void setbuttonlayout(int layout);
	//This sets the list of string objects that are given as a choice.
	void setstringlist(vector <string> slist);
	//This sets the font in which all the text is drawn.
	void setfont(sf::Font font);
	static void resetcontrolbools();
	static void Printcontrols();
	void settextsize(int size);
	//This function will draw the choice GUI to the screen.
	void draw(sf::RenderWindow &win);
	
	static void init(sf::Font Default_font);
	
};

