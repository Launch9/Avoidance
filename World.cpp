#include "stdafx.h"
#include "World.h"
#include "Wall.h"
#include "Bg.h"
#include "Shop.h"
#include <vector>
#include "Light_MOTHER.h"
#include "Dia.h"
#include "Bullet.h"
#include "Laser.h"
#include "GF.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Basic_Tile_MOTHER.h"
#include "ConstLight.h"
#include "FlickerLight.h"
#include "Stair.h"
#include <thread>
#include "GUI.h"
#include "Debug.h"
#include "Sound.h"
#include "SoundBlock.h"
#include "HomingSkull.h"
#include "AniBg.h"
#include "ChainBall.h"
#include "Screen_MOTHER.h"
#include "Screen_Credits.h"
#include "Character.h"
#include "SaveStation.h"
#include "Door.h"
#include "Foreground.h"
#include "Font.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "TileMap.h"
#include "Projectile.h"
#include "Corner.h"
#include "P_Switch.h"
#include "Seal.h"
#include "RTile.h"
#include "P_Switch_MAIN.h"
#include "P_Spawner_Const.h"
#include "PTile.h"
#include "Skeleton.h"
#include "ParticleSystem.h"
#include "Cloud_Spawner.h"
#include "Cloud_Start.h"
#include "Cloud.h"
#include "InvisibleWall.h"
#include "Teleporter.h"
#include "Sign.h"
#include "Hurts.h"
#include "Stream.h"
#include "Chest.h"
#include "Room.h"
#include "Entrance.h"
#include "Exit.h"
#include "TripleChest.h"
#include "Shielder.h"
#include "Slime.h"
#include "Dragon.h"
#include "Rock.h"
#include "Break_Spawner.h"
#include "Weather.h"
#include "AniWall.h"
#include "random2.h"
#include "Dino.h"
#include "BounceTile.h"
#include "Squisher.h"
#include "W_bomb.h"
#include "Flame.h"
#include "Blast.h"
#include "Projectile.h"
#include "ParticleSystem.h"
#include "EyeBall.h"
#include "EBM.h"
#include "EyeBall_MAIN.h"
#include "Elevator.h"
#include "BackSplash_MOTHER.h"
#include "Sub_NPC_Block.h"
#include "IPTile.h"
#include "Big_Squisher.h"
#include "FlameThrower.h"
#include "Com_Hand.h"
#include "Com_MAIN.h"
#include "NPC_Spawner.h"
#include "App.h"
#include "P_Fog.h"
#define base32 32
#define SWTX 32 * 3
#define worth_of_life 30 //This is how much having extra lives over three is worth. 
using namespace std;
bool World::isClockActive;
float World::time;
std::string World::PlayerDefault;
int World::load_x;
int World::load_y;
int World::slotnum;
int World::hazeindex;
int World::momentumx;
int World::momentumy;
int World::hazetype;
int World::hx;
int World::hy;
int World::SHazeW;
int World::SHazeH;
int World::Animation;
int World::newFloor;
int World::newDungeon;
int World::effect_ID;
int World::newExitID;
bool World::should_reset_world;
std::string World::newFile;
std::string World::CurrentWorld;
sf::Texture World::preRender_tex;
sf::RectangleShape World::preRender;
MusicPlayer World::MP;
std::vector<int> World::r_c_c;
std::vector<bool> World::Switches;
std::vector <std::string> World::PlayerFiles;
int World::newExtra;
sf::Texture World::wtex;
sf::Sprite World::Haze;
//These are the amount of ticks that need to be reached to move the haze.
int World::max_ticks;
//These are the ticks.
int World::ticks;
std::vector<sf::Sprite> World::Hazes;
std::vector<std::vector<std::vector<std::string>>> World::Files;

