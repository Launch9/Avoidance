#include "stdafx.h"
#include "App.h"
#include "Screen_MOTHER.h"
#include "Player.h"
std::vector<bool> App::H_Controls;
std::vector<bool> App::P_Controls;
std::vector<int> App::control_cache;
bool App::HQ;
bool App::Debug_Unlock_Key;
bool App::is_pending_mainmenu;
void App::Pause(sf::RenderWindow &win, TileMap &TM) {
	
	Screen_MOTHER::start(2);
}

void App::init() {
	H_Controls = { false,false,false,false };
	P_Controls = { false,false,false,false };
}

void App::P_RESET() {
	P_Controls = { false,false,false,false };
}

void App::goto_mainmenu() {
	
	is_pending_mainmenu = true;	
}

void App::check_pendings(sf::RenderWindow &win, TileMap &TM) {
	if (is_pending_mainmenu == true) {
		//World::ClearWorld();
		//Player::deleteALL();
		Screen_MOTHER::start(0);
		is_pending_mainmenu = false;
	}
	
}

bool App::is_pending() {
	return is_pending_mainmenu;
}