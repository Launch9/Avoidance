#include "stdafx.h"
#include "TempText.h"
#include "Font.h"
#include "GF.h"
#include <iostream>
std::vector<TempText *> TempText::TT;
#define default_time 5
#define default_size 10
TempText::TempText(const float &x_pos, const float &y_pos, const std::string &string, int type_of_disapearence, const sf::Color &color)
{
	sf::Text t;
	t.setString(string);
	t.setColor(color);
	t.setFont(Font::Get_smalle());
	t.setPosition(x_pos, y_pos);
	t.setCharacterSize(20);
	text.setText(t);
	type = type_of_disapearence;
	time = default_time;
	TT.push_back(this);
}

TempText::TempText() {
	sf::Text t;
	t.setColor(sf::Color::Red);
	t.setFont(Font::Get_smalle());
	t.setCharacterSize(default_size);
	text.setText(t);
	time = default_time;
	TT.push_back(this);
}

void TempText::tick() {
	for (unsigned int i = 0; i < TT.size(); i++) {
		TT[i]->time = TT[i]->time - GF::getDelta();
		
			switch (TT[i]->type) {
			case 0:
				if (TT[i]->time <= 0) {
					//Making the text not visible.
					TT[i]->text.vanish();
					//Setting the time back to default.
					TT[i]->time = default_time;
				}
				break;
			case 1:
				if (TT[i]->time <= 0) {
					if (TT[i]->text.getIs_visible() == true) {
						//Setting the color back to what is was before the fading.
						sf::Color c = TT[i]->text.getColor();
						c.a = 255;
						TT[i]->text.setColor(c);
						//Making the text not visible.
						TT[i]->text.vanish();
						
					}
					//Setting the time back to default.
					TT[i]->time = default_time;
				}
				else {
					if (TT[i]->text.getIs_visible() == true) {
						sf::Color b = TT[i]->text.getColor();
						b.a = ((TT[i]->time * 15) / 100) * 255;
						TT[i]->text.setColor(b);
					}
					

				}
				break;
				
			}
			
		
	}
	
}

TempText::~TempText() {
	for (unsigned int i = 0; i < TT.size(); i++) {
		if (this == TT[i]) {
			TT.erase(TT.begin() + i);
			break;
		}
		
	}
	
	
}

void TempText::setString(const std::string &string) {
	//Setting the string.
	text.setString(string);
	//Making sure that its visible.
	text.appear();
	//Setting the time back to default.
	time = default_time;

}

void TempText::setPosition(const float &x_pos, const float &y_pos) {
	//Setting the position of the text.
	text.setPosition(x_pos + 16, y_pos - 32);

}
void TempText::setColor(const sf::Color &color) {
	text.setColor(color);
}
void TempText::setType(int Type) {
	type = Type;
}

void TempText::free() {
	delete this;
}

void TempText::setPosition(const sf::Vector2f &position) {
	text.setPosition(position);
}

void TempText::vanish() {
	text.vanish();
	time = -1;
}