void World::LoadWorld(std::string FileLocation, TileMap &Tmap, bool Clear) {
	std::cout << "Started loading up world: " << FileLocation << std::endl;
	P_Switch_MAIN::clearSwitches();
	if (Clear == true) {
		ClearWorld();
	}
	CurrentWorld = FileLocation;
	
	ifstream file;
	//The booleans determine what is happening currently in the file reading process.
	bool tile = false;
	bool settype = false;
	char CurrentChar;
	//Reusable string for multi purpose.
	//Mostly for putting parameters in here consisting of more then one integer.
	std::string Rstring;
	//This is a vector to be used when you 
	std::vector<int> items;
	//These are for multi purpose as well.
	//These reset every loop.
	bool A = false;
	bool B = false;
	bool C = false;
	//These must be put back to false after use.
	bool Z = false;
	bool Y = false;
	bool X = false;
	//Checking to see if you have loaded up a file that is in the dungeons vector.
	Player::PlayerObjects[0]->setFloor(newFloor);
	Player::PlayerObjects[0]->setDungeon(newDungeon);
	int d = newDungeon;
	int f = newFloor;
	switch (d) {
	case 0:
		
		if (MP.get_track_ID() != 2) {
			MP.play_track(2);
		}
		
		break;
	case 1:
		switch (f) {
		case 0:
			MP.play_track(1);
			break;
		case 1:
			MP.play_track(0);
			break;
		}
		break;
	case 2:
		switch (f) {
		case 0:
			MP.play_track(1);
			break;
		case 1:
			MP.play_track(3);
			break;
		}
		break;
	case 3:
		switch (f) {
		case 0:
			MP.play_track(1);
			break;
		case 1:
			MP.play_track(4);
			break;
		}
		break;
	case 4:
		if (MP.get_track_ID() != 2) {
			MP.play_track(2);
		}
		break;
	case 5:
		if (MP.get_track_ID() != 2) {
			MP.play_track(2);
		}
		break;
	case 6:
		if (MP.get_track_ID() != 5) {
			MP.play_track(5);
		}
		
		//switch (f) {
		//case 0:
		//	MP.play_track(1);
		//	break;
		//case 1:
			
			//break;
		//}
		break;
	}
	
	setHaze(-1);
	Dia::clear();
	//Variables for holding the parameters.
	int NumPara = 0;
	//This is a vector for holding parameters.
	std::vector<int> Parameters;
	int typeID = 0;
	int ClassNum = -1;
	
	file.open(FileLocation, ios::in);
	while (file.good()) {
		
		file.seekg(0, ios::cur);
		file >> CurrentChar;
		if (CurrentChar == *"&" && settype == false) {
			settype = true;
		}
		else if (CurrentChar == *"&" && settype == true) {
			ClassNum = GF::StringtoInt(Rstring);
			settype = false;
			Rstring.clear();
		}
		else if (settype == true) {
			Rstring.push_back(CurrentChar);
		}
		else {

			//This reads to find the start of a tile object.
			if (CurrentChar == *":" && tile == false) {
				tile = true;

			}
			//This reads to find the start of a tile object.
			else if (CurrentChar == *":" && tile == true) {
				switch (ClassNum) {
					//World saves
				case -1:
					
					Tmap.setTexture(Parameters[0]);
					
					effect_ID = Parameters[2];
					setHaze(Parameters[1]);
					if (GF::does_exist(3, Parameters.size()) == true) {
						BackSplash_MOTHER::create(Parameters[3]);
						
					}
					break;
				
					//Basic_Tile_MOTHER class
				case 0:
				//	std::cout << "Basic_Tile_MOTHER: " + GF::str(Parameters[0]) << std::endl;
					switch (Parameters[0]) {
					case 0:
						
						new Wall(Parameters[3], Parameters[1], Parameters[2], Tmap);
						break;
					case 1:
						new Bg(Parameters[3], Parameters[1], Parameters[2], Tmap);
						break;
					case 2:
						items = {};
						//Making the item vector for the shop to have.
						//Any parameters after the dialouge number(Parameter[3]) is an item.
						for (unsigned int i = 5; i < Parameters.size(); i++) {
							items.push_back(Parameters[i]);
						}
						
						new Shop(Parameters[3], Parameters[1], Parameters[2], Parameters[4], items, Tmap);

						items = {};
						break;

					case 3:

						new Stair(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Tmap);
						break;

					case 4:
						
						new AniBg(Parameters[3], Parameters[1], Parameters[2], Tmap);
						break;
					case 5:
						new SaveStation(Parameters[1], Parameters[2], Tmap);
						break;
					case 6:
						new Door(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Parameters[6], Parameters[7], Tmap);
						break;
					case 7:
						new Foreground(Parameters[3], Parameters[1], Parameters[2], Tmap);
						break;
					case 8:
						new Chest(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Tmap);
						break;
					case 9:
						new Corner(Parameters[3], Parameters[1], Parameters[2], Parameters[4], Tmap);
						break;
					case 10:
						new P_Switch(Parameters[3], Parameters[1], Parameters[2], Parameters[4], Parameters[5], Tmap);
						break;
					case 11:
						items = {};
						for (unsigned int i = 5; i < Parameters.size(); i++) {
							items.push_back(Parameters[i]);
						}
						new Seal(Parameters[3], Parameters[1], Parameters[2], Parameters[4], items, Tmap);
						items = {};
						break;
					case 12:
						new RTile(Parameters[3], Parameters[1], Parameters[2], Tmap);
						break;
					case 13:
						new P_Spawner_Const(Parameters[3], Parameters[1], Parameters[2], Parameters[4], Tmap, Parameters[5]);
						break;
					case 14:
						new PTile(Parameters[3], Parameters[1], Parameters[2], Parameters[4], Tmap);
						break;
					case 15:
						new Sign(Parameters[3], Parameters[1], Parameters[2], Tmap);
						break;
					case 16:
						new Stream(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Tmap);
						break;
					case 17:
						new TripleChest(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Tmap);
						break;
					case 18:
						new Rock(Parameters[1], Parameters[2], Parameters[3], Tmap);
						break;
					case 19:
						new AniWall(Parameters[3], Parameters[1], Parameters[2], Tmap);
						break;
					case 20:
						new BounceTile(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Tmap);
						break;
					case 21:
						new EyeBall(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Tmap);
						break;
					case 22:
						new FlameThrower(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Tmap);
						break;
					case 23:
						new NPC_Spawner(Parameters[1], Parameters[2], Parameters[3], Tmap);
						break;
					}
					break;
					//NPC_MOTHER class
				case 1:
					//std::cout << "NPC_MOTHER: " + GF::str(Parameters[0]) << std::endl;
					switch (Parameters[0]) {
					case 0:
						new Laser(Parameters[1], Parameters[2], Parameters[3], Tmap, Parameters[4], Parameters[5], Parameters[6]);
						break;
					case 1:
						new HomingSkull(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Tmap);
						break;
					case 2:
						new ChainBall(Parameters[1], Parameters[2], Parameters[3], Tmap, Parameters[4], Parameters[5], Parameters[6]);
						break;
					case 3:
						new Character(Parameters[1], Parameters[2], Parameters[3], Tmap);
						break;
					case 4:
						new Skeleton(Parameters[1], Parameters[2], Parameters[3], Tmap);
						break;
					case 5:
						new Slime(Parameters[1], Parameters[2], Parameters[3], Tmap);
						break;
					case 6:
						items = {};
						for (unsigned int i = 5; i < Parameters.size(); i++) {
							items.push_back(Parameters[i]);
						}
						new Shielder(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Tmap, items);
						break;
					case 7:
						new Dragon(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Tmap);
						break;
					case 8:
						new Break_Spawner(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Parameters[6], Tmap);
						break;
					case 9:
						new Dino(Parameters[1], Parameters[2], Parameters[3], Tmap);
						break;
					case 10:
						new Squisher(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Parameters[6], Parameters[7], Tmap);
						break;
					case 11:
						new W_bomb(Parameters[1], Parameters[2], Parameters[3], Tmap);
						break;
					case 12:
						new EBM(Parameters[1], Parameters[2], Parameters[3], Tmap);
						break;
					case 13:
						items = {};
						for (unsigned int i = 4; i < Parameters.size(); i++) {
							items.push_back(Parameters[i]);
						}
						new EyeBall_MAIN(Parameters[1], Parameters[2], Parameters[3], items, Tmap);
						break;
					case 14:
						new Big_Squisher(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Tmap);
						break;
					case 15:
						new Com_Hand(Parameters[1], Parameters[3], Parameters[4], Parameters[2], Tmap);
						break;
					case 16:
						new Com_MAIN(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Tmap);
						break;
					}
					break;

					//Light_MOTHER class
				case 2:
					//std::cout << "Light_MOTHER: " + GF::str(Parameters[0]) << std::endl;
					switch (Parameters[0]) {
					//ConstLight
					case 0:
						//1 = x
						//2 = y 
						//3 = baselightpower
						//4,5,6 = color
						new ConstLight(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Parameters[6]);
						break;

					//FlickerLight
					case 1:
						new FlickerLight(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Parameters[6]);
						break;
					}
					break;
					//Invisible_MOTHER class
				case 3:
					//std::cout << "Invisible_MOTHER: " + GF::str(Parameters[0]) << std::endl;
					switch (Parameters[0]) {
					//Sound block
					case 0:
						
						items = {};
						for (unsigned int i = 4; i < Parameters.size(); i++) {
							items.push_back(Parameters[i]);
						}
						new SoundBlock(Parameters[1], Parameters[2], Parameters[3], items);
						items = {};
						break;
					case 1:
						new Cloud_Spawner(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Parameters[6]);
						break;
					case 2:
						new Cloud_Start(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5]);
						break;
					case 3:
						new InvisibleWall(Parameters[1], Parameters[2]);
						break;
					case 4:
						if (Parameters.size() == 6) {
							new Teleporter(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], 0);
						}
						else {
							new Teleporter(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Parameters[6]);
						}
						
						break;
					case 5:
						new Hurts(Parameters[1], Parameters[2], Parameters[3]);
						break;
					case 6:
						new Room(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Parameters[6]);
						break;
					case 7:
						new Entrance(Parameters[1], Parameters[2], Parameters[3], Parameters[4], 0);
						break;
					case 8:
						new Exit(Parameters[1], Parameters[2], Parameters[3], Parameters[4]);
						break;
					case 9:
						new Weather(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Tmap);
						break;
					case 10:
						new Elevator(Parameters[1], Parameters[2], Parameters[3], Parameters[4], Parameters[5], Tmap);
						break;
					case 11:
						new Sub_NPC_Block(Parameters[1], Parameters[2], Parameters[3], Parameters[4]);
						break;
					case 12:
						new IPTile(Parameters[1], Parameters[2], Parameters[3], Parameters[4]);
						break;
					case 13:
						new P_Fog(Parameters[1], Parameters[2], Parameters[3], Tmap);
						break;

					}
					break;

				}
				
				Parameters.clear();
				Rstring.clear();
				tile = false;

			}
			//Reading for integers.
			else if (CurrentChar == *"," && tile == true) {

				Parameters.push_back(GF::StringtoInt(Rstring));

				//Cleaing the Rstring for reuse.
				Rstring.clear();

			}

			else if (tile == true) {
				Rstring.push_back(CurrentChar);
			}

		}
		
		A = false;
		B = false;
		C = false;
	}
	file.close();
	DText::clear();
	Cloud_Start::activate_all();
	Room::update();
	Light_MOTHER::ResetLighting();
	Exit::teleport_to_exit(newExitID);
	Sub_NPC_CD::check();
	P_Switch_MAIN::update();
	GUI::update();
	newExitID = -1;
	std::cout << "Finished loading world file at: " << FileLocation << std::endl;
	
}

