
// ###### Growth Model Studies
// ###### Diffusion Limited Aggregation
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _DLA
#define _DLA

#include "ofMain.h" 
#include "ofxGui.h"
#include "Scene.h"
#include "RandomWalker.h"
#include "Octree.h"

class DLA : public Scene
{
public:
	//using Layer::c1;
	//using Layer::c2;

	// ##### Basic Functions
	DLA();
	~DLA();
	void setup();
	void update();
	void draw();

	//static Layer * __stdcall Create() { return new DLA(); }

	void setColor1(ofColor c1);
	void setColor2(ofColor c2);
	void setOpacity(int opacity);

	// ##### GUI Setup

	ofParameterGroup gui();
	ofParameterGroup params;
	ofParameter<float> sticky;
	ofParameter<float> towardsAggregation;
	ofParameter<bool> displayWalkers;

	// ##### Particle Vectors

	vector<RandomWalker> walkers;
	vector<RandomWalker> fixed;

	ofColor c1;
	ofColor c2;
	int opacity;

	// ##### Other Variables

	int walkerQty;
	float walkerWalk;
	string spawn;

	Octree *octree;

private:
};

#endif
