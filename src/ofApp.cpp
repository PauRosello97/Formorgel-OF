#include "ofApp.h"
#include <string> 
#include <sstream>

void ofApp::setup(){
	//ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(40);
	//ofSetVerticalSync(false);
	ofEnableAlphaBlending();
	ofEnableDepthTest();

	lateralWidth = geometryPanel.w + 20;

	newPattern();
	displayLinesToggle = Button(400, 10, 100, 30);
	displayPolygonsToggle = Button(510, 10, 130, 30);
	
	geometryColorSwitch = GeometryColorSwitch();
	infoButton = InfoButton(ofGetWidth()-40, 10, 30, 30);
}

void ofApp::update(){ }

void ofApp::draw(){

	float margin = 10;

	displayLinesToggle.display(displayingLines ? "Hide lines" : "Show lines");
	displayPolygonsToggle.display(displayingPolygons ? "Hide polygons" : "Show polygons");
	infoButton.display();

	// Lateral panels
	geometryColorSwitch.display();
	if (geometryColorSwitch.inGeometryMode()) {
		geometryPanel.display();
	}
	else {
		colorPanel.display();
	} 

	float width = ofGetWindowWidth();
	float height = ofGetWindowHeight();

	// Composition stroke
	ofSetColor(165);
	ofDrawLine(lateralWidth, margin*5, width - margin, margin*5); // Top
	ofDrawLine(lateralWidth, margin*5, lateralWidth, height-margin); // Left
	ofDrawLine(lateralWidth, height - margin, width - margin, height - margin); // Bottom
	ofDrawLine(width - margin, margin * 5, width - margin, height - margin); // Right

	//Margins
	ofSetColor(110);
	
	ofDrawRectangle(0, 0, width, margin*5); //Top
	ofDrawRectangle(0, height-margin, width, margin); //Bot
	ofDrawRectangle(width- margin, 0, margin, height); //Right
	ofDrawRectangle(0, 0, lateralWidth, height); //Left

	if (displayingLines) {
		geometricSynth.displayLines();
	}

	//Polygons
	if (displayingPolygons) {
		geometricSynth.display();
	}	
}

void ofApp::keyPressed(int key){ }
void ofApp::keyReleased(int key){ }
void ofApp::mouseMoved(int x, int y ){ }
void ofApp::mouseDragged(int x, int y, int button){ }

void ofApp::newPattern() {
	geometricSynth = GeometricSynth();

	if (displayingPolygons) {
		geometricSynth.generateComposition(
			Formorgel(geometryPanel.oscA.offset, geometryPanel.oscA.angle, geometryPanel.oscA.length, 0),
			Formorgel(geometryPanel.oscB.offset, geometryPanel.oscB.angle, geometryPanel.oscB.length, 1),
			Formorgel(geometryPanel.oscC.offset, geometryPanel.oscC.angle, geometryPanel.oscC.length, 2),
			iterations
		);
	}
	else {
		geometricSynth.generateLines(
			Formorgel(geometryPanel.oscA.offset, geometryPanel.oscA.angle, geometryPanel.oscA.length, 0),
			Formorgel(geometryPanel.oscB.offset, geometryPanel.oscB.angle, geometryPanel.oscB.length, 1),
			Formorgel(geometryPanel.oscC.offset, geometryPanel.oscC.angle, geometryPanel.oscC.length, 2),
			iterations
		);
	}

	colorPanel.update(geometricSynth.polygons);
	geometricSynth.applyColors(colorPanel.assignations);
}

void ofApp::mousePressed(int x, int y, int button){
	if (geometryColorSwitch.inGeometryMode() && geometryPanel.mousePressed()) {
		iterations = round(geometryPanel.iterations);
		newPattern();
	}
	else if (displayLinesToggle.mousePressed()) {
		displayingLines = !displayingLines;
	}
	else if (displayPolygonsToggle.mousePressed()) {
		displayingPolygons = !displayingPolygons;
		newPattern();
	}
	else if (geometryColorSwitch.mousePressed()) {
		if (!geometryColorSwitch.inGeometryMode() && !displayingPolygons) {
			displayingPolygons = true;
			newPattern();
		}
	}else {
		colorPanel.mousePressed();
		geometricSynth.applyColors(colorPanel.assignations);
	}
}

void ofApp::mouseReleased(int x, int y, int button){ 
	if (geometryPanel.mouseReleased()) {
		newPattern();
	}
}
void ofApp::mouseEntered(int x, int y){ }
void ofApp::mouseExited(int x, int y){ }
void ofApp::windowResized(int w, int h){ }
void ofApp::gotMessage(ofMessage msg){ }
void ofApp::dragEvent(ofDragInfo dragInfo){ }
