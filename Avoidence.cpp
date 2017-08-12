#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <thread>
#include <vector>
#include "Player.h"
#include "Temporarytxt.h"
#include "Wall.h"
#include "BG.h"
#include "Shop.h"
#include "ChoiceRTEXT.h"
#include "Itemids.h"
#include "Sound.h"
#include "Light_MOTHER.h"
#include "GF.h"
#include "Cam.h"
#include "Dia.h"
#include "Bullet.h"
#include "NPC_MOTHER.h"
#include "Basic_Tile_MOTHER.h"
#include "Debug.h"
#include "Editor.h"
#include "World.h"
#include "ConstLight.h"
#include "Screen_MOTHER.h"
#include "Music.h"
#include "GUI.h"
#include "SoundBlock.h"
#include "Font.h"
#include "Inventory.h"
#include "ST.h"
#include "Projectile.h"
#include "Gauntlets.h"
#include "ParticleSystem.h"
#include "ParticleSettings.h"
#include <functional>
#include "PText.h"
#include "TempText.h"
#include "App.h"
#include "Choice.h"
#include "P_Switch_MAIN.h"
#include "Sub_NPC_A.h"
#include "Cloud.h"
#include "random2.h"
#include "Weather.h"
#include "Misc_Sprites.h"
#include "Flame.h"
#include "Blast.h"
#include "BackSplash_MOTHER.h"
#include "MusicPlayer.h"
#define base32 32
#define max_delta 0.017000
#define off 0.0075
///Notes to self///
//Error C4430: missing type specifier - int assumed. Note: C++ does not support default-int:
//In this case you must have included the file that includes that file, thus making a loop.
//eg. foo.h						loo.h
//    #include loo.h			#include foo.h
//This will produce that kind of error and should be avoided at all costs.
//This error is nasty because the warning it gives is very vauge.

//Make fake stairs, that when you get close enough, it will come and attack you.
//Link Error will occur if you try to inline a static function!

//Temptext needs referbishing.
//TO FIX
//make the framerate smooth again!
//by using interpolation with the time step!

bool commandblock = false;

void test() {
	ST f;
	f.setup();
}
void tick1(sf::RenderWindow &win, TileMap &TM) {
	//std::cout << "tick1:START" << std::endl;
	Bullet::tick();
	//std::cout << "tick1:test" << std::endl;
	SoundBlock::All_Tick();
	//std::cout << "tick1:test" << std::endl;
	World::hazetick();
	//std::cout << "tick1:test" << std::endl;
	World::timetick(win, TM);
	//std::cout << "tick1:test" << std::endl;
	Flame::maintick();
	//std::cout << "tick1:test" << std::endl;
	Projectile::tickall();
	//std::cout << "tick1:test" << std::endl;
	ParticleSystem::tickparticles();
	//std::cout << "tic1::End" << std::endl;
	BackSplash_MOTHER::tick_all();
}
void tick2() {
	Blast::tick_all();
	//std::cout << "tick2::start" << std::endl;
	Dia::tick();
	//std::cout << "tick2:test" << std::endl;
	Debug::tick();
	//std::cout << "tick2:test" << std::endl;
	Player::PlayerObjects[0]->constanimation(0);
	//std::cout << "tick2:test" << std::endl;
	NPC_MOTHER::maintick();
	//std::cout << "tick2:test" << std::endl;
	World::maintick();
	Sub_NPC_A::A_tick();
	
	//std::cout << "tick2:test" << std::endl;
	Basic_Tile_MOTHER::mainanimate();
	//std::cout << "tick2:test" << std::endl;
	Cloud::maintick();
	//std::cout << "tick2:test" << std::endl;
	TempText::tick();
	//std::cout << "tick2:test" << std::endl;
	Temporarytxt::TTxT_tick();
	//std::cout << "tick2:test" << std::endl;
	Editor::tick();
	//std::cout << "tick2:test" << std::endl;
	GF::tick();
	//std::cout << "tick2:test" << std::endl;
	GUI::anitick();
	//std::cout << "tick2:End" << std::endl;	
	
	
	
}
void Calculate(sf::RenderWindow &win, TileMap &TM) {
	
		tick1(win, TM);
		tick2();
		
	
}

