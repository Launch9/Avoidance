#include "stdafx.h"
#include "Screen_Pause.h"
#include "Font.h"
#include <iostream>
#include "Cam.h"
#include "App.h"
#include "Player.h"
Screen_Pause::Screen_Pause()
{
	shader.setPosition(0, 0);
	shader.setSize(sf::Vector2f(Cam::getdisplaywidth(), Cam::getdisplayheight()));
	sf::Color dark;
	dark.a = 100;
	dark.b = 0;
	dark.g = 0;
	dark.r = 0;
	text.setPosition(Cam::getdisplaywidth() / 2, Cam::getdisplayheight() / 2);
	text.setColor(sf::Color::Blue);
	text.setFont(Font::Get_isocpeur());
	text.setCharacterSize(20);
	text.setString("Paused");
	shader.setFillColor(dark);
	make_lambda_functions();
	sf::Text T1;
	T1.setString("Continue");
	T1.setCharacterSize(15);
	T1.setFont(Font::Get_arial());
	
	sf::Text T4;
	switch (mp.isMusic_On()) {
	case 0:
		T4.setString("Music: Off");
		break;
	case 1:
		T4.setString("Music: On");
	}
	
	T4.setCharacterSize(15);
	T4.setFont(Font::Get_arial());
	sf::Text T2;
	T2.setString("Main Menu");
	T2.setCharacterSize(15);
	T2.setFont(Font::Get_arial());
	sf::Text T3;
	T3.setString("Exit Program");
	T3.setCharacterSize(15);
	T3.setFont(Font::Get_arial());
	//These are the controls.
	//sf::Text T5;
	std::string control_string;
	control_string.append("Controls:\nShift->toggle power shot.\nSpace->Hold to slide.\nW->move up/slide up.\nA->move left/slide left.\nS->move down/slide down.\nD->move right/slide right.");
	control_string.append("\nQ->switch gauntlet up.\nZ->switch gauntlet down.\nEsc->pause game.");
	controls.setString(control_string);
	//*);
	controls.setPosition(sf::Vector2f(160, 150));
	controls.setFont(Font::Get_arial());
	controls.setCharacterSize(11);
	//controls.
	//controls = T5;
	options = { T1,T4,T2,T3 };
	C.setText({ T1,T4,T2,T3 });
	C.setPosition(Cam::getdisplaywidth() / 2, Cam::getdisplayheight() / 2);
	C.setColorCursor(sf::Color::Black);
	//Setting the size of the preRender rectangle.
	preRender.setSize(sf::Vector2f(Cam::getdisplaywidth(), Cam::getdisplayheight()));
	preRender_Tex.create(Cam::getdisplaywidth(), Cam::getdisplayheight());

}

void Screen_Pause::make_lambda_functions() {
	//Exit Program option
	Lambdas.push_back([&](sf::RenderWindow &win){
		Exit = true;
		win.close();
	});
	
	//Main menu option
	Lambdas.push_back([&](sf::RenderWindow &win) {
		Exit = true;
		App::goto_mainmenu();
	});
	//Toggle music option
	Lambdas.push_back([&](sf::RenderWindow &win) {
		mp.toggleMusic_On();
		switch (mp.isMusic_On()) {
		case 0:
			options[1].setString("Music: Off");
			break;
		case 1:
			options[1].setString("Music: On");
		}
		C.setText(options, false);
	});
	//Continue option
	Lambdas.push_back([&](sf::RenderWindow &win) {
		if (was_timer_on == true) {
			Player::PlayerObjects[0]->getScoring().setTimer(true);
		}
		
		Exit = true;
	});
	
}


bool Screen_Pause::main(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event) {
	if (is_first == true) {
		was_timer_on = Player::PlayerObjects[0]->getScoring().isTimerActive();
		Player::PlayerObjects[0]->getScoring().setTimer(false);
		preRender_Tex.update(win);
		preRender.setTexture(&preRender_Tex);
		is_first = false;
	}
	
	
	

	
			//Rendering everything that needs to be rendered.
			render(win);
		
			
			switch (C.check()) {
				case -5:
					//Moving forward
					//Calling choice function depending on index.
					Lambdas[C.getIndex()](win);
					break;
				case -6:
					//Moving backward
					//Calling continue choice function.
					Lambdas[2](win);
					break;
			
			
			}
			
		
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

void Screen_Pause::render(sf::RenderWindow &win) {
	win.clear();
	Cam::drawGUI_chan(0, win, preRender);
	Cam::drawGUI_chan(0, win, shader);
	Cam::drawGUI_chan(0, win, text);
	Cam::drawGUI_chan(0, win, controls);
	Cam::drawGUI_chan(0, win, C);
	win.display();
}

