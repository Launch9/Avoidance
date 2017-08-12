#include "stdafx.h"
#include "Cam.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Player.h"
#include <iostream>
//#include <Windows.h>
int Cam::num_of_pics;
#define base32 32
#define Render_X 64
#define Render_Y 64
#define stand_w 32 * base32
#define stand_h 20 *base32
#define screen_scale 1
float Cam::displayheight;
float Cam::displaywidth;
float Cam::displaywidth_fac;
float Cam::displayheight_fac;
bool Cam::ready_to_take_screenshot;
std::vector <Cam> Cam::CamObjects;

void Cam::init() {
	
	displaywidth = stand_w * screen_scale;
	displayheight = stand_h * screen_scale;
	displaywidth_fac = displaywidth / stand_w;
	displayheight_fac = displayheight / stand_h;
	ready_to_take_screenshot = false;
	
	num_of_pics = 0;
}
Cam::Cam()
{
	view.reset(sf::FloatRect(300, 0, displaywidth, displayheight));
	view.setViewport(sf::FloatRect(0, 0, 1, 1));
	setxy(-displaywidth / 2, -displayheight / 2, true);
	//setxy(0, 0, true);
	//view.zoom(screen_scale - 1);
	CamObjects.push_back(*this);
	
}

float Cam::getx() {
	return x;
}
float Cam::gety() {
	return y;
}

bool Cam::RenderBasic(int x, int y, int CamChannel, unsigned int Size) {
	//Checking to see if the point is actually on the screen.
	if ((x >= CamObjects[CamChannel].getax() - Render_X && x <= CamObjects[CamChannel].getax() + displaywidth + Render_X) && (y > CamObjects[CamChannel].getay() - Render_Y && y < CamObjects[CamChannel].getay() + displayheight + Render_Y)){
		return true;
	}
	else {
		return false;
	}
}

int Cam::getdisplayheight() {
	return displayheight;
}
int Cam::getdisplaywidth() {
	return displaywidth;
}
void Cam::zoom(float offset) {
	view.zoom(offset);
}

void Cam::scroll(float offset1, float offset2) {
	x = x + offset1;
	y = y + offset2;
	view.move(offset1, offset2);
}


float Cam::getx_chan(int channel) {
	return CamObjects[channel].getx();
}

float Cam::gety_chan(int channel) {
	return CamObjects[channel].gety();
}

void Cam::scroll_chan(int channel, float offset1, float offset2) {
	CamObjects[channel].scroll(offset1, offset2);
}

void Cam::setviewport(float f1, float f2, float f3, float f4) {
	view.setViewport(sf::FloatRect(f1, f2, f3, f4));
}

void Cam::setviewport_chan(int channel, float f1, float f2, float f3, float f4) {
	CamObjects[channel].setviewport(f1, f2, f3, f4);
}

void Cam::drawGUI_chan(const int &channel, sf::RenderWindow &win, const sf::Drawable &drawable) {
	CamObjects[channel].drawGUI(win, drawable);
}
void Cam::setview(sf::RenderWindow &win) {
	win.setView(view);
}

void Cam::setview_chan(int channel, sf::RenderWindow &win) {
	CamObjects[channel].setview(win);
}

void Cam::setxy(float x_pos, float y_pos, bool center) {
	view.setCenter(x_pos, y_pos);
	x = x_pos - (displaywidth / 2);
	y = y_pos - (displayheight / 2);
	
	
}

void Cam::setxy_chan(int channel, float x, float y, bool center) {
	CamObjects[channel].setxy(x, y, center);
}

void Cam::zoom_chan(int channel, float offset) {
	CamObjects[channel].zoom(offset);
}

float &Cam::getax() {
	return x;
}
float &Cam::getay() {
	return y;
}

void Cam::takeScreenShot(sf::RenderWindow &win) {

	sf::Image i;
	
	i = win.capture();
	
	
	if (i.saveToFile("R/Screenshots/image" + GF::str(num_of_pics) + ".png") == true) {
		std::cout << "Took screenshot successfuly." << std::endl;
		num_of_pics++;
	}
	else {
		std::cout << "Failed to take screenshot" << std::endl;
	}
	ready_to_take_screenshot = false;
}

void Cam::readyScreenShot() {
	ready_to_take_screenshot = true;
}



void Cam::drawGUI(sf::RenderWindow &win, const sf::Drawable &drawable) {
	win.setView(win.getDefaultView());
	
	win.draw(drawable);
	win.setView(view);
}

bool Cam::get_is_ready() {
	return ready_to_take_screenshot;
}