
// ###### Helper Classes
// ###### Particle Class
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _PARTICLE
#define _PARTICLE

#include "ofMain.h"

enum SpawnType
{
	Spawn_Random,
	Spawn_SphereSurface,
	Spawn_Box,
};

class Particle
{

public:

	Particle();
	~Particle();

	void debugDraw();

	// Math
	void update();
	void applyVelocity(glm::vec3 vel, float maxVel = 0);

	// Specific Forces
	void alignment(vector<Particle> v, float maxForce, float maxSpeed);
	void separation(vector<Particle> v, float maxForce, float maxSpeed);
	void cohesion(vector<Particle> v, float maxForce, float maxSpeed);

	glm::vec3 getRepulsion(vector<std::shared_ptr<Particle>> nodes);
	glm::vec3 getAttraction(vector<std::shared_ptr<Particle>> nodes);

	// Movements
	void randomWalk(float walk = 1, bool is3D = false);

	// Containments
	void containment();

	// Spawn
	void spawn(SpawnType spawn, bool is3D);

	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 acc;

private:
};

#endif
