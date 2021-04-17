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

	lateralWidth = oscillators.w + 20;

	geometricSynth = GeometricSynth();
	geometricSynth.generateComposition(
		Formorgel(oscillators.oscA.offset, oscillators.oscA.angle, oscillators.oscA.length, 0),
		Formorgel(oscillators.oscB.offset, oscillators.oscB.angle, oscillators.oscB.length, 1)
	);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	float margin = 25;

	geometryColorSwitch.display();
	if (geometryColorSwitch.inGeometryMode()) {
		oscillators.display();
	}
	

	//Margins
	ofSetColor(120, 120, 120);
	float width = ofGetWindowWidth();
	float height = ofGetWindowHeight();
	ofDrawRectangle(0, 0, width, margin); //Top
	ofDrawRectangle(0, height-margin, width, margin); //Bot
	ofDrawRectangle(width- margin, 0, margin, height); //Right
	ofDrawRectangle(0, 0, lateralWidth, height); //Left

	geometricSynth.displayLines();

	//Polygons
	geometricSynth.display();
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
	if (oscillators.mousePressed()) {
		geometricSynth = GeometricSynth();
		geometricSynth.generateComposition(
			Formorgel(oscillators.oscA.offset, oscillators.oscA.angle, oscillators.oscA.length, 0),
			Formorgel(oscillators.oscB.offset, oscillators.oscB.angle, oscillators.oscB.length, 1)
		);
	}
	else {
		geometryColorSwitch.mousePressed();
	}
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
