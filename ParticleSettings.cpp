#include "stdafx.h"
#include "ParticleSettings.h"
#include <iostream>

ParticleSettings::ParticleSettings(const float &x_pos, const float &y_pos, const float &duration, const float &num_of_particles, const int &maxspeed, const int &fadeout_type)
{
	x = x_pos;
	y = y_pos;
	time_to_last = duration;
	num_of_particle = num_of_particles;
	max_speed = maxspeed;
	out_type = fadeout_type;
}

ParticleSettings::ParticleSettings() {
	
	x = 0;
	y = 0;
	color = sf::Color::White;
	max_speed = 2;
	num_of_particle = 30;
	out_type = 0;
	time_to_last = 4;
	ac1 = 0;
	ac2 = 360;

}


void ParticleSettings::operator=(const ParticleSettings &o) {
	this->x = o.x;
	this->y = o.y;
	this->time_to_last = o.time_to_last;
	this->num_of_particle = o.num_of_particle;
	this->max_speed = o.max_speed;
	this->out_type = o.out_type;
	this->color = o.color;
	this->ac1 = o.ac1;
	this->ac2 = o.ac2;

}