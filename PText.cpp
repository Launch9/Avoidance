#include "stdafx.h"
#include "PText.h"
#include "GF.h"
#include "Font.h"
#define Default_Font Font::Get_arial() 
std::vector<PText *> PText::all_text;

PText::PText(const sf::Text &text_to_be_drawn) {

	//Making it know its visible
	isVisible = true;
	//Copying
	text = text_to_be_drawn;
	//Setting font
	text.setFont(Default_Font);
	//Pushing the text object into the static vector for later drawing.
	all_text.push_back(this);
}

PText::PText(){
	//Setting position
	text.setPosition(0, 0);
	//Setting string
	text.setString("Nothing added");
	//Setting font
	text.setFont(Default_Font);
	//Pushing the text object into the static vector for later drawing.
	all_text.push_back(this);
}

PText::~PText() {
	for (unsigned int i = 0; i < all_text.size(); i++) {
		//Checking to see if it is the right text pointer.
		if (this == all_text[i]) {
			//If so, erase it from the vector.
			all_text.erase(all_text.begin() + i);
		}
	}
}
void PText::setPosition(const float &x_pos, const float &y_pos) {
	text.setPosition(x_pos, y_pos);
}

void PText::setString(const std::string &str) {
	text.setString(str);
}

void PText::setText(const sf::Text &txt) {
	text = txt;
}

void PText::vanish() {
	if (isVisible == true) {
		sf::Color b;
		b = text.getColor();
		b.a = 0;
		text.setColor(b);
		isVisible = false;
	}
}

void PText::appear() {
	if (isVisible == false) {
		sf::Color b;
		b = text.getColor();
		b.a = 255;
		text.setColor(b);
		isVisible = true;
	}
	
}

void PText::drawAll(sf::RenderWindow &win) {
	for (unsigned int i = 0; i < all_text.size(); i++) {
		win.draw(all_text[i]->text);
	}
}

void PText::setColor(const sf::Color &color) {
	text.setColor(color);
}

void PText::free() {
	delete this;
}

const sf::Color &PText::getColor() {
	return text.getColor();
}

bool PText::getIs_visible() {
	return isVisible;
}

void PText::setPosition(const sf::Vector2f &position) {
	text.setPosition(position);
}