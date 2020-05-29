
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

void Particle::applyVelocity(glm::vec3 force, float maxVel)
{
	vel += force;
	if (maxVel > 0)
	{
		vel = glm::normalize(vel) * maxVel;
	}
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

void Particle::randomWalk(float walk, bool is3D)
{
	vel.x += ofRandom(-walk, walk);
	vel.y += ofRandom(-walk, walk);
	if (is3D)
	{
		vel.z += ofRandom(-walk, walk);
	}
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

// ##### Differential Line Growth

// # exponentially decreasing influence depending on distance                                                  // Haven't added this yet ! could be useful in some other cases
glm::vec3 Particle::getAttraction(vector<std::shared_ptr<Particle>> neighbours) {
	glm::vec3 attractionForce; // don't need to divide by two again because we're normalizing;
	for (std::shared_ptr<Particle> v : neighbours)
	{
		attractionForce += v->pos;
	}
	attractionForce = glm::normalize(attractionForce);
	return attractionForce;
}

// # exponentially decreasing influence depending on distance
glm::vec3 Particle::getRepulsion(vector<std::shared_ptr<Particle>> closeby) {
	glm::vec3 repulsionForce;

	for (std::shared_ptr<Particle> v : closeby)
	{
		float d = glm::distance(v->pos, pos);
		glm::vec3 diff = (pos - v->pos) / exp(d);
		repulsionForce += diff;
	}
	//repulsionForce /= neighbours.size(); //dont need to do that anymore because Im normalizing
	repulsionForce = glm::normalize(repulsionForce);
	return repulsionForce;
}

// ##### DEBUG DRAW

void Particle::debugDraw() {

	float size = 3;

	// draw acceleration in green
	if(glm::length(acc) > 0)
	{ 
		ofSetColor(0,255,0);
		ofDrawSphere(pos, size);
	}

	// draw velocity in red
	if (glm::length(vel) > 0)
	{
		ofSetColor(255, 0, 0);
		ofDrawSphere(pos, size);
	}

	// draw position in white
	ofSetColor(255);
	ofDrawSphere(pos, size);
}

// ##### SPAWNING SYSTEM

void Particle::spawn(SpawnType spawn, bool is3D=false) {

	float w = ofGetWidth();
	float h = ofGetHeight();

	switch (spawn)
	{

		case Spawn_Random:
		{
			pos.x = ofRandom(-w / 2, w / 2);
			pos.y = ofRandom(-h / 2, h / 2);
			pos.z = 0;
	
			if (is3D) // if 3D then give it a z too
			{
				pos.z = ofRandom(-w / 2, w / 2);
			}
			break;
		}
		case Spawn_SphereSurface:
		{
			float r = w / 2; // radius
	
			if (!is3D) // Circle Perimeter
			{
				float phi = ofRandom(0, 2 * PI);
				pos.x = cos(phi) * r;
				pos.y = sin(phi) * r;
				pos.z = 0;
			}
			else // Sphere Surface
			{
				pos.z = ofRandom(-r, r);
				float phi = ofRandom(0, 2 * PI);
				pos.x = sqrt((r*r - pos.z * pos.z)) * cos(phi);
				pos.y = sqrt((r*r - pos.z * pos.z)) * sin(phi);
			}
			break;
		}
		case Spawn_Box:
		{
			if (!is3D) // Screen Space Walls
			{
				int wall = (int)ofRandom(1, 5);
				switch (wall) {
				case 1: // NORTH
					pos.x = ofRandom(-w / 2, w / 2);
					pos.y = h / 2;
					pos.z = 0;
					break;
				case 2: // EAST
					pos.x = w / 2;
					pos.y = ofRandom(-h / 2, h / 2);
					pos.z = 0;
					break;
				case 3: // SOUTH
					pos.x = ofRandom(-w / 2, w / 2);
					pos.y = -h / 2;
					pos.z = 0;
					break;
				case 4: // WEST
					pos.x = -w / 2;
					pos.y = ofRandom(-h / 2, h / 2);
					pos.z = 0;
					break;
				default:
					pos.x = ofRandom(-w / 2, w / 2);
					pos.y = ofRandom(-h / 2, h / 2);
					pos.z = 0;
				}
			}
			else // 3D Box
			{
				int wall = (int)ofRandom(1, 7);
				switch (wall) {
				case 1: // FRONT
					pos.x = ofRandom(-w / 2, w / 2);
					pos.y = ofRandom(-w / 2, w / 2);
					pos.z = w / 2;
					break;
				case 2: // BACK
					pos.x = ofRandom(-w / 2, w / 2);
					pos.y = ofRandom(-w / 2, w / 2);
					pos.z = -w / 2;
					break;
				case 3: // TOP
					pos.x = ofRandom(-w / 2, w / 2);
					pos.y = w / 2;
					pos.z = ofRandom(-w / 2, w / 2);
					break;
				case 4: // BOTTOM
					pos.x = ofRandom(-w / 2, w / 2);
					pos.y = -w / 2;
					pos.z = ofRandom(-w / 2, w / 2);
					break;
				case 5: // LEFT
					pos.x = -w / 2;
					pos.y = ofRandom(-w / 2, w / 2);
					pos.z = ofRandom(-w / 2, w / 2);
					break;
				case 6: // RIGHT
					pos.x = w / 2;
					pos.y = ofRandom(-w / 2, w / 2);
					pos.z = ofRandom(-w / 2, w / 2);
					break;
				default:
					pos.x = ofRandom(-w / 2, w / 2);
					pos.y = ofRandom(-w / 2, w / 2);
					pos.z = ofRandom(-w / 2, w / 2);
				}
			}
			break;
		}
	}
}