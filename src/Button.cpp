#include "Button.h"

Button::Button() {}

Button::Button(float _x, float _y, float _w, float _h) {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	openSans.load("OpenSans/OpenSans-Regular.ttf", 12, false, false, true);
}

void Button::display(string message) {

	// Text
	ofSetColor(40);
	ofRectangle rect = openSans.getStringBoundingBox(message, 0, 0);
	openSans.drawStringAsShapes(message, x + w / 2 - rect.width / 2, y + 21);

	// Stroke
	ofDrawLine(x, y, x + w, y); // Top
	ofDrawLine(x, y, x, y + h); // Left
	ofDrawLine(x + w, y, x + w, y + h); // Right
	ofDrawLine(x, y + h, x + w, y + h);

	// Fill
	if (isOver()) {
		ofSetColor(165);
	}
	else {
		ofSetColor(135);
	}
	ofDrawRectangle(x, y, w, h);
}

bool Button::mousePressed() {
	return isOver();
}