
// ##### Scene Class
// #####
// ##### Wrapper Class for Scenes
// ##### 

#pragma once

#ifndef _SCENE
#define _SCENE

#include "ofMain.h" 
#include "ofxGui.h"
#include "Layer.h"

class Scene : public Layer
{
public:
	// ##### Basic Functions
	Scene() {};
	~Scene() {};
	virtual void setup() {};
	virtual void update() {};
	virtual void draw() {};
	virtual void reset() {};
	virtual ofParameterGroup gui() { return params; };
	virtual void setColor1(ofColor c1) {};
	virtual void setColor2(ofColor c2) {};
	virtual void setOpacity(int opacity) {};

	ofParameterGroup params;

private:

};

#endif
