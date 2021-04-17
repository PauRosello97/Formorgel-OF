#include "Osc.h"

void Osc::display() {
	//Inputs
	offsetInput.display();
	angleInput.display();
	lengthInput.display();

	//Square
	ofSetColor(25, 25, 25);
	ofDrawRectangle(x + 10, y + 10, h-20, h-20);

	ofSetColor(0, 0, 0);
	if (isOver()) {
		ofSetColor(255, 0, 0);
	}
	else {
		ofSetColor(255, 255, 255);
	}
	
	ofDrawRectangle(x, y, w, h);
}

bool Osc::isOver() {
	return ofGetMouseX() > x&& ofGetMouseX() < x + w && ofGetMouseY() > y&& ofGetMouseY() < y + h;
}

bool Osc::mousePressed() {
	if (isOver()) {
		if (!offsetInput.mousePressed()) {
			if (!angleInput.mousePressed()) {
				lengthInput.mousePressed();
			}
		}
		return true;
	}
	else {
		return false;
	}
}