
// ###### 
// ###### Layer System
// ###### Kaspar Ravel - 2020

#include "Layer.h"

#include "DefaultScene.h"

#include "DLA.h"
#include "Diffline.h"
#include "Boids.h"

// ##### Shaders
#include "SimplexTerrain.h"
#include "Julia2D.h"
#include "DomainWarping.h"
#include "ShaderTest.h"

void Layer::setup() {
	setup(Scene_Default);
}

void Layer::setup(SceneType Type) {

	// ##### GUI Setup

	params.setName("Scene Settings");
	params.add(layer.set("Layer", 1, 1, 5));
	params.add(blendMode.set("Blend Mode", 1, 1, 4));
	params.add(opacity.set("Opacity", 255, 0, 255)); // ADD THIS : make it so that if opacity is 0 it doesn't even draw to save some memory
	params.add(xSpeed.set("Speed", 1.0, 0.25, 4.0)); // ADD THIS : 	button to double or halve speed
	params.add(restart.set("Restart", false));
	params.add(color1.set("Color 1", 0, 0, 255));

	// Start Simulation
	scene = CreateScene(Type);
	scene->setup();
	params.add(scene->gui());

	// Change scene button doesnt work yet
	//changeScene(Scene_DiffLine);


}

ofParameterGroup Layer::gui()
{
	return params;
}

void Layer::update() {
	scene->update();
}

void Layer::draw() {
	ofSetColor(color1, color1, color1, opacity); 
	scene->draw();
}

/*
void Layer::changeScene(SceneType Type) {
	if (scene) delete scene;
	scene = CreateScene(Type);
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