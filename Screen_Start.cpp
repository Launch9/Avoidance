#include "stdafx.h"
#include "Screen_Start.h"
#include <iostream>
#include "Cam.h"
#include "GF.h"
#include <vector>
#include "Ani_MOTHER.h"
#include "Player.h"
#include "Font.h"
#include "App.h"
#include "random2.h"
#define SpaceBH 640
#define GrassBH 250
#define TitleBH 64
#define TitleBW 150
Screen_Start::Screen_Start()
{
	Cx = (Cam::getdisplaywidth() / 2) - 100;
	Cy = Cam::getdisplayheight() / 2;
	Tx = Cam::getdisplaywidth() - (Cam::getdisplaywidth() / 2);
	Ty = Cam::getdisplayheight() / 10;
	if (!tex.loadFromFile("R/Texturemaps/Start_Screen_Tex.png"))
	{
		throw("Screen_Start class, texturemap failed to load.");
	}
	
	
	//{ "Start Game", "Exit" };
	// = { "Slot 1" , "Slot 2", "Slot 3", "Erase File" }
	//First choice text
	sf::Text T_a1;
	T_a1.setString("Start Game");
	T_a1.setFont(Font::Get_isocpeur());
	sf::Text T_a2;
	T_a2.setString("Exit");
	T_a2.setFont(Font::Get_isocpeur());
	//Choosing slot text
	sf::Text T_b1;
	T_b1.setString("Slot 1");
	T_b1.setFont(Font::Get_isocpeur());
	sf::Text T_b2;
	T_b2.setString("Slot 2");
	T_b2.setFont(Font::Get_isocpeur());
	sf::Text T_b3;
	T_b3.setString("Slot 3");
	T_b3.setFont(Font::Get_isocpeur());
	sf::Text T_b4;
	T_b4.setString("Erase File");
	T_b4.setFont(Font::Get_isocpeur());
	sf::Text T_c1;
	T_c1.setString("Too Easy");
	T_c1.setFont(Font::Get_isocpeur());
	sf::Text T_c2;
	T_c2.setString("Normal");
	T_c2.setFont(Font::Get_isocpeur());
	sf::Text T_c3;
	T_c3.setString("Frustratingly Hard");
	T_c3.setFont(Font::Get_isocpeur());
	sf::Text Controls;
	Controls.setPosition(Cam::getdisplaywidth() / 50, Cam::getdisplayheight() / 2);
	Controls.setCharacterSize(24);
	Controls.setString("W to move up.\nS to move down.\nD to select.\nA to go back.\nEsc: for more controls once in game.");
	Controls.setColor(sf::Color::Magenta);
	Controls.setFont(Font::Get_isocpeur());
	CP0 = { T_a1, T_a2 };
	CP1 = { T_b1,T_b2,T_b3,T_b4 };
	CP2 = { T_c1, T_c2,T_c3 };
	controls = Controls;
	C.setText(CP0);
	C.setPosition(Cx, Cy);
	C.setColorCursor(sf::Color::Yellow);
	//Background frames
	sf::Sprite s1;
	s1.setTexture(tex);
	s1.setTextureRect(sf::IntRect(0,0,1024,SpaceBH));
	sf::Sprite s2;
	s2.setTexture(tex);
	s2.setTextureRect(sf::IntRect(0, SpaceBH, 1024, SpaceBH));
	sf::Sprite s3;
	s3.setTexture(tex);
	s3.setTextureRect(sf::IntRect(0, SpaceBH * 2, 1024, SpaceBH));
	
	//Grass frames
	sf::Sprite s4;
	s4.setTexture(tex);
	s4.setTextureRect(sf::IntRect(0, (SpaceBH * 3), 1024, GrassBH));
	sf::Sprite s5;
	s5.setTexture(tex);
	s5.setTextureRect(sf::IntRect(0, (SpaceBH * 3) + (GrassBH * 1), 1024, GrassBH));
	sf::Sprite s6;
	s6.setTexture(tex);
	s6.setTextureRect(sf::IntRect(0, (SpaceBH * 3) + (GrassBH * 2), 1024, GrassBH));
	sf::Sprite s7;
	s7.setTexture(tex);
	s7.setTextureRect(sf::IntRect(0, (SpaceBH * 3) + (GrassBH * 3), 1024, GrassBH));
	//Title sprite
	sf::Sprite s8;
	s8.setTexture(tex);
	s8.setTextureRect(sf::IntRect(0, (SpaceBH * 3) + (GrassBH * 4), TitleBW, TitleBH));
	s8.setPosition(sf::Vector2f(Tx, Ty));
	s8.setScale(sf::Vector2f(3, 3));
	Sprites = { s1,s2,s3,s4,s5,s6,s7,s8 };
	AO = { Ani_MOTHER(0, 0, { s1, s2, s3 }, 0.2), Ani_MOTHER(0, Cam::getdisplayheight() - GrassBH,{ s4,s5,s6,s7,s6,s5 }, 0.2), Ani_MOTHER(0, Cam::getdisplayheight() - 150, {s4,s5,s6,s7,s6,s5}, 0.3) };
	typeID = 0;
}

