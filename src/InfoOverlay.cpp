#include "InfoOverlay.h"

InfoOverlay::InfoOverlay() {
	w = ofGetWidth()/2;
	h = ofGetHeight() / 2;
	x = ofGetWidth() / 4;
	y = ofGetHeight() / 4;	
}

void InfoOverlay::display() {
	// Stroke
	ofSetColor(40);
	ofDrawLine(x, y, x + w, y); // Top
	ofDrawLine(x, y, x, y + h); // Left
	ofDrawLine(x + w, y, x + w, y + h); // Right
	ofDrawLine(x, y + h, x + w, y + h);

	//Background
	ofSetColor(135);
	ofDrawRectangle(x, y, w, h);
}