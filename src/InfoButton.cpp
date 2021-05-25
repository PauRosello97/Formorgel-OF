#include "InfoButton.h"

InfoButton::InfoButton(float _x, float _y, float _w, float _h) {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	lightLogo.load("icons/lightInfo.svg");
	darkLogo.load("icons/darkInfo.svg");
}

void InfoButton::display() {
	// logo
	ofPushMatrix();
	ofSetColor(40);
	ofTranslate(x, y);
	
	if (isOver()) {
		darkLogo.draw();
	}
	else {
		lightLogo.draw();
	}
	ofPopMatrix();
}

bool InfoButton::mousePressed() {
	return isOver();
}