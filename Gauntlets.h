#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "ParticleSettings.h"
#include "ParticleSystem.h"
class Gauntlets
{
private:
	static std::vector<sf::Sprite> Gauntlets::icons;
	static std::vector<ParticleSettings> Gauntlets::Settings;
	static std::vector<ParticleSettings> Gauntlets::Power_Settings;
public:
	//This plays the sound of the gauntlet id, it will not make a projectile object for you.
	static void PlaySound(const int &Gauntletid, const float &x, const float &y);
	//This plays the sound of the gauntlet id, for a power shot.
	static void PlayPowerSound(int Gauntletid, float x, float y);
	//This shoots the projectile of the gauntlet id, it will not make a sound for you.
	static void Shoot(const int &Gauntletid, float x, float y, const int &direction, bool should_have_particles = true);
	//This shoots the projectile of the gauntlet id, it will not make a sound for you.
	//This function also adds particles to where you have fires.
	static void Shoot_with_particles(int Gauntletid, float x, float y, int direction, float length_of_arc = 30, bool should_have_particles = true);
	
	//This shoots the powershot of the projectile of the gauntlet id. It will not make a sound for you.
	static void Shoot_Power(int Gauntletid, float x, float y, int direction);
	//This returns the amount of fuel using a type of gauntlet uses.
	static int getFuel(const int &Gauntletid);
	//This gets the icon for the specific gauntlet id.
	static sf::Sprite GetIcon(const int &Gauntletid);
	//This gets the ParticleSettings object to be used if you want to make it come out of something with particles.
	static ParticleSettings GetParticleSettings(const int &Gauntletid);
	//Initilizer
	static void init(sf::Texture &tex);
	
};

