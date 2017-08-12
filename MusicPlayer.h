#pragma once
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
/*This class is here to give access to some static variables, and give organization to playing songs.*/
class MusicPlayer
{
	//This tells if the music should be playing or not.
	static bool MusicPlayer::should_play_music;
	//This is the static object that is currently playing music.
	static sf::Music MusicPlayer::song;
	//This is the id of the song that is currently playing.
	static int MusicPlayer::song_ID;
	//These are strings that direct that song object on what audio file to load.
	static std::vector<std::string> MusicPlayer::saved_tracks;
public:
	/*This class is here to give access to some static variables, and give organization to playing songs.*/
	MusicPlayer();

	~MusicPlayer();
	//This will play a song that has been initialized at the start of the program.
	//It will overwrite another song that might be currently playing.
	//track = 0 = D1_music.wav
	void play_track(int track);
	//This will turn all the music off.
	//No music can be played when this is not active.
	void setMusic_On(bool TF);
	//This will return true if the music is on.
	//Otherwise, it will return false.
	bool isMusic_On();
	//This will toggle the music on/off boolean.
	//If it was on before the call to this function, it would now be off.
	void toggleMusic_On();
	//This gets the track ID.
	int get_track_ID();
	//This initializes the songs, so that they can be played later.
	static void init();
};