void World::LoadWorld_NextFloorAni(std::string FileLocation, sf::RenderWindow &win, int Animation, int PlayerChan, TileMap &TM, sf::Event &s_event) {
	if (Animation == 0) {
		//r_c_c = App::control_cache;
		//App::control_cache.clear();
		
		Player::PlayerObjects[PlayerChan]->StandStill();
		if (PlayerChan != -1) {
			Player::PlayerObjects[PlayerChan]->setXY(0, 0);
			Player::PlayerObjects[PlayerChan]->SnapCam();
		}
		//win.setActive(true);
		std::thread t1(LoadWorld, FileLocation, std::ref(TM), true);
		
		//win.setActive(true);
		A0FadeOut(win, TM, s_event);
		A0MoveGUI(win, PlayerChan, s_event);
		t1.join();
		BackSplash_MOTHER::draw_all(win);
		A0FadeIn(win, TM, s_event);
		//App::control_cache = r_c_c;
	}
	else if (Animation == 1) {
		//App::control_cache.clear();
		Player::PlayerObjects[PlayerChan]->StandStill();
		if (PlayerChan != -1) {
			Player::PlayerObjects[PlayerChan]->setXY(0, 0);
			Player::PlayerObjects[PlayerChan]->SnapCam();
		}
		//win.setActive(false);
		std::thread t1(LoadWorld, FileLocation, std::ref(TM), true);
		//win.setActive(true);
		A0FadeOut(win, TM, s_event);
		t1.join();
		BackSplash_MOTHER::draw_all(win);
		A0FadeIn(win, TM, s_event);
		//App::control_cache = r_c_c;

	}
	else if (Animation == 2) {
		//App::control_cache.clear();
		Player::PlayerObjects[PlayerChan]->StandStill();
		if (PlayerChan != -1) {
			Player::PlayerObjects[PlayerChan]->setXY(0, 0);
			Player::PlayerObjects[PlayerChan]->SnapCam();
		}
		//win.setActive(true);
		std::thread t1(LoadWorld, FileLocation, std::ref(TM), true);

		//win.setActive(true);
		A0FadeOut(win, TM, s_event);
		A1MoveGUI(win, PlayerChan, s_event);
		t1.join();
		BackSplash_MOTHER::draw_all(win);
		A0FadeIn(win, TM, s_event);
		//App::control_cache = r_c_c;
	}


	
}

void World::SaveWorld(std::string FileLocation, TileMap &TMap) {
	std::string Print;
	Print.append(World::getSave(TMap)); //The BackSplash_MOTHER save happens in here!

	Print.append(Basic_Tile_MOTHER::GetSave());
	Print.append(NPC_MOTHER::GetSave());
	Print.append(Light_MOTHER::GetSave());
	Print.append(Invisible_MOTHER::GetSave());
	ofstream file;
	file.open(FileLocation, ios::out);
	file.clear();
	file << Print;
	file.close();
	std::cout << "World saved to " << FileLocation << std::endl;
}

void World::ClearWorld() {
	Cloud::clear_all();
	BackSplash_MOTHER::clear();
	Invisible_MOTHER::clear_all();
	ParticleSystem::destroy_all();
	Projectile::clear_all();
	Basic_Tile_MOTHER::deleteAll();
	NPC_MOTHER::deleteAll();
	Light_MOTHER::deleteAll();
	Light_MOTHER::ResetLighting();
	for (unsigned int i = 0; i < Switches.size(); i++) {
		Switches[i] = false;
	}

}

