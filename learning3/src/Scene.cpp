
// ##### Scene Class
// #####
// ##### Wrapper Class for Scenes
// ##### 

#include "Scene.h"

Scene::Scene() { std::cout << "value: " << c1 << endl; }

Scene::~Scene() {}

void Scene::setup() {}

void Scene::update() {}

void Scene::setColor1(ofColor c1) {}
void Scene::setColor2(ofColor c2) {}
void Scene::setOpacity(int opacity) {}

void Scene::draw() {}

ofParameterGroup Scene::gui() {
	return params;

}