#include "stdafx.h"
#include "GF.h"
#include <random>
#include "Time.h"
#include <iostream>
#include "Wall.h"
#include "Bg.h"
#include "Shop.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <sstream>
#include "Basic_Tile_MOTHER.h"
#include <string>
#include "NPC_MOTHER.h"
#include <future>
#include "Editor.h"
#include <cmath>
using namespace GF;

extern sf::Clock GF::c = sf::Clock();
extern float GF::delta = 0;
extern float GF::ttr = 0;
extern float GF::tlr = 0;
extern bool GF::isPaused = 0;
extern sf::Time GF::tss = sf::milliseconds(1);
extern int GF::standardFramerate = 60;
extern sf::Sprite GF::OverlapSprite = sf::Sprite();
extern vector<std::vector<int>> GF::Overlapcords = {};
extern std::vector<sf::Font> GF::Fonts = {};
#define Pi 3.14159265359
#define tss_limit 3600 //time until it resets the time object.
void GF::init(sf::Texture &tex, int framerate) {
	standardFramerate = framerate;
	tss = sf::seconds(0);
	OverlapSprite.setTexture(tex);
	OverlapSprite.setTextureRect(sf::IntRect(0, 32, 32, 32));

}
/*int GF::randomrange(int lownum, int highnum) {
	
	srand(rtick);// * rtick+time(NULL));
	rtick += c.getElapsedTime().asMilliseconds() + 534;
	if (rtick >= 500000) {
		rtick = 0;
	}
	
	int rint = (fastrand() % highnum) + lownum;
	return rint;
}

int GF::randomrange_neg(int lownum, int highnum) {
	srand(rtick);// * rtick+time(NULL));
	rtick += c.getElapsedTime().asMilliseconds() + 534;
	if (rtick >= 500000) {
		rtick = 0;
	}
	int rint = (fastrand() % highnum) + lownum;
	bool rint2 = (fastrand() % 1) + 0;
	if (rint2 == 1) {
		//Flipping sign because of the change of negative boolean being true.
		rint = -rint;
	}
	return rint;
}*/

void GF::tick() {
	
	//rtick += rand() % (rtick + 1) + 1;
	if (Editor::GetStatus() == true) {
		for (unsigned int i = 0; i < Overlapcords.size(); i++) {
			OverlapSprite.setPosition(Overlapcords[i][0], Overlapcords[i][1]);
		}
	}
	
	
}

void GF::setSeed(float new_seed) {
	//rtick = new_seed;
}
void GF::draw(sf::RenderWindow &win) {
	if (Editor::GetStatus() == true) {
		for (unsigned int i = 0; i < Overlapcords.size(); i++) {
			win.draw(OverlapSprite);
		}
	}
}
std::string GF::str(float conversionint) {
	stringstream ss;
	ss << conversionint;
	return(ss.str());
}

int GF::StringtoInt(std::string string) {
	return std::stoi(string);
}

float GF::StringtoFloat(std::string string) {
	return std::stof(string);
}

unsigned int GF::StringtoUnint(std::string string) {
	return std::stoul(string);
}

bool GF::CheckTile_OverLap(int x, int y) {
	std::future<bool> bSUS = std::async(Basic_Tile_MOTHER::Check_Overlap, x, y);
	bool b2 = NPC_MOTHER::Check_Overlap(x, y);
	bool b = bSUS.get();
	if (b == true || b2 == true) {
		//Putting the cordinates into the vector to tell the class that it needs to draw a sprite there.
		Overlapcords.push_back( { x , y } );
	}
	else {
		return false;
	}

}

void GF::DeleteTile_OverLap(int x, int y) {
	for (unsigned int i = 0; i < Overlapcords.size(); i++) {
		if (x == Overlapcords[i][0] && y == Overlapcords[i][1]) {
			Overlapcords.erase(Overlapcords.begin() + i);
		}
		
	}
}


int GF::MinValue(std::vector<int> Vector) {
 	auto max = std::min_element(std::begin(Vector), std::end(Vector));
	
	
	return std::distance(Vector.begin(), max);
}

int GF::MaxValue(std::vector<int> Vector) {
	auto max = std::max_element(std::begin(Vector), std::end(Vector));
	if (*max > 255) {
		*max = 255;
	}
	int &m = *max;
	return m;
}



int GF::Distance(int x1, int x2, int y1, int y2) {
	int d = sqrt((pow((x1 - x2), 2) + pow((y1 - y2), 2)));
	d /= base32;
	return d;
}



int GF::getFramerate() {
	return standardFramerate;
}

float GF::radians(float degree) {
	return (degree*Pi) / 180;
}

void GF::setPause(const bool &TF) {
	isPaused = TF;
}

bool GF::getPause() {
	return isPaused;
}
void GF::setDelta(float Delta) {
	delta = Delta;
}
void GF::setTTR(float Timethisround) {
	ttr = Timethisround;
}

void GF::setTLR(float Timelastround) {
	tlr = Timelastround;
}

void GF::setTSS(sf::Time TimeSinceStart) {
	if (tss.asSeconds() >= tss_limit) { //If reached limit
		tss = sf::seconds(0);
	}
	else {
		tss = TimeSinceStart;
	}
	
}

float GF::getDelta() {
	return delta;
}

float GF::getTTR() {
	return ttr;
}

float GF::getTLR() {
	return tlr;
}

sf::Time GF::getTSS() {
	return c.getElapsedTime();
}
int round32(float num) {
	int t = int(num) % 32;
	int r = num + t;
	return r;
}

bool GF::is_all_false(const std::vector<bool> &Vector) {
	for (unsigned int i = 0; i < Vector.size(); i++) {
		if (Vector[i] == true) {
			return false;
		}
	}
	return true;
}
bool GF::is_all_true(const std::vector<bool> &Vector) {
	for (unsigned int i = 0; i < Vector.size(); i++) {
		if (Vector[i] == false) {
			return false;
		}
	}
	return true;
}

bool GF::does_exist(int index, int size_of_vector) {
	if (index >= 0 && index <= size_of_vector - 1) {
		return true;
	}
	else {
		return false;
	}
}

float GF::average(float num1, float num2) {
	return (num1 + num2) / 2;
}

float GF::getDistance_Pixels(const sf::Vector2f &position1, const sf::Vector2f &position2) {
	float d = sqrt((pow((position1.x - position2.x), 2) + pow((position1.y - position2.y), 2)));
	return d;
}
