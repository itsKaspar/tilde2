
// ###### Default Scene
// ###### Startup Scene
// ###### Kaspar Ravel - 2020

#include "Test1.h"

ofParameterGroup Test1::gui() {

	// ##### GUI Setup

	params.setName("Default Scene");
	params.add(positionX.set("Scale", 0.0, 0.0, 30.0)); // make this a type variable
	params.add(positionY.set("Scale", 0.0, 0.0, 30.0)); // make this a type variable
	return params;
}

void Test1::setup() {

	ofSetSphereResolution(3);

	// populate
	for (size_t i = 0; i < NUMSNAKES; i++)                         
	{
		snakes[i] = new Snake();         
	}
}

void Test1::update() {

	for (size_t i = 0; i < NUMSNAKES; i++)
	{
		snakes[i]->update();
	}

}

void Test1::draw() {



	for (size_t i = 0; i < NUMSNAKES; i++)                       // MAYBE WE CAN PUT THIS ON ONYL ONE LINE
	{
		//material.setDiffuseColor(ofColor(c1.r, c1.g, c1.b).lerp(ofColor(c2.r, c2.g, c2.b), snakes[i]->ci));
		//material.begin();
		ofSetColor(ofColor(c1.r, c1.g, c1.b).lerp(ofColor(c2.r, c2.g, c2.b), snakes[i]->ci), opacity);
		snakes[i]->draw();
	}



	// PERLIN NOISE

	//float speed = 0.1;
	//float time = ofGetElapsedTimef();

	//for (size_t i = 0; i < ofGetWidth(); i += ofGetWidth()/50)
	//{
	//	for (size_t j = 0; j < ofGetHeight(); j += ofGetHeight() / 50)
	//	{
	//		int grayscale = (int) (ofNoise(time*speed+ofVec2f(i,j))*255);
	//		ofSetColor(grayscale, 50);
	//		ofCircle(i, j, 5);
	//	}
	//}

}