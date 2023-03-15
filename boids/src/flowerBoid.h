#pragma once
#include "boid.h"
#include "ofMain.h"

class FlowerBoid : public Boid
{
	
	private:
		ofVec3f position;
		ofVec3f velocity;
		float gravity;
		float radius;
		void Gravity();
		void collide(std::vector<Boid*>& Boids1, std::vector<Boid*>& Boids2);
		ofColor color;

	public:
		FlowerBoid();
		FlowerBoid(ofVec3f& pos);

		~FlowerBoid();

		void update(std::vector<Boid*>& Boids1, std::vector<Boid*>& Boids2, ofVec3f& min, ofVec3f& max);

		void walls(ofVec3f& min, ofVec3f& max);

		void draw();
		
};

