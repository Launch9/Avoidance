#include "stdafx.h"
#include "Sound.h"
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <mutex>
std::mutex m;
#define NumberOfChannels 32
//Setting up static variables for use in the .cpp file.
std::vector<sf::SoundBuffer> Sound::SoundBuffers;
std::vector<sf::Sound> Sound::Channel;
void Sound::init() {
	sf::SoundBuffer b0;
	if (!b0.loadFromFile("R/Game Sounds/choice_tick.wav")) {
		throw ("Sound Loading error b1");
	}
	sf::SoundBuffer b1;
	if (!b1.loadFromFile("R/Game Sounds/SlidingSound.wav")) {
		throw("Sound Loading error b1");
	}
	sf::SoundBuffer b2;
	if (!b2.loadFromFile("R/Game Sounds/WallCollisionSound.wav")) {
		throw("Sound Loading error b2");
	}
	sf::SoundBuffer b3;
	if (!b3.loadFromFile("R/Game Sounds/PlayerDieSound.wav")) {
		throw ("Sound Loading error b3");
	}
	sf::SoundBuffer b4;
	if (!b4.loadFromFile("R/Game Sounds/Step Sound.wav")) {
		throw("Sound Loading error b4");
	}
	sf::SoundBuffer b5;
	if (!b5.loadFromFile("R/Game Sounds/NumFallSound.wav")) {
		throw("Sound Loading error b5");
	}
	sf::SoundBuffer b6;
	if (!b6.loadFromFile("R/Game Sounds/Laser Sound.wav")) {
		throw ("Sound Loading error b6");
	}
	sf::SoundBuffer b7;
	if (!b7.loadFromFile("R/Game Sounds/Electro Chainsaw.wav")) {
		throw("Sound Loading error b7");
	}
	sf::SoundBuffer b8;
	if (!b8.loadFromFile("R/Game Sounds/HomingSkullSound.wav")) {
		throw("Sound Loading error b8");
	}
	sf::SoundBuffer b9;
	if (!b9.loadFromFile("R/Game Sounds/Save Sound.wav")) {
		throw("Sound Loading error b9");
	}
	sf::SoundBuffer b10;
	if (!b10.loadFromFile("R/Game Sounds/Door_Open.wav")) {
		throw("Sound Loading error b10");
	}
	sf::SoundBuffer b11;
	if (!b11.loadFromFile("R/Game Sounds/CornerCollision.wav")) {
		throw("Sound Loading error b11");
	}
	sf::SoundBuffer b12;
	if (!b12.loadFromFile("R/Game Sounds/BulletShot0.wav")) {
		throw("Sound Loading error b12");
	}
	sf::SoundBuffer b13;
	if (!b13.loadFromFile("R/Game Sounds/BulletShot1.wav")) {
		throw("Sound Loading error b13");
	}
	sf::SoundBuffer b14;
	if (!b14.loadFromFile("R/Game Sounds/Seal_Open_Sound.wav")) {
		throw("Sound Loading error b14");
	}
	sf::SoundBuffer b15;
	if (!b15.loadFromFile("R/Game Sounds/Stair_Sound.wav")) {
		throw("Sound Loading error b15");
	}
	sf::SoundBuffer b16;
	if (!b16.loadFromFile("R/Game Sounds/Teleporter_Sound.wav")) {
		throw("Sound Loading error b16");
	}
	sf::SoundBuffer b17;
	if (!b17.loadFromFile("R/Game Sounds/RTile_Sound.wav")) {
		throw("Sound Loading error b17");
	}
	sf::SoundBuffer b18;
	if (!b18.loadFromFile("R/Game Sounds/PTile_Sound.wav")) {
		throw("Sound Loading error b18");
	}
	sf::SoundBuffer b19;
	if (!b19.loadFromFile("R/Game Sounds/Corner_Bounce_Sound.wav")) {
		throw("Sound Loading error b19");
	}
	sf::SoundBuffer b20;
	if (!b20.loadFromFile("R/Game Sounds/Change_Gauntlet_Sound.wav")) {
		throw("Sound Loading error b20");
	}
	sf::SoundBuffer b21;
	if (!b21.loadFromFile("R/Game Sounds/Chest_Open_Sound.wav")) {
		throw("Sound Loading error b21");
	}
	sf::SoundBuffer b22;
	if (!b22.loadFromFile("R/Game Sounds/Out_of_Fuel_Sound.wav")) {
		throw("Sound Loading error b22");
	}
	sf::SoundBuffer b23;
	if (!b23.loadFromFile("R/Game Sounds/Shield_Collision_Sound.wav")) {
		throw("Sound Loading error b23");
	}
	sf::SoundBuffer b24;
	if (!b24.loadFromFile("R/Game Sounds/Shield_Damage_Sound.wav")) {
		throw("Sound Loading error b24");
	}
	sf::SoundBuffer b25;
	if (!b25.loadFromFile("R/Game Sounds/Shielder_Die_Sound.wav")) {
		throw("Sound Loading error b25");
	}
	sf::SoundBuffer b26;
	if (!b26.loadFromFile("R/Game Sounds/Mining_Sound.wav")) {
		throw("Sound Loading error b26");
	}
	sf::SoundBuffer b27;
	if (!b27.loadFromFile("R/Game Sounds/Dragon_Hurt_Sound.wav")) {
		throw("Sound Loading error b27");
	}
	sf::SoundBuffer b28;
	if (!b28.loadFromFile("R/Game Sounds/Dragon_Defeat_Sound.wav")) {
		throw("Sound Loading error b28");
	}
	sf::SoundBuffer b29;
	if (!b29.loadFromFile("R/Game Sounds/Break_Spawner_Die_Sound.wav")) {
		throw("Sound Loading error b29");
	}
	sf::SoundBuffer b30;
	if (!b30.loadFromFile("R/Game Sounds/Break_Spawner_Shot_Sound.wav")) {
		throw("Sound Loading error b30");
	}
	sf::SoundBuffer b31;
	if (!b31.loadFromFile("R/Game Sounds/Select.wav")) {
		throw("Sound Loading error b31");
	}
	sf::SoundBuffer b32;
	if (!b32.loadFromFile("R/Game Sounds/Slime_Die_Sound.wav")) {
		throw("Sound Loading error b32");
	}
	sf::SoundBuffer b33;
	if (!b33.loadFromFile("R/Game Sounds/Slime_Hurt_Sound.wav")) {
		throw("Sound Loading error b33");
	}
	sf::SoundBuffer b34;
	if (!b34.loadFromFile("R/Game Sounds/Slime_Move_Sound.wav")) {
		throw("Sound Loading error b34");
	}
	sf::SoundBuffer b35;
	if (!b35.loadFromFile("R/Game Sounds/Mega_Shoot_Blue_Sound.wav")) {
		throw("Sound loading error b35");
	}
	sf::SoundBuffer b36;
	if (!b36.loadFromFile("R/Game Sounds/Mega_Shoot_Purple_Sound.wav")) {
		throw("Sound loading error b36");
	}
	sf::SoundBuffer b37;
	if (!b37.loadFromFile("R/Game Sounds/Mega_Shot_Ready_Sound.wav")) {
		throw("Sound loading error b37");
	}
	sf::SoundBuffer b38;
	if (!b38.loadFromFile("R/Game Sounds/Mega_Shot_UnReady_Sound.wav")) {
		throw("Sound loading error b38");
	}
	sf::SoundBuffer b39;
	if (!b39.loadFromFile("R/Game Sounds/BulletShot2.wav")) {
		throw("Sound loading error b39");
	}
	sf::SoundBuffer b40;
	if (!b40.loadFromFile("R/Game Sounds/BulletTurn_Green.wav")) {
		throw("Sound loading error b40");
	}
	sf::SoundBuffer b41;
	if (!b41.loadFromFile("R/Game Sounds/Dino_Die_Sound.wav")) {
		throw("Sound loading error b41");
	}
	sf::SoundBuffer b42;
	if (!b42.loadFromFile("R/Game Sounds/Dino_Hurt_Sound.wav")) {
		throw("Sound loading error b42");
	}
	sf::SoundBuffer b43;
	if (!b43.loadFromFile("R/Game Sounds/Flame_Sound.wav")) {
		throw("Sound loading error b43");
	}
	sf::SoundBuffer b44;
	if (!b44.loadFromFile("R/Game Sounds/Bounce_Sound.wav")) {
		throw("Sound loading error b44");
	}
	sf::SoundBuffer b45;
	if (!b45.loadFromFile("R/Game Sounds/Squisher_die_sound.wav")) {
		throw("Sound loading error b45");
	}
	sf::SoundBuffer b46;
	if (!b46.loadFromFile("R/Game Sounds/Squisher_move.wav")) {
		throw("Sound loading error b46");
	}
	sf::SoundBuffer b47;
	if (!b47.loadFromFile("R/Game Sounds/W_bomb_explode.wav")) {
		throw("Sound loading error b47");
	}
	sf::SoundBuffer b48;
	if (!b48.loadFromFile("R/Game Sounds/P_Switch_Timer.wav")) {
		throw("Sound loading error b48");
	}
	sf::SoundBuffer b49;
	if (!b49.loadFromFile("R/Game Sounds/Mega_Shoot_Green_Sound.wav")) {
		throw("Sound loading error b49");
	}
	sf::SoundBuffer b50;
	if (!b50.loadFromFile("R/Game Sounds/EBM_Die.wav")) {
		throw("Sound loading error b50");
	}
	sf::SoundBuffer b51;
	if (!b51.loadFromFile("R/Game Sounds/EBM_Shield.wav")) {
		throw("Sound loading error b51");
	}
	sf::SoundBuffer b52;
	if (!b52.loadFromFile("R/Game Sounds/EyeBall_Die.wav")) {
		throw("Sound loading error b52");
	}
	sf::SoundBuffer b53;
	if (!b53.loadFromFile("R/Game Sounds/EyeBall_MAIN_Charge.wav")) {
		throw("Sound loading error b53");
	}
	sf::SoundBuffer b54;
	if (!b54.loadFromFile("R/Game Sounds/EyeBall_MAIN_Die.wav")) {
		throw("Sound loading error b54");
	}
	sf::SoundBuffer b55;
	if (!b55.loadFromFile("R/Game Sounds/EyeBall_MAIN_Shoot.wav")) {
		throw("Sound loading error b55");
	}
	sf::SoundBuffer b56;
	if (!b56.loadFromFile("R/Game Sounds/EyeBall_MAIN_Hurt.wav")) {
		throw("Sound loading error b56");
	}
	sf::SoundBuffer b57;
	if (!b57.loadFromFile("R/Game Sounds/Elevator.wav")) {
		throw("Sound loading error b57");
	}
	sf::SoundBuffer b58;
	if (!b58.loadFromFile("R/Game Sounds/Big_Squisher_Sound.wav")) {
		throw("Sound loading error b58");
	}

	sf::SoundBuffer b59;
	if (!b59.loadFromFile("R/Game Sounds/Com_Hand_Launch.wav")) {
		throw("Sound loading error b58");
	}
	sf::SoundBuffer b60;
	if (!b60.loadFromFile("R/Game Sounds/Com_Hand_Blink.wav")) {
		throw("Sound loading error b58");
	}
	sf::SoundBuffer b61;
	if (!b61.loadFromFile("R/Game Sounds/Com_Hand_Hurt.wav")) {
		throw("Sound loading error b58");
	}
	sf::SoundBuffer b62;
	if (!b62.loadFromFile("R/Game Sounds/Com_Hand_Die.wav")) {
		throw("Sound loading error b58");
	}
	sf::SoundBuffer b63;
	if (!b63.loadFromFile("R/Game Sounds/Com_MAIN_Die.wav")) {
		throw("Sound loading error b58");
	}
	sf::SoundBuffer b64;
	if (!b64.loadFromFile("R/Game Sounds/Com_MAIN_Hurt.wav")) {
		throw("Sound loading error b58");
	}
	sf::SoundBuffer b65;
	if (!b65.loadFromFile("R/Game Sounds/Com_MAIN_Jaw.wav")) {
		throw("Sound loading error b58");
	}
	sf::SoundBuffer b66;
	if (!b66.loadFromFile("R/Game Sounds/NPC_Spawner_Die.wav")) {
		throw("Sound loading error b58");
	}
	sf::SoundBuffer b67;
	if (!b67.loadFromFile("R/Game Sounds/NPC_Spawner_Hurt.wav")) {
		throw("Sound loading error b58");
	}
	sf::SoundBuffer b68;
	if (!b68.loadFromFile("R/Game Sounds/Dialogue_skip.wav")) {
		throw("Sound loading error b58");
	}
	sf::SoundBuffer b69;
	if (!b69.loadFromFile("R/Game Sounds/Score_add.wav")) {
		throw("Sound loading error b58");
	}
	sf::SoundBuffer b70;
	if (!b70.loadFromFile("R/Game Sounds/Dragon_Drop_in.wav")) {
		throw("Sound loading error b70");
	}
	sf::SoundBuffer b71;
	if (!b71.loadFromFile("R/Game Sounds/Scoring_Life_Count.wav")) {
		throw("Sound loading error b71");
	}
	
	

	SoundBuffers = { b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16,b17,b18,b19,b20,b21,b22,b23,b24,b25,b26,b27,b28,b29,b30,b31,b32,b33,b34,b35,b36,b37,b38
	,b39,b40,b41,b42,b43,b44,b45,b46,b47,b48,b49,b50,b51,b52,b53,b54,b55,b56,b57,b58,b59,b60,b61,b62,b63,b64,b65,b66,b67,b68,b69,b70,
	b71};

	//Making the channels.
	for (unsigned int i = 0; i < 100; i++) {
		sf::Sound s;
		Channel.push_back(s);
	}

}
void Sound::Play(int SoundID, int x_pos, int y_pos, float pitch, float attenuation, float mindistance) {
	m.lock();
	for (unsigned int i = 0; i < Channel.size(); i++) {
		//If a channel is not playing anything.
		if (Channel[i].getStatus() == 0) {
			//Setting the channel's sound object to all the given parameters.
			Channel[i].setBuffer(SoundBuffers[SoundID]);
			Channel[i].setAttenuation(attenuation);
			Channel[i].setMinDistance(mindistance);
			Channel[i].setPitch(pitch);
			Channel[i].setPosition(x_pos, y_pos, 0);
			//Playing the sound.
			Channel[i].play();
			//Then leaving the function to go on with the program.
			break;
		}
	}
	m.unlock();
}

const sf::SoundBuffer& Sound::GetSoundBuffer(int index) {
	return SoundBuffers[index];
}

void Sound::PlayIF(sf::Sound &Sound) {
	if (Sound.getStatus() != 2) {
		Sound.play();
	}
}