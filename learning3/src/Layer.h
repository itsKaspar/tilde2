
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
	Scene_DomainWarping,

	Scene_Test1
};

class Layer
{
public:

	// ##### Basic Functions

	Layer();
	Layer(int i, SceneType Type);
	~Layer();
	void setup();
	void update();
	void draw();

	double debug[100000];

	// ##### Active Layer Handling

	void setActiveLayer();
	int getActiveLayer();
	bool isActiveLayer();

	// ##### Factory Design Scene Change

	static Scene *CreateScene(SceneType Type);

	// ##### GUI Setup

	void gui();
	ofxPanel sceneMenu;
	ofParameterGroup sceneGroup;
	ofParameterGroup params;
	ofParameter<int> opacity;
	ofParameter<int> blendMode;

	ofParameter<ofColor> c1;
	ofParameter<ofColor> c2;
	ofParameter<bool> lighting;
	ofParameter<ofVec3f> speedLight;
	ofParameter<ofVec3f> speedCamera;
	ofParameter<float> xBpm;
	ofParameter<bool> resetAtBpm;
	ofParameter<bool> reset;

	void resetChanged(bool & reset);

	// Other Variables

	int bpm;
	float timeSinceLastBeat;
	int id; // layer id
	static int activeLayer;

	Scene *scene;

	// Transform

	ofEasyCam camera;

	// Lights

	ofLight light;
	ofMaterial material;

	bool inTransition;
private:

};

#endif
