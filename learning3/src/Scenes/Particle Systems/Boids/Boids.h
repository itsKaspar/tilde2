
// ###### Particle Systems
// ###### Boids
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _BOIDS
#define _BOIDS

#include "ofMain.h" 
#include "ofxGui.h"
#include "Scene.h"
#include "Boid.h"
#include "Octree.h"

class Boids : public Scene
{
public:

	// ##### Basic Functions

	void reset();
	void setup();
	void update();
	void draw();

	// ##### GUI Setup

	ofParameterGroup gui();
	ofParameterGroup params;
	ofParameter<int> nBoids;
	ofParameter<bool> is3D;
	ofParameter<bool> drawOctree;


	// ##### Other Variables

	vector<shared_ptr<Boid>> boids;
	Octree *octree;

private:

};

#endif