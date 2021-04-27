#include "PolygonColorControl.h"


void PolygonColorControl::display() {
	ofSetColor(0);
	ofDrawBitmapString(ofToString(area), x + 10, y + 20);
	ofSetColor(color);
	ofDrawRectangle(x, y, w, h);
}

bool PolygonColorControl::isOver() {
	return ofGetMouseX() > x&& ofGetMouseX() < x + w && ofGetMouseY() > y&& ofGetMouseY() < y + h;
}

void PolygonColorControl::mousePressed() {
	if (isOver()) {
		for (int i = 0; i < colors.size(); i++) {
			colors[i] = ofColor(255, 0, 0);
		}
	}
}