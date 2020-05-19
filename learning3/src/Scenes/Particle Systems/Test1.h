
// ###### Default Scene
// ###### Startup Scene
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _TEST1
#define _TEST1

#include "ofMain.h" 
#include "ofxGui.h"
#include "Scene.h"
#include "Snake.h"

#define NUMSNAKES 10

class Test1 : public Scene
{
public:

	// ##### Basic Functions

	void setup();
	void update();
	void draw();

	// ##### GUI Setup

	ofParameterGroup gui();
	ofParameterGroup params;
	ofParameter<float> positionX;
	ofParameter<float> positionY;

	// ##### Layer Settings

	void setColor1(ofColor color1) { c1 = color1; }
	void setColor2(ofColor color2) { c2 = color2; }
	void setOpacity(int o) { opacity = o; }

	ofColor c1;
	ofColor c2;
	int opacity;

	// ##### Other Variables

	Snake *snakes[NUMSNAKES];




private:
};

#endif