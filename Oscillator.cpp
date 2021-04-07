#include "Oscillator.h"

Oscillator::Oscillator(){}

Oscillator::Oscillator(float _x, float _y, float _w, float _h) {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	button = Button(x, y, 100, 100);
}

void Oscillator::display() {

	button.display();

	ofSetColor(255, 255, 255);
	ofDrawRectangle(x, y, w, h);
}