void World::init(sf::Texture &HazeTexture) {
	P_Switch_MAIN::clearSwitches();
	Animation = -1;
	std::vector<std::vector<std::string>> Lobby = { {"Lob.txt"}, { "Spaceship_G.txt" }, { "Path to dungeon one.txt" }, {"Path to dungeon one two.txt"}, {"Path to dungeon one three.txt"}, {"Path to dungeon two.txt"}, {"Path to dungeon two two.txt"}, {"Path to dungeon two three.txt"} };
	std::vector<std::vector<std::string>> Lobby2 = { { "Lob.txt" },{ "Spaceship_G.txt" },{ "Path to dungeon one.txt" },{ "Path to dungeon one two.txt" },{ "Path to dungeon one three.txt" }, { "Path to dungeon two.txt" },{ "Path to dungeon two two.txt" },{ "Path to dungeon two three.txt" } };
	std::vector<std::vector<std::string>> Lobby3 = { { "Lob.txt" },{ "Spaceship_G.txt" },{ "Path to dungeon one.txt" },{ "Path to dungeon one two.txt" },{ "Path to dungeon one three.txt" }, 
	{ "Path to dungeon two.txt" },{ "Path to dungeon two two.txt" },{ "Path to dungeon two three.txt" }
	,{ "Path to dungeon three.txt" },{ "Path to dungeon three two.txt" },{ "Path to dungeon three three.txt" } };
	std::vector<std::vector<std::string>> Lobby4 = { { "Lob.txt" },{ "Spaceship_G.txt" },{ "Path to dungeon one.txt" },{ "Path to dungeon one two.txt" },{ "Path to dungeon one three.txt" },
	{ "Path to dungeon two.txt" },{ "Path to dungeon two two.txt" },{ "Path to dungeon two three.txt" }
	,{ "Path to dungeon three.txt" },{ "Path to dungeon three two.txt" },{ "Path to dungeon three three.txt" } };
	
	std::vector<std::vector<std::string>> Dungeon1 = {};
	std::vector<std::vector<std::string>> Dungeon2 = {};
	std::vector<std::vector<std::string>> Dungeon3 = {};// = { {"R/World Files/Dungeon 1/F1.txt"}, {"R/World Files/Dungeon 1/F2.txt"}, {"R/World Files/Dungeon 1/F3.txt"},
	/*{ "R/World Files/Dungeon 1/F4.txt" },{ "R/World Files/Dungeon 1/F5.txt" },{ "R/World Files/Dungeon 1/F6.txt" } ,
	{ "R/World Files/Dungeon 1/F7.txt" },{ "R/World Files/Dungeon 1/F8.txt" },{ "R/World Files/Dungeon 1/F9.txt" } ,
	{ "R/World Files/Dungeon 1/F10.txt" },{ "R/World Files/Dungeon 1/F11.txt" },{ "R/World Files/Dungeon 1/F12.txt" },
	{ "R/World Files/Dungeon 1/F13.txt" },{ "R/World Files/Dungeon 1/F14.txt" },{ "R/World Files/Dungeon 1/F15.txt" } ,
	{ "R/World Files/Dungeon 1/F16.txt" }, { "R/World Files/Dungeon 1/F17.txt" }, { "R/World Files/Dungeon 1/F18.txt" },//std::vector<std::vector<std::string>> Dungeon1 = { {"R/World Files/F0 D1.txt", "R/World Files/F0 D1 E0.txt"}, {"R/World Files/F1 D1.txt"}, {"R/World Files/F2 D1.txt"}, {"R/World Files/F3 D1.txt"}, {"R/World Files/F4 D1.txt"}, {"R/World Files/F5 D1.txt"}, {"R/World Files/F6 D1.txt"},
	{ "R/World Files/Dungeon 1/F19.txt" }, { "R/World Files/Dungeon 1/F20.txt" }, { "R/World Files/Dungeon 1/F21.txt" } };*///{"R/World Files/F7 D1.txt" }, { "R/World Files/F8 D1.txt" }, { "R/World Files/F9 D1.txt" }, { "R/World Files/F10 D1.txt" }, { "R/World Files/F11 D1.txt" }, { "R/World Files/F12 D1.txt" }
	//};
	for (unsigned int i = 1; i < 100; i++) {
		Dungeon1.push_back({ "R/World Files/Dungeon 1/F" + GF::str(i) + ".txt" });
	}
	for (unsigned int i = 1; i < 100; i++) {
		Dungeon2.push_back({ "R/World Files/Dungeon 2/F" + GF::str(i) + ".txt" });
	}
	for (unsigned int i = 1; i < 100; i++) {
		Dungeon3.push_back({ "R/World Files/Dungeon 3/F" + GF::str(i) + ".txt" });
	}
	/*std::vector<std::vector<std::string>> Dungeon2 = { { "R/World Files/World 2/F0 D2.txt" },{ "R/World Files/World 2/F1 D2.txt" },{ "R/World Files/World 2/F2 D2.txt" },{ "R/World Files/World 2/F3 D2.txt" },{ "R/World Files/World 2/F4 D2.txt" },{ "R/World Files/World 2/F5 D2.txt" },{ "R/World Files/World 2/F6 D2.txt" },
	{ "R/World Files/World 2/F7 D2.txt" },{ "R/World Files/World 2/F8 D2.txt" },{ "R/World Files/World 2/F9 D2.txt" },{ "R/World Files/World 2/F10 D2.txt" },{ "R/World Files/World 2/F11 D2.txt" },{ "R/World Files/World 2/F12 D2.txt" }
	*/
	
	time = 1;
	isClockActive = false;
	if (!wtex.create(Cam::getdisplaywidth(), Cam::getdisplayheight())) {
		throw("Error creating wtex texture in World.cpp.");
	}
	Switches = { false,false,false,false };
	int sheight = Cam::getdisplayheight();
	int swidth = Cam::getdisplaywidth();
	should_reset_world = true;
	sf::Sprite s1;//Red splochy haze
	s1.setScale(2, 2);
	s1.setTexture(HazeTexture);
	s1.setColor(sf::Color(255, 255, 255, 50));
	s1.setTextureRect(sf::IntRect(0, 0, swidth, sheight));
	sf::Sprite s2;//White specs haze
	s2.setScale(2, 2);
	s2.setTexture(HazeTexture);
	s2.setColor(sf::Color(255, 255, 255, 20));
	s2.setTextureRect(sf::IntRect(0, sheight, swidth, sheight));
	sf::Sprite def; //Default sprite
	SHazeW = swidth * 2;
	SHazeH = sheight * 2;
	hx = -(Cam::getdisplaywidth() / 2);
	hy = -(Cam::getdisplayheight() / 2);
	newDungeon = 1;
	newFloor = 0;
	newExitID = -1;
	newExtra = 0;
	newFile = "";
	PlayerDefault = "(0,0,3,0,1,-1,:;)";
	PlayerFiles = { "R/Player Files/Save 1.txt", "R/Player Files/Save 2.txt", "R/Player Files/Save 3.txt" };
	preRender_tex.create(Cam::getdisplaywidth(), Cam::getdisplayheight());
	preRender.setSize(sf::Vector2f(Cam::getdisplaywidth(), Cam::getdisplayheight()));
	Hazes = { s1, s2, def };
	Files = { Lobby, Dungeon1, Dungeon2, Dungeon3, Lobby2, Lobby3, Lobby4 };
}
void World::W1() {
	//LoadWorld("World Files/F1 D1.txt");
	//LoadWorld("World Files/Default.txt");
}

