#include "ofApp.h"
#include <cmath>
using namespace std;

int width = 1500;
int height = 1500;

int mouseX = 100;
int mouseY = 100;
int pMouseX = 100;
int pMouseX2 = 100;
int pMouseY = 100;

double TwoPI = 3.1416 * 2;
int centerX = width/2;
int radius = 300;
int lines = 1500;

float spacing = TwoPI / lines;

int countT = 0;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
	ofSetWindowShape(width, height);
	ofSetWindowPosition(10, 10);
    myfont.load("Ma.ttf", 45);
    image.load("2.png");
    // cout << myfont << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
	// cout << mouseX << endl;
    countT++;
}

int colorSegment = 150;

//--------------------------------------------------------------
void ofApp::draw(){
    
    countT++;

    //update previous mouse position info 
    float mouseXlerp = ofLerp(pMouseX, mouseX, 0.05);
    float mouseXlerp2 = ofLerp(pMouseX2, mouseX, 0.003);
    float mouseYlerp = ofLerp(pMouseY, mouseY, 0.06);
    float circleInsideY = ofMap(mouseXlerp, 0, width, 0, height);
    float circleInsideR = ofMap(abs(mouseYlerp - height / 2), 0, height / 2, radius * 2, radius * 0.1);

    ofClear(0, 0, 0);

    //draw background color
    float spacingBg = height / lines;
    for (int j = 0;j < lines; j++) {
        float distanceToY = abs(mouseYlerp - spacingBg * j);
        float colorBGlerp = ofMap(distanceToY, 0, height, 0, 1);

        ofColor green = ofColor::green;
        ofColor lineColor = ofColor::black;
        // ofColor green(0, 255, 0);
        ofSetColor(lineColor.lerp(green, colorBGlerp));

        ofDrawLine(0, spacingBg * j, width, spacingBg * j);
    }

    //circle
    for (int i = 0; i < lines * (sin(countT * 0.01) * 0.2 + 0.4); i++) {

        int colorL = i % colorSegment;
        int colorT = ofMap(colorL, 0, colorSegment, 0, 255);
        if (colorT > 255) colorT = 255;
        else if (colorT < 0) colorT = 0;
        ofColor waveColor(0, colorT, 0);
        ofSetColor(waveColor);

        int fromX = centerX + cos(i * spacing + countT * 0.05) * (sin(countT * 0.01) * radius + radius);
        int fromY = height / 2 + sin(i * spacing + countT * 0.05) * (sin(countT * 0.01) * radius+ radius);
        int toX = centerX + cos(i * spacing - countT * 0.05) * circleInsideR;
        int toY = circleInsideY + sin(i * spacing - countT * 0.05) * circleInsideR * (sin(countT * 0.01) * 0.05 + 0.1);

        ofDrawLine(fromX, fromY, toX, toY);        
    }
    
    ofColor black = ofColor::black;
    ofSetColor(black);

    //ofDrawBitmapString("YENNY", 100, 100);
    myfont.drawString("YENNY", width/2*0.7, height/2); 

    pMouseX = mouseXlerp;
    pMouseY = mouseYlerp;
    pMouseX2 = mouseXlerp2;
    


    //image.draw(ofGetWidth() / 2, ofGetHeight() / 2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
