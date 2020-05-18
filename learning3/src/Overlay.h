#ifndef _OVERLAY
#define _OVERLAY

#include "ofMain.h" 
#include "ofxGui.h"

#pragma once
class Overlay
{
public:
	void setup();
	void update();
	void draw();

	bool display;

	// ##### GUI Setup

	ofParameterGroup params;
	ofParameter<int> fps;
	ofParameter<int> bgColor;
	ofParameter<int> opacity;
	ofParameter<bool> fill;

	// Info Text

	string infoText;
};

#endif