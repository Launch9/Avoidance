#pragma once
#include "Sound.h"
#include "Player.h"
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <SFML/Graphics/Color.hpp>
#include "Temporarytxt.h"
#include "Wall.h"
#include "Shop.h"

class Sound
{
private:
	//This vector holds all the sound buffers used to determine what sound needs to be played.
	static std::vector<sf::SoundBuffer> Sound::SoundBuffers;
	//This holds the Sound objects that will be reused many times.
	//These are never deleted!
	//It contains 32 channels!
	static std::vector<sf::Sound> Sound::Channel;
public:
	
	//This gets the SoundBuffer that you want to use on a sound created in your class.
	//Use this if you want to make your own sound object not including this class.
	//YOU MAY NOT MODIFY THE SOUNDBUFFER RETURNED BY THIS FUNCTION. Its const.
	static const sf::SoundBuffer& GetSoundBuffer(int index);
	//Setting all the sounds up.
	static void init();
	//Use this to play a sound.
	static void Play(int SoundID, int x_pos = 0, int y_pos = 0, float pitch = 1, float attenuation = 1, float mindistance = 1);
	//Use this to play a sound that is given to the function.
	//This function will not play the sound if it is already being played, thus, allowing you to play through the entire thing each time.
	static void PlayIF(sf::Sound &Sound);
};

