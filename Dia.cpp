#include "stdafx.h"
#include "Dia.h"
#include <vector>
#include "Cam.h"
#include <iostream>
#include "GF.h"
#include "Player.h"
#include "Cam.h"
#include "Sound.h"
#include "random2.h"
#define Txtsize 30
std::vector <Dia> Dia::DiaObjects;
int Dia::screendivisionY;
int Dia::screendivisionX;
int Dia::txt_spr_div;
bool Dia::apress;
bool Dia::bpress = false;
sf::Font Dia::f;
std::vector<sf::Sprite> Dia::DiaSprites;

Dia::Dia(sf::Sprite &sprite, const std::string &string, bool bpress_Compatibility)
{
	spr = sprite;
	bpress_compatibility = bpress_Compatibility;
	bpress = false;
	apress = false;
	//Setting the string and font to the text object.
	txt.setFont(f);txt.setString(string);txt.setCharacterSize(Txtsize);
	//Setting the position of the sprite that is going to be drawn.
	//This is the sprite of the dialouge image(The character who is speaking).
	spr.setPosition(screendivisionX, screendivisionY);
	txt.setPosition(txt_spr_div, screendivisionY);
	DiaObjects.push_back(*this);
}

Dia::Dia(sf::Sprite &sprite, const std::vector<std::string> &string, bool bpress_Compatibility)
{
	for (unsigned int i = 0; i < string.size(); i++) {
		spr = sprite;
		bpress_compatibility = bpress_Compatibility;
		//Setting the string and font to the text object.
		txt.setFont(f);txt.setString(string[i]);txt.setCharacterSize(Txtsize);
		//Setting the position of the sprite that is going to be drawn.
		//This is the sprite of the dialouge image(The character who is speaking).
		spr.setPosition(screendivisionX, screendivisionY);
		txt.setPosition(txt_spr_div, screendivisionY);
		DiaObjects.push_back(*this);
	}
	
}

void Dia::init(sf::Texture &t, sf::Font font) {
	//This is setting how far the text and sprites need to be from the bottom of the screen.
	//WidthDivisor
	unsigned int WD = 20;
	//HeightDivisor
	unsigned int HD = 5;
	f = font;
	screendivisionX = Cam::getdisplaywidth() / WD;
	screendivisionY = Cam::getdisplayheight() - (Cam::getdisplayheight() / 5);
	txt_spr_div = screendivisionX + (Cam::getdisplaywidth() / (WD / 2));
	sf::Sprite Europa_neutral;
	Europa_neutral.setTexture(t);
	Europa_neutral.setTextureRect(sf::IntRect(480,480,96,96));
	sf::Sprite Europa_sad;
	Europa_sad.setTexture(t);
	Europa_sad.setTextureRect(sf::IntRect(480, 480 - 96, 96, 96));
	sf::Sprite Europa_happy;
	Europa_happy.setTexture(t);
	Europa_happy.setTextureRect(sf::IntRect(480, 480 - (96 * 2), 96, 96));
	sf::Sprite sign_confused;
	sign_confused.setTexture(t);
	sign_confused.setTextureRect(sf::IntRect(384, 288, 96, 96));
	sf::Sprite sign_angry;
	sign_angry.setTexture(t);
	sign_angry.setTextureRect(sf::IntRect(384, 288 + 96, 96, 96));
	sf::Sprite sign_neutral;
	sign_neutral.setTexture(t);
	sign_neutral.setTextureRect(sf::IntRect(384, 288 + (96 * 2), 96, 96));
	DiaSprites = { Europa_neutral, sign_confused, sign_angry, sign_neutral, Europa_sad, Europa_happy };
}

void Dia::iterate() {
	bpress = true;
}
sf::Sprite Dia::getsprite() {
	return spr;
}

void Dia::setspritexy(int x, int y) {
	spr.setPosition(x, y);
}

void Dia::settextxy(int x, int y) {
	txt.setPosition(x, y);
}
sf::Text Dia::gettext() {
	return txt;
}

bool Dia::get_bpress_compatibility() {
	return bpress_compatibility;
}

