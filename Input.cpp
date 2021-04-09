#include "Input.h"
#include <iostream>

void Input::display() {
	ofSetColor(0, 0, 0);

	//ofDrawBitmapString("Angle: " + ofToString(pointer), x+10, y+20);
	if (isOver()) {
		ofSetColor(200, 200, 200);
	}
	else {
		ofSetColor(100, 100, 100);
	}
	
	ofDrawRectangle(x, y, w, h);
}

bool Input::isOver() {
	return ofGetMouseX() > x&& ofGetMouseX() < x + w && ofGetMouseY() > y&& ofGetMouseY() < y + h;
}

void Input::mousePressed() {

}