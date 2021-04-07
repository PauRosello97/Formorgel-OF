#include "ofApp.h"
#include <string> 
#include <sstream>

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(50, 50, 50);
	ofSetVerticalSync(false);
	ofEnableAlphaBlending();

	ofEnableDepthTest();

	geometricSynth = GeometricSynth();
	geometricSynth.generateComposition(
		Formorgel(offsetA, angleA, lengthA, 0), 
		Formorgel(offsetB, angleB, lengthB, 1)
	);

	float margin = 25;
	float lateralWidth = 350;
	oscA = Oscillator(margin, margin, lateralWidth - 50, 300);
	oscB = Oscillator(margin, lateralWidth, lateralWidth - 50, 300);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	float margin = 25;
	float lateralWidth = 350;
	oscA.display();
	oscB.display();
	ofSetColor(120, 120, 120);
	float width = ofGetWindowWidth();
	float height = ofGetWindowHeight();
	ofDrawRectangle(0, 0, width, margin); //Top
	ofDrawRectangle(0, height-margin, width, margin); //Bot
	ofDrawRectangle(width- margin, 0, margin, height); //Right
	ofDrawRectangle(0, 0, lateralWidth, height); //Left
	geometricSynth.display();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	geometricSynth = GeometricSynth();
	geometricSynth.generateComposition(
		Formorgel(offsetA, ofRandom(90), lengthA, 0),
		Formorgel(offsetB, angleB, lengthB, 1)
	);
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
