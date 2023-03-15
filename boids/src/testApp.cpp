#include "testApp.h"

testApp::~testApp()
{
	for (int i = 0; i < boids.size(); i++)
	{
		delete boids[i];
	}
	for (int i = 0; i < childBoids.size(); i++)
	{
		delete childBoids[i];
	}

	for (int i = 0; i < flowerBoids.size(); i++)
	{
		delete flowerBoids[i];
	}
}

//--------------------------------------------------------------
void testApp::setup() {


	int screenW = ofGetScreenWidth();
	int screenH = ofGetScreenHeight();

	ofBackground(0, 0, 0);

	// set up the boids
	for (int i = 0; i < 30; i++) {
		boids.push_back(new Boid());
	}
	for (int i = 0; i < 60; i++) {
		childBoids.push_back(new childBoid());
	}
}

//--------------------------------------------------------------
void testApp::update() {

	ofVec3f min(0, 0);
	ofVec3f max(ofGetWidth(), ofGetHeight());

	for (int i = 0; i < boids.size(); i++)
	{
		boids[i]->update(boids, childBoids, min, max);
	}
	for (int i = 0; i < childBoids.size(); i++)
	{
		childBoids[i]->update(childBoids, boids, min, max);
	}
	for (int i = 0; i < flowerBoids.size(); i++)
	{
		flowerBoids[i]->update(boids, childBoids, min, max);
	}

}
//--------------------------------------------------------------
void testApp::draw() {

	for (int i = 0; i < boids.size(); i++)
	{
		boids[i]->draw();
	}

	for (int i = 0; i < childBoids.size(); i++)
	{
		childBoids[i]->draw();
	}

	for (int i = 0; i < flowerBoids.size(); i++)
	{
		flowerBoids[i]->draw();
	}

}


//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
	ofVec3f pos = ofVec3f(ofGetMouseX(), ofGetMouseY());
	flowerBoids.push_back(new FlowerBoid(pos));
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}