#include "PolygonColorControl.h"

PolygonColorControl::PolygonColorControl(float _x, float _y, int _area, ofColor _color) {
	x = _x;
	y = _y;
	color = _color;
	area = _area;
}

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
		cout << "isOverColorCOntrol";
	}
}