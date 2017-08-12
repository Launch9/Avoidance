#include "stdafx.h"
#include "Gameover_Screen.h"
#include "App.h"
#include "Font.h"
#include "World.h"
#include "Player.h"
#include "ParticleSystem.h"
Gameover_Screen::Gameover_Screen()
{
	/*Cx = (Cam::getdisplaywidth() / 2) - 100;
	Cy = Cam::getdisplayheight() / 2;
	Tx = Cam::getdisplaywidth() - (Cam::getdisplaywidth() / 2);
	Ty = Cam::getdisplayheight() / 10;*/
	

	
	
	
	
	
	sf::Text T1;
	T1.setString("Retry");
	T1.setCharacterSize(15);
	T1.setFont(Font::Get_arial());
	sf::Text T2;
	T2.setString("Main Menu");
	T2.setCharacterSize(15);
	T2.setFont(Font::Get_arial());
	

	C.setText({ T1,T2 });
	C.setPosition(Cam::getdisplaywidth() / 2, Cam::getdisplayheight() / 2);
	C.setColorCursor(sf::Color::Black);
	//Setting the size of the preRender rectangle.
	preRender.setSize(sf::Vector2f(Cam::getdisplaywidth(), Cam::getdisplayheight()));
	preRender_Tex.create(Cam::getdisplaywidth(), Cam::getdisplayheight());
}

bool Gameover_Screen::main(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event) {

	if (is_first == true) {
		preRender_Tex.update(win);
		preRender.setTexture(&preRender_Tex);
	}
	
	switch (C.check()) {
	case -5:
		//Moving forward
		switch (C.getIndex()) {
		case 0:
			App::goto_mainmenu();
			return false;
		case 1:
			//World::Files[Player::PlayerObjects[0]->getDungeon()][0][0]
			if (Player::PlayerObjects[0]->get_is_in_dungeon() == true) {
				World::LoadWorld_NextFloorAni(World::Files[Player::PlayerObjects[0]->getDungeon()][0][0], win, 0, 0, TM, s_event);
			}
			else {
				World::LoadWorld_NextFloorAni(World::GetCurrentLobby(0), win, 0, 0, TM, s_event);
			}
			Exit = true;
		}
		break;
	}
	
	//Rendering everything that needs to be rendered.
	render(win);



	if (Exit == true) {

		App::control_cache.clear();
		is_first = true;
		Exit = false;
		return true;
	}
	else {
		is_first = false;
		return false;
	}
	
}

void Gameover_Screen::render(sf::RenderWindow &win) {
	win.clear();
	Cam::drawGUI_chan(0,win,preRender);
	Cam::drawGUI_chan(0,win,C);
	win.display();
}