void render(sf::RenderWindow &window, TileMap &tilemap, ParticleSystem &PSystem) {
	window.clear(sf::Color::Black);//Clearing the window to have everything be drawn again.
	BackSplash_MOTHER::draw_all(window);
	Bullet::draw(window);
	window.draw(tilemap);//Drawing tilemap
	Projectile::drawall(window);
	NPC_MOTHER::maindraw(window);
	window.draw(PSystem);
	
	Temporarytxt::drawalltext(window);
	PText::drawAll(window);
	Dia::draw(window);
	World::draw(window);
	GUI::Draw_All(window, 0);
	GF::draw(window);
	Player::PlayerObjects[0]->drawPSprite(window);
	BackSplash_MOTHER::draw_all_fore(window);
	Cloud::draw_all(window);
	Editor::draw(window);
	Debug::draw(window);
	
	
}


void checkControls(sf::RenderWindow &window, sf::Event &event, TileMap &TM, bool(&slidemap)[4]) {
	while (window.pollEvent(event)) {
		//Checking events
		//close requested event

		if (event.type == sf::Event::Closed) {
			window.close();
		}


		if (Debug::GetMenuOpen() == true) {
			if (event.type == sf::Event::KeyPressed) {
				//This deactives the command line.
				if (event.key.code == sf::Keyboard::Escape) {
					
						commandblock = true;
						Debug::SetDebugMenu(window, false);
					
					
						
					
					
				}
				//This will delete the last character delivered to the command line.
				if (event.key.code == sf::Keyboard::BackSpace) {
					commandblock = true;
					Debug::Backspace();
				}
				//This just uses the command that is currently in the command line.
				if (event.key.code == sf::Keyboard::Return) {
					Debug::UseCommand(window, TM);
					commandblock = true;
				}
				//This will use the last command used in the command line.
				if (event.key.code == sf::Keyboard::LBracket) {
					Debug::setlastcommand();
					commandblock = true;
				}
				//This clears the entire commandline.
				if (event.key.code == sf::Keyboard::LAlt) {
					Debug::Clearcommand();
					commandblock = true;
				}


			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::SemiColon) {
					App::Debug_Unlock_Key = false;
				}
				if (event.key.code == sf::Keyboard::BackSpace) {
					commandblock = false;
				}
				if (event.key.code == sf::Keyboard::Return) {
					commandblock = false;
				}
			}
			//This happens if you did not click any of the buttons above.
			if (commandblock == false) {
				if (event.type == sf::Event::TextEntered)
				{

					if (event.text.unicode < 128) {
						Debug::AddCommandChar(static_cast<char>(event.text.unicode));
					}

				}
			}


		}

		else {
			if (event.type == sf::Event::KeyPressed) {
				
				//THESE ARE IF YOU ARE TRYING TO WALK.
				if (event.key.code == sf::Keyboard::D) {
					App::H_Controls[1] = true;
					App::P_Controls[1] = true;
					App::control_cache.push_back(1);
					ChoiceRTEXT::DK = true;
				}
				if (event.key.code == sf::Keyboard::S) {
					App::H_Controls[2] = true;
					App::P_Controls[2] = true;
					App::control_cache.push_back(2);
					ChoiceRTEXT::SK = true;

				}
				if (event.key.code == sf::Keyboard::A) {
					App::H_Controls[3] = true;
					App::P_Controls[3] = true;
					App::control_cache.push_back(3);
					ChoiceRTEXT::AK = true;

				}
				if (event.key.code == sf::Keyboard::W) {
					App::H_Controls[0] = true;
					App::P_Controls[0] = true;
					App::control_cache.push_back(0);
					ChoiceRTEXT::WK = true;

				}
				if (Player::PlayerObjects.size() != 0) {
					
					if (event.key.code == sf::Keyboard::Escape) {
						App::Pause(window, TM);
					}
					if (event.key.code == sf::Keyboard::RShift) {
						Player::PlayerObjects[0]->set_Ready();
					}
					if (event.key.code == sf::Keyboard::E) {
						if (Editor::GetStatus() == true) {
							Editor::deletetile();
						}
						else {

							Dia::iterate();

						}


					}
					if (event.key.code == sf::Keyboard::I) {
						Cam::readyScreenShot();
					}

					if (event.key.code == sf::Keyboard::Q) {
						Player::PlayerObjects[0]->addGtype(1);
					}
					if (event.key.code == sf::Keyboard::Z) {
						Player::PlayerObjects[0]->subGtype(1);
					}
					//THESE ARE IF YOU ARE SHOOTING.
					if (event.key.code == sf::Keyboard::Right) {
						if (Editor::GetStatus() == true) {
							Editor::Tiletype_UP(1);
						}
						else {


							Player::PlayerObjects[0]->shootright();
						}

					}
					if (event.key.code == sf::Keyboard::Down) {
						if (Editor::GetStatus() == true) {
							Editor::Tileid_DOWN(1);
						}
						else {
							GUI::Iup();


							Player::PlayerObjects[0]->shootdown();
						}

					}
					if (event.key.code == sf::Keyboard::Left) {
						if (Editor::GetStatus() == true) {
							Editor::Tiletype_DOWN(1);
						}
						else {
							Player::PlayerObjects[0]->shootleft();
						}

					}
					if (event.key.code == sf::Keyboard::Up) {
						if (Editor::GetStatus() == true) {
							Editor::Tileid_UP(1);
						}
						else {
							GUI::Idown();

							Player::PlayerObjects[0]->shootup();
						}
					}
					if (event.key.code == sf::Keyboard::Space) {
						if (Editor::GetStatus() == true) {
							Editor::placetile(TM);
						}
						App::HQ = true;
					}
					if (event.key.code == sf::Keyboard::SemiColon) {
						App::Debug_Unlock_Key = true;
					}
					if (event.key.code == sf::Keyboard::F) {
						if (App::Debug_Unlock_Key == true) {
							Debug::SetDebugMenu(window, true);
							
						}
						
					}
					if (Editor::GetStatus() == true) {
						if (event.key.code == sf::Keyboard::X) {
							Editor::PauseNPCs();
						}
						if (event.key.code == sf::Keyboard::Z) {
							Editor::UnPauseNPCs();
						}
						//This will quickly save the world to a default set file.
						if (event.key.code == sf::Keyboard::RAlt) {
							Editor::SaveDWorld(TM);
						}
					}

				}
				}
				
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::SemiColon) {
					App::Debug_Unlock_Key = false;
				}
				if (event.key.code == sf::Keyboard::D) {
					for (unsigned int i = 0; i < App::control_cache.size(); i++) {
						if (App::control_cache[i] == 1) {
							App::control_cache.erase(App::control_cache.begin() + i);
						}
					}
					slidemap[0] = false;
					App::H_Controls[1] = false;
				}
				if (event.key.code == sf::Keyboard::S) {
					for (unsigned int i = 0; i < App::control_cache.size(); i++) {
						if (App::control_cache[i] == 2) {
							App::control_cache.erase(App::control_cache.begin() + i);
						}
					}
					slidemap[1] = false;
					App::H_Controls[2] = false;
				}
				if (event.key.code == sf::Keyboard::A) {
					for (unsigned int i = 0; i < App::control_cache.size(); i++) {
						if (App::control_cache[i] == 3) {
							App::control_cache.erase(App::control_cache.begin() + i);
						}
					}
					slidemap[2] = false;
					App::H_Controls[3] = false;
				}
				if (event.key.code == sf::Keyboard::W) {
					for (unsigned int i = 0; i < App::control_cache.size(); i++) {
						if (App::control_cache[i] == 0) {
							App::control_cache.erase(App::control_cache.begin() + i);
						}
					}
					slidemap[3] = false;
					App::H_Controls[0] = false;
				}
				if (Player::PlayerObjects.size() != 0) {
					if (event.key.code == sf::Keyboard::Space) {
						App::HQ = false;
					}
					if (event.key.code == sf::Keyboard::RBracket) {
						Debug::uselastcommand(window, TM);
					}
				}
				
			}

		}
		
	}
	bool should_stop = false;
	
		if (App::control_cache.size() > 0 && Player::PlayerObjects.size() != 0 && Screen_MOTHER::get_is_ready() == false) {
			switch (App::control_cache[App::control_cache.size() - 1]) {
			case 0:
				if (Editor::GetStatus() == true) {
					Editor::moveup();
				}
				else {
					if (App::HQ == true) {
						Player::PlayerObjects[0]->slideup(3);
					}
					else {
						Player::PlayerObjects[0]->moveup(base32);
					}
					
				}
				
				
				break;
			case 1:
				if (Editor::GetStatus() == true) {
					Editor::moveright();
				}
				else {
					if (App::HQ == true) {
						Player::PlayerObjects[0]->slideright(3);
					}
					else {
						Player::PlayerObjects[0]->moveright(base32);
					}
					
				}
				
				
				break;
			case 2:
				if (Editor::GetStatus() == true) {
					Editor::movedown();
				}
				else {
					if (App::HQ == true) {
						Player::PlayerObjects[0]->slidedown(3);
					}
					else {
						Player::PlayerObjects[0]->movedown(base32);
					}
					
				}
				
				
				break;
			case 3:
				if (Editor::GetStatus() == true) {
					Editor::moveleft();
				}
				else {
					if (App::HQ == true) {
						Player::PlayerObjects[0]->slideleft(3);
					}
					else {
						Player::PlayerObjects[0]->moveleft(base32);
					}
				}
				
				
			}
			should_stop = true;
		}
			
	
	
}

