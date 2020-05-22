#include "Boid.h"

Boid::Boid(ofVec3f p) {
	pos = p;
	vel = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), 0);
}

void Boid::update() {
	pos += vel;
	vel += acc;
	acc *= 0; // reset acceleration
}

void Boid::edges() {
	float w = ofGetWidth();
	float h = ofGetHeight();

	if (pos.x > w / 2) pos.x = -w / 2;
	if (pos.y > h / 2) pos.y = - h / 2;
	if (pos.x < - w / 2) pos.x = w / 2;
	if (pos.y < - h / 2) pos.y = h / 2;
}

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
		float dist = pos.distance(nearbies[i].pos);
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

