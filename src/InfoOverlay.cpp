#include "InfoOverlay.h"

InfoOverlay::InfoOverlay() {
	w = ofGetWidth()/2;
	h = ofGetHeight() / 2;
	x = ofGetWidth() / 4;
	y = ofGetHeight() / 4;	
	openSans.load("OpenSans/OpenSans-Regular.ttf", 14, false, false, true);
}

void InfoOverlay::display() {
	// Stroke
	ofSetColor(40);
	ofDrawLine(x, y, x + w, y); // Top
	ofDrawLine(x, y, x, y + h); // Left
	ofDrawLine(x + w, y, x + w, y + h); // Right
	ofDrawLine(x, y + h, x + w, y + h);

	// Text
	ofSetColor(40);
	openSans.drawStringAsShapes("This application generates geometric patterns implementing Hans", x + 20, y + 35);
	openSans.drawStringAsShapes("Hinterreiter's ideas exposed in his book Die Kunst der Reiner Form.", x + 20, y + 60);

	//This application generates geometric patterns implementing Hans Hinterreiter's ideas exposed in his book Die Kunst der Reiner Form.

	//Background
	ofSetColor(135);
	ofDrawRectangle(x, y, w, h);
}