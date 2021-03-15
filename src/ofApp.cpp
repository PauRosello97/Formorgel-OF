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
	
	generatePattern();
}

void ofApp::generatePattern() {
	lines = {};
	
	lines.push_back({ {10, 10}, {500, 500} }); // Diagonal
	lines.push_back({ {20, 10}, {20,  500} }); // Vertical
	lines.push_back({ {10, 20}, {500, 20} }); // Horitzontal
	lines.push_back({ {10, 300},{300, 10} });
	
	//lines.push_back({ {10,1000}, {1000,1000} });
	//lines.push_back({ {1000,10}, {1000,1000} });

	
	for (int i = 0; i < 50; i++) {
		lines.push_back({ 
			{ofRandom(ofGetWidth()),ofRandom(ofGetHeight())}, 
			{ofRandom(ofGetWidth()),ofRandom(ofGetHeight())} 
		});
	}
	
	

	PolyDetector pd;

	for (auto& l : lines)
	{
		pd.AddLine(l);
	}

	if (!pd.DetectPolygons())
	{
		logoutf("%s", "WARN: cannot detect polys!");
	}

	polygons = pd.polys;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < lines.size(); i++) {
		ofSetColor(0, 0, 0);
		ofDrawLine(lines.at(i).a.x, lines.at(i).a.y, lines.at(i).b.x, lines.at(i).b.y);
	}
	for (int i = 0; i < polygons.size(); i++) {
		polygons.at(i).draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	generatePattern();
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
