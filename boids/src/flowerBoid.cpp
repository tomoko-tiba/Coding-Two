#include "flowerBoid.h"
#include "ofMain.h"
#include "boid.h"

FlowerBoid::FlowerBoid()
{
	position = ofVec3f(ofRandom(0, 200), ofRandom(0, 200));
	velocity = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1));

	gravity = ofRandom(0, 0.2);
	radius = ofRandom(0, 15);
	color = ofColor(255, 0, 255);
}

FlowerBoid::FlowerBoid(ofVec3f& pos)
{
	position = pos;
	velocity = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1));
	gravity = ofRandom(0, 0.2);
	radius = ofRandom(0, 15);
	color = ofColor(255, 0, 255);
}

FlowerBoid::~FlowerBoid()
{
}

void FlowerBoid::collide(std::vector<Boid*>& Boids1, std::vector<Boid*>& Boids2) {

	for (int i = 0; i < Boids1.size(); i++)
	{
		//collide boids
		float dis = position.distance(Boids1[i]->getPosition()) - radius / 2 - Boids1[i]->radius / 2;
		if (dis <= 0.5)
		{
			//bound
			velocity *= -1;

			//change color
			color = ofColor(0, (int)ofRandom(150, 255), (int)ofRandom(150, 255));

		}
	}
	//collide childBoids
	for (int i = 0; i < Boids2.size(); i++)
	{
		float dis = position.distance(Boids2[i]->getPosition()) - radius / 2 - Boids2[i]->radius / 2;
		if (dis <= 0.5)
		{
			//bound
			velocity *= -1;

			//change color
			//ofSetColor(255, 234, 80);
			color = ofColor((int)ofRandom(200, 255), (int)ofRandom(200, 255), (int)ofRandom(40, 100));

		}
	}
}

void FlowerBoid::update(std::vector<Boid*>& Boids1, std::vector<Boid*>& Boids2, ofVec3f& min, ofVec3f& max)
{
	collide(Boids1, Boids2);

	walls(min, max);
	Gravity();
	position += velocity;
}

void FlowerBoid::walls(ofVec3f& min, ofVec3f& max)
{
	if (position.x < min.x) {
		velocity.x *= -1;
	}
	else if (position.x > max.x) {
		velocity.x *= -1;
	}

	if (position.y < min.y) {
		velocity.y *= -1;
	}
	else if (position.y > max.y) {
		if (position.y - max.y >= 0.15) {
			position.y = max.y - 0.15;
			if (velocity.y > -0.1) {
				velocity.x *= 0.96;
			}
		}
		velocity.y *= -0.9;
	}
}

void FlowerBoid::Gravity() {
	float maxYV = 20;

	if (velocity.y < maxYV) {
		velocity.y += gravity;
	}
}

void FlowerBoid::draw()
{
	ofSetColor(color);
	ofDrawRectangle(position.x, position.y, radius, radius);

}