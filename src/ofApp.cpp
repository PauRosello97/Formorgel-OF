#include "ofApp.h"
#include <string> 
#include <sstream>

void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(50, 50, 50);
	ofSetVerticalSync(false);
	ofEnableAlphaBlending();
	ofEnableDepthTest();

	lateralWidth = geometryPanel.w + 20;

	newPattern();
	displayLinesToggle = Button(420, 10, 100, 30);
}

void ofApp::update(){ }

void ofApp::draw(){
	float margin = 25;

	displayLinesToggle.display();

	// Lateral panels
	geometryColorSwitch.display();
	if (geometryColorSwitch.inGeometryMode()) {
		geometryPanel.display();
	}
	else {
		colorPanel.display();
	}

	//Margins
	ofSetColor(120, 120, 120);
	float width = ofGetWindowWidth();
	float height = ofGetWindowHeight();
	ofDrawRectangle(0, 0, width, margin*2); //Top
	ofDrawRectangle(0, height-margin, width, margin); //Bot
	ofDrawRectangle(width- margin, 0, margin, height); //Right
	ofDrawRectangle(0, 0, lateralWidth, height); //Left

	if (displayingLines) {
		geometricSynth.displayLines();
	}

	//Polygons
	geometricSynth.display();
}

void ofApp::keyPressed(int key){ }
void ofApp::keyReleased(int key){ }
void ofApp::mouseMoved(int x, int y ){ }
void ofApp::mouseDragged(int x, int y, int button){ }

void ofApp::newPattern() {
	geometricSynth = GeometricSynth();
	geometricSynth.generateComposition(
		Formorgel(geometryPanel.oscA.offset, geometryPanel.oscA.angle, geometryPanel.oscA.length, 0),
		Formorgel(geometryPanel.oscB.offset, geometryPanel.oscB.angle, geometryPanel.oscB.length, 1)
	);

	colorPanel.update(geometricSynth.polygons);
	geometricSynth.applyColors(colorPanel.assignations);
}

void ofApp::mousePressed(int x, int y, int button){
	if (geometryColorSwitch.inGeometryMode() && geometryPanel.mousePressed()) {
		newPattern();
	}
	else if (displayLinesToggle.mousePressed()) {
		displayingLines = !displayingLines;
	}
	else {
		geometryColorSwitch.mousePressed();
		colorPanel.mousePressed();
		geometricSynth.applyColors(colorPanel.assignations);
	}
}


void ofApp::mouseReleased(int x, int y, int button){ }
void ofApp::mouseEntered(int x, int y){ }
void ofApp::mouseExited(int x, int y){ }
void ofApp::windowResized(int w, int h){ }
void ofApp::gotMessage(ofMessage msg){ }
void ofApp::dragEvent(ofDragInfo dragInfo){ }