void Screen_Start::updateleaves(sf::RenderWindow &win) {
	for (unsigned int i = 0; i < LC.size(); i++) {
		//Making it fall.
		LC[i][1] += LC[i][2];
		LS[i].setPosition(LC[i][0], LC[i][1]);
		
		win.draw(LS[i]);
		if (LC[i][1] > Cam::getdisplayheight()) {
			LC.erase(LC.begin() + i);
			LS.erase(LS.begin() + i);
		}
	}
}
void Screen_Start::makeleaf() {
	sf::Sprite s;
	switch (random2::randomrange(0, 3)) {
	case 0:
		s.setColor(sf::Color::Green);
		break;
	case 1:
		s.setColor(sf::Color::Magenta);
		break;
	case 2:
		s.setColor(sf::Color::Yellow);
		break;
	}
	
	LC.push_back({ random2::randomrange(0, Cam::getdisplaywidth()), 0, random2::randomrange(1,4) });
	LS.push_back(s);
}

bool Screen_Start::main(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event) {
	
	
		
		
	
		
		if (is_first_time == true) {
			Player::deleteALL();
			TM.clear_all();
			is_first_time = false;
		}
		
		
			
			win.clear(sf::Color::Blue);
			
			for (unsigned int i = 0; i < AO.size(); i++) {
				AO[i].animate(win, true);
			}
			
			
			Cam::drawGUI_chan(0, win, Sprites[7]);
			Cam::drawGUI_chan(0, win, C);
			Cam::drawGUI_chan(0, win, controls);
			win.display();
			
		
		
		if (Ctype == 0) {
			
			switch (C.check()) {
				
				case -5: //Case that you selected something.
					
					switch (C.getIndex()) {
						//In the case that you want to start the game.
					case 1:
						
						
						Ctype = 1;
						C.setText(CP1);
						

						break;
						//In the case that you want to exit the window.
					case 0:
						App::goto_mainmenu();
						win.close();
						Exit = true;
						App::P_RESET();
						C.setText(CP0);
						Ctype = 0;
						return true;
					}
			}
			
		}
		else if (Ctype == 1) {
			int b = AskForSlot(win, TM);
			//This happens if you have selected a slot.
			if (b == 0) {
				reset();
				Exit = true;
				return true;
			}
			//This happens if you exited out and went back to the CP0.
			else if(b == 1){

				
				Ctype = 0;
				C.setText(CP0);

			}
			else if (b == 3) {
				Ctype = 2;
				C.setText(CP2);
			}
		}
		else if (Ctype == 2) { //This is for asking what difficulty you want your slot at.
			int x = AskForDifficulty(win, TM);
			switch (x) {
			case 0:
				break;
			case 1:
				reset();
				Exit = true;
				return true;
			}

		}
		
		
	

		
		
	
		
		return false;
	}
	
	
	


int Screen_Start::AskForSlot(sf::RenderWindow &win, TileMap &TM) {
	
	switch (C.check()) {
	case -5:
		switch (C.getIndex()) {

		case 3:
			if (isErase == true) {
				World::SetPlayerFiletoDefault(0);
				C.setColor(sf::Color::White);
				isErase = false;
				return 2;
			}
			else {
				selected_slot = 0;
				if (Player::get_difficulty_from_file("R/Player Files/Save 1.txt") == -1) {
					return 3;
				}
				else {
					create_Player(TM);
					World::setSlotnum(0);
					return 0;
				}
				
			}



		case 2:
			if (isErase == true) {
				World::SetPlayerFiletoDefault(1);
				C.setColor(sf::Color::White);
				isErase = false;
				return 2;
			}
			else {
				selected_slot = 1;
				if (Player::get_difficulty_from_file("R/Player Files/Save 2.txt") == -1) {
					return 3;
				}
				else {
					create_Player(TM);
					World::setSlotnum(1);
				}
				return 0;
			}
		case 1:
			
			if (isErase == true) {
				World::SetPlayerFiletoDefault(2);
				C.setColor(sf::Color::White);
				isErase = false;
				return 2;
			}
			else {
				selected_slot = 2;
				if (Player::get_difficulty_from_file("R/Player Files/Save 3.txt") == -1) {
					return 3;
				}
				else {
					create_Player(TM);
					World::setSlotnum(2);
				}
				return 0;
			}
		case 0:
			if (isErase == true) {
				isErase = false;
				C.setColor(sf::Color::White);
			}
			else {
				isErase = true;
				C.setColor(sf::Color::Red);
			}

			break;
		}
		break;
		//return 2;
	case -6:
		
		C.setText(CP0);
		isErase = false;
		C.setColor(sf::Color::White);
		return 1;
	}
	
	
	
	
	return 2;
	
	
}

void Screen_Start::reset() {
	Ctype = 0;
	C.setText(CP0);
	is_first_time = true;
	isErase = false;
}

int Screen_Start::AskForDifficulty(sf::RenderWindow &win, TileMap &TM) {
	switch (C.check()) {
	case -5:
		switch (C.getIndex()) {
		case 2: //Easy
			create_Player(TM, 0);
			return 1;
			break;
		case 1: //Normal
			create_Player(TM, 1);
			return 1;
			break;
		case 0: //Hard
			create_Player(TM, 2);
			return 1;
			break;
		}
	}
	return 0;
}

void Screen_Start::create_Player(TileMap &TM, int new_difficulty) {
	
	World::setSlotnum(selected_slot);
	
	switch (selected_slot) {
	case 0:
		new Player("R/Player Files/Save 1.txt", TM, new_difficulty);
		break;
	case 1:
		new Player("R/Player Files/Save 2.txt", TM, new_difficulty);
		break;
	case 2:
		new Player("R/Player Files/Save 3.txt", TM, new_difficulty);
	}
	TM.setTexture(0);
	//TM.setTexture(0);
}