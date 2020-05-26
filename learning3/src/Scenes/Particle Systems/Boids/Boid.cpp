#include "Boid.h"

Boid::Boid(glm::vec3 p) {
	Particle::pos = p;
	float r2 = 1;
	Particle::vel = glm::vec3(ofRandom(-r2, r2), ofRandom(-r2, r2), ofRandom(-r2, r2));


	// Select Random Image

	ofDirectory dir("/incroyable"); // can relative or absolute to bin/data
	// dir.allowExt("png"); //only show png files
	//populate the directory object
	dir.listDir();
	int r = ofRandom(0, dir.size() - 1);
	string rndImg = dir.getPath(r);

	// Apply Texture

	ofDisableArbTex();
	mTex.enableMipmap();
	ofLoadImage(mTex, rndImg);

	// Set Geometry

	butterfly.setGlobalPosition(p);

	lWing.setParent(butterfly);
	rWing.setParent(butterfly);

	lWing.set(20, 20, 2, 2);
	rWing.set(20, 20, 2, 2);

	glm::vec3 rWingOffset(20, 20, 0);
	//move all the vertices so these start at 0,0
	for (auto&v : rWing.getMesh().getVertices()) { v += rWingOffset / 2.0; }

	glm::vec3 lrWingOffset(20, -20, 0);
	//move all the vertices so these start at 0,0
	for (auto&v : lWing.getMesh().getVertices()) { v += lrWingOffset / 2.0; }

	rWing.rotateDeg(90, glm::vec3(0, -1, 0));
	lWing.rotateDeg(90, glm::vec3(0, -1, 0));
}

void Boid::update() {
	Particle::update();

	butterfly.move(vel);

	float flapSpeed = length(vel) * 20;

	rWing.rotateDeg(ofMap(sin(flapSpeed * ofGetElapsedTimef()), -1, 1, flapSpeed, -flapSpeed), glm::vec3(0, 0, 1));
	lWing.rotateDeg(ofMap(sin(flapSpeed * ofGetElapsedTimef()), -1, 1, -flapSpeed, flapSpeed), glm::vec3(0, 0, 1));

	butterfly.lookAt(butterfly.getGlobalPosition() + vel);
}

void Boid::draw() {

	//glm::vec3 head = pos + vel * 10;
	//glm::vec3 tail = pos;

	//ofSetColor(255, 0, 0);
	//ofDrawSphere(head, 10);
	//ofSetColor(255, 255, 255);
	//ofDrawSphere(tail, 10);

	//butterfly.draw();
	ofSetColor(255);
	mTex.bind();

	rWing.draw();
	lWing.draw();

	mTex.unbind();

	ofNoFill();
	ofSetColor(5);
	ofDrawSphere(glm::vec3(0), ofGetWidth()/2);
}
