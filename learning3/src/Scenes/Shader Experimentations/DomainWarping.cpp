
// ###### Shader Experimentations
// ###### Domain Warping
// ###### Kaspar Ravel - 2020

#include "DomainWarping.h"

ofParameterGroup DomainWarping::gui() {

	// ##### GUI Setup

	params.setName("Domain Warping");
	params.add(scale.set("Scale", 0.1, 0.01, 1)); // make this a type variable
	params.add(rotation.set("Rotation", ofVec3f(0, 1, 0.5), ofVec3f(-1, -1, -1), ofVec3f(1, 1, 1)));
	return params;
}

void DomainWarping::setup() {

	shader.load("shaders/DomainWarping/domainwarping");
}

void DomainWarping::update() {

}

void DomainWarping::draw() {

	// ##### Plane Transformation

	float cx = ofGetWidth() / 2.0; // get center x
	float cy = ofGetHeight() / 2.0; // get center y
	ofPushMatrix();
	//ofTranslate(cx, cy);
	//ofRotateDeg(180, rotation->x, rotation->y, rotation->z);

	// ##### Shader Begin

	shader.begin();

	// ##### Pass Uniform Variables

	shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform1f("scale", scale);

	// ##### Setup Shader Canvas
	ofFill(); 
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	// ##### Shader End

	shader.end();

	// ##### Reset Plane Transformation

	ofPopMatrix();
}

