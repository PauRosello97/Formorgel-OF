#include "GeometryColorSwitch.h"

void GeometryColorSwitch::display() {
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("Geometry", x + 10, y + 20);
	ofDrawBitmapString("Color", x + w / 2 + 10, y + 20);

	// Border lines
	ofSetColor(40);
	ofDrawLine(x, y, x + w, y);
	ofDrawLine(x, y, x, y + h);
	ofDrawLine(x + w / 2, y, x + w / 2, y + h);
	ofDrawLine(x + w, y, x + w, y + h);
	
	if (mode == "geometry") {
		ofDrawLine(x + w / 2, y + h, x + w, y + h);
	}else{
		ofDrawLine(x, y + h, x + w/2, y + h);
	}

	//Geometry
	if (mode == "geometry") {
		ofSetColor(135);
	}
	else {
		ofSetColor(180);
	}
	ofDrawRectangle(x, y, w / 2, h);

	//Color
	if (mode == "color") {
		ofSetColor(135);
	}
	else {
		ofSetColor(180);
	}
	ofDrawRectangle(x + w / 2, y, w / 2, h);
}

bool GeometryColorSwitch::isOverA() {
	return ofGetMouseX() > x&& ofGetMouseX() < x + w / 2 && ofGetMouseY() > y&& ofGetMouseY() < y + h;
}

bool GeometryColorSwitch::isOverB() {
	return ofGetMouseX() > x + w / 2 && ofGetMouseX() < x + w && ofGetMouseY() > y&& ofGetMouseY() < y + h;
}

bool GeometryColorSwitch::mousePressed() {
	if (isOverA()) {
		mode = "geometry";
		return true;
	}
	else if (isOverB()) {
		mode = "color";
		return true;
	}
	return false;
}

bool GeometryColorSwitch::inGeometryMode() {
	return mode == "geometry";
}