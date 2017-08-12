#include "stdafx.h"
#include "Music.h"
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


Music::Music() {
	index = -1;
}

void Music::init(int songindex) {
	index = songindex;
	switch (songindex) {
	
	case 0:
		//Loading up Europa music file.
		if (!m.openFromFile("R/Music/Europa.wav")) {
			throw("Music class opening from file error. index 0, Europa.wav");
		}
		break;
	case 1:
		//Loading up Project 12 music file.
		if (!m.openFromFile("R/Music/Project 12.wav")) {
			throw("Music class opening from file error, index 1, Project 12.wav");
		}
		break;
	case 2:
		//Loading up Project 4 music file.
		if (!m.openFromFile("R/Music/Project 4.wav")) {
			throw("Music class opening from file error, index 2, Project 4.wav");
		}
	}
	
	
	

}

void Music::play(int track) {
	if (m.getStatus() != 2) {
		m.play();
	}
}
void Music::pause() {
	m.pause();
}
void Music::back() {
	bool p = false;
	
	if (m.getStatus() == 2) {
		p = true;
	}
	m.stop();

	if (p = true) {
		m.play();
	}
	
}
void Music::setpitch(float pitch) {
	m.setPitch(pitch);
}
void Music::setvolume(float volume) {
	m.setVolume(volume);
}
void Music::setloop(bool TF) {
	m.setLoop(TF);
}
void Music::setposition(float x, float y, float z) {
	m.setPosition(x, y, z);
}

