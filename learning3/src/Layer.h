
// ##### Layer Class
// #####
// ##### The Layer class is parent to every class in the Scenes folder
// ##### It creates a sort of wrapper with parameters common to every scene
// ##### Things like opacity, color palette, etc

#pragma once
class Scene;// forward declaration because of circular dependency

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
	Scene_SpaceColonization,

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
	Layer(int id);
	~Layer();
	void setup(SceneType Type);
	void update();
	void draw();

	ofParameterGroup gui();

	// ##### Active Layer Handling

	void setActiveLayer();
	int getActiveLayer();
	bool isActiveLayer();

	// ##### Factory Design Scene Change

	static Scene *CreateScene(SceneType Type);

	// ##### GUI Setup

	ofxPanel sceneMenu;
	ofParameterGroup sceneGroup;

	ofParameterGroup params;
	ofParameter<int> layer;
	ofParameter<int> blendMode;
	ofParameter<int> opacity;
	ofParameter<float> xSpeed;
	ofParameter<bool> restart;
	ofParameter<ofColor> c1;
	ofParameter<ofColor> c2;

	ofParameter<float> randColor;

	ofColor random;

	// Other Variables

	int id; // layer id
	static int activeLayer;

	Scene *scene;

private:

};

#endif
