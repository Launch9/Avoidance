#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Cam.h"
#include "TileMap.h"
#include "ParticleSystem.h"
#include "MusicPlayer.h"
#include "GUI.h"
class GUI;
class World
{

private:
	friend GUI;
	//This is a MusicPlayer, it helps determine and play the songs.
	static MusicPlayer World::MP;
	//This boolean tells the computer whether or not the clock is active.
	static bool World::isClockActive;
	//This is the current world string that is being used.
	static std::string World::CurrentWorld;
	//This is the timer to tell you how much time you have left in that dungeon.
	static float World::time;
	//This holds the string of what should be put on a delete player file.
	static std::string World::PlayerDefault;
	//This tells what play slot is being selected.
	static int World::slotnum;
	//This tells the haze how fast it is moving.
	static int World::momentumx;
	static int World::momentumy;
	//This decides whether or not the class is ready to animate something and what.
	static int World::Animation;
	//This is the interger that tells what effect the world has. Rain, snow, clouds.
	static int World::effect_ID;
	//This tells what to load.
	static int World::newFloor;
	static int World::newDungeon;
	static int World::newExtra;
	static int World::newExitID; //This tells you where to spawn into the world when entering the world
	static std::string World::newFile; //This tells which file to load up.
	//This tells if the world needs to be reset or not
	static bool World::should_reset_world;
	//This tells the world where to spawn you in when loading the world in and animation.
	static int World::load_x;
	static int World::load_y;
	//This is the front haze if you want to add one.
	static sf::Sprite World::Haze;
	//These are the amount of ticks that need to be reached to move the haze.
	static int World::max_ticks;
	//These are the ticks.
	static int World::ticks;
	//These are the standard sizes for the haze sprite.
	static int World::SHazeW;
	static int World::SHazeH;
	//This will check the window's basic events, such as closing it's self.
	static void World::checkEvents(sf::RenderWindow &win, sf::Event &s_event);
	//This is a texture object that is suppost to be used to copy the window contents onto it and be drawn in a seperate rectangle.
	static sf::Texture World::preRender_tex;
	//This is a rectangleshape that is meant to be attached to the preRender and drawn.
	static sf::RectangleShape World::preRender;
	//This is animation zero.
	//This animation is used when you want the screen to fade to black, then appear back.
	//THIS FUNCTION CLEARS AND DISPLAYS THE SCREEN!
	//There is an event loop within this function.
	static void World::A0FadeOut(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event);
	//This animation Fades everything in.
	//There is an event loop within this function.
	static void World::A0FadeIn(sf::RenderWindow &win, TileMap &TM, sf::Event &s_event);
	//This animation Moves the GUI for the NextFloorAnimation.
	//There is an event loop within this function.
	static void World::A0MoveGUI(sf::RenderWindow &win, int PlayerChannel, sf::Event &s_event);
	//This animation Moves the GUI for the NextFloorAnimation and checks the high score.
	//There is an event loop within this function.
	static void World::A1MoveGUI(sf::RenderWindow &win, int PlayerChannel, sf::Event &s_event);
	//This is a vector that holds all the haze sprites.
	static std::vector<sf::Sprite> World::Hazes;
	//This is a integer to determine what haze type it is.
	static int World::hazetype;
	//These are the cordinates of the haze sprite.
	static int World::hx;
	static int World::hy;
	//This tells whats the basic main index of the haze.
	static int World::hazeindex; //Used for saving and such.
	static sf::Texture World::wtex; //This is used for everything that is not the player.
	//This function clears the event object and makes it ready for the next use in avoidence.cpp.
	static void clearEvent(sf::RenderWindow &win, sf::Event &s_event);
	//This is the reserve control_cache.
	//Once an animation is done, it is set to the real cache.
	//This is to prevent weird control holdings, when you press a button during loading.
	static std::vector<int> World::r_c_c;
public:
	//These are for P_Switchs and other things in the world.
	//They tell what has been actived or what not.
	static std::vector<bool> World::Switches;
	//First vector = Dungeon
	//Second vector = Floors
	static std::vector<std::vector<std::vector<std::string>>> World::Files;
	static std::vector <std::string> World::PlayerFiles;
	//This loads the world from a file up.
	//This deletes the world being played at the moment.
	static void LoadWorld(std::string FileLocation, TileMap &Tmap, bool Clear);
	//This function loads the world as well as giving an animation to make it smooth and pretty.
	//The animation is done in a different function. To make an animation refer to this class please.
	static void LoadWorld_NextFloorAni(std::string FileLocation, sf::RenderWindow &win, int Animation, int PlayerChan, TileMap &TM, sf::Event &s_event);
	//This saves the current world to the given file to be loaded up later.
	static void SaveWorld(std::string FileLocation, TileMap &TMap);
	//This clears the world of all the tiles.
	static void ClearWorld();
	//This clears the world of non-lasting things.
	//Such as flames, blasts, projectiles, particles.
	static void ClearSome();
	//This makes all the world files and hazes.
	//GIVE THIS FUNCTION THE HAZE TEXTURE!-=-=-=-=-=-=-=-=-=-=-
	static void init(sf::Texture &HazeTexture);
	static void W1();
	//This is a function that checks to see if the world is ready to shift to the next floor or dungeon.
	//Will reset clock after animation has been finished.
	
	static void anitick(sf::Clock &clock, sf::RenderWindow &win, TileMap &TM, sf::Event &s_event);
	//This is a function that does the ticking for all the special effects of the current map.
	static void maintick();
	//This is for the time that is being recorded during your dungeon run.
	static void timetick(sf::RenderWindow &win, TileMap &TM);
	//This is a function that changes the floor loading variable.
	static void setFloor(int new_floor);
	//This is a function that changes the dungeon loading variable.
	static void setDungeon(int new_dungeon);
	//This is a function that changes the extra loading variable.
	static void setExtra(int new_extra);
	//This is a function that changes what file should be loaded when doing certain animations.
	static void setFile(const std::string &File);
	//This is a function that changes the ExitID loading variable.
	static void setExitID(int new_exitID);
	//This is a function that changes the animation loading variable.
	//Changing this animation will load a new world once the program has reached the tick function in this class.
	//Changing this to -1 will make nothing happen.
	static void setAnimation(int new_Animation);
	//This is for drawing hazes and such.
	static void draw(sf::RenderWindow &win);
	//This is for animating the haze.
	static void hazetick();
	//This is a function that tells the world what kind of front haze to use.
	static void setHaze(int index);
	//This gets the save string.
	static std::string getSave(TileMap &TMap);
	//This saves the player's file to the one already there.
	static void SavePlayerFile();
	//This sets the slot number.
	static void setSlotnum(int num);
	//This sets a player's file back to the default.
	static void SetPlayerFiletoDefault(int index);
	//This gets the dungeon time.
	static float getTime();
	//This sets the load_x and load_y cordinates.
	static void setLCords(int x, int y);
	//This gets the CurrentWorld file location and name in a string.
	static std::string getCurrentWorld();
	//This overwrites the world that was last loaded.
	static void OverwriteCurrentWorld(TileMap &TM);
	//This function gives you the entire directory to the file chosen in the R/World Files/Lobby/????/????.
	//The File_within is the last file name loaded up.
	//The second last one is dependent on how many dungeons the player has gone through.
	//These purpose of this function is to assist in the location of the file within the Step0,Step1, and so on folders.
	static std::string GetCurrentLobby(int Floor);

};

