
// ###### 
// ###### Layer System
// ###### Kaspar Ravel - 2020

#pragma once

#ifndef _LAYER
#define _LAYER

#include "ofMain.h" 
#include "ofxGui.h"

enum SceneType
{
	Scene_None,
	Scene_Default,

	// Growth Models
	Scene_DiffLine,
	Scene_DLA,

	// Particle Systems
	Scene_Boids,

	// Shader Experimentations
	Scene_ShaderTest,
	Scene_Julia2D,
	Scene_SimplexTerrain,
	Scene_DomainWarping
};

class Layer
{
public:

	// ##### Basic Functions

	Layer();
	~Layer();
	virtual void setup();
	virtual void setup(SceneType Type);
	virtual ofParameterGroup gui();
	virtual void update();
	virtual void draw();

	// ##### Factory Design Scene Change

	void changeScene(SceneType Type);
	static Layer *CreateScene(SceneType Type);

	// ##### GUI Setup

	ofParameterGroup params;
	ofParameter<int> layer;
	ofParameter<int> blendMode;
	ofParameter<int> opacity;
	ofParameter<float> xSpeed;
	ofParameter<bool> restart;
	ofParameter<int> color1;

	// Other Variables

	Layer* scene;

private:
};

#endif
