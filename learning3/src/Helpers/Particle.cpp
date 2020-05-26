
// ###### Helper Classes
// ###### Particle Class
// ###### Kaspar Ravel - 2020

#include "Particle.h"

Particle::Particle() {
}

Particle::~Particle() {

}

void Particle::update() {
	pos += vel;
	vel += acc;
	acc *= 0; // reset acceleration
}

void Particle::alignment(vector <Particle> nearbies, float maxForce, float maxSpeed) {
	ofVec3f steering = ofVec3f(0, 0, 0);
	for (size_t i = 0; i < nearbies.size(); i++)
	{
		steering += nearbies[i].Particle::vel;
	}
	if (nearbies.size() > 1) steering /= nearbies.size();
	steering.scale(maxSpeed);
	steering -= Particle::vel;
	steering = steering.getLimited(maxForce);
	Particle::acc += steering;
}

void Particle::cohesion(vector <Particle> nearbies, float maxForce, float maxSpeed) {
	ofVec3f steering = ofVec3f(0, 0, 0);
	for (size_t i = 0; i < nearbies.size(); i++)
	{
		steering += nearbies[i].Particle::pos;
	}
	if (nearbies.size() > 1) steering /= nearbies.size();
	steering -= Particle::pos;
	steering.scale(maxSpeed);
	steering -= Particle::vel;
	steering = steering.getLimited(maxForce);
	Particle::acc += steering;
}

void Particle::separation(vector <Particle> nearbies, float maxForce, float maxSpeed) {
	ofVec3f steering = ofVec3f(0, 0, 0);
	for (size_t i = 0; i < nearbies.size(); i++)
	{
		float dist = glm::distance(pos, nearbies[i].Particle::pos);
		ofVec3f diff = Particle::pos - nearbies[i].Particle::pos;
		diff /= dist; // to make it invertly proportional
		steering += diff;
	}
	if (nearbies.size() > 1) steering /= nearbies.size();
	steering.scale(maxSpeed);
	steering -= Particle::vel;
	steering = steering.getLimited(maxForce);
	Particle::acc += steering;
}

void Particle::containment()
{   // maybe I can make this better by raycasting instead ? or even rayMarching idk ?
	// ref tutorial https://gamedevelopment.tutsplus.com/tutorials/understanding-steering-behaviors-collision-avoidance--gamedev-7777

	glm::vec3 steering(0);

	float maxSeeAhead = 20;
	float maxAvoidance = 2;
	glm::vec3 ahead = pos + normalize(vel) * maxSeeAhead;

	//std::cout << "not found obstacle " << glm::length(ahead) << endl;

	if (glm::length(ahead) > ofGetWidth() / 2)
	{
		//std::cout << "found obstacle " << steering << endl;
		steering = -ahead;
		steering = normalize(steering) * maxAvoidance;
	}

	Particle::acc += steering;
}

void Particle::debugDraw() {
	ofDrawSphere(pos, 5);
}
