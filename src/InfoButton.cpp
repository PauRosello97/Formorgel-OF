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
	ofPushMatrix();
	ofSetColor(40);
	ofTranslate(x, y);
	
	if (isOver()) {
		lightLogo.draw();
	}
	else {
		darkLogo.draw();		
	}
	ofPopMatrix();
}

bool InfoButton::mousePressed() {
	return isOver();
}