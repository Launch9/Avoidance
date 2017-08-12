#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
///This class holds the information used in making a source of particles.
class ParticleSettings
{
public:
	/*
	Variables and Definitions:
	
	float x; X_position to start at.
	float y; Y_position to start at.
	float time_to_last; How long your particle is going to last.
	float num_of_particle; Number of particles that come out of the source created.
	int max_speed; max speed that a particle can start at.
	int out_type; type of way your particles dissapear.
	int ac1; Close off point of particle generation. (Smaller number) : (Allows you to choose what degrees the particles come out in.)
	int ac2; Close off point of particle generation. (Bigger number) : (Allows you to choose what degrees the particles come out in.)
	sf::Color color; This is the color of all the particles.
	*/
	ParticleSettings(const float &x_pos, const float &y_pos, const float &duration, const float &num_of_particles, const int &maxspeed, const int &fadeout_type);
	/*
	Variables and Definitions:

	float x; X_position to start at.
	float y; Y_position to start at.
	float time_to_last; How long your particle is going to last.
	float num_of_particle; Number of particles that come out of the source created.
	int max_speed; max speed that a particle can start at.
	int out_type; type of way your particles dissapear.
	int ac1; Degree at which it is spawned.
	int ac2; Degree to tell how wide the angle of spawnage is.
	sf::Color color; This is the color of all the particles.
	*/
	ParticleSettings();//Default constructor
	float x = 0;
	float y = 0;
	float time_to_last = 3;
	float num_of_particle = 50;
	int max_speed = 1;
	int out_type = 0;
	int ac1 = 0;
	int ac2 = 360;
	sf::Color color = sf::Color::White;
	
	void operator=(const ParticleSettings &o);
};

