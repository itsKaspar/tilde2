
// ###### Shader Experimentations
// ###### 2D Julia Sets
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _JULIA2D
#define _JULIA2D

#include "ofMain.h" 
#include "ofxGui.h"
#include "Scene.h"

class Julia2D : public Scene
{
public:

	// ##### Basic Functions

	void setup();
	void update();
	void draw();

	//static Layer * __stdcall Create() { return new Julia2D(); }

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