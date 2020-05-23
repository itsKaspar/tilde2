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
}

void Boid::update() {
	pos += vel;
	vel += acc;
	acc *= 0; // reset acceleration
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
	ofSetColor(255,0,0);
	ofDrawSphere(pos + vel, 5);
	ofSetColor(255);
	ofDrawSphere(pos, 5);

	//ofDrawPlane(50.0, 50.0);//move back by the centre offset


	//ofDrawCircle(pos, 5);                // Make a function to show
	mTex.bind();
	//ofDrawPlane(pos, 50.0, 50.0);

	ofPushMatrix();
	ofTranslate(pos); // Now my origin is my boid origin
	// Now I need my origin axis to be aligned with my 

	ofRotate(90, vel.x, vel.y, vel.z);

	glm::vec3 plane1 = glm::vec3(- 30, 0, 0);
	glm::vec3 plane2 = glm::vec3( 30, 0, 0);
	ofDrawPlane(plane1, 50.0, 50.0);
	ofDrawPlane(plane2, 50.0, 50.0);

	ofPopMatrix();

	//ofRotate(ofGetFrameNum() * .1, 0, 0, 1);//rotate from centre
	//ofPushMatrix();
	//ofDrawPlane(50.0, 50.0);//move back by the centre offset
	//ofPopMatrix();


	mTex.unbind();
}
