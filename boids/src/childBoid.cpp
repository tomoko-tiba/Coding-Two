#include "childBoid.h"
#include "ofMain.h"

childBoid::childBoid()
{

	alignmentWeight = 0.1f;
	separationWeight = 0.7f;
	cohesionWeight = 0.2f;

	separationThreshold = 100;
	neighbourhoodSize = 200;

	position = ofVec3f(ofRandom(0, 200), ofRandom(0, 200));
	velocity = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1));

	radius = ofRandom(5, 10);
}

childBoid::childBoid(ofVec3f& pos, ofVec3f& vel)
{
	alignmentWeight = 0.1f;
	separationWeight = 0.7f;
	cohesionWeight = 0.2f;

	separationThreshold = 100;
	neighbourhoodSize = 200;

	position = pos;
	velocity = vel;

	radius = ofRandom(5, 10);
}

childBoid::~childBoid()
{

}
void childBoid::draw() {
    ofSetColor(200, 255, 120);
    ofCircle(position.x, position.y, radius);
}