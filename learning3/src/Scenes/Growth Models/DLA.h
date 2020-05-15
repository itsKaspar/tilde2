
// ###### Growth Model Studies
// ###### Diffusion Limited Aggregation
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _DLA
#define _DLA

#include "ofMain.h" 
#include "ofxGui.h"
#include "Layer.h"
#include "RandomWalker.h"

class DLA : public Layer
{
public:

	// ##### Basic Functions

	void setup();
	void update();
	void draw();

	// ##### GUI Setup

	ofParameterGroup gui();
	ofParameterGroup params;
	ofParameter<float> sticky;
	ofParameter<float> towardsAggregation;
	ofParameter<bool> displayWalkers;

	// ##### Particle Vectors

	vector<RandomWalker> walkers;
	vector<RandomWalker> fixed;

	// ##### Other Variables

	int walkerQty;
	float walkerWalk;
	string spawn;

private:
};

#endif
