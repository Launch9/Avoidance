#include "stdafx.h"
#include "MusicPlayer.h"
#include <iostream>
sf::Music MusicPlayer::song;
std::vector<std::string> MusicPlayer::saved_tracks;
int MusicPlayer::song_ID;
bool MusicPlayer::should_play_music;
MusicPlayer::MusicPlayer()
{
}


MusicPlayer::~MusicPlayer()
{
}

void MusicPlayer::play_track(int track) {
	
	song_ID = track;
	
	if (!song.openFromFile(saved_tracks[track])) {
		std::cout << "Failed to load " << saved_tracks[track] << " in MusicPlayer.cpp." << std::endl;
		throw("error");
	}
	song.setVolume(50);

	if (should_play_music == true) {
		song.play();
	}
	
}

void MusicPlayer::init() {
	song.setVolume(50);
	should_play_music = true;
	song.setLoop(true);
	saved_tracks = { "R/Music/D1_music.wav", "R/Music/Dungeon_Enter_Theme.wav", "R/Music/Lobby_Theme.wav", "R/Music/D2_music.wav", "R/Music/D3_music.wav", "R/Music/Credits_Music.wav"};
}

int MusicPlayer::get_track_ID() {
	return song_ID;
}

//This will turn all the music off.
//No music can be played when this is not active.
void MusicPlayer::setMusic_On(bool TF) {
	should_play_music = TF;
	switch (TF) {
	case 0: //False; turning music off.
		song.pause();
		break;
	case 1:
		song.play();
	}
	
}

bool MusicPlayer::isMusic_On() {
	return should_play_music;
}

void MusicPlayer::toggleMusic_On() {
	switch (should_play_music) {
	case 0:
		setMusic_On(true);
		break;
	case 1:
		setMusic_On(false);
	}
}