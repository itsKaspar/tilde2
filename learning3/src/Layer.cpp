
// ##### Layer Class
// #####
// ##### The Layer class is parent to every class in the Scenes folder
// ##### It creates a sort of wrapper with parameters common to every scene
// ##### Things like opacity, color palette, etc

#include "Layer.h"

// ##### Scene Headers Includes

#include "DefaultScene.h"
#include "DLA.h"
#include "Diffline.h"
#include "Boids.h"
#include "SimplexTerrain.h"
#include "Julia2D.h"
#include "DomainWarping.h"
#include "ShaderTest.h"


Layer::Layer() {
		gui();
}
Layer::~Layer() {
}

void Layer::setup() {
	setup(Scene_Default);
}

void Layer::setup(SceneType Type) {
	// Start Simulation
	scene = CreateScene(Type);
	scene->setup();
	params.add(scene->gui());
}

ofParameterGroup Layer::gui()
{
	// ##### GUI Setup
	params.setName("Scene Settings");
	params.add(layer.set("Layer", 1, 1, 5));
	params.add(blendMode.set("Blend Mode", 1, 1, 4));
	params.add(opacity.set("Opacity", 255, 0, 255)); // ADD THIS : make it so that if opacity is 0 it doesn't even draw to save some memory
	params.add(xSpeed.set("Speed", 1.0, 0.25, 4.0)); // ADD THIS : button to double or halve speed
	params.add(restart.set("Restart", false));
	params.add(color1.set(ofColor::white));
	return params;
}

void Layer::update() {
	scene->update();
}

void Layer::draw() {
	ofSetColor(color1, opacity); 
	scene->draw();
}

/*
void Layer::deleteScene() {
	if (scene) delete scene;
}*/

Layer *Layer::CreateScene(SceneType Type)
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
	}
}