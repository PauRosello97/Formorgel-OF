#include "InfoButton.h"

InfoButton::InfoButton(float _x, float _y, float _w, float _h) {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}

void InfoButton::display() {
	if (isOver()) {
		ofSetColor(255, 0, 0);
	}
	else {
		ofSetColor(0, 0, 255);
	}
	
	ofDrawRectangle(x, y, w, h);
}

bool InfoButton::mousePressed() {
	return isOver();
}