
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _SPACECOLONIZATION
#define _SPACECOLONIZATION

#include "ofMain.h" 
#include "ofxGui.h"
#include "Scene.h"
#include "SCTree.h"

class SpaceColonization : public Scene
{
public:

	// ##### Basic Functions

	void setup();
	void update();
	void draw();

	// ##### GUI Setup

	ofParameterGroup gui();
	ofParameterGroup params;
	//ofParameter<float> scale;
	//ofParameter<ofVec3f> rotation;

	SCTree tree;
	float maxDist; // max dist for branch in range of leaf
	float minDist; // min dist for branch in range of leaf

private:
};

#endif