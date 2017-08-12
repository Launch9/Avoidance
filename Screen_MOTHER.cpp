#include "stdafx.h"
#include "Screen_MOTHER.h"
#include "Cam.h"
#include "Screen_Start.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Font.h"
#include "Screen_Credits.h"
#include "Screen_Pause.h"
#include "Gameover_Screen.h"
std::vector<Screen_MOTHER*> Screen_MOTHER::Screens;
int Screen_MOTHER::screen_index;
bool Screen_MOTHER::is_ready;
#define Dflt_Txt_Size 10

void Screen_MOTHER::init() {

	//Making all of the screen objects.
	Screens = { new Screen_Start(), new Screen_Credits(), new Screen_Pause(), new Gameover_Screen() };

}



bool Screen_MOTHER::main(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event) {
	std::cout << "You forgot to put the main() function in your Screen_MOTHER class!" << std::endl;
	throw("You forgot to put the main() function in your Screen_MOTHER class!");
}

void Screen_MOTHER::start(int Screen_index) {
	screen_index = Screen_index;
	is_ready = true;
}

bool Screen_MOTHER::check(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event) {
	if (is_ready == true) {
		if (Screens[screen_index]->main(win, TM, s_event) == true) {
			is_ready = false;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return true;
	}
	
	std::cout << "ERROR: Screen_MOTHER::check() has encountered an error." << std::endl;
	throw(1);
}

bool Screen_MOTHER::get_is_ready() {
	return is_ready;
}