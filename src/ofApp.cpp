#include "ofApp.h"
#include <string> 
#include <sstream>

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


	doShader = true;
	ofEnableDepthTest();
	/*
	lines = {
			{{0,250,0}, {1000,250,0}},
			{{0,750,0}, {1000,750,0}},
			{{750,0,0}, {750,1000,0}},
			{{300,0,0}, {600,1000,0}},
			{{300,0,0}, {0,300,0}},
	};
	*/
	lines = {
			{{0,300,0}, {600,1000,0}},
			{{0,600,0}, {600,0,0}},
			{{300,0,0}, {1000,600,0}},
			{{300,1000,0}, {1000,300,0}},
	};
	
	for (int i = 0; i < 50; i++) {
		lines.push_back({ {ofRandom(1000),ofRandom(1000),0}, {ofRandom(1000),ofRandom(1000),0} });
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

	logoutf("nPolys:%u dissolveSteps:%u lines:%u", uint32_t(pd.polys.size()), pd.dissolveCount + 1, uint32_t(pd.lines.size()));

	
	for (int i = 0; i < pd.polys.size(); i++) {
		logoutf("nPolys: (%u,%u) ", uint32_t(pd.polys.at(i).p.at(0).x), uint32_t(pd.polys.at(i).p.at(0).y));
	}

	polygons = pd.polys;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	for (int i = 0; i < polygons.size(); i++) {
		polygons.at(i).draw();
	}

	for (int i = 0; i < lines.size(); i++) {
		ofDrawLine(lines.at(i).a.x, lines.at(i).a.y, lines.at(i).b.x, lines.at(i).b.y);
	}

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