void World::A0FadeOut(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event) {
	//win.setActive(true);
	preRender_tex.update(win);
	preRender.setTexture(&preRender_tex);

	bool Exit = false;
	int FadeSpeed = 500;
	float FadeAmount = 0;
	sf::Clock clock;
	sf::Time t;
	sf::Color FadeColor(0, 0, 0, 0);
	//Making the rectangle that fades the entire screen into darkness.
	sf::RectangleShape rect(sf::Vector2f(0, 0));
	//Setting the size of that rectangle mentioned up there.
	//Why am I writting these commments?
	rect.setSize(sf::Vector2f(Cam::getdisplaywidth(), Cam::getdisplayheight()));
	
	while (Exit == false) {
		//if (t.asMilliseconds() > 1000 / GF::getFramerate()) {
		t = clock.restart();
				checkEvents(win, s_event);
				if (int(FadeColor.a) + (FadeSpeed * t.asSeconds()) <= 255) {
					FadeAmount += FadeSpeed * t.asSeconds();
					FadeColor.a = FadeAmount;
				}
				else {
					FadeColor.a = 255;
					Exit = true;
				}

				rect.setFillColor(FadeColor);

				win.clear(sf::Color::Black);
				Cam::drawGUI_chan(0, win, preRender);
				Cam::drawGUI_chan(0, win, rect);
				
				
				win.display();
				
				t = sf::seconds(0);

			

		//}
		sf::sleep(sf::milliseconds(1));
	}
	
	//win.setActive(false);
}

void World::A0FadeIn(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event) {
	
	bool Exit = false;
	
	sf::Time t;
	int FadeSpeed = 300;
	float FadeAmount = 255;
	sf::Clock clock; 
	sf::Color FadeColor(0, 0, 0, 255);
	//Making the rectangle that fades the entire screen into darkness.
	sf::RectangleShape rect(sf::Vector2f(0, 0));
	//Setting the size of that rectangle mentioned up there.
	//Why am I writting these commments?
	rect.setSize(sf::Vector2f(Cam::getdisplaywidth(), Cam::getdisplayheight()));

	while (Exit == false) {
		t = clock.restart();
		
			checkEvents(win, s_event);
			FadeAmount -= FadeSpeed * t.asSeconds();
			FadeColor.a = FadeAmount;

			if (FadeAmount <= 0) { //Checking to see if the fade rectangle has reached transperancy.
				FadeColor.a = 0;
				Exit = true;
			}

			rect.setFillColor(FadeColor);

			win.clear(sf::Color::Black);
			BackSplash_MOTHER::draw_all(win);
			win.draw(TM);
			//Basic_Tile_MOTHER::Drawall(win);
			Dia::draw(win);
			Bullet::draw(win);
			NPC_MOTHER::maindraw(win);
			Debug::draw(win);
			
			Temporarytxt::drawalltext(win);
			Player::PlayerObjects[0]->drawPSprite(win);
			//Basic_Tile_MOTHER::DrawForeGround(win);
			World::draw(win);
			GF::draw(win);
			Cam::drawGUI_chan(0, win, rect);
			GUI::Draw_All(win, 0);
			win.display();
			t = sf::seconds(0);
		
		sf::sleep(sf::milliseconds(1));
	}

	
}

void World::A0MoveGUI(sf::RenderWindow &win, int PlayerChannel, sf::Event &s_event) {
	bool Exit = false;
	sf::Clock clock;
	sf::Time t;
	float y_velocity = 5;
	float x_velocity = random2::randomrange(200,300);
	int rotationspeed = random2::randomrange(200, 500);
	float gravity = 3.5;
	sf::Text FFN; //Falling Floor Number
	
	FFN.setString(GF::str(Player::PlayerObjects[PlayerChannel]->getFloor()));
	FFN.setPosition(GUI::getTextPosition_x(0) + 110, GUI::getTextPosition_y(0) + 20);
	FFN.setOrigin(16, 16);
	FFN.setCharacterSize(GUI::getTextSize(0));
	FFN.setFont(GUI::getTextFont(0));
	FFN.setColor(sf::Color::White);
	Sound::Play(5, FFN.getPosition().x, FFN.getPosition().y);
	Player::PlayerObjects[PlayerChannel]->setFloor(Player::PlayerObjects[PlayerChannel]->getFloor() + 1);
	GUI::update();
	while (Exit == false) {
		t = clock.restart();
		
		checkEvents(win, s_event);
			
		y_velocity += gravity;
		FFN.rotate(rotationspeed * t.asSeconds());
		FFN.move(sf::Vector2f(x_velocity * t.asSeconds(), y_velocity * t.asSeconds()));

		if (FFN.getPosition().y > Cam::getdisplayheight() + 50) {
			Exit = true;
		}
			
		
		
			win.clear(sf::Color::Black);
			GUI::Draw_All(win, 0);
			Cam::drawGUI_chan(0, win, FFN);
			win.display();
			
		
		sf::sleep(sf::milliseconds(1));
	}
}

