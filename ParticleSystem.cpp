#include "stdafx.h"
#include "ParticleSystem.h"
#include "GF.h"
#include <iostream>
#include <thread>
#define C2D 2
#define speedVariation 200
#define timeVariation 5
#define timeBase 2
#define max_number_of_particles 1000
std::vector<int> ParticleSystem::to_be_destroyed1;
std::vector<int> ParticleSystem::to_be_destroyed2;
std::vector<sf::Vertex> ParticleSystem::Particles;
std::vector<ParticleSystem::PD> ParticleSystem::Data;
void ParticleSystem::TALL() {
	for (unsigned int i = 0; i < Particles.size(); i++) {
		Data[i].time -= GF::getDelta();
		//Checking to see if it should destroy the particle.
		if (Data[i].time <= 0) {

			to_be_destroyed1.push_back(i);
			
			
		}
		else {
			Particles[i].position.x = Particles[i].position.x + (Data[i].x_vel * GF::getDelta());
			Particles[i].position.y = Particles[i].position.y + (Data[i].y_vel * GF::getDelta());
			switch (Data[i].type) {
			case 0:
				
				break;
			case 1://slow fade out
				Particles[i].color.a = ((Data[i].time * 15) / 100) * 255;
				   break;
			case 2:
				if (Data[i].time <= Data[i].start_time / C2D) {

				}
				break;
			}
		}
		
	}
}
void ParticleSystem::T1() {
	for (unsigned int i = 0; i < Particles.size() / 2; i++) {
		Data[i].time -= GF::getDelta();
		//Checking to see if it should destroy the particle.
		if (Data[i].time <= 0) {
			
			to_be_destroyed1.push_back(i);
			
			
		}
		else {
			Particles[i].position.x = Particles[i].position.x + (Data[i].x_vel * GF::getDelta());
			Particles[i].position.y = Particles[i].position.y + (Data[i].y_vel * GF::getDelta());
			switch (Data[i].type) {
			case 0:
				
				break;
			case 1://slow fade out
				Particles[i].color.a = ((Data[i].time * 15) / 100) * 255;
				   break;
			case 2:
				if (Data[i].time <= Data[i].start_time / C2D) {

				}
				break;
			}
		}
		
	}
}
void ParticleSystem::T2() {
	int add_on = 0;
	//If not even number of particles.
	if (Particles.size() % 2 == 0) {
		add_on = 1;
	}
	else {
		
	}
	for (unsigned int i = (Particles.size() / 2) + add_on; i < Particles.size(); i++) {
		Data[i].time -= GF::getDelta();
		//Checking to see if it should destroy the particle.
		if (Data[i].time <= 0) {
			to_be_destroyed2.push_back(i);
		}
		else {
			Particles[i].position.x = Particles[i].position.x + (Data[i].x_vel * GF::getDelta());
			Particles[i].position.y = Particles[i].position.y + (Data[i].y_vel * GF::getDelta());
			switch (Data[i].type) {
			case 0:
				
				
				break;
			case 1://slow fade out
				Particles[i].color.a = ((Data[i].time * 15) / 100) * 255;
				   break;
			case 2:
				
				if (Data[i].time <= Data[i].start_time / C2D) {

				}
				break;
			}
		}
		
	}
}
void ParticleSystem::tickparticles() {
	
	if (Particles.size() > 1) {
		std::thread t1(&T1);
		T2();
		t1.join();
	}
	else {
		TALL();
	}
	//TALL();
	int extra = 0;
	for (unsigned int i = 0; i < to_be_destroyed1.size(); i++) {
		Data.erase(Data.begin() + (to_be_destroyed1[i] - extra));
		Particles.erase(Particles.begin() + (to_be_destroyed1[i] - extra));
		extra++;
	}
	for (unsigned int i = 0; i < to_be_destroyed2.size(); i++) {
		Data.erase(Data.begin() + (to_be_destroyed2[i] - extra));
		Particles.erase(Particles.begin() + (to_be_destroyed2[i] - extra));
		extra++;
	}
	to_be_destroyed1.clear();
	to_be_destroyed2.clear();
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;

	for (unsigned int i = 0; i < Particles.size(); i++) {

		// draw the vertex array
		target.draw(&Particles[i], 1, sf::Points, states);
	}
	
}

void ParticleSystem::create(const ParticleSettings &s) {
	float angle = 3;
	float length;
	int time_add;
	int max_point = 0;
	sf::Vertex v;
	PD a;

	for (unsigned int i = 0; i < s.num_of_particle; i++) {
		v.color = s.color;
		v.position.x = s.x;
		v.position.y = s.y;
		a.friction = 1;
		a.start_time = s.time_to_last;
		srand(GF::getTSS().asMicroseconds() * rand() + i);
		time_add = rand() % (timeBase + (timeBase + timeVariation));
		a.time = s.time_to_last + time_add;
		a.type = s.out_type;
		angle = ((rand() % s.ac2 + s.ac1) * 3.14) / 180;
		length = rand() % (s.max_speed + (s.max_speed - speedVariation));
		a.y_vel = sin(angle) * length;
		a.x_vel = cos(angle) * length;
		Data.push_back(a);
		Particles.push_back(v);
		if (Particles.size() >= max_number_of_particles) {
			max_point++;
		}
	}
	for (unsigned int i = 0; i < max_point; i++) {
		//Deleting the objects.
		Particles.erase(Particles.begin() + i);
		Data.erase(Data.begin() + i);
	}
}

void ParticleSystem::destroy_all() {
	Particles.clear();
	Data.clear();
}