
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

	// ##### Layer Settings

	void setColor1(ofColor color1) { c1 = color1; }
	void setColor2(ofColor color2) { c2 = color2; }
	void setOpacity(int o) { opacity = o; }

	ofColor c1;
	ofColor c2;
	int opacity;

	SCTree tree;
	float maxDist; // max dist for branch in range of leaf
	float minDist; // min dist for branch in range of leaf

private:
};

#endif