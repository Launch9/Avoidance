#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Tilemap.h"
class App
{
private:
	static bool App::is_pending_mainmenu;
public:
	//This tells if you are holding down a button that allows the debug menu to be opened.
	static bool App::Debug_Unlock_Key;
	//This tells if you are holding down space or not.
	static bool App::HQ;
	//These are the Held_Controls.
	//These will tell you what buttons are being held down.
	//Control Map-=-=-=-=-=-=-=-
	//0 = W, 1 = D, 2 = S, 3 = A
	static std::vector<bool> App::H_Controls;
	//These are the Pressed_Controls.
	//These will tell you what buttons just got pressed this frame.
	//Control Map-=-=-=-=-=-=-=-
	//0 = W, 1 = D, 2 = S, 3 = A
	static std::vector<bool> App::P_Controls;
	//These are the controls use by the player to slide and walk in the chosen directions.
	static std::vector<int> App::control_cache;
	//This will pause the application and allow you to pick from some options.
	static void Pause(sf::RenderWindow &win, TileMap &TM);
	//This will initiate everything.
	static void init();
	//This will set the P_Controls back to default.
	static void P_RESET();
	//This will go back to the main menu.
	static void goto_mainmenu();
	//This checks to see if there is a pending request to go to the main menu.
	static void check_pendings(sf::RenderWindow &win, TileMap &TM);
	//This returns true if the application is waiting to go the main menu.
	static bool is_pending();
};

