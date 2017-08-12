#pragma once
#include "Screen_MOTHER.h"
#include "Music.h"
#include "Choice.h"
class Screen_Start: public Screen_MOTHER
{
private:
	sf::Time timer;
	//This determines whether or not the next slot you choose will erase it.
	bool isErase = false;
	//This is an integer that decides what choice is in focus.
	int Ctype = 0;
	//This tells what slot you have selected.
	int selected_slot = -1;
	//This tells if this is the first loop when entering the mainmenu.
	bool is_first_time = true;
	//This makes the player object.
	void create_Player(TileMap &TM, int new_difficulty = -1);
	//This resets a couple of things for the next time you come to the menu.
	void reset();
	//This decides first timesies.
	bool FT = false;
	//Choice's x cordinate.
	int Cx;
	//Choice's y cordinate.
	int Cy;
	//Title's x cordinate.
	int Tx;
	//Title's y cordinate.
	int Ty;
	//This is the choice object to be used.
	Choice C;
	//Leaf Spawn tick.
	int tick = 0;
	//Leaf Spawn tick max.
	int tickmax = 30;
	//This is the text that is displayed to show you the controls.
	sf::Text controls;
	//This is a vector full of the leaf cordinates.
	//0 = x cordinate, 1 = y cordinate, 2 = fall speed
	std::vector<std::vector<int>> LC;
	//This is a vector full of the leaf sprites.
	std::vector<sf::Sprite> LS;
	//This is a vector full of the text that is displayed during the 0th phase of choice.
	std::vector<sf::Text> CP0;// = { "Start Game", "Exit" }; //Start or exit?
	//This is a vector full of the text that is display during the 1st phase of choice.
	std::vector<sf::Text> CP1;// = { "Slot 1" , "Slot 2", "Slot 3", "Erase File" }; //File selection
	//This is a vector full of the text that is displayed during the 2nd phase of choice.
	std::vector<sf::Text> CP2;// = { "Too Easy", "Normal", "Frustratingly Hard" };

public:
	//This will ask for a player slot to activate.
	//You need to give it the information that tells it if you want it to see up variables and such.
	//if "return" == 0, then that means it created a player object. AND SHOULD START THE GAME.
	//if "return" == 1, then that means it did not create a player object and that player just exited out.
	//if "return" == 2, then you didn't do anything.
	//if "return" == 3, then it should be asking for the difficulty you want your slot at.
	int AskForSlot(sf::RenderWindow &win, TileMap &TM);
	//This asks for the difficulty of your game.
	//if "return" == 0, then that means that you have done nothing.
	//if "return" == 1, then the player has selected one of the difficulties.
	int AskForDifficulty(sf::RenderWindow &win, TileMap &TM);
	void makeleaf();
	void updateleaves(sf::RenderWindow &win);
	//This will be initiation of the class.
	Screen_Start::Screen_Start();
	//This is the main function that will be run all the time.
	bool main(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event);
};