void Dia::tick() {
	if (DiaObjects.size() > 0) {
		
		
		

		//Deleting the object if you made bpress = true.
		if (bpress == true && DiaObjects[0].get_bpress_compatibility() == true) {
			Sound::Play(68, 0, 0, random2::randomrange(1, 5));
			DiaObjects.erase(DiaObjects.begin());
			bpress = false;
		}
		else {
			//This happens if you have an advanced(apress) object.
			if (apress == true && DiaObjects[0].get_bpress_compatibility() == false) {
				DiaObjects.erase(DiaObjects.begin());
				apress = false;
			}
		}
		
	}
	
}

void Dia::draw(sf::RenderWindow &win) {
	if (DiaObjects.size() > 0) {
		Cam::drawGUI_chan(0, win, DiaObjects[0].getsprite());
		Cam::drawGUI_chan(0, win, DiaObjects[0].gettext());
		
	}
}
int Dia::getcachelength() {
	return DiaObjects.size();
}

void Dia::iterate_apress() {
	apress = true;
}
sf::Sprite Dia::getDia_sprite(int ID) {
	return DiaSprites[ID];
	
}
std::string Dia::getDia_string(int ID) {
	switch (ID) {
		//Europa Speaking::Shop greeting 0
	case 0:
		return("Europa: Welcome to my shop!");
		
		//Europa Speaking::Shop greeting 1
	case 1:
		return("Europa: The forest is rather massive. There are many dungeons lying around.");
		
	case 2:
		//Sign speaking because you are ignoring someone.
		return("Mr. Sign: Good heavens! How rude you are! You musn't ignore people.");
	case 3:
		//Sign speaking because you are ignoring someone.
		return("Mr. Sign: I am not giving you any information until you listen.");
	case 4:
		//Introduction to himself
		return("Mr. Sign: Hello, I am Mr. Sign\nI am here to educate you on many things.");
	case 5:
		//Introduction to himself
		return("Mr. Sign: Let us begin our education, shall we?");
	case 6:
		//Learning sliding and lasers.
		return("Mr. Sign: Those over there, are lasers.\nYou can slide under lasers by holding the SPACE bar.\nWhile holding the space bar,\nuse W,A,S,D to move in the direction you wish.");
	case 7:
		//Learning sliding and lasers.
		return("Mr. Sign: Don't ask me what a SPACE bar is. \nI would have to guess that it is a bar in space though.");
	case 8:
		//More of the game under construction.
		return("Mr. Sign: Don't come this way, the creator is still working here.");
	case 9:
		return("Mr. Sign: This tower has been used to \nobserve this world above the clouds. \nIt is not in use anymore though, since everyone has left the planet.\nAh, It really is a lovely sight up there.");
	case 10:
		return("Mr. Sign: Remember, it must be below freezing up there. \nMake sure you drink plenty of warm tea before you go.");
	case 11:
		return("Mr. Sign: Europa wrote something on me while I was asleep. \nHere, I will read it to you.");
	case 12:
		return("Europa: There is something I never told you...");
	case 13:
		return("Europa: I had to steal many parts from other \npeople who also needed to escape. \nMany people are going to die because of me...");
	case 14:
		return("Europa: I do not need to take the ship anymore. \nI have decided that I deserve to rest on this planet forever.");
	case 15:
		return("Europa: Anode is in the ship waiting for you. \nTake good care of him please.");
	case 16:
		return("Europa: Thanks for getting the parts, \nnobody else would help someone of the likes of me.");
	case 17:
		return("Europa: Good bye, friend?");
	case 18:
		return("Mr. Sign: Well, that was depressing. \nYou better get on that ship before you die from these ashes.");
	case 19:
		return("Mr. Sign: I will be okay, \nI am only a spirit possessing a wooden sign.");
	case 20:
		return("Mr. Sign: There is no time to go looking for her. \nYou need to leave now!");
	case 21:
		return("Mr. Sign: You can hold space to slide around.\nironically, it will make you go faster. ");
	case 22:
		return("Mr. Sign: As long as you are holding the space bar.\nEvery W,A,S, or D move you make, you will slide instead of walking.");
	case 23:
		return("Mr. Sign: This dungeon gives me the splinters.\nDon't go breathing in the toxic gas.\nI heard that stuff is bad for your health.");

	}
}

void Dia::clear() {
	DiaObjects.clear();
}