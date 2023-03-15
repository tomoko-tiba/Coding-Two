
/*
 *  boid.cpp
 *  boids
 *
 *  Created by Marco Gillies on 05/10/2010.
 *  Copyright 2010 Goldsmiths, University of London. All rights reserved.
 *
 */

#include "boid.h"
#include "ofMain.h"

Boid::Boid()
{
	separationWeight = 1.2f;
	cohesionWeight = 0.1f;
	alignmentWeight = 0.15f;

	separationThreshold = 25;
	neighbourhoodSize = 150;

	position = ofVec3f(ofRandom(0, 200), ofRandom(0, 200));
	velocity = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1));

	radius = ofRandom(5, 10);
}

Boid::Boid(ofVec3f& pos, ofVec3f& vel)
{
	separationWeight = 1.2f;
	cohesionWeight = 0.1f;
	alignmentWeight = 0.15f;

	separationThreshold = 25;
	neighbourhoodSize = 150;

	position = pos;
	velocity = vel;

	radius = ofRandom(5, 10);
}

Boid::~Boid()
{

}

float Boid::getSeparationWeight()
{
	return separationWeight;
}
float Boid::getCohesionWeight()
{
	return cohesionWeight;
}

float Boid::getAlignmentWeight()
{
	return alignmentWeight;
}


float Boid::getSeparationThreshold()
{
	return separationThreshold;
}

float Boid::getNeighbourhoodSize()
{
	return neighbourhoodSize;
}


void Boid::setSeparationWeight(float f)
{
	separationWeight = f;
}
void Boid::setCohesionWeight(float f)
{
	cohesionWeight = f;
}

void Boid::setAlignmentWeight(float f)
{
	alignmentWeight = f;
}


void Boid::setSeparationThreshold(float f)
{
	separationThreshold = f;
}

void Boid::setNeighbourhoodSize(float f)
{
	neighbourhoodSize = f;
}


ofVec3f Boid::getPosition()
{
	return position;
}

ofVec3f Boid::getVelocity()
{
	return velocity;
}

ofVec3f Boid::separation(std::vector<Boid*>& otherBoids)
{
	// finds the first collision and avoids that
	// should probably find the nearest one
	// can you figure out how to do that?
	ofVec3f v(0, 0, 0);
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < separationThreshold)
		{
			v = position - otherBoids[i]->getPosition();
			v.normalize();
			// I fixed the bug here. Return is must requried in all conditions.
			// return v;
		}
	}
	return v;
}

ofVec3f Boid::cohesion(std::vector<Boid*>& otherBoids)
{
	ofVec3f average(0, 0, 0);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)
		{
			average += otherBoids[i]->getPosition();
			count += 1;
		}
	}
	average /= count;
	ofVec3f v = average - position;
	v.normalize();
	return v;
}

ofVec3f Boid::alignment(std::vector<Boid*>& otherBoids)
{
	ofVec3f average(0, 0, 0);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < otherBoids[0]->neighbourhoodSize)
		{
			average += otherBoids[i]->getVelocity();
			count += 1;
		}
	}
	average /= count;
	ofVec3f v = average - velocity;
	v.normalize();
	return v;
}


ofVec3f Boid::otherCohesion(std::vector<Boid*>& otherBoids)
{
	ofVec3f average(0, 0, 0);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < otherBoids[0]->neighbourhoodSize)
		{
			average += otherBoids[i]->getPosition();
			count += 1;
		}
	}
	average /= count;
	ofVec3f v = average - position;
	v.normalize();
	return v;
}

ofVec3f Boid::otherSeparation(std::vector<Boid*>& otherBoids)
{
	ofVec3f v(0, 0, 0);
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < otherBoids[0]->separationThreshold)
		{
			v = position - otherBoids[i]->getPosition();
			v.normalize();
			// I fixed the bug here. Return is must requried in all conditions.
			// return v;
		}
	}
	return v;
}

void Boid::update(std::vector<Boid*>& otherBoids, std::vector<Boid*>& childBoids, ofVec3f& min, ofVec3f& max)
{
	velocity += separationWeight * separation(otherBoids);
	velocity += cohesionWeight * cohesion(otherBoids);
	velocity += alignmentWeight * alignment(otherBoids);

	//childBoids类中所有实例化的对象都有同样的separationWeight浮点数，和separation函数，所以调用第一个
	velocity += childBoids[0]->separationWeight * otherSeparation(childBoids);
	velocity += childBoids[0]->cohesionWeight * otherCohesion(childBoids);

	if (sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)) >= 10) {
		velocity *= 0.9;
	}

	walls(min, max);
	position += velocity;
}

void Boid::walls(ofVec3f& min, ofVec3f& max)
{
	if (position.x < min.x) {
		position.x = min.x;
		velocity.x *= -1;
	}
	else if (position.x > max.x) {
		position.x = max.x;
		velocity.x *= -1;
	}

	if (position.y < min.y) {
		position.y = min.y;
		velocity.y *= -1;
	}
	else if (position.y > max.y) {
		position.y = max.y;
		velocity.y *= -1;
	}

}

void Boid::draw()
{
	ofSetColor(0, 255, 255);
	ofCircle(position.x, position.y, radius);
}