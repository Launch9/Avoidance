#pragma once
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Music
{
private:
	
	//This is the integer that contains the index of the music you wanted.
	int index = 0;
	//This is the sf::Music object that this Music object contains.
	sf::Music m;
public:
	
	
	//WARNING::You must initilize the object before using any other function on it.
	//Call .init(songindex) to initilize your object.
	//Please only call it once.
	Music();
	//This function intitiates the sf::music object in the your object.
	//ONLY CALL THIS FUNCTION ONCE!
	void init(int songindex);
	//This 
	void stop();
	//This function will play the 
	void play(int track);
	//This function will pause the object's song.
	void pause();
	//This function will start the song from the start.
	void back();
	//This function will change the pitch of the song.
	void setpitch(float pitch);
	//This function will change the volume of the song.
	void setvolume(float volume);
	//This function will change wether or not the song loops or not.
	void setloop(bool TF);
	//This function sets the position of the song.
	void setposition(float x, float y, float z);
};