int main() {
	std::cout << "Setting up..." << std::endl;
	int numplayers = 1;
	int Framerate = 5;
	//Loading up the texture for tiles(Mostly 32 x 32 tiles).
	sf::Texture texturemap;
	//Texture for all character sprites and dialouge boxes.
	sf::Texture charmap;
	sf::Texture hazemap;
	sf::Texture Lobbymap;
	sf::Texture Lobbymap2;
	sf::Texture Lobbymap3;
	sf::Texture Lobbymap4;
	sf::Texture texturemap2;
	sf::Texture texturemap3;
	sf::Texture backsplash_texture;
	if (!texturemap.loadFromFile("R/Texturemaps/Textureplate.png"))
	{
		cout << "It failed" << endl;
		throw("errorz");
	}
	if (!texturemap2.loadFromFile("R/Texturemaps/Textureplate2.png")) {
		cout << "Textureplate2.png failed to load" << std::endl;
		throw("Error");
	}
	if (!charmap.loadFromFile("R/Texturemaps/Characters_Tex.png")) {
		cout << "Failed to load Texturemaps/Characters_Tex.png! " << std::endl;
		throw("errorz");
	}
	if (!hazemap.loadFromFile("R/Texturemaps/Hazes_Tex.png")) {
		cout << "Hazemap failed to load. Avoidence.cpp" << endl;
		throw("errorz");
	}
	if (!Lobbymap.loadFromFile("R/Texturemaps/Lobby.png")) {
		cout << "Lobby.png failed to load. Avoidence.cpp" << std::endl;
		throw("erroz");
	}
	if (!Lobbymap2.loadFromFile("R/Texturemaps/Lobby2.png")) {
		cout << "Lobby2.png failed to load. Avoidence.cpp" << std::endl;
		throw("erroz");
	}
	if (!Lobbymap3.loadFromFile("R/Texturemaps/Lobby3.png")) {
		cout << "Lobby3.png failed to load. Avoidence.cpp" << std::endl;
		throw("erroz");
	}
	if (!Lobbymap4.loadFromFile("R/Texturemaps/Lobby4.png")) {
		cout << "Lobby4.png failed to load. Avoidence.cpp" << std::endl;
	}
	if (!texturemap3.loadFromFile("R/Texturemaps/Textureplate3.png")) {
		cout << "Textureplate3.png failed to load. Avoidence.cpp" << std::endl;
		throw("erroz");
	}
	
	if (!backsplash_texture.loadFromFile("R/Texturemaps/BackSplashes.png")) {
		cout << "backsplash_texture.png failed to load. Avoidence.cpp" << std::endl;
		throw("errorz");
	}
	//Loading the text font.
	sf::Font font;
	std::cout << "2/10" << std::endl;
	if (!font.loadFromFile("R/Fonts/arial.ttf")) {
		cout << "Failed to load font." << endl;
	}
	Font::init();
	MusicPlayer::init();
	sf::Sprite player1sprite;
	player1sprite.setTexture(texturemap);
	std::cout << "3/10" << std::endl;

	player1sprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
	BackSplash_MOTHER::init(backsplash_texture);
	P_Switch_MAIN::init();
	App::init();
	Choice::init(texturemap);
	Inventory::init(texturemap);
	ChoiceRTEXT::init(Font::Get_isocpeur());
	Basic_Tile_MOTHER::init(texturemap);
	std::cout << "4/10" << std::endl;

	Gauntlets::init(charmap);
	NPC_MOTHER::maininit(texturemap, charmap);
	Projectile::init();
	Weather::init();
	Misc_Sprites::init();
	GF::init(texturemap, Framerate);
	ParticleSystem PSystem;
	Itemids::init(texturemap);
	Sound::init();
	Bullet::init(texturemap);
	std::cout << "6/10" << std::endl;

	Player::init(charmap);
	Cloud::init();
	Invisible_MOTHER::init(texturemap);
	
	//theres four are sliding controls.
	
	bool slidemap[4] = { false, false, false, false };
	
	Cam::init();
	Cam::Cam();
	Debug::init(Font::Get_isocpeur());
	Dia::init(charmap, Font::Get_isocpeur());
	Editor::init(texturemap, Font::Get_isocpeur());
	Screen_MOTHER::init();
	GUI::init(texturemap, Font::Get_isocpeur());
	World::init(hazemap);
	//Making the window happens here
	std::cout << "8/10" << std::endl;

	//sf::RenderWindow window(sf::VideoMode(Cam::getdisplaywidth(), Cam::getdisplayheight()), "Avoidance Beta", sf::Style::Close | sf::Style::Titlebar);
	sf::RenderWindow window(sf::VideoMode(Cam::getdisplaywidth(), Cam::getdisplayheight()), "Avoidance Beta", sf::Style::Close | sf::Style::Titlebar);
	window.setKeyRepeatEnabled(false);
	
	TileMap tilemap(&charmap);
	tilemap.load(&Lobbymap);
	tilemap.load(&texturemap);
	tilemap.load(&Lobbymap2);
	tilemap.load(&texturemap2);
	tilemap.load(&Lobbymap3);
	tilemap.load(&texturemap3);
	tilemap.load(&Lobbymap4);
	//tilemap.setTexture(0);
	
	//This is for setting up the dungeon layout.
	std::cout << "10/10" << std::endl;

	World::W1();
	sf::Clock clock;
	sf::Time time;
	sf::Event event;
	std::cout << "Done!" << std::endl;
	Screen_MOTHER::start(0);
	//Setting up the camera to the correct position before displaying the world.
	//Cam::setxy_chan(0, Player::PlayerObjects[0].getx(), Player::PlayerObjects[0].gety(), true);
	//Run as long as the window is open.
	
	while (window.isOpen()) {
		
		
			
			
		
			
			//time = clock.getElapsedTime() - timebefore;
			time = clock.restart();	
			
				
				//timebefore = time + timebefore;
				//clock.restart();
				//int m = time.asSeconds() - ceil(time.asSeconds());
				GF::setTTR(time.asSeconds());
				float delta = time.asSeconds();// = GF::getTTR() - GF::getTLR();
				
				GF::setTSS(GF::getTSS() + time);
				//Checking to make sure the delta doesn't go over a certain amount.
				if (delta >= max_delta) {
					
					delta = max_delta;
					
				}
				//delta = 0.00005;
				GF::setDelta(delta);
				
				time = sf::seconds(0);
				checkControls(window, event, tilemap, slidemap);
				
				if (Screen_MOTHER::check(window, tilemap, event) == true) {
					if (App::is_pending() == false) {
						World::anitick(clock, window, tilemap, event); //This checks to see if any animations are being called.
						GF::setTLR(GF::getTTR());
						Calculate(window, tilemap); //This ticks all the objects in the game.
						Cam::setview_chan(0, window);
						render(window, tilemap, PSystem);


						//window.draw(sprite);
						window.display();//Displaying everything to the screen.
					}
					
				}
				//This checks to see if you wanted a screenshot taken or not.
				if (Cam::get_is_ready() == true) {
					Cam::takeScreenShot(window);
				}
				//Reseting the control variables inside these classes.
				ChoiceRTEXT::WK = false;
				ChoiceRTEXT::AK = false;
				ChoiceRTEXT::SK = false;
				ChoiceRTEXT::DK = false;
				ChoiceRTEXT::UPK = false;
				ChoiceRTEXT::DOWNK = false;
				ChoiceRTEXT::LEFTK = false;
				ChoiceRTEXT::RIGHTK = false;
				App::P_RESET();
				App::check_pendings(window, tilemap);
			
				//if (Player::PlayerObjects.size() > 0) {
				//	std::cout << Player::PlayerObjects[0]->getDungeon() << std::endl;
				//}
				
			
			
				//std::cout << Sub_NPC_A::Object_Cache.size() << std::endl;
			
			
			sf::sleep(sf::milliseconds(1));
		}
		
	
	window.close();
	}
