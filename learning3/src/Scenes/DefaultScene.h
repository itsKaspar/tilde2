
// ###### Default Scene
// ###### Startup Scene
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _DEFAULTSCENE
#define _DEFAULTSCENE

#include "ofMain.h" 
#include "ofxGui.h"
#include "Scene.h"

class DefaultScene : public Scene
{
public:

	// ##### Basic Functions

	void setup();
	void update();
	void draw();
	void reset();

	// ##### GUI Setup

	ofParameterGroup gui();
	//ofParameterGroup params;
	//ofParameter<float> scale;
	//ofParameter<ofVec3f> rotation;

	// ##### Layer Settings

	void setColor1(ofColor color1) { c1 = color1; }
	void setColor2(ofColor color2) { c2 = color2; }
	void setOpacity(int o) { opacity = o; }

	ofColor c1;
	ofColor c2;
	int opacity;

	// ##### Shader Variables

	//ofShader shader;

	//float tx;
	//float ty;
	//float tz;
	//float dt;

	//ofTexture tex;
	//ofPixels pix;

private:
};

#endif