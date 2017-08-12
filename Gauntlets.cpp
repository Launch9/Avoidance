#include "stdafx.h"
#include "Gauntlets.h"
#include "Sound.h"
#include "GF.h"
#include "Projectile.h"
#include "random2.h"
std::vector<sf::Sprite> Gauntlets::icons;
std::vector<ParticleSettings> Gauntlets::Settings;
std::vector<ParticleSettings> Gauntlets::Power_Settings;
void Gauntlets::PlaySound(const int &Gauntletid, const float &x, const float &y) {
	switch (Gauntletid) {
	case 0:
		Sound::Play(12, x, y, random2::randomrange(1, 5), 0.0005, 2);
		break;
	case 1:
		Sound::Play(13, x, y, random2::randomrange(1, 5), 0.0005, 2);
		break;
	case 2:
		Sound::Play(39, x, y, random2::randomrange(1, 5), 0.0005, 2);
		break;
	}
}

void Gauntlets::Shoot(const int &Gauntletid, float x, float y, const int &direction, bool should_have_particles) {
	
	switch (direction) {
	case 2:
		y += 32;
		break;
	case 1:
		x += 32;
		break;
	}
	switch (Gauntletid) {
	case 0:
		Projectile(0, x, y, direction, should_have_particles);
		break;
	case 1:
		Projectile(1, x, y, direction, should_have_particles);
		break;
	case 2:
		Projectile(5, x, y, direction, should_have_particles);
		break;
	case 3:
		Projectile(2, x, y, direction, should_have_particles);
	}
}


sf::Sprite Gauntlets::GetIcon(const int &Gauntletid) {
	return icons[Gauntletid];
}

ParticleSettings Gauntlets::GetParticleSettings(const int &Gauntletid) {
	return Settings[Gauntletid];
}
void Gauntlets::init(sf::Texture &tex) {
	sf::Sprite s0;
	s0.setTexture(tex);
	s0.setTextureRect(sf::IntRect(64, 384 - 96, 32, 32));
	sf::Sprite s1;
	s1.setTexture(tex);
	s1.setTextureRect(sf::IntRect(64, 384 - 64, 32, 32));
	sf::Sprite s2;
	s2.setTexture(tex);
	s2.setTextureRect(sf::IntRect(64, 384, 32, 32));
	icons = { s0,s1,s2 };
	//Particle settings-=-
	ParticleSettings f(0, 0, 0.5, 50, 4, 1); 
	f.color = sf::Color::Blue;
	f.ac1 = 0; f.ac2 = 360; 
	ParticleSettings f1(0, 0, 0.5, 50, 4, 1);
	f1.color = sf::Color::Magenta;
	f1.ac1 = 0; f1.ac2 = 360;
	ParticleSettings f2(0, 0, 0.5, 50, 4, 1);
	f2.color = sf::Color::Yellow;
	f2.ac1 = 0; f2.ac2 = 360;
	ParticleSettings p;
	p.color = sf::Color::Blue;
	p.max_speed = 2;
	p.num_of_particle = 500;
	p.out_type = 0;
	p.time_to_last = 4;
	p.ac1 = 0; p.ac2 = 360;
	ParticleSettings p1;
	p1.color = sf::Color::Magenta;
	p1.max_speed = 2;
	p1.num_of_particle = 500;
	p1.out_type = 0;
	p1.time_to_last = 4;
	p1.ac1 = 0; p1.ac2 = 360;
	ParticleSettings p2;
	p2.color = sf::Color::Yellow;
	p2.max_speed = 2;
	p2.num_of_particle = 500;
	p2.out_type = 0;
	p2.time_to_last = 4;
	p2.ac1 = 0; p2.ac2 = 360;
	ParticleSettings f3;
	f3.color = sf::Color::Green;
	f3.max_speed = 2;
	f3.num_of_particle = 50;
	f3.out_type = 1;
	f3.time_to_last = 4;
	f3.ac1 = 0; f3.ac2 = 360;
	ParticleSettings p3;
	p3.color = sf::Color::Green;
	p3.max_speed = 2;
	p3.num_of_particle = 500;
	p3.out_type = 1;
	p3.time_to_last = 4;
	p3.ac1 = 0; f3.ac2 = 360;
	
	Settings = { f,f1,f2,f3 };
	Power_Settings = { p,p1,p2,p3 };
	
	
}