void World::A1MoveGUI(sf::RenderWindow &win, int PlayerChannel, sf::Event &s_event) {
	bool Exit = false;
	//This tells if it is done waiting.
	bool is_done_waiting = false;
	//This is how long it has been waiting since finishing the calculations.
	float c_ticks = 0;
	//This is the max number of ticks needed before ending the function.
	float max_c_ticks = 2;
	sf::Clock clock;
	sf::Time t;
	bool waiting_on_start = true;
	bool should_calculate_score = false;
	bool finished_calculating = false;
	float y_velocity = 5;
	float x_velocity = random2::randomrange(200, 300);
	int rotationspeed = random2::randomrange(200, 500);
	float gravity = 3.5;
	sf::Text FFN; //Falling Floor Number
	sf::Text TS; //Total score number.
	//This is how much score you have.
	int score = 0;
	//This is how fast it should move the score around.
	int speed_cal = 1;
	//This tells if its the first time going to the command_int = 3 section of the switch/case statement.
	bool is_first = true;
	sf::Color TSCOLOR = sf::Color::Green;
	TS.setString("Total Score: 0");
	TS.setPosition(Cam::getdisplaywidth() / 2, Cam::getdisplayheight() / 2);
	TS.setCharacterSize(30);
	TS.setFont(Font::Get_smalle());
	TS.setColor(TSCOLOR);
	//These are the ticks that are used to count the lives.
	float lc_ticks = 0;
	//This is the max number of lc_ticks needed to make a life turn into score.
	float max_lc_ticks = 1;
	bool should_blink = false;
	int command_int = 0;
	//These are the ticks for the blink animation.
	float bw_ticks = 0;
	//These are the max ticks for the blink animation.
	float max_bw_ticks = 0.5;
	//This tells if the blink is on or off.
	bool is_on = false;
	float h_ticks = 0;
	float max_h_ticks = 3;
	//These colors are used for the blinking back and forth animation.
	sf::Color f1 = sf::Color::Red;
	sf::Color f2 = sf::Color::Green;
	//This is the default color of the high score text.
	sf::Color default_Color = GUI::Texts[5].getColor();
	Scoring *SO = &Player::PlayerObjects[0]->getScoring();
	Player *PO = Player::PlayerObjects[0];
	Player::PlayerObjects[0]->getScoring().setTime(round(Player::PlayerObjects[0]->getScoring().getTime()));
	FFN.setString(GF::str(Player::PlayerObjects[PlayerChannel]->getFloor()));
	FFN.setPosition(GUI::getTextPosition_x(0) + 110, GUI::getTextPosition_y(0) + 20);
	FFN.setOrigin(16, 16);
	FFN.setCharacterSize(GUI::getTextSize(0));
	FFN.setFont(GUI::getTextFont(0));
	FFN.setColor(sf::Color::White);
	Sound::Play(5, FFN.getPosition().x, FFN.getPosition().y);
	Player::PlayerObjects[PlayerChannel]->setFloor(Player::PlayerObjects[PlayerChannel]->getFloor() + 1);
	GUI::update();
	while (Exit != true) {
		t = clock.restart();
		switch (command_int) {
		case 0: //Fading the text in.
			c_ticks += t.asSeconds();
			TSCOLOR.a = 255 * (c_ticks / max_c_ticks);
			TS.setColor(TSCOLOR);
			if (c_ticks >= max_c_ticks) {
				command_int = 1;
				TSCOLOR.a = 255;
				c_ticks = max_c_ticks;
			}
			break;
		case 1: //Putting score into the total score.
			if (SO->getScore() > speed_cal) {
				score += speed_cal;
				SO->add_score(-speed_cal);


			}
			else {
				score += SO->getScore();
				command_int = 2;

			}
			Sound::Play(68, 0, 0, random2::randomrange(1, 5));
			break;
		case 2://Putting time into the total score.
			if (SO->getTime() > speed_cal) {
				score -= speed_cal;
				SO->setTime(SO->getTime() - speed_cal);
			}
			else {
				score -= SO->getTime();
				SO->setTime(0);

				command_int = 3;

			}
			Sound::Play(68, 0, 0, random2::randomrange(1, 5));
			break;
		case 3: //Adding lives
			lc_ticks += GF::getDelta();
			if (lc_ticks >= max_lc_ticks) {
				
				if (PO->loseLife(3) == true) {
					command_int = 4;
					PO->setLife(3);

				}
				else {
					score += worth_of_life;
					Sound::Play(71, 0, 0, random2::randomrange(1, 6));
				}
				
				lc_ticks = 0;
			}
			break;
		case 4://Waiting a bit so that the player will notice if they got a high score.
			if (is_first == true) {
				if (SO->getCal_Score() > SO->get_high_score()) {
					SO->set_High_Score_Direct(score);

					should_blink = true;
				}
				else {

					should_blink = false;
				}
				is_first = false;
			}
			h_ticks += t.asSeconds();
			if (h_ticks >= max_h_ticks) {
				command_int = 5;

			}
			break;
		case 5://Fading out
			c_ticks -= t.asSeconds();
			TSCOLOR.a = 255 * (c_ticks / max_c_ticks);
			TS.setColor(TSCOLOR);

			if (c_ticks <= 0) {
				Exit = true;
			}
			break;
		}

		if (should_blink == true) {
			bw_ticks += t.asSeconds();
			if (bw_ticks >= max_bw_ticks) {
				switch (is_on) {
				case 0:
					GUI::Texts[5].setColor(f1);
					is_on = 1;
					break;
				case 1:
					GUI::Texts[5].setColor(f2);
					is_on = 0;
					break;
				}
				bw_ticks = 0;
			}
		}
	
		checkEvents(win, s_event);
		Player::PlayerObjects[0]->getScoring().setCal_Score(score);
		
		TS.setString("Total Score: " + GF::str(score));
		GUI::update();

		y_velocity += gravity;
		FFN.rotate(rotationspeed * t.asSeconds());
		FFN.move(sf::Vector2f(x_velocity * t.asSeconds(), y_velocity * t.asSeconds()));

		if (FFN.getPosition().y > Cam::getdisplayheight() + 50 && is_done_waiting == true) {
			Exit = true;
		}



		win.clear(sf::Color::Black);
		GUI::Draw_All(win, 0);
		Cam::drawGUI_chan(0, win, FFN);
		Cam::drawGUI_chan(0, win, TS);
		win.display();


		sf::sleep(sf::milliseconds(1));
	}
	GUI::Texts[5].setColor(default_Color);
}

