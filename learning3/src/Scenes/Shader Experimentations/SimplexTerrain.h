
// ###### Shader Experimentations
// ###### Simplex Terrain
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _SIMPLEXTERRAIN
#define _SIMPLEXTERRAIN

#include "ofMain.h" 
#include "ofBaseApp.h" // Can I delete this call ?
#include "Scene.h"
#include "ofxGui.h"


class SimplexTerrain : public Scene
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
	ofParameter<int> octaves;
	ofParameter<float> persistence;
	ofParameter<float> lacunarity;
	ofParameter<float> speed;
	ofParameter<ofVec3f> rotation;
	ofParameter<float> direction;

	// ##### Shader Variables

	ofShader shader;
	ofShader noise;
	ofPlanePrimitive plane;

	float tx;
	float ty;
	float tz;
	float dt;

	ofTexture tex;
	ofPixels pix;

private:
};

#endif