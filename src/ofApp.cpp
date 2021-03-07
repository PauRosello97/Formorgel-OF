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

	std::vector<PolyLine> lines = {
			{{0,25,0}, {100,25,0}},
			{{0,75,0}, {100,75,0}},
			{{25,0,0}, {25,100,0}},
			{{75,0,0}, {75,100,0}},
	};

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