void World::anitick(sf::Clock &clock, sf::RenderWindow &win, TileMap &TM, sf::Event &s_event) {
	
	
	//New floor fade out/in
	if (Animation == 0) {
		Player::PlayerObjects[0]->addFuel(Player::PlayerObjects[0]->get_maxFuel());
		World::LoadWorld_NextFloorAni(World::Files[newDungeon][newFloor][0], win, 0, 0, TM, s_event);
		Animation = -1;
		clock.restart();
	}
	//Credits screen
	else if (Animation == 1) {
		
		Screen_MOTHER::start(1);
		Animation = -1;
	}
	//Door entrance/exit
	else if (Animation == 2) {
		Player::PlayerObjects[0]->setXY(load_x, load_y);
		Player::PlayerObjects[0]->StandStill();
		Player::PlayerObjects[0]->SnapCam();
		LoadWorld(Files[newDungeon][newFloor][newExtra], TM, true);
		

		Animation = -1;
	}

	else if (Animation == 3) {
		Player::PlayerObjects[0]->addFuel(Player::PlayerObjects[0]->get_maxFuel());
		LoadWorld_NextFloorAni(Files[newDungeon][newFloor][newExtra], win, 1, 0, TM, s_event);
		Animation = -1;
	}
	else if (Animation == 4) {
		Player::PlayerObjects[0]->addFuel(Player::PlayerObjects[0]->get_maxFuel());
		LoadWorld_NextFloorAni(GetCurrentLobby(newFloor), win, 1, 0, TM, s_event);
		Animation = -1;
		newFile = "";
	}
	else if (Animation == 5) {
		Player::PlayerObjects[0]->addFuel(Player::PlayerObjects[0]->get_maxFuel());
		if (Player::PlayerObjects[0]->getStep() == 0) {
			Player::PlayerObjects[0]->setStep(1);
		}
		LoadWorld_NextFloorAni(GetCurrentLobby(newFloor), win, 1, 0, TM, s_event);
		Animation = -1;
		newFile = "";
		
	}
	else if (Animation == 6) {
		Player::PlayerObjects[0]->addFuel(Player::PlayerObjects[0]->get_maxFuel());
		if (Player::PlayerObjects[0]->getStep() == 1) {
			Player::PlayerObjects[0]->setStep(2);
		}
		LoadWorld_NextFloorAni(Files[newDungeon][newFloor][newExtra], win, 1, 0, TM, s_event);
		Animation = -1;
		newFile = "";
		
	}
	else if (Animation == 7) { //This is called when you finish a dungeon. It will count up the score for you.
		Player::PlayerObjects[0]->addFuel(Player::PlayerObjects[0]->get_maxFuel());
		World::LoadWorld_NextFloorAni(World::Files[newDungeon][newFloor][0], win, 2, 0, TM, s_event);
		Animation = -1;
		Player::PlayerObjects[0]->getScoring().deposit(0,Player::PlayerObjects[0]->getScoring().getCal_Score());
		Player::PlayerObjects[0]->getScoring().reset();
		clearEvent(win, s_event);
		clock.restart();
	}
	else if (Animation == 8) { //This is called when you finish a dungeon. It will count up the score for you.
		Player::PlayerObjects[0]->addFuel(Player::PlayerObjects[0]->get_maxFuel());
		World::LoadWorld_NextFloorAni(World::Files[newDungeon][newFloor][0], win, 2, 0, TM, s_event);
		Animation = -1;
		Player::PlayerObjects[0]->getScoring().deposit(1, Player::PlayerObjects[0]->getScoring().getCal_Score());
		Player::PlayerObjects[0]->getScoring().reset();
		clearEvent(win, s_event);
		clock.restart();
	}
	else if (Animation == 9) { //This is called when you finish a dungeon. It will count up the score for you.
		Player::PlayerObjects[0]->addFuel(Player::PlayerObjects[0]->get_maxFuel());
		World::LoadWorld_NextFloorAni(World::Files[newDungeon][newFloor][0], win, 2, 0, TM, s_event);
		Animation = -1;
		Player::PlayerObjects[0]->getScoring().deposit(2, Player::PlayerObjects[0]->getScoring().getCal_Score());
		Player::PlayerObjects[0]->getScoring().reset();
		clearEvent(win, s_event);
		clock.restart();
	}
	clearEvent(win, s_event);
}

void World::setFloor(int new_floor) {
	newFloor = new_floor;
}

void World::setDungeon(int new_dungeon) {
	newDungeon = new_dungeon;
}

void World::setAnimation(int new_Animation) {
	Animation = new_Animation;
}

void World::setHaze(int index) {
	momentumx = 0;
	momentumy = 0;
	ticks = 0;
	hazeindex = index;
	switch (index) {
	case -1:
		max_ticks = 3;
		Haze = Hazes[2];
		hazetype = -1;
		hx = 0;
		hy = 0;
		break;
	case 0:
		max_ticks = 3;
		
		Haze = Hazes[index];
		hazetype = 0;
		hx = -(Cam::getdisplaywidth() / 2) + 25;
		hy = -(Cam::getdisplayheight() / 2) + 60;
		break;
	case 1:
		max_ticks = 3;
		Haze = Hazes[index];
		hazetype = 0;
		hx = -(Cam::getdisplaywidth() / 2) + 25;
		hy = -(Cam::getdisplayheight() / 2) + 60;
	}
}

void World::draw(sf::RenderWindow &win) {
	if (Haze.getTexture() != nullptr) {
		
		Cam::drawGUI_chan(0, win, Haze);
	}
	
}

void World::hazetick() {
	ticks++;
	if (ticks >= max_ticks) {
		
		switch (hazetype) {
		case 0:
			
			int speed = 1;
			int x = Haze.getPosition().x + (SHazeW / 2);
			int y = Haze.getPosition().y + (SHazeH / 2);
			int cx = Cam::getdisplaywidth() / 2;
			int cy = Cam::getdisplayheight() / 2;
			if(x > cx){
				momentumx -= speed;
			}
			else if (x < cx) {
				momentumx += speed;
			}
			if (y > cy) {
				momentumy -= speed;
			}
			else if (y < cy) {
				momentumy += speed;
			}
			
			hx += momentumx;
			hy += momentumy;
			break;
		
		}
		Haze.setPosition(hx, hy);
		ticks = 0;
	}
	
}

