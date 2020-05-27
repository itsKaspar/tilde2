
// ###### Growth Model Studies
// ###### Collatz Conjecture
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _COLLATZ
#define _COLLATZ

#include "ofMain.h" 
#include "ofxGui.h"
#include "Scene.h"
#include "CollatzBranch.h"

class Collatz : public Scene
{
public: 

	// ##### Basic Functions

	void reset();
	void setup(); 
	void update(); 
	void draw();


	// ##### Other Functions

	int collatz(int n);

	// ##### Helper Functions

	// ##### GUI Setup

	ofParameterGroup gui();
	ofParameterGroup params;
	ofParameter<bool> isCentered;
	ofParameter<bool> is3D;

	// ##### Layer Settings

	void setColor1(ofColor color1) { c1 = color1; }
	void setColor2(ofColor color2) { c2 = color2; }
	void setOpacity(int o) { opacity = o; }

	ofColor c1;
	ofColor c2;
	int opacity;

	// ##### Other Variables

	vector <CollatzBranch> branches;

	int iter;

private:
};

#endif