int Gauntlets::getFuel(const int &Gauntletid) {
	switch (Gauntletid) {
	case 0:
		return 5;
		break;
	case 1:
		return 10;
		break;
	case 2:
		return 5;
		break;
	}
}

void Gauntlets::Shoot_with_particles(int Gauntletid, float x, float y, int direction, float length_of_arc, bool should_have_particles) {
	ParticleSettings Particle_setting;
	
	switch (Gauntletid) {
	case 0:
		Particle_setting = Settings[0];
		break;
	case 1:
		Particle_setting = Settings[1];
		break;
	case 2:
		Particle_setting = Settings[3];
		break;
	default:
		std::cout << "Forgot to put a particle setting for the gauntlet you created! Gauntlets.cpp" << std::endl;
		throw("error");
	}
	
	switch (direction) {
	case 1: //direction is right
		Particle_setting.x = x + 32;
		Particle_setting.y = y + 16;
		Particle_setting.ac1 = -(length_of_arc / 2);
		Particle_setting.ac2 = length_of_arc;
		break;
	case 2: //direction is down
		Particle_setting.x = x + 16;
		Particle_setting.y = y + 32;
		Particle_setting.ac1 = 90 + (-(length_of_arc / 2));
		Particle_setting.ac2 = length_of_arc;
		break;
	case 3: //direction is left
		Particle_setting.x = x;
		Particle_setting.y = y + 16;
		Particle_setting.ac1 = 180 + (-(length_of_arc / 2));
		Particle_setting.ac2 = length_of_arc;
		break;
	case 0: //direction is up
		Particle_setting.x = x + 16;
		Particle_setting.y = y;
		Particle_setting.ac1 = 270 + (-(length_of_arc / 2));
		Particle_setting.ac2 = length_of_arc;
		break;

	}
	ParticleSystem::create(Particle_setting);
	Shoot(Gauntletid, x, y, direction, should_have_particles);
}

void Gauntlets::Shoot_Power(int Gauntletid, float x, float y, int direction) {
	int length_of_arc = 100;
	ParticleSettings Particle_setting;
	switch (Gauntletid) {
	case 0:
		Particle_setting = Power_Settings[0];
		break;
	case 1:
		Particle_setting = Power_Settings[1];
		break;
	case 2:
		Particle_setting = Power_Settings[3];
		break;
	default:
		std::cout << "Forgot to put a particle setting for the gauntlet you created! Gauntlets.cpp" << std::endl;
		throw("error");
	}
	

	switch (direction) {
	case 1: //direction is right
		Particle_setting.x = x + 32;
		Particle_setting.y = y + 16;
		Particle_setting.ac1 = -(length_of_arc / 2);
		Particle_setting.ac2 = length_of_arc;
		break;
	case 2: //direction is down
		Particle_setting.x = x + 16;
		Particle_setting.y = y + 32;
		Particle_setting.ac1 = 90 + (-(length_of_arc / 2));
		Particle_setting.ac2 = length_of_arc;
		break;
	case 3: //direction is left
		Particle_setting.x = x;
		Particle_setting.y = y + 16;
		Particle_setting.ac1 = 180 + (-(length_of_arc / 2));
		Particle_setting.ac2 = length_of_arc;
		break;
	case 0: //direction is up
		Particle_setting.x = x + 16;
		Particle_setting.y = y;
		Particle_setting.ac1 = 270 + (-(length_of_arc / 2));
		Particle_setting.ac2 = length_of_arc;
		break;

	}
	ParticleSystem::create(Particle_setting);
	switch (direction) {
	case 2:
		y += 32;
		break;
	case 1:
		x += 32;
		break;
	}
	switch (Gauntletid) {
	case 0:
		Projectile(3, x, y, direction, false);
		break;
	case 1:
		Projectile(4, x, y, direction, false);
		break;
	case 2:
		Projectile(6, x, y, direction, false);
		break;
	case 3:
		Projectile(6, x, y, direction, false);
		break;
	}
	
}

void Gauntlets::PlayPowerSound(int Gauntletid, float x, float y) {
	switch (Gauntletid) {
	case 0:
		Sound::Play(35, x, y, random2::randomrange(1, 5));
		break;
	case 1:
		Sound::Play(36, x, y, random2::randomrange(1, 5));
		break;
	case 2:
		Sound::Play(49, x, y, random2::randomrange(1, 5));
		break;
	}
}