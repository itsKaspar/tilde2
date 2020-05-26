
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

void Particle::debugDraw() {
	ofDrawSphere(pos, 5);
}
