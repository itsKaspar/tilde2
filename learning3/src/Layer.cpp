
// ##### Layer Class
// #####
// ##### The Layer class is parent to every class in the Scenes folder
// ##### It creates a sort of wrapper with parameters common to every scene
// ##### Things like opacity, color palette, etc

#include "Layer.h"
#include "Global.h"

// ##### Scene Headers Includes

#include "DefaultScene.h"
#include "DLA.h"
#include "Diffline.h"
#include "SpaceColonization.h"
#include "Boids.h"
#include "SimplexTerrain.h"
#include "Julia2D.h"
#include "DomainWarping.h"
#include "ShaderTest.h"
#include "Test1.h"

int Layer::activeLayer;

Layer::Layer() {
}

Layer::Layer(int i) {
	id = i;
	activeLayer = i;
}

Layer::~Layer() {
}


void Layer::setup(SceneType Type) {
	// ##### Lighting                                         // MAKE THIS A BOOL CUZ WE DONT ALWAYS NeED LIGHTS

	light.setup();
	light.disable(); // disable in setup because else there is a bug
	ofDisableDepthTest();

	scene = CreateScene(Type);
	scene->setup();
	sceneGroup.add(gui()); // add general scene menu
	sceneGroup.add(scene->gui()); // add specific scene menu
	sceneMenu.setup(sceneGroup);
}


ofParameterGroup Layer::gui()
{

	// ##### GUI Setup
	params.setName("Scene Settings");                                       // ADD THIS NAME OF SIMULATION
	params.add(opacity.set("Opacity", 255, 0, 255));
	params.add(blendMode.set("Blend Mode", 1, 1, 4));
	params.add(xSpeed.set("Speed", 1.0, 0.25, 4.0));                    // ADD THIS : button to double or halve speed
	params.add(restart.set("Restart", false));
	params.add(c1.set(ofColor(200, 100, 148)));
	params.add(c2.set(ofColor(19, 60, 85)));
	params.add(lighting.set("Lighting", true));
	params.add(speedLight.set("Speed Light", ofVec3f::zero(), ofVec3f::zero(), ofVec3f(10))); // make this a type variable
	params.add(speedCamera.set("Rotation", ofVec3f::zero(), ofVec3f::zero(), ofVec3f(1000)));
	return params;
}


void Layer::update() {

	float time = ofGetElapsedTimef();
	light.setPosition(200 * sin(time*speedLight->x), 200 * cos(time*speedLight->y), 200 * cos(time*speedLight->y));

	scene->update();
	scene->setColor1(c1);
	scene->setColor2(c2);
	scene->setOpacity(opacity);
}


void Layer::draw() {
	if (opacity > 0) // if opacity of the layer is at 0 don't draw
	{
		// # Blend Modes
		if (blendMode == '1') 		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		if (blendMode == '2') 		ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
		if (blendMode == '3') 		ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
		if (blendMode == '4') 		ofEnableBlendMode(OF_BLENDMODE_SCREEN);
		// unused blend modes
		//OF_BLENDMODE_DISABLED
		//OF_BLENDMODE_ADD


		// # Lights

		if (lighting)
		{
			light.enable();                                                                 // MAKE LIGHTING VARIABLE ACCESSIBLE TO CHILDREN
			ofEnableDepthTest();
			//material.setDiffuseColor(ofColor::red);
			//material.setAmbientColor(ofColor::red);
			//material.setSpecularColor(ofColor::white);
			//material.begin();
		}

		// # Camera
		camera.begin();

		// lights VISUALIZER
		//float time = ofGetElapsedTimef();
		//ofDrawSphere(200*sin(time*speedLight->x), 200*cos(time*speedLight->y), 200 * cos(time*speedLight->y), 30); // light visualizer

		ofRotateXDeg(speedCamera->x * ofGetElapsedTimef());
		ofRotateYDeg(speedCamera->y * ofGetElapsedTimef());
		ofRotateZDeg(speedCamera->z * ofGetElapsedTimef());

		ofSetColor(10);
		//ofDrawBox(0, 0, 0, 128);

		scene->draw();

		// Reset Transform
		//ofPopMatrix();

		camera.end();

		// Reset Lights
		if (lighting)
		{
			material.end();
			light.disable();
			ofDisableDepthTest();
		}
	}
		// Display Scene Menu
	if (id == activeLayer) sceneMenu.draw();

}

// Active Layer Handling
void Layer::setActiveLayer() { activeLayer = id; }
int Layer::getActiveLayer() { return activeLayer; }
bool Layer::isActiveLayer() { if (id == activeLayer) { return true; } else { return false; } }                  // Make this ternaryyyyyyyyyyyyy i can never remember

/*
void Layer::deleteScene() {
	if (scene) delete scene;
}*/


Scene *Layer::CreateScene(SceneType Type)
{

	switch (Type)
	{
	// ##### Defaults

	case Scene_Default:
	default:
		return new DefaultScene();
	case Scene_None:
		return nullptr;

	// ##### Growth Models

	case Scene_DLA:
		return new DLA();
	case Scene_DiffLine:
		return new DiffLine();
	case Scene_SpaceColonization:
		return new SpaceColonization();

	// ##### Particle Systems

	case Scene_Boids:
		return new Boids();

	// ##### Shader Experimentations

	case Scene_ShaderTest:
		return new ShaderTest();
	case Scene_Julia2D:
		return new Julia2D();
	case Scene_SimplexTerrain:
		return new SimplexTerrain();
	case Scene_DomainWarping:
		return new DomainWarping();
	case Scene_Test1:
		return new Test1();
	}
}
