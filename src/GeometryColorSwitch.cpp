#include "GeometryColorSwitch.h"

GeometryColorSwitch::GeometryColorSwitch() {
	openSans.load("OpenSans/OpenSans-Regular.ttf", 12, false, false, true);
}

void GeometryColorSwitch::display() {
	ofSetColor(0);
	ofRectangle rectA = openSans.getStringBoundingBox("Geometry", 0, 0);
	openSans.drawStringAsShapes("Geometry", x + w / 4 - rectA.width / 2, y + 26);
	ofRectangle rectB = openSans.getStringBoundingBox("Color", 0, 0);
	openSans.drawStringAsShapes("Color", x + 3* w / 4 - rectB.width / 2, y + 26);

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