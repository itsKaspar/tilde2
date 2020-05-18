
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

	scene = CreateScene(Type);
	scene->setup();
	sceneGroup.add(gui()); // add general scene menu
	sceneGroup.add(scene->gui()); // add specific scene menu
	sceneMenu.setup(sceneGroup);
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
	params.add(c1.set(ofColor(200, 100, 148)));
	params.add(c2.set(ofColor(19, 60, 85)));
	params.add(randColor.set("Randomize Colors", 1.0, 0.0, 1.0)); // ADD THIS : button to double or halve speed
	return params;
}


void Layer::update() {
	scene->update();

	scene->setColor1(c1);
	scene->setColor2(c2);
	scene->setOpacity(opacity);
}


void Layer::draw() {
	scene->draw();
	if(id == activeLayer) sceneMenu.draw();
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
	}
}
