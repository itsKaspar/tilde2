#include "Boid.h"

Boid::Boid(glm::vec3 p) {
	pos = p;
	float r2 = 1;
	vel = glm::vec3(ofRandom(-r2, r2), ofRandom(-r2, r2), ofRandom(-r2, r2));
	//vel = glm::vec3(0, 0, 0);

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

	lWing.setParent(butterfly);
	rWing.setParent(butterfly);

	lWing.move(-110, 0,0);
	rWing.move(110, 0, 0);

	butterfly.move(pos);
}

void Boid::update() {
	pos += vel;
	vel += acc;
	acc *= 0; // reset acceleration
	butterfly.move(vel);
	butterfly.rotate(vel);
}

//void Boid::edges() {
//	float w = ofGetWidth();
//	float h = ofGetHeight();
//
//	if (pos.x > w / 2) pos.x = -w / 2;
//	if (pos.y > h / 2) pos.y = - h / 2;
//	if (pos.x < - w / 2) pos.x = w / 2;
//	if (pos.y < - h / 2) pos.y = h / 2;
//}

void Boid::alignment(vector <Boid> nearbies) {
	ofVec3f steering = ofVec3f(0, 0, 0);
	for (size_t i = 0; i < nearbies.size(); i++)
	{
		steering += nearbies[i].vel;
	}
	if (nearbies.size() > 1) steering /= nearbies.size();
	steering.scale(maxSpeed);
	steering -= vel;
	steering = steering.getLimited(maxForce);
	acc += steering;
}

void Boid::cohesion(vector <Boid> nearbies) {
	ofVec3f steering = ofVec3f(0, 0, 0);
	for (size_t i = 0; i < nearbies.size(); i++)
	{
		steering += nearbies[i].pos;
	}
	if(nearbies.size() > 1) steering /= nearbies.size();
	steering -= pos;
	steering.scale(maxSpeed);
	steering -= vel;
	steering = steering.getLimited(maxForce);
	acc += steering;
}

void Boid::separation(vector <Boid> nearbies) {
	ofVec3f steering = ofVec3f(0, 0, 0);
	for (size_t i = 0; i < nearbies.size(); i++)
	{
		float dist = glm::distance(pos, nearbies[i].pos);
		ofVec3f diff = pos - nearbies[i].pos;
		diff /=  dist; // to make it invertly proportional
		steering += diff;
	}
	if (nearbies.size() > 1) steering /= nearbies.size();
	steering.scale(maxSpeed);
	steering -= vel;
	steering = steering.getLimited(maxForce);
	acc += steering;
}


void Boid::draw() {

	//glm::vec3 head = pos + vel;
	//glm::vec3 tail = pos;

	//tail.draw();

	mTex.bind();

	lWing.rotateAroundDeg(sin(ofGetElapsedTimef()), glm::vec3(1,0,0), glm::vec3(0, 0, 0));
	rWing.rotateAroundDeg(sin(ofGetElapsedTimef()), glm::vec3(1,0,0), glm::vec3(0, 0, 0));

	rWing.draw();
	lWing.draw();


	mTex.unbind();
}
