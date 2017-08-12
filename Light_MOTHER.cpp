#include "stdafx.h"
#include "Light_MOTHER.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cmath>
#include <thread>
#include "GF.h"
#include "Wall.h"
#include "Bg.h"
#include "Shop.h"
#include "Basic_Tile_MOTHER.h"
#include "Cam.h"
unsigned int Light_MOTHER::t;
using namespace std;
#define base32 32
#define CamChan 0
//This defines the macro for the amount of power that the light wave reachs until it is deleted.
#define maxLWPOW 100
//This defines the max number of ticks that need to be reached to loop through all the objects and do the calculations.
//The higher the number, the faster runtime.
#define maxTick 10


std::vector<Light_MOTHER*> Light_MOTHER::LObjects;

void Light_MOTHER::tick() {
	throw("Did not make tick function in class!");
}

unsigned int Light_MOTHER::getbaselightpower() {
	return baselightpow;
}

void Light_MOTHER::setlightpower(int power) {
	lightpow = power;
}

int Light_MOTHER::getx() {
	return x;
}
int Light_MOTHER::gety() {
	return y;
}
sf::Sprite Light_MOTHER::getsprite() {
	return s;
}
int Light_MOTHER::getlightpower() {
	return lightpow;
}
sf::Color Light_MOTHER::getcolor() {
	return LColor;
}
int Light_MOTHER::get_tile_lighting(int tilex, int tiley) {
	std::vector<int> dv;
	
	for (unsigned int i = 0; i < LObjects.size(); i++) {
		//Using the distance formula to get the answer.
		int d = sqrt((pow((LObjects[i]->getx() - tilex), 2) + pow((LObjects[i]->gety() - tiley), 2))); d /= base32;
		
		if (d < LObjects[i]->getlightpower()) {
			dv.push_back((LObjects[i]->getlightpower()-d)*LObjects[i]->getbaselightpower()/2);
		}
		
	}
	
	if (dv.size() == 0) {
		return NULL;
	}
	else {
		auto max = std::max_element(std::begin(dv), std::end(dv));
		if (*max > 255) {
			*max = 255;
		}
		return *max;
		
	}
	


}
void Light_MOTHER::SetColorAndLighting(sf::Color &tilecolor, int tilex, int tiley) {
	//addColor(tilecolor.g, 5);
	int max_bright = 0;
	//Vector full of distance integers.
	std::vector<int> dv;
	std::vector<Light_MOTHER *> Objects;
	int r_add = 0;
	int g_add = 0;
	int b_add = 0;
	sf::Color color;
	color.r = 0;
	color.b = 0;
	color.g = 0;
	color.a = 255;
	
	for (unsigned int i = 0; i < LObjects.size(); i++) {
		//Using the distance formula to get the answer.
		int d = GF::Distance(LObjects[i]->getx(), tilex, LObjects[i]->gety(), tiley);
		if (d <= LObjects[i]->getlightpower()) {
			
			int p = LObjects[i]->getlightpower() / round(d + 1);
			if (d == 0) {
				p = LObjects[i]->getlightpower();
			}
			//int p = (LObjects[i]->getlightpower() - d) * LObjects[i]->getbaselightpower() / 2;
			dv.push_back((LObjects[i]->getlightpower() - d) * LObjects[i]->getbaselightpower() / 2);
			Objects.push_back(LObjects[i]);
			max_bright += p;
			if (LObjects[i]->r == true) {
				if (r_add + p <= 255) {
					r_add += p;
				}
				else {
					r_add = 255;
				}
			}
			if (LObjects[i]->g == true) {
				if (g_add + p <= 255) {
					g_add += p;
				}
				else {
					g_add = 255;
				}
			}
			if (LObjects[i]->b == true) {
				if (b_add + p <= 255) {
					b_add += p;
				}
				else {
					b_add = 255;
				}
			}
				
				
			
			
		}
	}

	if (max_bright > 255) {
		max_bright = 255;
	}
	else if (max_bright < 0) {
		max_bright = 0;
	}
	color.g = g_add;
	color.b = b_add;
	color.r = r_add;
		
		
		tilecolor = color;

	
}

bool Light_MOTHER::addColor(sf::Uint8 &color_element, int amount_to_add) {
	if (color_element + amount_to_add <= 255) {
		color_element += amount_to_add;
		return true;
	}
	else {
		color_element = 255;
		return false;
	}
}
bool Light_MOTHER::subtractColor(sf::Uint8 &color_element, int amount_to_subtract) {
	if (color_element - amount_to_subtract >= 0) {
		color_element -= amount_to_subtract;
		return true;
	}
	else {
		color_element = 0;
		return false;
	}
}

bool Light_MOTHER::add_subtract_Color(sf::Uint8 &color_element, int amount) {
	if (amount > 0) {
		if (color_element + amount >= 255) {
			color_element += amount;
			return true;
		}
		else {
			color_element = 255;
			return false;
		}
	}
	else if (amount > 0) {
		if (color_element - amount <= 0) {
			color_element -= amount;
			return true;
		}
		else {
			color_element = 0;
			return false;
		}
	}
	else {
		return false;
	}
	
}
void Light_MOTHER::maintick() {

	//Raising the tick by one.
	t++;
	if (t >= maxTick) {
		
		for (unsigned int i = 0; i < LObjects.size(); i++) {
				LObjects[i]->tick();
			
		}
		
		ResetLighting();
		//Reseting the ticks back to zero.
		t = 0;
	}
	

}


bool Light_MOTHER::deletetile(int x, int y) {
	for (unsigned int i = 0; i < LObjects.size(); i++) {
		if (LObjects[i]->getx() == x && LObjects[i]->gety() == y) {
			delete LObjects[i];
			LObjects.erase(LObjects.begin() + i);
			return true;
		}
	}
	return false;
}

void Light_MOTHER::ResetLighting() {
	Basic_Tile_MOTHER::ResetAllLighting();
}


int Light_MOTHER::gettypeID() {
	return typeID;
}
void Light_MOTHER::deleteAll() {
	for (unsigned int i = 0; i < LObjects.size(); i++) {
		delete LObjects[i];
	}
	LObjects.clear();
	ResetLighting();
}
std::vector<int> &Light_MOTHER::getSavedParametersA() {
	return SavedParameters;
}
std::string Light_MOTHER::GetSave() {
	std::string r = "&2&";
	for (unsigned int i = 0; i < LObjects.size(); i++) {
		r.append(":");
		//typeID
		r.append(std::to_string(LObjects[i]->gettypeID()) + ",");
		//X cordinate
		r.append(std::to_string(LObjects[i]->getx()) + ",");
		//Y cordinate
		r.append(std::to_string(LObjects[i]->gety()) + ",");
		for (unsigned int b = 0; b < LObjects[i]->getSavedParametersA().size(); b++) {
			r.append(std::to_string(LObjects[i]->getSavedParametersA()[b]) + ",");
		}
		r.append(":");
	}

	return r;
}

void Light_MOTHER::init() {
	t = 0;
}

