#include "ofApp.h"
#include <string> 

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetLogLevel(OF_LOG_VERBOSE);
	ofBackground(50, 50, 50);
	ofSetVerticalSync(false);
	ofEnableAlphaBlending();

	shader.setGeometryInputType(GL_LINES);
	shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
	shader.setGeometryOutputCount(4);
	shader.load("shaders/vert.glsl", "shaders/frag.glsl", "shaders/geom.glsl");

	ofLog() << "Maximum number of output vertices support is: " << shader.getGeometryMaxOutputCount();


	pattern.setup(shader);

	doShader = true;
	ofEnableDepthTest();

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	pattern.draw();

	ofDrawBitmapString(
		"fps: " + ofToString((int)ofGetFrameRate()) + 
		"\nPress 's' to toggle shader: " + (doShader ? "ON" : "OFF") + 
		"\nPress 'r' to reload" +
		"\nnLines: " + std::to_string(pattern.getNLines()) +
		"\nnNodes: " + std::to_string(pattern.getNNodes()) +
		"\nnTriangles: " + std::to_string(pattern.getNTriangles()),
		20, 
		20
	);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') {
		doShader = !doShader;
		pattern.setDoShader(doShader);
	}
	else if (key == 'r') {
		pattern.setup(shader);
		pattern.setDoShader(doShader);
	}
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
