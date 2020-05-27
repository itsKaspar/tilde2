#ifndef _RANDOMWALER
#define _RANDOMWALKER

#include "ofMain.h" 
#include "Particle.h"

#pragma once
class RandomWalker : public Particle
{
public:
	RandomWalker(glm::vec3 pos, float radius, float walk, float stick, float colorInterpol);
	RandomWalker(float radius, float walk, float stick, float colorInterpol, bool is3D);
	void update(bool is3D);
	void draw(ofColor c1, ofColor c2, float opacity, bool is3D);

	float ci; // color interpolation

	ofMaterial material;

	float randomWalk;
	float radius;
	float sticky; 

private:
};

#endif