std::string World::getSave(TileMap &TMap) {
	std::string r = "&-1&";
	r.append(":");
	r.append(std::to_string(TMap.getTextureID() - 1));
	r.append(",");
	r.append(std::to_string(hazeindex));
	r.append(",");
	r.append("0");
	r.append(",");
	r.append(std::to_string(BackSplash_MOTHER::getSave()));
	r.append(",");
	r.append(":");
	return r;
}

void World::SavePlayerFile() {
	Player::PlayerObjects[0]->SavePlayerFile(PlayerFiles[slotnum]);
}

void World::setSlotnum(int num) {
	slotnum = num;
}

void World::SetPlayerFiletoDefault(int index) {
	ofstream file;
	file.open(PlayerFiles[index], ios::out);
	file.clear();
	file << PlayerDefault;
	file.close();
}

void World::timetick(sf::RenderWindow &win, TileMap &TM) {
	if (isClockActive == true) {
		
		time -= GF::getDelta();
		if (time <= 0) {
			isClockActive = false;
			
			if (Player::PlayerObjects[0]->getFloor() > 7) {
				LoadWorld(World::Files[Player::PlayerObjects[0]->getDungeon()][7][0], TM, true);
				
			}
			else {
				LoadWorld(World::Files[Player::PlayerObjects[0]->getDungeon()][0][0], TM, true);
				
			}
			
			Player::PlayerObjects[0]->setXY(0, 0);
			Player::PlayerObjects[0]->SnapCam();
			time = 0;

		}
		GUI::update();
	}
	
}


float World::getTime() {
	return time;
}

void World::setExtra(int new_extra) {
	newExtra = new_extra;
}

void World::setLCords(int x, int y) {
	load_x = x;
	load_y = y;
	
}

void World::maintick() {
	if (should_reset_world == true) {
		Projectile::clear_all();
		ParticleSystem::destroy_all();
		Blast::clear_all();
		Flame::clear_all();
		should_reset_world = false;
	}
	switch (effect_ID) {
	case 0:
		break;
	}
}

std::string World::getCurrentWorld() {
	return CurrentWorld;
}

void World::OverwriteCurrentWorld(TileMap &TM) {
	SaveWorld(CurrentWorld, TM);
}

void World::setExitID(int new_exitID) {
	newExitID = new_exitID;
}

std::string World::GetCurrentLobby(int Floor) {
	switch (Player::PlayerObjects[0]->getStep()) {
	case 0:
		newDungeon = 0;
		return "R/World Files/Lobby/Step 0/" + Files[newDungeon][Floor][0];
	case 1:
		newDungeon = 4;
		return "R/World Files/Lobby/Step 1/" + Files[newDungeon][Floor][0];
	case 2:
		newDungeon = 5;
		return "R/World Files/Lobby/Step 2/" + Files[newDungeon][Floor][0];
	case 3:
		setDungeon(6);
		newDungeon = 6;
		return "R/World Files/Lobby/Step 3/" + Files[newDungeon][Floor][0];
	}
}

void World::setFile(const std::string &File) {
	newFile = File;
}

void World::ClearSome() {
	should_reset_world = true;
}

void World::checkEvents(sf::RenderWindow &win, sf::Event &s_event) {
	while (win.pollEvent(s_event)) {
		//Checking events
		//close requested event

		if (s_event.type == sf::Event::Closed) {
			win.close();
		}
		
		if (s_event.type == sf::Event::KeyPressed) {
			if (s_event.key.code == sf::Keyboard::D) {
				App::H_Controls[1] = true;
				App::P_Controls[1] = true;
				App::control_cache.push_back(1);
				ChoiceRTEXT::DK = true;
			}
			if (s_event.key.code == sf::Keyboard::S) {
				App::H_Controls[2] = true;
				App::P_Controls[2] = true;
				App::control_cache.push_back(2);
				ChoiceRTEXT::SK = true;

			}
			if (s_event.key.code == sf::Keyboard::A) {
				App::H_Controls[3] = true;
				App::P_Controls[3] = true;
				App::control_cache.push_back(3);
				ChoiceRTEXT::AK = true;

			}
			if (s_event.key.code == sf::Keyboard::W) {
				App::H_Controls[0] = true;
				App::P_Controls[0] = true;
				App::control_cache.push_back(0);
				ChoiceRTEXT::WK = true;

			}
			if (s_event.key.code == sf::Keyboard::Space) {
				App::HQ = true;
			}
		}

		if (s_event.type == sf::Event::KeyReleased) {
			if (s_event.key.code == sf::Keyboard::D) {
				for (unsigned int i = 0; i < App::control_cache.size(); i++) {
					if (App::control_cache[i] == 1) {
						App::control_cache.erase(App::control_cache.begin() + i);
					}
				}
				//slidemap[0] = false;
				App::H_Controls[1] = false;
			}
			if (s_event.key.code == sf::Keyboard::S) {
				for (unsigned int i = 0; i < App::control_cache.size(); i++) {
					if (App::control_cache[i] == 2) {
						App::control_cache.erase(App::control_cache.begin() + i);
					}
				}
				//slidemap[1] = false;
				App::H_Controls[2] = false;
			}
			if (s_event.key.code == sf::Keyboard::A) {
				for (unsigned int i = 0; i < App::control_cache.size(); i++) {
					if (App::control_cache[i] == 3) {
						App::control_cache.erase(App::control_cache.begin() + i);
					}
				}
				//slidemap[2] = false;
				App::H_Controls[3] = false;
			}
			if (s_event.key.code == sf::Keyboard::W) {
				for (unsigned int i = 0; i < App::control_cache.size(); i++) {
					if (App::control_cache[i] == 0) {
						App::control_cache.erase(App::control_cache.begin() + i);
					}
				}
				//slidemap[3] = false;
				App::H_Controls[0] = false;
			}
			if (Player::PlayerObjects.size() != 0) {
				if (s_event.key.code == sf::Keyboard::Space) {
					App::HQ = false;
				}
				if (s_event.key.code == sf::Keyboard::RBracket) {
					//Debug::uselastcommand(win, TM);
				}
			}
		}
	}
	
}

void World::clearEvent(sf::RenderWindow &win, sf::Event &s_event) {
	s_event.type = sf::Event::KeyPressed;
}