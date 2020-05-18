
// ###### Particle Systems
// ###### Boids
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _BOIDS
#define _BOIDS

#include "ofMain.h" 
#include "ofxGui.h"
#include "Scene.h"

class Boids : public Scene
{
public:

	// ##### Basic Functions

	void setup();
	void update();
	void draw();

	// ##### GUI Setup

	ofParameterGroup gui();
	ofParameterGroup params;
	ofParameter<float> scale;
	ofParameter<ofVec3f> rotation;

	// ##### Other Variables

	int boidQty;

private:
};

#endif