#pragma once
#include "ParticleSettings.h"

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
private:
	static std::vector<int> ParticleSystem::to_be_destroyed1;
	static std::vector<int> ParticleSystem::to_be_destroyed2;
	static void T1();
	static void T2();
	static void TALL();
protected:
	
	//All the vertices for drawing everything.
	static std::vector<sf::Vertex> ParticleSystem::Particles;
	//Structure of particle data.
	static struct PD {
		float time;
		float start_time;
		float x_vel = 0;
		float y_vel = 0;
		float friction = 0; //How fast they slow down.
		int type = 0; //How they disappear
	};

	static std::vector<PD> ParticleSystem::Data;
	
public:
	static void create(const ParticleSettings &s);
	static void tickparticles();
	//This will delete all the particles present.
	static void destroy_all();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
};

