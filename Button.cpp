#include "Button.h"


Button::Button() {}

Button::Button(float _x, float _y, float _w, float _h) {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}

void Button::display() {
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("Show lines", x + 10, y + 20);
	if (isOver()) {
		ofSetColor(125, 125, 0);
	}
	else {
		ofSetColor(0, 125, 125);
	}
	
	ofDrawRectangle(x, y, w, h);
}

bool Button::isOver() {
	return ofGetMouseX() > x && ofGetMouseX() < x+w && ofGetMouseY()> y && ofGetMouseY()<y+h;
}

bool Button::mousePressed() {
	return isOver();
}