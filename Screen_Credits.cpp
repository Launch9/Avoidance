#include "stdafx.h"
#include "Screen_Credits.h"
#include "Font.h"

Screen_Credits::Screen_Credits()
{
	if (!tex.loadFromFile("R/Texturemaps/Credits_Screen_Tex.png"))
	{
		throw("Screen_Credits class, texturemap failed to load.");
	}
	sf::Text t1; //Thank you text
	t1.setString("Thanks for playing my game!");
	t1.setCharacterSize(40);
	t1.setPosition(Cam::getdisplaywidth() / 4, Cam::getdisplayheight() / 6);
	t1.setFont(Font::Get_isocpeur());
	sf::Text t2; //Credit sign
	t2.setString("Made by Joshua Schudt\n\nThis was a demo by the way.\n I will be making more in the future.\nPlease let me know of any bugs you have noticed.");
	t2.setPosition(Cam::getdisplaywidth() / 4, Cam::getdisplayheight() / 2);
	t2.setFont(Font::Get_isocpeur());
	sf::Text t3; //Thanks to sfml
	t3.setString("Made using the awesome media interface that is ");
	t3.setPosition(50, Cam::getdisplayheight() - 50);
	t3.setFont(Font::Get_isocpeur());
	sf::Sprite s1; //SFML logo
	s1.setPosition(Cam::getdisplaywidth() - 373, Cam::getdisplayheight() - 113);
	s1.setTexture(tex);
	s1.setTextureRect(sf::IntRect(0, 0, 373, 113));
	Texts = { t1,t2,t3 };
	Sprites = {s1};
	AO = {};
	typeID = 1;
}

bool Screen_Credits::main(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event) {
	
	sf::Event event;
	sf::Clock clock;
	while (Exit == false && win.isOpen()) {
		while (win.pollEvent(event)) {
			//Checking events
			//close requested event
			if (event.type == sf::Event::Closed) {
			
				return false;
			}

			if (event.type == sf::Event::KeyPressed) {


				if (event.key.code == sf::Keyboard::D) {
					ChoiceRTEXT::DK = true;
				}
				if (event.key.code == sf::Keyboard::S) {
					ChoiceRTEXT::SK = true;
				}
				if (event.key.code == sf::Keyboard::A) {
					ChoiceRTEXT::AK = true;
				}
				if (event.key.code == sf::Keyboard::W) {
					ChoiceRTEXT::WK = true;
				}
				if (event.key.code == sf::Keyboard::E) {
					Exit = true;
				}
			}
		}


		if (clock.getElapsedTime().asMilliseconds() > 1000 / GF::getFramerate()) {
			win.clear(sf::Color::Black);
			for (unsigned int i = 0; i < Texts.size(); i++) {
				Cam::drawGUI_chan(0, win, Texts[i]);
			}
			for (unsigned int i = 0; i < Sprites.size(); i++) {
				Cam::drawGUI_chan(0, win, Sprites[i]);
			}
			win.display();
			clock.restart();
		}

		




		ChoiceRTEXT::DK = false;
		ChoiceRTEXT::SK = false;
		ChoiceRTEXT::AK = false;
		ChoiceRTEXT::WK = false;
		GF::tick();
		sf::sleep(sf::milliseconds(1));
	}
	

	Exit = false;
	return true;
}

