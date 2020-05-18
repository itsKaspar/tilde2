
// ###### Shader Experimentations
// ###### Domain Warping
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _DOMAINWARPING
#define _DOMAINWARPING

#include "ofMain.h" 
#include "ofxGui.h"
#include "Scene.h"

class DomainWarping : public Scene
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

	// ##### Shader Variables

	ofShader shader;

	float tx;
	float ty;
	float tz;
	float dt;

	ofTexture tex;
	ofPixels pix;

private:
};

#endif